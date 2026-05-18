#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "test.h"

#define TRACKED_ALLOCS_MAX 32
#define TRACKED_ALLOC_POISON 0xa5

typedef struct tracked_alloc_t {
  void *ptr;
  size_t size;
  int freed;
} tracked_alloc_t;

typedef struct tracked_memory_state_t {
  tracked_alloc_t allocs[ TRACKED_ALLOCS_MAX ];
  size_t count;
  int invalid_free;
} tracked_memory_state_t;

static tracked_memory_state_t tracked_memory_state;

static void
tracked_memory_reset( void )
{
  memset( &tracked_memory_state, 0, sizeof( tracked_memory_state ) );
}

static int
tracked_memory_store( void *ptr, size_t size )
{
  tracked_alloc_t *alloc;

  if( !ptr ) return 0;

  if( tracked_memory_state.count >= TRACKED_ALLOCS_MAX ) return 1;

  alloc = &tracked_memory_state.allocs[ tracked_memory_state.count++ ];
  alloc->ptr = ptr;
  alloc->size = size;
  alloc->freed = 0;

  return 0;
}

static tracked_alloc_t*
tracked_memory_find( void *ptr )
{
  size_t i;

  for( i = 0; i < tracked_memory_state.count; i++ ) {
    if( tracked_memory_state.allocs[i].ptr == ptr ) {
      return &tracked_memory_state.allocs[i];
    }
  }

  return NULL;
}

static tracked_alloc_t*
tracked_memory_find_by_size( size_t size )
{
  size_t i;
  tracked_alloc_t *found = NULL;

  for( i = 0; i < tracked_memory_state.count; i++ ) {
    if( tracked_memory_state.allocs[i].size != size ) continue;
    if( found ) return NULL;
    found = &tracked_memory_state.allocs[i];
  }

  return found;
}

static void*
tracked_malloc( size_t size )
{
  void *ptr;

  ptr = malloc( size );
  if( ptr && size ) memset( ptr, TRACKED_ALLOC_POISON, size );
  if( tracked_memory_store( ptr, size ) ) return NULL;

  return ptr;
}

static void*
tracked_calloc( size_t nmemb, size_t size )
{
  void *ptr;

  ptr = calloc( nmemb, size );
  if( tracked_memory_store( ptr, nmemb * size ) ) return NULL;

  return ptr;
}

static void*
tracked_realloc( void *ptr, size_t size )
{
  tracked_alloc_t *alloc;
  void *new_ptr;

  if( !ptr ) return tracked_malloc( size );

  if( !size ) {
    free( ptr );
    alloc = tracked_memory_find( ptr );
    if( alloc ) alloc->freed = 1;
    return NULL;
  }

  alloc = tracked_memory_find( ptr );
  if( !alloc || alloc->freed ) {
    tracked_memory_state.invalid_free = 1;
    return NULL;
  }

  new_ptr = realloc( ptr, size );
  if( !new_ptr ) return NULL;

  if( size > alloc->size ) {
    memset( (char*)new_ptr + alloc->size, TRACKED_ALLOC_POISON,
            size - alloc->size );
  }

  alloc->ptr = new_ptr;
  alloc->size = size;
  alloc->freed = 0;

  return new_ptr;
}

static void
tracked_free( void *ptr )
{
  tracked_alloc_t *alloc;

  if( !ptr ) return;

  alloc = tracked_memory_find( ptr );
  if( !alloc || alloc->freed ) {
    tracked_memory_state.invalid_free = 1;
    return;
  }

  alloc->freed = 1;
  free( ptr );
}

static void
use_system_memory_vtable( void )
{
  libspectrum_mem_vtable_t table = { malloc, calloc, realloc, free };

  libspectrum_mem_set_vtable( &table );
}

static void
use_tracked_memory_vtable( void )
{
  libspectrum_mem_vtable_t table = {
    tracked_malloc, tracked_calloc, tracked_realloc, tracked_free
  };

  tracked_memory_reset();
  libspectrum_mem_set_vtable( &table );
}

static test_return_t
check_rzx_read_frame_cleanup( const char *filename, size_t frame_data_length,
                              int expect_invalid_free )
{
  libspectrum_byte *buffer = NULL;
  size_t length = 0;
  libspectrum_rzx *rzx;
  libspectrum_error error;
  tracked_alloc_t *frame_data_alloc;
  test_return_t r = TEST_PASS;

  if( read_file( &buffer, &length, filename ) ) return TEST_INCOMPLETE;

  rzx = libspectrum_rzx_alloc();

  use_tracked_memory_vtable();
  error = libspectrum_rzx_read( rzx, buffer, length );
  use_system_memory_vtable();

  if( error != LIBSPECTRUM_ERROR_CORRUPT ) {
    fprintf( stderr, "%s: corrupt RZX did not return LIBSPECTRUM_ERROR_CORRUPT\n",
             progname );
    r = TEST_FAIL;
    goto done;
  }

  if( tracked_memory_state.invalid_free != expect_invalid_free ) {
    fprintf( stderr, "%s: invalid free state %d, expected %d\n", progname,
             tracked_memory_state.invalid_free, expect_invalid_free );
    r = TEST_FAIL;
    goto done;
  }

  frame_data_alloc = tracked_memory_find_by_size( frame_data_length );
  if( !frame_data_alloc ) {
    fprintf( stderr, "%s: could not uniquely identify frame data allocation\n",
             progname );
    r = TEST_FAIL;
    goto done;
  }

  if( !frame_data_alloc->freed ) {
    fprintf( stderr, "%s: frame data allocation was not freed on error\n",
             progname );
    r = TEST_FAIL;
    goto done;
  }

 done:
  libspectrum_rzx_free( rzx );
  libspectrum_free( buffer );
  return r;
}

test_return_t
rzx_invalid_frame_data_error_does_not_free_repeat_frame_pointer( void )
{
  const char *filename = STATIC_TEST_PATH( "invalid-repeat-frame.rzx" );

  return check_rzx_read_frame_cleanup( filename, 7, 0 );
}

test_return_t
write_rzx_with_incompressible_snap( void )
{
#ifndef HAVE_ZLIB_H
  return TEST_SKIPPED; /* gzip not enabled in build */
#endif

  const char *filename = STATIC_TEST_PATH( "random.szx" );
  libspectrum_byte *buffer = NULL;
  size_t filesize = 0;
  size_t rzx_length = 0;
  libspectrum_snap *snap;
  libspectrum_rzx *rzx;
  test_return_t r = TEST_INCOMPLETE;

  if( read_file( &buffer, &filesize, filename ) ) return TEST_INCOMPLETE;

  snap = libspectrum_snap_alloc();

  if( libspectrum_snap_read( snap, buffer, filesize, LIBSPECTRUM_ID_UNKNOWN,
                             filename ) != LIBSPECTRUM_ERROR_NONE ) {
    fprintf( stderr, "%s: reading `%s' failed\n", progname, filename );
    libspectrum_snap_free( snap );
    libspectrum_free( buffer );
    return TEST_INCOMPLETE;
  }

  libspectrum_free( buffer );

  rzx = libspectrum_rzx_alloc();

  if( libspectrum_rzx_add_snap( rzx, snap, 0 ) != LIBSPECTRUM_ERROR_NONE ) {
    fprintf( stderr, "%s: adding snap failed\n", progname );
    libspectrum_rzx_free( rzx );
    libspectrum_snap_free( snap );
    return TEST_INCOMPLETE;
  }

  if( libspectrum_rzx_write( &buffer, &rzx_length, rzx,
        LIBSPECTRUM_ID_SNAPSHOT_SZX, NULL, 1, NULL ) != LIBSPECTRUM_ERROR_NONE ) {
    fprintf( stderr, "%s: error serializing RZX\n", progname );
    libspectrum_rzx_free( rzx );
    return TEST_INCOMPLETE;
  }

  libspectrum_rzx_free( rzx );
  libspectrum_free( buffer );

  if( rzx_length > 49152 ) {
    r = TEST_PASS;
  } else {
    fprintf( stderr, "%s: length %lu too short\n", progname,
             (unsigned long)rzx_length );
    r = TEST_FAIL;
  }

  return r;
}
