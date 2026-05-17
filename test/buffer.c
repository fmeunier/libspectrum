#include "config.h"

#include <stdio.h>

#include "test.h"

/* Buffer write tests */

test_return_t
test_77( void )
{
  /* libspectrum_buffer_write_byte: single byte stored correctly */
  libspectrum_buffer *buf = libspectrum_buffer_alloc();
  test_return_t r = TEST_FAIL;
  const libspectrum_byte *data;

  libspectrum_buffer_write_byte( buf, 0xab );

  if( libspectrum_buffer_get_data_size( buf ) != 1 ) {
    fprintf( stderr, "%s: test_77: expected size 1, got %lu\n", progname,
             (unsigned long)libspectrum_buffer_get_data_size( buf ) );
    goto done;
  }

  data = libspectrum_buffer_get_data( buf );
  if( data[0] != 0xab ) {
    fprintf( stderr, "%s: test_77: expected 0xab, got 0x%02x\n",
             progname, data[0] );
    goto done;
  }

  r = TEST_PASS;

done:
  libspectrum_buffer_free( buf );
  return r;
}

test_return_t
test_78( void )
{
  /* libspectrum_buffer_write_word: value stored little-endian */
  libspectrum_buffer *buf = libspectrum_buffer_alloc();
  test_return_t r = TEST_FAIL;
  const libspectrum_byte *data;

  libspectrum_buffer_write_word( buf, 0x1234 );

  if( libspectrum_buffer_get_data_size( buf ) != 2 ) {
    fprintf( stderr, "%s: test_78: expected size 2, got %lu\n", progname,
             (unsigned long)libspectrum_buffer_get_data_size( buf ) );
    goto done;
  }

  data = libspectrum_buffer_get_data( buf );
  if( data[0] != 0x34 || data[1] != 0x12 ) {
    fprintf( stderr, "%s: test_78: expected 0x34 0x12, got 0x%02x 0x%02x\n",
             progname, data[0], data[1] );
    goto done;
  }

  r = TEST_PASS;

done:
  libspectrum_buffer_free( buf );
  return r;
}

test_return_t
test_79( void )
{
  /* libspectrum_buffer_write_dword: value stored little-endian */
  libspectrum_buffer *buf = libspectrum_buffer_alloc();
  test_return_t r = TEST_FAIL;
  const libspectrum_byte *data;

  libspectrum_buffer_write_dword( buf, 0x12345678 );

  if( libspectrum_buffer_get_data_size( buf ) != 4 ) {
    fprintf( stderr, "%s: test_79: expected size 4, got %lu\n", progname,
             (unsigned long)libspectrum_buffer_get_data_size( buf ) );
    goto done;
  }

  data = libspectrum_buffer_get_data( buf );
  if( data[0] != 0x78 || data[1] != 0x56 ||
      data[2] != 0x34 || data[3] != 0x12 ) {
    fprintf( stderr,
             "%s: test_79: expected 0x78 0x56 0x34 0x12, got"
             " 0x%02x 0x%02x 0x%02x 0x%02x\n",
             progname, data[0], data[1], data[2], data[3] );
    goto done;
  }

  r = TEST_PASS;

done:
  libspectrum_buffer_free( buf );
  return r;
}

test_return_t
test_80( void )
{
  /* libspectrum_buffer_write_buffer: contents of src copied to dest */
  libspectrum_buffer *src = libspectrum_buffer_alloc();
  libspectrum_buffer *dest = libspectrum_buffer_alloc();
  test_return_t r = TEST_FAIL;
  const libspectrum_byte *data;

  libspectrum_buffer_write_byte( src, 0x01 );
  libspectrum_buffer_write_byte( src, 0x02 );
  libspectrum_buffer_write_byte( src, 0x03 );

  libspectrum_buffer_write_buffer( dest, src );

  if( libspectrum_buffer_get_data_size( dest ) != 3 ) {
    fprintf( stderr, "%s: test_80: expected dest size 3, got %lu\n", progname,
             (unsigned long)libspectrum_buffer_get_data_size( dest ) );
    goto done;
  }

  data = libspectrum_buffer_get_data( dest );
  if( data[0] != 0x01 || data[1] != 0x02 || data[2] != 0x03 ) {
    fprintf( stderr,
             "%s: test_80: expected 0x01 0x02 0x03, got 0x%02x 0x%02x 0x%02x\n",
             progname, data[0], data[1], data[2] );
    goto done;
  }

  r = TEST_PASS;

done:
  libspectrum_buffer_free( src );
  libspectrum_buffer_free( dest );
  return r;
}

test_return_t
test_81( void )
{
  /* libspectrum_buffer_is_empty / is_not_empty */
  libspectrum_buffer *buf = libspectrum_buffer_alloc();
  test_return_t r = TEST_FAIL;

  if( !libspectrum_buffer_is_empty( buf ) ) {
    fprintf( stderr, "%s: test_81: new buffer should be empty\n", progname );
    goto done;
  }
  if( libspectrum_buffer_is_not_empty( buf ) ) {
    fprintf( stderr, "%s: test_81: new buffer should not be non-empty\n",
             progname );
    goto done;
  }

  libspectrum_buffer_write_byte( buf, 0xff );

  if( libspectrum_buffer_is_empty( buf ) ) {
    fprintf( stderr, "%s: test_81: buffer with data should not be empty\n",
             progname );
    goto done;
  }
  if( !libspectrum_buffer_is_not_empty( buf ) ) {
    fprintf( stderr, "%s: test_81: buffer with data should be non-empty\n",
             progname );
    goto done;
  }

  r = TEST_PASS;

done:
  libspectrum_buffer_free( buf );
  return r;
}

test_return_t
test_82( void )
{
  /* libspectrum_buffer_clear: size resets to zero */
  libspectrum_buffer *buf = libspectrum_buffer_alloc();
  test_return_t r = TEST_FAIL;

  libspectrum_buffer_write_byte( buf, 0x42 );
  libspectrum_buffer_write_byte( buf, 0x43 );

  if( libspectrum_buffer_get_data_size( buf ) != 2 ) {
    fprintf( stderr, "%s: test_82: expected size 2 before clear, got %lu\n",
             progname,
             (unsigned long)libspectrum_buffer_get_data_size( buf ) );
    goto done;
  }

  libspectrum_buffer_clear( buf );

  if( libspectrum_buffer_get_data_size( buf ) != 0 ) {
    fprintf( stderr, "%s: test_82: expected size 0 after clear, got %lu\n",
             progname,
             (unsigned long)libspectrum_buffer_get_data_size( buf ) );
    goto done;
  }
  if( !libspectrum_buffer_is_empty( buf ) ) {
    fprintf( stderr, "%s: test_82: cleared buffer should be empty\n",
             progname );
    goto done;
  }

  r = TEST_PASS;

done:
  libspectrum_buffer_free( buf );
  return r;
}

test_return_t
test_83( void )
{
  /* libspectrum_buffer_set: N bytes are filled with given value */
  libspectrum_buffer *buf = libspectrum_buffer_alloc();
  test_return_t r = TEST_FAIL;
  const libspectrum_byte *data;
  size_t i;

  libspectrum_buffer_set( buf, 0x5a, 4 );

  if( libspectrum_buffer_get_data_size( buf ) != 4 ) {
    fprintf( stderr, "%s: test_83: expected size 4, got %lu\n", progname,
             (unsigned long)libspectrum_buffer_get_data_size( buf ) );
    goto done;
  }

  data = libspectrum_buffer_get_data( buf );
  for( i = 0; i < 4; i++ ) {
    if( data[i] != 0x5a ) {
      fprintf( stderr, "%s: test_83: byte %lu: expected 0x5a, got 0x%02x\n",
               progname, (unsigned long)i, data[i] );
      goto done;
    }
  }

  r = TEST_PASS;

done:
  libspectrum_buffer_free( buf );
  return r;
}

test_return_t
test_84( void )
{
  /* libspectrum_buffer_append: contents of src are appended to raw buffer */
  libspectrum_buffer *src = libspectrum_buffer_alloc();
  libspectrum_byte *raw = NULL;
  size_t raw_len = 0;
  libspectrum_byte *ptr;
  test_return_t r = TEST_FAIL;

  libspectrum_buffer_write_byte( src, 0x11 );
  libspectrum_buffer_write_byte( src, 0x22 );
  libspectrum_buffer_write_byte( src, 0x33 );

  ptr = raw;
  libspectrum_buffer_append( &raw, &raw_len, &ptr, src );

  if( (size_t)( ptr - raw ) != 3 ) {
    fprintf( stderr, "%s: test_84: expected 3 bytes written, got %lu\n",
             progname, (unsigned long)( ptr - raw ) );
    goto done;
  }

  if( raw[0] != 0x11 || raw[1] != 0x22 || raw[2] != 0x33 ) {
    fprintf( stderr,
             "%s: test_84: expected 0x11 0x22 0x33, got 0x%02x 0x%02x 0x%02x\n",
             progname, raw[0], raw[1], raw[2] );
    goto done;
  }

  r = TEST_PASS;

done:
  libspectrum_free( raw );
  libspectrum_buffer_free( src );
  return r;
}
