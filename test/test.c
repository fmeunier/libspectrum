#include "config.h"

#include <stdio.h>
#include <string.h>

#include "internals.h"
#include "common.h"
#include "test.h"

/* Specific tests begin here */

/* Test for bugs #47 and #78: tape object incorrectly freed after reading
   invalid tape */
test_return_t
test_1( void )
{
  return read_tape( STATIC_TEST_PATH( "invalid.tzx" ), LIBSPECTRUM_ERROR_UNKNOWN );
}

/* Test for bugs #84: TZX turbo blocks with zero pilot pulses and #85: freeing
   a turbo block with no data produces segfault */
test_return_t
test_2( void )
{
  libspectrum_byte *buffer = NULL;
  size_t filesize = 0;
  libspectrum_tape *tape;
  const char *filename = STATIC_TEST_PATH( "turbo-zeropilot.tzx" );
  libspectrum_dword tstates;
  int flags;

  if( read_file( &buffer, &filesize, filename ) ) return TEST_INCOMPLETE;

  tape = libspectrum_tape_alloc();

  if( libspectrum_tape_read( tape, buffer, filesize, LIBSPECTRUM_ID_UNKNOWN,
			     filename ) ) {
    libspectrum_tape_free( tape );
    libspectrum_free( buffer );
    return TEST_INCOMPLETE;
  }

  libspectrum_free( buffer );

  if( libspectrum_tape_get_next_edge( &tstates, &flags, tape ) ) {
    libspectrum_tape_free( tape );
    return TEST_INCOMPLETE;
  }

  if( flags ) {
    fprintf( stderr, "%s: reading first edge of `%s' gave unexpected flags 0x%04x; expected 0x0000\n",
	     progname, filename, flags );
    libspectrum_tape_free( tape );
    return TEST_FAIL;
  }

  if( tstates != 667 ) {
    fprintf( stderr, "%s: first edge of `%s' was %u tstates; expected 667\n",
	     progname, filename, tstates );
    libspectrum_tape_free( tape );
    return TEST_FAIL;
  }

  if( libspectrum_tape_free( tape ) ) return TEST_INCOMPLETE;

  return TEST_PASS;
}

/* Test for bug #88: writing empty .tap file causes crash */
test_return_t
test_3( void )
{
  libspectrum_tape *tape;
  libspectrum_byte *buffer = (libspectrum_byte*)1;
  size_t length = 0;

  tape = libspectrum_tape_alloc();

  if( libspectrum_tape_write( &buffer, &length, tape, LIBSPECTRUM_ID_TAPE_TAP ) ) {
    libspectrum_tape_free( tape );
    return TEST_INCOMPLETE;
  }

  /* `buffer' should now have been set to NULL */
  if( buffer ) {
    fprintf( stderr, "%s: `buffer' was not NULL after libspectrum_tape_write()\n", progname );
    libspectrum_tape_free( tape );
    return TEST_FAIL;
  }

  if( libspectrum_tape_free( tape ) ) return TEST_INCOMPLETE;

  return TEST_PASS;
}

/* Test for bug #102: invalid compressed file causes crash */
test_return_t
test_4( void )
{
  #ifndef HAVE_ZLIB_H
    return TEST_SKIPPED; /* gzip not enabled in build */
  #endif

  const char *filename = STATIC_TEST_PATH( "invalid.gz" );
  return read_snap( filename, filename, LIBSPECTRUM_ERROR_UNKNOWN );
}

/* Further test for bug #102: invalid compressed file causes crash */
test_return_t
test_5( void )
{
  #ifndef HAVE_ZLIB_H
    return TEST_SKIPPED; /* gzip not enabled in build */
  #endif

  return read_snap( STATIC_TEST_PATH( "invalid.gz" ), NULL, LIBSPECTRUM_ERROR_UNKNOWN );
}

/* Test for bug #103: pointer wraparound causes segfault */
test_return_t
test_6( void )
{
  const char *filename = STATIC_TEST_PATH( "invalid.szx" );
  return read_snap( filename, filename, LIBSPECTRUM_ERROR_CORRUPT );
}

/* Test for bug #105: lack of sanity check in GDB code */
test_return_t
test_7( void )
{
  return read_tape( STATIC_TEST_PATH( "invalid-gdb.tzx" ), LIBSPECTRUM_ERROR_CORRUPT );
}

/* Test for bug #106: empty DRB causes segfault */
test_return_t
test_8( void )
{
  return read_tape( STATIC_TEST_PATH( "empty-drb.tzx" ), LIBSPECTRUM_ERROR_NONE );
}

/* Test for bug #107: problems with invalid archive info block */
test_return_t
test_9( void )
{
  return read_tape( STATIC_TEST_PATH( "invalid-archiveinfo.tzx" ), LIBSPECTRUM_ERROR_CORRUPT );
}

/* Test for bug #108: invalid hardware info blocks can leak memory */
test_return_t
test_10( void )
{
  return read_tape( STATIC_TEST_PATH( "invalid-hardwareinfo.tzx" ), LIBSPECTRUM_ERROR_CORRUPT );
}

/* Test for bug #111: invalid Warajevo tape block offset causes segfault */
test_return_t
test_11( void )
{
  return read_tape( STATIC_TEST_PATH( "invalid-warajevo-blockoffset.tap" ), LIBSPECTRUM_ERROR_CORRUPT );
}

/* Test for bug #112: invalid custom info block causes memory leak */
test_return_t
test_12( void )
{
  return read_tape( STATIC_TEST_PATH( "invalid-custominfo.tzx" ), LIBSPECTRUM_ERROR_CORRUPT );
}

/* Test for bug #113: loop end without a loop start block accesses uninitialised
   memory */
test_return_t
test_13( void )
{
  libspectrum_byte *buffer = NULL;
  size_t filesize = 0;
  libspectrum_tape *tape;
  const char *filename = STATIC_TEST_PATH( "loopend.tzx" );
  libspectrum_dword tstates;
  int flags;

  if( read_file( &buffer, &filesize, filename ) ) return TEST_INCOMPLETE;

  tape = libspectrum_tape_alloc();

  if( libspectrum_tape_read( tape, buffer, filesize, LIBSPECTRUM_ID_UNKNOWN,
			     filename ) ) {
    libspectrum_tape_free( tape );
    libspectrum_free( buffer );
    return TEST_INCOMPLETE;
  }

  libspectrum_free( buffer );

  if( libspectrum_tape_get_next_edge( &tstates, &flags, tape ) ) {
    libspectrum_tape_free( tape );
    return TEST_INCOMPLETE;
  }

  if( libspectrum_tape_free( tape ) ) return TEST_INCOMPLETE;

  return TEST_PASS;
}

/* Test for bug #113: TZX loop blocks broken */
test_return_t
test_14( void )
{
  return play_tape( STATIC_TEST_PATH( "loop.tzx" ) );
}

/* Test for bug #118: TZX loop blocks still broken */
test_return_t
test_16( void )
{
  return play_tape( STATIC_TEST_PATH( "loop2.tzx" ) );
}

/* Test for bug #119: TZX jump blocks broken */
test_return_t
test_17( void )
{
  return play_tape( STATIC_TEST_PATH( "jump.tzx" ) );
}

/* Test for bug #121: crashes writing and reading empty CSW files */
test_return_t
test_18( void )
{
  return play_tape( STATIC_TEST_PATH( "empty.csw" ) );
}

/* Test for bug #125: .tap writing code does not handle all block types */
test_return_t
test_19( void )
{
  libspectrum_byte *buffer = NULL;
  size_t length = 0;
  libspectrum_tape *tape;
  const char *filename = DYNAMIC_TEST_PATH( "complete-tzx.tzx" );
  test_return_t r;

  r = load_tape( &tape, filename, LIBSPECTRUM_ERROR_NONE );
  if( r ) return r;

  if( libspectrum_tape_write( &buffer, &length, tape,
                              LIBSPECTRUM_ID_TAPE_TAP ) ) {
    fprintf( stderr, "%s: writing `%s' to a .tap file was not successful\n",
             progname, filename );
    libspectrum_tape_free( tape );
    return TEST_INCOMPLETE;
  }

  libspectrum_free( buffer );

  if( libspectrum_tape_free( tape ) ) return TEST_INCOMPLETE;

  return TEST_PASS;
}

/* Tests for bug #129: SP not sanity checked when reading .sna files;
   also tests bug #130: compressed snapshots cause segfault */
test_return_t
test_20( void )
{
  #ifndef HAVE_ZLIB_H
    return TEST_SKIPPED; /* gzip not enabled in build */
  #endif

  const char *filename = STATIC_TEST_PATH( "sp-2000.sna.gz" );
  return read_snap( filename, filename, LIBSPECTRUM_ERROR_CORRUPT );
} 
  
test_return_t
test_21( void )
{
  #ifndef HAVE_ZLIB_H
    return TEST_SKIPPED; /* gzip not enabled in build */
  #endif

  const char *filename = STATIC_TEST_PATH( "sp-ffff.sna.gz" );
  return read_snap( filename, filename, LIBSPECTRUM_ERROR_CORRUPT );
} 

test_return_t
test_24( void )
{
  const char *filename = DYNAMIC_TEST_PATH( "complete-tzx.tzx" );
  libspectrum_byte *buffer = NULL;
  size_t filesize = 0;
  libspectrum_tape *tape;
  libspectrum_tape_iterator it;
  libspectrum_tape_block *block;
  libspectrum_dword expected_sizes[20] = {
    15216886,	/* ROM */
    3493371,	/* Turbo */
    356310,	/* Pure tone */
    1761,	/* Pulses */
    1993724,	/* Pure data */
    2163000,	/* Pause */
    0,		/* Group start */
    0,		/* Group end */
    0,		/* Jump */
    205434,	/* Pure tone */
    0,		/* Loop start */
    154845,	/* Pure tone */
    0,		/* Loop end */
    0,		/* Stop tape if in 48K mode */
    0,		/* Comment */
    0,		/* Message */
    0,		/* Archive info */
    0,		/* Hardware */
    0,		/* Custom info */
    771620,	/* Pure tone */
  };
  libspectrum_dword *next_size = &expected_sizes[ 0 ];
  test_return_t r = TEST_PASS;

  if( read_file( &buffer, &filesize, filename ) ) return TEST_INCOMPLETE;

  tape = libspectrum_tape_alloc();

  if( libspectrum_tape_read( tape, buffer, filesize, LIBSPECTRUM_ID_UNKNOWN,
			     filename ) ) {
    libspectrum_tape_free( tape );
    libspectrum_free( buffer );
    return TEST_INCOMPLETE;
  }

  libspectrum_free( buffer );

  block = libspectrum_tape_iterator_init( &it, tape );

  while( block )
  {
    libspectrum_dword actual_size = libspectrum_tape_block_length( block ); 

    if( actual_size != *next_size )
    {
      fprintf( stderr, "%s: block had length %lu, but expected %lu\n", progname, (unsigned long)actual_size, (unsigned long)*next_size );
      r = TEST_FAIL;
      break;
    }

    block = libspectrum_tape_iterator_next( &it );
    next_size++;
  }

  if( libspectrum_tape_free( tape ) ) return TEST_INCOMPLETE;

  return r;
}

test_return_t
test_25( void )
{
  const char *filename = STATIC_TEST_PATH( "empty.z80" );
  libspectrum_byte *buffer = NULL;
  size_t filesize = 0, length = 0;
  libspectrum_snap *snap;
  int flags;
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
  buffer = NULL;

  if( libspectrum_snap_write( &buffer, &length, &flags, snap,
                              LIBSPECTRUM_ID_SNAPSHOT_SNA, NULL, 0 ) != 
      LIBSPECTRUM_ERROR_NONE ) {
    fprintf( stderr, "%s: serialising to SNA failed\n", progname );
    libspectrum_snap_free( snap );
    return TEST_INCOMPLETE;
  }

  libspectrum_snap_free( snap );
  snap = libspectrum_snap_alloc();

  if( libspectrum_snap_read( snap, buffer, length, LIBSPECTRUM_ID_SNAPSHOT_SNA,
                             NULL ) != LIBSPECTRUM_ERROR_NONE ) {
    fprintf( stderr, "%s: restoring from SNA failed\n", progname );
    libspectrum_snap_free( snap );
    libspectrum_free( buffer );
    return TEST_INCOMPLETE;
  }

  libspectrum_free( buffer );

  if( libspectrum_snap_pc( snap ) != 0x1234 ) {
    fprintf( stderr, "%s: PC is 0x%04x, not the expected 0x1234\n", progname,
             libspectrum_snap_pc( snap ) );
    r = TEST_FAIL;
  } else if( libspectrum_snap_sp( snap ) != 0x8000 ) {
    fprintf( stderr, "%s: SP is 0x%04x, not the expected 0x8000\n", progname,
             libspectrum_snap_sp( snap ) );
    r = TEST_FAIL;
  } else {
    r = TEST_PASS;
  }

  libspectrum_snap_free( snap );

  return r;
}

/* Tests for bug #198: last out to 0x1ffd is not serialised into .z80 files */
test_return_t
test_26( void )
{
  const char *filename = STATIC_TEST_PATH( "plus3.z80" );
  libspectrum_byte *buffer = NULL;
  size_t filesize = 0, length = 0;
  libspectrum_snap *snap;
  int flags;
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
  buffer = NULL;

  if( libspectrum_snap_write( &buffer, &length, &flags, snap,
                              LIBSPECTRUM_ID_SNAPSHOT_Z80, NULL, 0 ) != 
      LIBSPECTRUM_ERROR_NONE ) {
    fprintf( stderr, "%s: serialising to Z80 failed\n", progname );
    libspectrum_snap_free( snap );
    return TEST_INCOMPLETE;
  }

  libspectrum_snap_free( snap );
  snap = libspectrum_snap_alloc();

  if( libspectrum_snap_read( snap, buffer, length, LIBSPECTRUM_ID_SNAPSHOT_Z80,
                             NULL ) != LIBSPECTRUM_ERROR_NONE ) {
    fprintf( stderr, "%s: restoring from Z80 failed\n", progname );
    libspectrum_snap_free( snap );
    libspectrum_free( buffer );
    return TEST_INCOMPLETE;
  }

  if( libspectrum_snap_out_plus3_memoryport( snap ) == 0xaa ) {
    r = TEST_PASS;
  } else {
    fprintf( stderr,
             "%s: Last out to 0x1ffd is 0x%02x, not the expected 0xaa\n",
             progname, libspectrum_snap_out_plus3_memoryport( snap ) );
    r = TEST_FAIL;
  }

  libspectrum_snap_free( snap );

  return r;
}

/* Tests for bug #184: SZX files were written with A and F reversed */
test_return_t
test_27( void )
{
  #ifndef HAVE_ZLIB_H
    return TEST_SKIPPED; /* gzip not enabled in build */
  #endif

  const char *filename = STATIC_TEST_PATH( "empty.szx" );
  libspectrum_byte *buffer = NULL;
  size_t filesize = 0;
  libspectrum_snap *snap;
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

  if( libspectrum_snap_a( snap ) != 0x12 ) {
    fprintf( stderr, "%s: A is 0x%02x, not the expected 0x12\n", progname,
             libspectrum_snap_a( snap ) );
    r = TEST_FAIL;
  } else if( libspectrum_snap_f( snap ) != 0x34 ) {
    fprintf( stderr, "%s: F is 0x%02x, not the expected 0x34\n", progname,
             libspectrum_snap_f( snap ) );
    r = TEST_FAIL;
  } else if( libspectrum_snap_a_( snap ) != 0x56 ) {
    fprintf( stderr, "%s: A' is 0x%02x, not the expected 0x56\n", progname,
             libspectrum_snap_a_( snap ) );
    r = TEST_FAIL;
  } else if( libspectrum_snap_f_( snap ) != 0x78 ) {
    fprintf( stderr, "%s: F' is 0x%02x, not the expected 0x78\n", progname,
             libspectrum_snap_f_( snap ) );
    r = TEST_FAIL;
  } else {
    r = TEST_PASS;
  }

  return r;
}

/* Test for bug #379: converting .tap file to .csw causes crash */
test_return_t
test_30( void )
{
  libspectrum_byte *buffer = NULL;
  size_t length = 0;
  libspectrum_tape *tape;
  const char *filename = STATIC_TEST_PATH( "standard-tap.tap" );
  test_return_t r;

  r = load_tape( &tape, filename, LIBSPECTRUM_ERROR_NONE );
  if( r ) return r;

  if( libspectrum_tape_write( &buffer, &length, tape,
                              LIBSPECTRUM_ID_TAPE_CSW ) ) {
    fprintf( stderr, "%s: writing `%s' to a .csw file was not successful\n",
             progname, filename );
    libspectrum_tape_free( tape );
    return TEST_INCOMPLETE;
  }

  libspectrum_free( buffer );

  if( libspectrum_tape_free( tape ) ) return TEST_INCOMPLETE;

  return TEST_PASS;
}

test_return_t
test_71( void )
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

test_return_t
test_72( void )
{
  const char *filename = DYNAMIC_TEST_PATH( "complete-tzx.tzx" );
  libspectrum_byte *buffer = NULL;
  size_t filesize = 0;
  libspectrum_tape *tape;
  libspectrum_tape_iterator it;
  libspectrum_tape_type expected_next_block_types[19] = {
    LIBSPECTRUM_TAPE_BLOCK_TURBO,       /* ROM */
    LIBSPECTRUM_TAPE_BLOCK_PURE_TONE,   /* Turbo */
    LIBSPECTRUM_TAPE_BLOCK_PULSES,      /* Pure tone */
    LIBSPECTRUM_TAPE_BLOCK_PURE_DATA,   /* Pulses */
    LIBSPECTRUM_TAPE_BLOCK_PAUSE,       /* Pure data */
    LIBSPECTRUM_TAPE_BLOCK_GROUP_START, /* Pause */
    LIBSPECTRUM_TAPE_BLOCK_GROUP_END,   /* Group start */
    LIBSPECTRUM_TAPE_BLOCK_JUMP,        /* Group end */
    LIBSPECTRUM_TAPE_BLOCK_PURE_TONE,   /* Jump */
    LIBSPECTRUM_TAPE_BLOCK_LOOP_START,  /* Pure tone */
    LIBSPECTRUM_TAPE_BLOCK_PURE_TONE,   /* Loop start */
    LIBSPECTRUM_TAPE_BLOCK_LOOP_END,    /* Pure tone */
    LIBSPECTRUM_TAPE_BLOCK_STOP48,      /* Loop end */
    LIBSPECTRUM_TAPE_BLOCK_COMMENT,     /* Stop tape if in 48K mode */
    LIBSPECTRUM_TAPE_BLOCK_MESSAGE,     /* Comment */
    LIBSPECTRUM_TAPE_BLOCK_ARCHIVE_INFO,/* Message */
    LIBSPECTRUM_TAPE_BLOCK_HARDWARE,    /* Archive info */
    LIBSPECTRUM_TAPE_BLOCK_CUSTOM,      /* Hardware */
    LIBSPECTRUM_TAPE_BLOCK_PURE_TONE,   /* Custom info */
  };
  libspectrum_tape_type *next_block_type = &expected_next_block_types[ 0 ];
  test_return_t r = TEST_PASS;
  int blocks_processed = 0;
  /* Expect to check the next block type of 19 of the 20 blocks in the test
     tzx */
  int expected_block_count = ARRAY_SIZE( expected_next_block_types );

  if( read_file( &buffer, &filesize, filename ) ) return TEST_INCOMPLETE;

  tape = libspectrum_tape_alloc();

  if( libspectrum_tape_read( tape, buffer, filesize, LIBSPECTRUM_ID_UNKNOWN,
			     filename ) )
  {
    libspectrum_tape_free( tape );
    libspectrum_free( buffer );
    return TEST_INCOMPLETE;
  }

  libspectrum_free( buffer );

  libspectrum_tape_iterator_init( &it, tape );

  while( libspectrum_tape_iterator_peek_next( it ) )
  {
    libspectrum_tape_type actual_next_block_type =
      libspectrum_tape_block_type( libspectrum_tape_iterator_peek_next( it ) );

    if( actual_next_block_type != *next_block_type )
    {
      r = TEST_FAIL;
      break;
    }

    libspectrum_tape_iterator_next( &it );
    next_block_type++;
    blocks_processed++;
  }

  if( blocks_processed != expected_block_count )
  {
      r = TEST_FAIL;
  }

  if( libspectrum_tape_free( tape ) ) return TEST_INCOMPLETE;

  return r;
}

test_return_t
test_75( void )
{
#ifndef HAVE_WAV_BACKEND
  return TEST_SKIPPED;
#else
  return check_wav_block( DYNAMIC_TEST_PATH( "wav-mono-threshold.wav" ),
                          3500000 / 22050, 0xa9 );
#endif
}

test_return_t
test_76( void )
{
#ifndef WAV_INTERNAL_MACOS
  return TEST_SKIPPED;
#else
  return check_wav_block( DYNAMIC_TEST_PATH( "wav-stereo-mixdown.wav" ),
                          3500000 / 22050, 0x8d );
#endif
}

/* Buffer write tests */












test_return_t
test_88( void )
{
  /* libspectrum_snap: main Z80 register getter/setter (a, f, bc, de, hl, alternates) */
  libspectrum_snap *snap = libspectrum_snap_alloc();
  test_return_t r = TEST_FAIL;

  if( !snap ) {
    fprintf( stderr, "%s: test_88: snap_alloc returned NULL\n", progname );
    return TEST_INCOMPLETE;
  }

  libspectrum_snap_set_a( snap, 0x12 );
  libspectrum_snap_set_f( snap, 0x34 );
  libspectrum_snap_set_bc( snap, 0x5678 );
  libspectrum_snap_set_de( snap, 0x9abc );
  libspectrum_snap_set_hl( snap, 0xdef0 );
  libspectrum_snap_set_a_( snap, 0xaa );
  libspectrum_snap_set_f_( snap, 0xbb );
  libspectrum_snap_set_bc_( snap, 0x1122 );
  libspectrum_snap_set_de_( snap, 0x3344 );
  libspectrum_snap_set_hl_( snap, 0x5566 );

  if( libspectrum_snap_a( snap ) != 0x12 ) {
    fprintf( stderr, "%s: test_88: expected a=0x12, got 0x%02x\n", progname,
             libspectrum_snap_a( snap ) );
    goto done;
  }
  if( libspectrum_snap_f( snap ) != 0x34 ) {
    fprintf( stderr, "%s: test_88: expected f=0x34, got 0x%02x\n", progname,
             libspectrum_snap_f( snap ) );
    goto done;
  }
  if( libspectrum_snap_bc( snap ) != 0x5678 ) {
    fprintf( stderr, "%s: test_88: expected bc=0x5678, got 0x%04x\n", progname,
             libspectrum_snap_bc( snap ) );
    goto done;
  }
  if( libspectrum_snap_de( snap ) != 0x9abc ) {
    fprintf( stderr, "%s: test_88: expected de=0x9abc, got 0x%04x\n", progname,
             libspectrum_snap_de( snap ) );
    goto done;
  }
  if( libspectrum_snap_hl( snap ) != 0xdef0 ) {
    fprintf( stderr, "%s: test_88: expected hl=0xdef0, got 0x%04x\n", progname,
             libspectrum_snap_hl( snap ) );
    goto done;
  }
  if( libspectrum_snap_a_( snap ) != 0xaa ) {
    fprintf( stderr, "%s: test_88: expected a_=0xaa, got 0x%02x\n", progname,
             libspectrum_snap_a_( snap ) );
    goto done;
  }
  if( libspectrum_snap_f_( snap ) != 0xbb ) {
    fprintf( stderr, "%s: test_88: expected f_=0xbb, got 0x%02x\n", progname,
             libspectrum_snap_f_( snap ) );
    goto done;
  }
  if( libspectrum_snap_bc_( snap ) != 0x1122 ) {
    fprintf( stderr, "%s: test_88: expected bc_=0x1122, got 0x%04x\n", progname,
             libspectrum_snap_bc_( snap ) );
    goto done;
  }
  if( libspectrum_snap_de_( snap ) != 0x3344 ) {
    fprintf( stderr, "%s: test_88: expected de_=0x3344, got 0x%04x\n", progname,
             libspectrum_snap_de_( snap ) );
    goto done;
  }
  if( libspectrum_snap_hl_( snap ) != 0x5566 ) {
    fprintf( stderr, "%s: test_88: expected hl_=0x5566, got 0x%04x\n", progname,
             libspectrum_snap_hl_( snap ) );
    goto done;
  }

  r = TEST_PASS;

done:
  libspectrum_snap_free( snap );
  return r;
}

test_return_t
test_89( void )
{
  /* libspectrum_snap: index and special register getter/setter (ix, iy, i, r, sp, pc) */
  libspectrum_snap *snap = libspectrum_snap_alloc();
  test_return_t r = TEST_FAIL;

  if( !snap ) {
    fprintf( stderr, "%s: test_89: snap_alloc returned NULL\n", progname );
    return TEST_INCOMPLETE;
  }

  libspectrum_snap_set_ix( snap, 0x1234 );
  libspectrum_snap_set_iy( snap, 0x5678 );
  libspectrum_snap_set_i( snap, 0xfe );
  libspectrum_snap_set_r( snap, 0xdc );
  libspectrum_snap_set_sp( snap, 0xba98 );
  libspectrum_snap_set_pc( snap, 0x7654 );

  if( libspectrum_snap_ix( snap ) != 0x1234 ) {
    fprintf( stderr, "%s: test_89: expected ix=0x1234, got 0x%04x\n", progname,
             libspectrum_snap_ix( snap ) );
    goto done;
  }
  if( libspectrum_snap_iy( snap ) != 0x5678 ) {
    fprintf( stderr, "%s: test_89: expected iy=0x5678, got 0x%04x\n", progname,
             libspectrum_snap_iy( snap ) );
    goto done;
  }
  if( libspectrum_snap_i( snap ) != 0xfe ) {
    fprintf( stderr, "%s: test_89: expected i=0xfe, got 0x%02x\n", progname,
             libspectrum_snap_i( snap ) );
    goto done;
  }
  if( libspectrum_snap_r( snap ) != 0xdc ) {
    fprintf( stderr, "%s: test_89: expected r=0xdc, got 0x%02x\n", progname,
             libspectrum_snap_r( snap ) );
    goto done;
  }
  if( libspectrum_snap_sp( snap ) != 0xba98 ) {
    fprintf( stderr, "%s: test_89: expected sp=0xba98, got 0x%04x\n", progname,
             libspectrum_snap_sp( snap ) );
    goto done;
  }
  if( libspectrum_snap_pc( snap ) != 0x7654 ) {
    fprintf( stderr, "%s: test_89: expected pc=0x7654, got 0x%04x\n", progname,
             libspectrum_snap_pc( snap ) );
    goto done;
  }

  r = TEST_PASS;

done:
  libspectrum_snap_free( snap );
  return r;
}

test_return_t
test_90( void )
{
  /* libspectrum_snap: Z80 status getter/setter (iff1, iff2, im, tstates, halted) */
  libspectrum_snap *snap = libspectrum_snap_alloc();
  test_return_t r = TEST_FAIL;

  if( !snap ) {
    fprintf( stderr, "%s: test_90: snap_alloc returned NULL\n", progname );
    return TEST_INCOMPLETE;
  }

  libspectrum_snap_set_iff1( snap, 1 );
  libspectrum_snap_set_iff2( snap, 0 );
  libspectrum_snap_set_im( snap, 2 );
  libspectrum_snap_set_tstates( snap, 69888 );
  libspectrum_snap_set_halted( snap, 1 );

  if( libspectrum_snap_iff1( snap ) != 1 ) {
    fprintf( stderr, "%s: test_90: expected iff1=1, got %d\n", progname,
             libspectrum_snap_iff1( snap ) );
    goto done;
  }
  if( libspectrum_snap_iff2( snap ) != 0 ) {
    fprintf( stderr, "%s: test_90: expected iff2=0, got %d\n", progname,
             libspectrum_snap_iff2( snap ) );
    goto done;
  }
  if( libspectrum_snap_im( snap ) != 2 ) {
    fprintf( stderr, "%s: test_90: expected im=2, got %d\n", progname,
             libspectrum_snap_im( snap ) );
    goto done;
  }
  if( libspectrum_snap_tstates( snap ) != 69888 ) {
    fprintf( stderr, "%s: test_90: expected tstates=69888, got %lu\n", progname,
             (unsigned long)libspectrum_snap_tstates( snap ) );
    goto done;
  }
  if( libspectrum_snap_halted( snap ) != 1 ) {
    fprintf( stderr, "%s: test_90: expected halted=1, got %d\n", progname,
             libspectrum_snap_halted( snap ) );
    goto done;
  }

  r = TEST_PASS;

done:
  libspectrum_snap_free( snap );
  return r;
}




test_return_t
test_94( void )
{
  /* libspectrum_snap: machine type getter/setter */
  libspectrum_snap *snap = libspectrum_snap_alloc();
  test_return_t r = TEST_FAIL;

  if( !snap ) {
    fprintf( stderr, "%s: test_94: snap_alloc returned NULL\n", progname );
    return TEST_INCOMPLETE;
  }

  if( libspectrum_snap_machine( snap ) != LIBSPECTRUM_MACHINE_UNKNOWN ) {
    fprintf( stderr, "%s: test_94: default machine should be UNKNOWN, got %d\n",
             progname, (int)libspectrum_snap_machine( snap ) );
    goto done;
  }

  libspectrum_snap_set_machine( snap, LIBSPECTRUM_MACHINE_48 );
  if( libspectrum_snap_machine( snap ) != LIBSPECTRUM_MACHINE_48 ) {
    fprintf( stderr, "%s: test_94: expected MACHINE_48, got %d\n",
             progname, (int)libspectrum_snap_machine( snap ) );
    goto done;
  }

  libspectrum_snap_set_machine( snap, LIBSPECTRUM_MACHINE_128 );
  if( libspectrum_snap_machine( snap ) != LIBSPECTRUM_MACHINE_128 ) {
    fprintf( stderr, "%s: test_94: expected MACHINE_128, got %d\n",
             progname, (int)libspectrum_snap_machine( snap ) );
    goto done;
  }

  r = TEST_PASS;

done:
  libspectrum_snap_free( snap );
  return r;
}

test_return_t
test_95( void )
{
  /* libspectrum_snap: memptr getter/setter */
  libspectrum_snap *snap = libspectrum_snap_alloc();
  test_return_t r = TEST_FAIL;

  if( !snap ) {
    fprintf( stderr, "%s: test_95: snap_alloc returned NULL\n", progname );
    return TEST_INCOMPLETE;
  }

  libspectrum_snap_set_memptr( snap, 0xabcd );
  if( libspectrum_snap_memptr( snap ) != 0xabcd ) {
    fprintf( stderr, "%s: test_95: expected memptr=0xabcd, got 0x%04x\n",
             progname, libspectrum_snap_memptr( snap ) );
    goto done;
  }

  libspectrum_snap_set_memptr( snap, 0x0000 );
  if( libspectrum_snap_memptr( snap ) != 0x0000 ) {
    fprintf( stderr, "%s: test_95: expected memptr=0x0000, got 0x%04x\n",
             progname, libspectrum_snap_memptr( snap ) );
    goto done;
  }

  r = TEST_PASS;

done:
  libspectrum_snap_free( snap );
  return r;
}

test_return_t
test_96( void )
{
  /* libspectrum_snap: ULA and 128K memory port getter/setter */
  libspectrum_snap *snap = libspectrum_snap_alloc();
  test_return_t r = TEST_FAIL;

  if( !snap ) {
    fprintf( stderr, "%s: test_96: snap_alloc returned NULL\n", progname );
    return TEST_INCOMPLETE;
  }

  libspectrum_snap_set_out_ula( snap, 0x07 );
  if( libspectrum_snap_out_ula( snap ) != 0x07 ) {
    fprintf( stderr, "%s: test_96: expected out_ula=0x07, got 0x%02x\n",
             progname, libspectrum_snap_out_ula( snap ) );
    goto done;
  }

  libspectrum_snap_set_out_128_memoryport( snap, 0x05 );
  if( libspectrum_snap_out_128_memoryport( snap ) != 0x05 ) {
    fprintf( stderr, "%s: test_96: expected out_128_memoryport=0x05, got 0x%02x\n",
             progname, libspectrum_snap_out_128_memoryport( snap ) );
    goto done;
  }

  libspectrum_snap_set_out_ay_registerport( snap, 0x0e );
  if( libspectrum_snap_out_ay_registerport( snap ) != 0x0e ) {
    fprintf( stderr, "%s: test_96: expected out_ay_registerport=0x0e, got 0x%02x\n",
             progname, libspectrum_snap_out_ay_registerport( snap ) );
    goto done;
  }

  r = TEST_PASS;

done:
  libspectrum_snap_free( snap );
  return r;
}

test_return_t
test_97( void )
{
  /* libspectrum_snap: custom_rom flag and custom_rom_pages getter/setter */
  libspectrum_snap *snap = libspectrum_snap_alloc();
  test_return_t r = TEST_FAIL;

  if( !snap ) {
    fprintf( stderr, "%s: test_97: snap_alloc returned NULL\n", progname );
    return TEST_INCOMPLETE;
  }

  if( libspectrum_snap_custom_rom( snap ) != 0 ) {
    fprintf( stderr, "%s: test_97: default custom_rom should be 0, got %d\n",
             progname, libspectrum_snap_custom_rom( snap ) );
    goto done;
  }

  libspectrum_snap_set_custom_rom( snap, 1 );
  if( libspectrum_snap_custom_rom( snap ) != 1 ) {
    fprintf( stderr, "%s: test_97: expected custom_rom=1, got %d\n",
             progname, libspectrum_snap_custom_rom( snap ) );
    goto done;
  }

  libspectrum_snap_set_custom_rom( snap, 0 );
  if( libspectrum_snap_custom_rom( snap ) != 0 ) {
    fprintf( stderr, "%s: test_97: expected custom_rom=0, got %d\n",
             progname, libspectrum_snap_custom_rom( snap ) );
    goto done;
  }

  if( libspectrum_snap_custom_rom_pages( snap ) != 0 ) {
    fprintf( stderr, "%s: test_97: default custom_rom_pages should be 0, got %lu\n",
             progname, (unsigned long)libspectrum_snap_custom_rom_pages( snap ) );
    goto done;
  }

  libspectrum_snap_set_custom_rom_pages( snap, 2 );
  if( libspectrum_snap_custom_rom_pages( snap ) != 2 ) {
    fprintf( stderr, "%s: test_97: expected custom_rom_pages=2, got %lu\n",
             progname, (unsigned long)libspectrum_snap_custom_rom_pages( snap ) );
    goto done;
  }

  r = TEST_PASS;

done:
  libspectrum_snap_free( snap );
  return r;
}

test_return_t
test_98( void )
{
  /* libspectrum_snap: RAM pages getter/setter */
  libspectrum_snap *snap = libspectrum_snap_alloc();
  libspectrum_byte *page;
  test_return_t r = TEST_FAIL;

  if( !snap ) {
    fprintf( stderr, "%s: test_98: snap_alloc returned NULL\n", progname );
    return TEST_INCOMPLETE;
  }

  if( libspectrum_snap_pages( snap, 0 ) != NULL ) {
    fprintf( stderr, "%s: test_98: default pages[0] should be NULL\n", progname );
    goto done;
  }

  page = libspectrum_new( libspectrum_byte, 0x4000 );
  page[0] = 0xaa;
  page[0x3fff] = 0x55;

  libspectrum_snap_set_pages( snap, 0, page );
  if( libspectrum_snap_pages( snap, 0 ) != page ) {
    fprintf( stderr, "%s: test_98: pages[0] pointer mismatch after set\n", progname );
    libspectrum_free( page );
    goto done;
  }

  if( libspectrum_snap_pages( snap, 0 )[0] != 0xaa ||
      libspectrum_snap_pages( snap, 0 )[0x3fff] != 0x55 ) {
    fprintf( stderr, "%s: test_98: pages[0] data mismatch\n", progname );
    goto done;
  }

  if( libspectrum_snap_pages( snap, 1 ) != NULL ) {
    fprintf( stderr, "%s: test_98: pages[1] should still be NULL\n", progname );
    goto done;
  }

  r = TEST_PASS;

done:
  /* snap_free frees all pages including the one we set */
  libspectrum_snap_free( snap );
  return r;
}

test_return_t
test_99( void )
{
  /* libspectrum_snap: interface1 active, paged, and drive_count getter/setter */
  libspectrum_snap *snap = libspectrum_snap_alloc();
  test_return_t r = TEST_FAIL;

  if( !snap ) {
    fprintf( stderr, "%s: test_99: snap_alloc returned NULL\n", progname );
    return TEST_INCOMPLETE;
  }

  if( libspectrum_snap_interface1_active( snap ) != 0 ) {
    fprintf( stderr, "%s: test_99: default interface1_active should be 0, got %d\n",
             progname, libspectrum_snap_interface1_active( snap ) );
    goto done;
  }

  libspectrum_snap_set_interface1_active( snap, 1 );
  if( libspectrum_snap_interface1_active( snap ) != 1 ) {
    fprintf( stderr, "%s: test_99: expected interface1_active=1, got %d\n",
             progname, libspectrum_snap_interface1_active( snap ) );
    goto done;
  }

  if( libspectrum_snap_interface1_paged( snap ) != 0 ) {
    fprintf( stderr, "%s: test_99: default interface1_paged should be 0, got %d\n",
             progname, libspectrum_snap_interface1_paged( snap ) );
    goto done;
  }

  libspectrum_snap_set_interface1_paged( snap, 1 );
  if( libspectrum_snap_interface1_paged( snap ) != 1 ) {
    fprintf( stderr, "%s: test_99: expected interface1_paged=1, got %d\n",
             progname, libspectrum_snap_interface1_paged( snap ) );
    goto done;
  }

  if( libspectrum_snap_interface1_drive_count( snap ) != 0 ) {
    fprintf( stderr, "%s: test_99: default interface1_drive_count should be 0, got %d\n",
             progname, libspectrum_snap_interface1_drive_count( snap ) );
    goto done;
  }

  libspectrum_snap_set_interface1_drive_count( snap, 4 );
  if( libspectrum_snap_interface1_drive_count( snap ) != 4 ) {
    fprintf( stderr, "%s: test_99: expected interface1_drive_count=4, got %d\n",
             progname, libspectrum_snap_interface1_drive_count( snap ) );
    goto done;
  }

  r = TEST_PASS;

done:
  libspectrum_snap_free( snap );
  return r;
}

test_return_t
test_100( void )
{
  /* libspectrum_snap: DivIDE interface flags getter/setter */
  libspectrum_snap *snap = libspectrum_snap_alloc();
  test_return_t r = TEST_FAIL;

  if( !snap ) {
    fprintf( stderr, "%s: test_100: snap_alloc returned NULL\n", progname );
    return TEST_INCOMPLETE;
  }

  if( libspectrum_snap_divide_active( snap ) != 0 ) {
    fprintf( stderr, "%s: test_100: default divide_active should be 0, got %d\n",
             progname, libspectrum_snap_divide_active( snap ) );
    goto done;
  }

  libspectrum_snap_set_divide_active( snap, 1 );
  if( libspectrum_snap_divide_active( snap ) != 1 ) {
    fprintf( stderr, "%s: test_100: expected divide_active=1, got %d\n",
             progname, libspectrum_snap_divide_active( snap ) );
    goto done;
  }

  if( libspectrum_snap_divide_eprom_writeprotect( snap ) != 0 ) {
    fprintf( stderr, "%s: test_100: default divide_eprom_writeprotect should be 0, got %d\n",
             progname, libspectrum_snap_divide_eprom_writeprotect( snap ) );
    goto done;
  }

  libspectrum_snap_set_divide_eprom_writeprotect( snap, 1 );
  if( libspectrum_snap_divide_eprom_writeprotect( snap ) != 1 ) {
    fprintf( stderr, "%s: test_100: expected divide_eprom_writeprotect=1, got %d\n",
             progname, libspectrum_snap_divide_eprom_writeprotect( snap ) );
    goto done;
  }

  if( libspectrum_snap_divide_paged( snap ) != 0 ) {
    fprintf( stderr, "%s: test_100: default divide_paged should be 0, got %d\n",
             progname, libspectrum_snap_divide_paged( snap ) );
    goto done;
  }

  libspectrum_snap_set_divide_paged( snap, 1 );
  if( libspectrum_snap_divide_paged( snap ) != 1 ) {
    fprintf( stderr, "%s: test_100: expected divide_paged=1, got %d\n",
             progname, libspectrum_snap_divide_paged( snap ) );
    goto done;
  }

  if( libspectrum_snap_divide_control( snap ) != 0 ) {
    fprintf( stderr, "%s: test_100: default divide_control should be 0, got 0x%02x\n",
             progname, libspectrum_snap_divide_control( snap ) );
    goto done;
  }

  libspectrum_snap_set_divide_control( snap, 0xa3 );
  if( libspectrum_snap_divide_control( snap ) != 0xa3 ) {
    fprintf( stderr, "%s: test_100: expected divide_control=0xa3, got 0x%02x\n",
             progname, libspectrum_snap_divide_control( snap ) );
    goto done;
  }

  r = TEST_PASS;

done:
  libspectrum_snap_free( snap );
  return r;
}

test_return_t
test_101( void )
{
  /* libspectrum_snap: SpecDrum active flag and DAC getter/setter */
  libspectrum_snap *snap = libspectrum_snap_alloc();
  test_return_t r = TEST_FAIL;

  if( !snap ) {
    fprintf( stderr, "%s: test_101: snap_alloc returned NULL\n", progname );
    return TEST_INCOMPLETE;
  }

  if( libspectrum_snap_specdrum_active( snap ) != 0 ) {
    fprintf( stderr, "%s: test_101: default specdrum_active should be 0, got %d\n",
             progname, libspectrum_snap_specdrum_active( snap ) );
    goto done;
  }

  libspectrum_snap_set_specdrum_active( snap, 1 );
  if( libspectrum_snap_specdrum_active( snap ) != 1 ) {
    fprintf( stderr, "%s: test_101: expected specdrum_active=1, got %d\n",
             progname, libspectrum_snap_specdrum_active( snap ) );
    goto done;
  }

  if( libspectrum_snap_specdrum_dac( snap ) != 0 ) {
    fprintf( stderr, "%s: test_101: default specdrum_dac should be 0, got %d\n",
             progname, (int)libspectrum_snap_specdrum_dac( snap ) );
    goto done;
  }

  libspectrum_snap_set_specdrum_dac( snap, -42 );
  if( libspectrum_snap_specdrum_dac( snap ) != -42 ) {
    fprintf( stderr, "%s: test_101: expected specdrum_dac=-42, got %d\n",
             progname, (int)libspectrum_snap_specdrum_dac( snap ) );
    goto done;
  }

  libspectrum_snap_set_specdrum_dac( snap, 100 );
  if( libspectrum_snap_specdrum_dac( snap ) != 100 ) {
    fprintf( stderr, "%s: test_101: expected specdrum_dac=100, got %d\n",
             progname, (int)libspectrum_snap_specdrum_dac( snap ) );
    goto done;
  }

  r = TEST_PASS;

done:
  libspectrum_snap_free( snap );
  return r;
}

test_return_t
test_102( void )
{
  /* libspectrum_snap: Fuller Box active flag getter/setter */
  libspectrum_snap *snap = libspectrum_snap_alloc();
  test_return_t r = TEST_FAIL;

  if( !snap ) {
    fprintf( stderr, "%s: test_102: snap_alloc returned NULL\n", progname );
    return TEST_INCOMPLETE;
  }

  if( libspectrum_snap_fuller_box_active( snap ) != 0 ) {
    fprintf( stderr, "%s: test_102: default fuller_box_active should be 0, got %d\n",
             progname, libspectrum_snap_fuller_box_active( snap ) );
    goto done;
  }

  libspectrum_snap_set_fuller_box_active( snap, 1 );
  if( libspectrum_snap_fuller_box_active( snap ) != 1 ) {
    fprintf( stderr, "%s: test_102: expected fuller_box_active=1, got %d\n",
             progname, libspectrum_snap_fuller_box_active( snap ) );
    goto done;
  }

  libspectrum_snap_set_fuller_box_active( snap, 0 );
  if( libspectrum_snap_fuller_box_active( snap ) != 0 ) {
    fprintf( stderr, "%s: test_102: expected fuller_box_active=0, got %d\n",
             progname, libspectrum_snap_fuller_box_active( snap ) );
    goto done;
  }

  r = TEST_PASS;

done:
  libspectrum_snap_free( snap );
  return r;
}

test_return_t
test_103( void )
{
  /* libspectrum_snap: Multiface interface flags getter/setter */
  libspectrum_snap *snap = libspectrum_snap_alloc();
  test_return_t r = TEST_FAIL;

  if( !snap ) {
    fprintf( stderr, "%s: test_103: snap_alloc returned NULL\n", progname );
    return TEST_INCOMPLETE;
  }

  if( libspectrum_snap_multiface_active( snap ) != 0 ) {
    fprintf( stderr, "%s: test_103: default multiface_active should be 0, got %d\n",
             progname, libspectrum_snap_multiface_active( snap ) );
    goto done;
  }

  libspectrum_snap_set_multiface_active( snap, 1 );
  if( libspectrum_snap_multiface_active( snap ) != 1 ) {
    fprintf( stderr, "%s: test_103: expected multiface_active=1, got %d\n",
             progname, libspectrum_snap_multiface_active( snap ) );
    goto done;
  }

  if( libspectrum_snap_multiface_paged( snap ) != 0 ) {
    fprintf( stderr, "%s: test_103: default multiface_paged should be 0, got %d\n",
             progname, libspectrum_snap_multiface_paged( snap ) );
    goto done;
  }

  libspectrum_snap_set_multiface_paged( snap, 1 );
  if( libspectrum_snap_multiface_paged( snap ) != 1 ) {
    fprintf( stderr, "%s: test_103: expected multiface_paged=1, got %d\n",
             progname, libspectrum_snap_multiface_paged( snap ) );
    goto done;
  }

  if( libspectrum_snap_multiface_model_one( snap ) != 0 ) {
    fprintf( stderr, "%s: test_103: default multiface_model_one should be 0, got %d\n",
             progname, libspectrum_snap_multiface_model_one( snap ) );
    goto done;
  }

  libspectrum_snap_set_multiface_model_one( snap, 1 );
  if( libspectrum_snap_multiface_model_one( snap ) != 1 ) {
    fprintf( stderr, "%s: test_103: expected multiface_model_one=1, got %d\n",
             progname, libspectrum_snap_multiface_model_one( snap ) );
    goto done;
  }

  if( libspectrum_snap_multiface_model_128( snap ) != 0 ) {
    fprintf( stderr, "%s: test_103: default multiface_model_128 should be 0, got %d\n",
             progname, libspectrum_snap_multiface_model_128( snap ) );
    goto done;
  }

  libspectrum_snap_set_multiface_model_128( snap, 1 );
  if( libspectrum_snap_multiface_model_128( snap ) != 1 ) {
    fprintf( stderr, "%s: test_103: expected multiface_model_128=1, got %d\n",
             progname, libspectrum_snap_multiface_model_128( snap ) );
    goto done;
  }

  if( libspectrum_snap_multiface_disabled( snap ) != 0 ) {
    fprintf( stderr, "%s: test_103: default multiface_disabled should be 0, got %d\n",
             progname, libspectrum_snap_multiface_disabled( snap ) );
    goto done;
  }

  libspectrum_snap_set_multiface_disabled( snap, 1 );
  if( libspectrum_snap_multiface_disabled( snap ) != 1 ) {
    fprintf( stderr, "%s: test_103: expected multiface_disabled=1, got %d\n",
             progname, libspectrum_snap_multiface_disabled( snap ) );
    goto done;
  }

  if( libspectrum_snap_multiface_software_lockout( snap ) != 0 ) {
    fprintf( stderr, "%s: test_103: default multiface_software_lockout should be 0, got %d\n",
             progname, libspectrum_snap_multiface_software_lockout( snap ) );
    goto done;
  }

  libspectrum_snap_set_multiface_software_lockout( snap, 1 );
  if( libspectrum_snap_multiface_software_lockout( snap ) != 1 ) {
    fprintf( stderr, "%s: test_103: expected multiface_software_lockout=1, got %d\n",
             progname, libspectrum_snap_multiface_software_lockout( snap ) );
    goto done;
  }

  r = TEST_PASS;

done:
  libspectrum_snap_free( snap );
  return r;
}

test_return_t
test_104( void )
{
  /* libspectrum_snap: ay_registers array getter/setter */
  libspectrum_snap *snap = libspectrum_snap_alloc();
  test_return_t r = TEST_FAIL;
  int i;

  if( !snap ) {
    fprintf( stderr, "%s: test_104: snap_alloc returned NULL\n", progname );
    return TEST_INCOMPLETE;
  }

  /* Default: all 16 AY registers should be zero */
  for( i = 0; i < 16; i++ ) {
    if( libspectrum_snap_ay_registers( snap, i ) != 0 ) {
      fprintf( stderr, "%s: test_104: default ay_registers[%d] should be 0, got %d\n",
               progname, i, libspectrum_snap_ay_registers( snap, i ) );
      goto done;
    }
  }

  /* Set each register to a unique value and verify round-trip */
  for( i = 0; i < 16; i++ )
    libspectrum_snap_set_ay_registers( snap, i, (libspectrum_byte)(i + 1) );

  for( i = 0; i < 16; i++ ) {
    if( libspectrum_snap_ay_registers( snap, i ) != (libspectrum_byte)(i + 1) ) {
      fprintf( stderr, "%s: test_104: expected ay_registers[%d]=%d, got %d\n",
               progname, i, i + 1, libspectrum_snap_ay_registers( snap, i ) );
      goto done;
    }
  }

  r = TEST_PASS;

done:
  libspectrum_snap_free( snap );
  return r;
}

test_return_t
test_105( void )
{
  /* libspectrum_snap: beta disk interface getter/setter */
  libspectrum_snap *snap = libspectrum_snap_alloc();
  test_return_t r = TEST_FAIL;

  if( !snap ) {
    fprintf( stderr, "%s: test_105: snap_alloc returned NULL\n", progname );
    return TEST_INCOMPLETE;
  }

  if( libspectrum_snap_beta_active( snap ) != 0 ) {
    fprintf( stderr, "%s: test_105: default beta_active should be 0, got %d\n",
             progname, libspectrum_snap_beta_active( snap ) );
    goto done;
  }
  libspectrum_snap_set_beta_active( snap, 1 );
  if( libspectrum_snap_beta_active( snap ) != 1 ) {
    fprintf( stderr, "%s: test_105: expected beta_active=1, got %d\n",
             progname, libspectrum_snap_beta_active( snap ) );
    goto done;
  }

  if( libspectrum_snap_beta_paged( snap ) != 0 ) {
    fprintf( stderr, "%s: test_105: default beta_paged should be 0, got %d\n",
             progname, libspectrum_snap_beta_paged( snap ) );
    goto done;
  }
  libspectrum_snap_set_beta_paged( snap, 1 );
  if( libspectrum_snap_beta_paged( snap ) != 1 ) {
    fprintf( stderr, "%s: test_105: expected beta_paged=1, got %d\n",
             progname, libspectrum_snap_beta_paged( snap ) );
    goto done;
  }

  if( libspectrum_snap_beta_autoboot( snap ) != 0 ) {
    fprintf( stderr, "%s: test_105: default beta_autoboot should be 0, got %d\n",
             progname, libspectrum_snap_beta_autoboot( snap ) );
    goto done;
  }
  libspectrum_snap_set_beta_autoboot( snap, 1 );
  if( libspectrum_snap_beta_autoboot( snap ) != 1 ) {
    fprintf( stderr, "%s: test_105: expected beta_autoboot=1, got %d\n",
             progname, libspectrum_snap_beta_autoboot( snap ) );
    goto done;
  }

  if( libspectrum_snap_beta_drive_count( snap ) != 0 ) {
    fprintf( stderr, "%s: test_105: default beta_drive_count should be 0, got %d\n",
             progname, libspectrum_snap_beta_drive_count( snap ) );
    goto done;
  }
  libspectrum_snap_set_beta_drive_count( snap, 4 );
  if( libspectrum_snap_beta_drive_count( snap ) != 4 ) {
    fprintf( stderr, "%s: test_105: expected beta_drive_count=4, got %d\n",
             progname, libspectrum_snap_beta_drive_count( snap ) );
    goto done;
  }

  r = TEST_PASS;

done:
  libspectrum_snap_free( snap );
  return r;
}

test_return_t
test_106( void )
{
  /* libspectrum_snap: ZXATASP active/upload/writeprotect getter/setter */
  libspectrum_snap *snap = libspectrum_snap_alloc();
  test_return_t r = TEST_FAIL;

  if( !snap ) {
    fprintf( stderr, "%s: test_106: snap_alloc returned NULL\n", progname );
    return TEST_INCOMPLETE;
  }

  if( libspectrum_snap_zxatasp_active( snap ) != 0 ) {
    fprintf( stderr, "%s: test_106: default zxatasp_active should be 0, got %d\n",
             progname, libspectrum_snap_zxatasp_active( snap ) );
    goto done;
  }
  libspectrum_snap_set_zxatasp_active( snap, 1 );
  if( libspectrum_snap_zxatasp_active( snap ) != 1 ) {
    fprintf( stderr, "%s: test_106: expected zxatasp_active=1, got %d\n",
             progname, libspectrum_snap_zxatasp_active( snap ) );
    goto done;
  }

  if( libspectrum_snap_zxatasp_upload( snap ) != 0 ) {
    fprintf( stderr, "%s: test_106: default zxatasp_upload should be 0, got %d\n",
             progname, libspectrum_snap_zxatasp_upload( snap ) );
    goto done;
  }
  libspectrum_snap_set_zxatasp_upload( snap, 1 );
  if( libspectrum_snap_zxatasp_upload( snap ) != 1 ) {
    fprintf( stderr, "%s: test_106: expected zxatasp_upload=1, got %d\n",
             progname, libspectrum_snap_zxatasp_upload( snap ) );
    goto done;
  }

  if( libspectrum_snap_zxatasp_writeprotect( snap ) != 0 ) {
    fprintf( stderr, "%s: test_106: default zxatasp_writeprotect should be 0, got %d\n",
             progname, libspectrum_snap_zxatasp_writeprotect( snap ) );
    goto done;
  }
  libspectrum_snap_set_zxatasp_writeprotect( snap, 1 );
  if( libspectrum_snap_zxatasp_writeprotect( snap ) != 1 ) {
    fprintf( stderr, "%s: test_106: expected zxatasp_writeprotect=1, got %d\n",
             progname, libspectrum_snap_zxatasp_writeprotect( snap ) );
    goto done;
  }

  r = TEST_PASS;

done:
  libspectrum_snap_free( snap );
  return r;
}

test_return_t
test_107( void )
{
  /* libspectrum_snap: ZXATASP port_a/b/c and control getter/setter */
  libspectrum_snap *snap = libspectrum_snap_alloc();
  test_return_t r = TEST_FAIL;

  if( !snap ) {
    fprintf( stderr, "%s: test_107: snap_alloc returned NULL\n", progname );
    return TEST_INCOMPLETE;
  }

  if( libspectrum_snap_zxatasp_port_a( snap ) != 0 ) {
    fprintf( stderr, "%s: test_107: default zxatasp_port_a should be 0, got 0x%02x\n",
             progname, libspectrum_snap_zxatasp_port_a( snap ) );
    goto done;
  }
  libspectrum_snap_set_zxatasp_port_a( snap, 0xaa );
  if( libspectrum_snap_zxatasp_port_a( snap ) != 0xaa ) {
    fprintf( stderr, "%s: test_107: expected zxatasp_port_a=0xaa, got 0x%02x\n",
             progname, libspectrum_snap_zxatasp_port_a( snap ) );
    goto done;
  }

  if( libspectrum_snap_zxatasp_port_b( snap ) != 0 ) {
    fprintf( stderr, "%s: test_107: default zxatasp_port_b should be 0, got 0x%02x\n",
             progname, libspectrum_snap_zxatasp_port_b( snap ) );
    goto done;
  }
  libspectrum_snap_set_zxatasp_port_b( snap, 0xbb );
  if( libspectrum_snap_zxatasp_port_b( snap ) != 0xbb ) {
    fprintf( stderr, "%s: test_107: expected zxatasp_port_b=0xbb, got 0x%02x\n",
             progname, libspectrum_snap_zxatasp_port_b( snap ) );
    goto done;
  }

  if( libspectrum_snap_zxatasp_port_c( snap ) != 0 ) {
    fprintf( stderr, "%s: test_107: default zxatasp_port_c should be 0, got 0x%02x\n",
             progname, libspectrum_snap_zxatasp_port_c( snap ) );
    goto done;
  }
  libspectrum_snap_set_zxatasp_port_c( snap, 0xcc );
  if( libspectrum_snap_zxatasp_port_c( snap ) != 0xcc ) {
    fprintf( stderr, "%s: test_107: expected zxatasp_port_c=0xcc, got 0x%02x\n",
             progname, libspectrum_snap_zxatasp_port_c( snap ) );
    goto done;
  }

  if( libspectrum_snap_zxatasp_control( snap ) != 0 ) {
    fprintf( stderr, "%s: test_107: default zxatasp_control should be 0, got 0x%02x\n",
             progname, libspectrum_snap_zxatasp_control( snap ) );
    goto done;
  }
  libspectrum_snap_set_zxatasp_control( snap, 0x9b );
  if( libspectrum_snap_zxatasp_control( snap ) != 0x9b ) {
    fprintf( stderr, "%s: test_107: expected zxatasp_control=0x9b, got 0x%02x\n",
             progname, libspectrum_snap_zxatasp_control( snap ) );
    goto done;
  }

  r = TEST_PASS;

done:
  libspectrum_snap_free( snap );
  return r;
}

test_return_t
test_108( void )
{
  /* libspectrum_snap: ZXATASP pages and current_page getter/setter */
  libspectrum_snap *snap = libspectrum_snap_alloc();
  test_return_t r = TEST_FAIL;

  if( !snap ) {
    fprintf( stderr, "%s: test_108: snap_alloc returned NULL\n", progname );
    return TEST_INCOMPLETE;
  }

  if( libspectrum_snap_zxatasp_pages( snap ) != 0 ) {
    fprintf( stderr, "%s: test_108: default zxatasp_pages should be 0, got %zu\n",
             progname, libspectrum_snap_zxatasp_pages( snap ) );
    goto done;
  }
  libspectrum_snap_set_zxatasp_pages( snap, 8 );
  if( libspectrum_snap_zxatasp_pages( snap ) != 8 ) {
    fprintf( stderr, "%s: test_108: expected zxatasp_pages=8, got %zu\n",
             progname, libspectrum_snap_zxatasp_pages( snap ) );
    goto done;
  }

  if( libspectrum_snap_zxatasp_current_page( snap ) != 0 ) {
    fprintf( stderr, "%s: test_108: default zxatasp_current_page should be 0, got %zu\n",
             progname, libspectrum_snap_zxatasp_current_page( snap ) );
    goto done;
  }
  libspectrum_snap_set_zxatasp_current_page( snap, 5 );
  if( libspectrum_snap_zxatasp_current_page( snap ) != 5 ) {
    fprintf( stderr, "%s: test_108: expected zxatasp_current_page=5, got %zu\n",
             progname, libspectrum_snap_zxatasp_current_page( snap ) );
    goto done;
  }

  r = TEST_PASS;

done:
  libspectrum_snap_free( snap );
  return r;
}

test_return_t
test_110( void )
{
  /* libspectrum_snap: DivIDE pages count and divide_eprom single-pointer */
  libspectrum_snap *snap = libspectrum_snap_alloc();
  libspectrum_byte *eprom;
  test_return_t r = TEST_FAIL;

  if( !snap ) {
    fprintf( stderr, "%s: test_110: snap_alloc returned NULL\n", progname );
    return TEST_INCOMPLETE;
  }

  if( libspectrum_snap_divide_pages( snap ) != 0 ) {
    fprintf( stderr, "%s: test_110: default divide_pages should be 0, got %zu\n",
             progname, libspectrum_snap_divide_pages( snap ) );
    goto done;
  }
  libspectrum_snap_set_divide_pages( snap, 3 );
  if( libspectrum_snap_divide_pages( snap ) != 3 ) {
    fprintf( stderr, "%s: test_110: expected divide_pages=3, got %zu\n",
             progname, libspectrum_snap_divide_pages( snap ) );
    goto done;
  }

  if( libspectrum_snap_divide_eprom( snap, 0 ) != NULL ) {
    fprintf( stderr, "%s: test_110: default divide_eprom[0] should be NULL\n", progname );
    goto done;
  }

  eprom = libspectrum_new( libspectrum_byte, 0x2000 );
  eprom[0]      = 0xde;
  eprom[0x1fff] = 0xad;

  libspectrum_snap_set_divide_eprom( snap, 0, eprom );
  if( libspectrum_snap_divide_eprom( snap, 0 ) != eprom ) {
    fprintf( stderr, "%s: test_110: divide_eprom[0] pointer mismatch after set\n", progname );
    libspectrum_free( eprom );
    goto done;
  }
  if( libspectrum_snap_divide_eprom( snap, 0 )[0]      != 0xde ||
      libspectrum_snap_divide_eprom( snap, 0 )[0x1fff] != 0xad ) {
    fprintf( stderr, "%s: test_110: divide_eprom[0] data mismatch\n", progname );
    goto done;
  }

  r = TEST_PASS;

done:
  libspectrum_snap_free( snap );
  return r;
}

test_return_t
test_111( void )
{
  /* libspectrum_snap: DivIDE RAM page pointer array (SNAPSHOT_DIVIDE_PAGES pages) */
  libspectrum_snap *snap = libspectrum_snap_alloc();
  libspectrum_byte *page0, *page1;
  test_return_t r = TEST_FAIL;

  if( !snap ) {
    fprintf( stderr, "%s: test_111: snap_alloc returned NULL\n", progname );
    return TEST_INCOMPLETE;
  }

  if( libspectrum_snap_divide_ram( snap, 0 ) != NULL ) {
    fprintf( stderr, "%s: test_111: default divide_ram[0] should be NULL\n", progname );
    goto done;
  }

  page0 = libspectrum_new( libspectrum_byte, 0x2000 );
  page0[0]      = 0x11;
  page0[0x1fff] = 0x22;

  libspectrum_snap_set_divide_ram( snap, 0, page0 );
  if( libspectrum_snap_divide_ram( snap, 0 ) != page0 ) {
    fprintf( stderr, "%s: test_111: divide_ram[0] pointer mismatch after set\n", progname );
    libspectrum_free( page0 );
    goto done;
  }
  if( libspectrum_snap_divide_ram( snap, 0 )[0]      != 0x11 ||
      libspectrum_snap_divide_ram( snap, 0 )[0x1fff] != 0x22 ) {
    fprintf( stderr, "%s: test_111: divide_ram[0] data mismatch\n", progname );
    goto done;
  }

  page1 = libspectrum_new( libspectrum_byte, 0x2000 );
  page1[0] = 0x33;
  libspectrum_snap_set_divide_ram( snap, 1, page1 );

  if( libspectrum_snap_divide_ram( snap, 2 ) != NULL ) {
    fprintf( stderr, "%s: test_111: divide_ram[2] should still be NULL\n", progname );
    goto done;
  }

  r = TEST_PASS;

done:
  libspectrum_snap_free( snap );
  return r;
}

test_return_t
test_112( void )
{
  /* libspectrum_snap: DivMMC flags (active, eprom_writeprotect, paged, control) */
  libspectrum_snap *snap = libspectrum_snap_alloc();
  test_return_t r = TEST_FAIL;

  if( !snap ) {
    fprintf( stderr, "%s: test_112: snap_alloc returned NULL\n", progname );
    return TEST_INCOMPLETE;
  }

  if( libspectrum_snap_divmmc_active( snap ) != 0 ) {
    fprintf( stderr, "%s: test_112: default divmmc_active should be 0, got %d\n",
             progname, libspectrum_snap_divmmc_active( snap ) );
    goto done;
  }
  libspectrum_snap_set_divmmc_active( snap, 1 );
  if( libspectrum_snap_divmmc_active( snap ) != 1 ) {
    fprintf( stderr, "%s: test_112: expected divmmc_active=1, got %d\n",
             progname, libspectrum_snap_divmmc_active( snap ) );
    goto done;
  }

  if( libspectrum_snap_divmmc_eprom_writeprotect( snap ) != 0 ) {
    fprintf( stderr, "%s: test_112: default divmmc_eprom_writeprotect should be 0, got %d\n",
             progname, libspectrum_snap_divmmc_eprom_writeprotect( snap ) );
    goto done;
  }
  libspectrum_snap_set_divmmc_eprom_writeprotect( snap, 1 );
  if( libspectrum_snap_divmmc_eprom_writeprotect( snap ) != 1 ) {
    fprintf( stderr, "%s: test_112: expected divmmc_eprom_writeprotect=1, got %d\n",
             progname, libspectrum_snap_divmmc_eprom_writeprotect( snap ) );
    goto done;
  }

  if( libspectrum_snap_divmmc_paged( snap ) != 0 ) {
    fprintf( stderr, "%s: test_112: default divmmc_paged should be 0, got %d\n",
             progname, libspectrum_snap_divmmc_paged( snap ) );
    goto done;
  }
  libspectrum_snap_set_divmmc_paged( snap, 1 );
  if( libspectrum_snap_divmmc_paged( snap ) != 1 ) {
    fprintf( stderr, "%s: test_112: expected divmmc_paged=1, got %d\n",
             progname, libspectrum_snap_divmmc_paged( snap ) );
    goto done;
  }

  if( libspectrum_snap_divmmc_control( snap ) != 0x00 ) {
    fprintf( stderr, "%s: test_112: default divmmc_control should be 0, got 0x%02x\n",
             progname, libspectrum_snap_divmmc_control( snap ) );
    goto done;
  }
  libspectrum_snap_set_divmmc_control( snap, 0xc7 );
  if( libspectrum_snap_divmmc_control( snap ) != 0xc7 ) {
    fprintf( stderr, "%s: test_112: expected divmmc_control=0xc7, got 0x%02x\n",
             progname, libspectrum_snap_divmmc_control( snap ) );
    goto done;
  }

  r = TEST_PASS;

done:
  libspectrum_snap_free( snap );
  return r;
}

test_return_t
test_113( void )
{
  /* libspectrum_snap: DivMMC pages count and divmmc_eprom single-pointer */
  libspectrum_snap *snap = libspectrum_snap_alloc();
  libspectrum_byte *eprom;
  test_return_t r = TEST_FAIL;

  if( !snap ) {
    fprintf( stderr, "%s: test_113: snap_alloc returned NULL\n", progname );
    return TEST_INCOMPLETE;
  }

  if( libspectrum_snap_divmmc_pages( snap ) != 0 ) {
    fprintf( stderr, "%s: test_113: default divmmc_pages should be 0, got %zu\n",
             progname, libspectrum_snap_divmmc_pages( snap ) );
    goto done;
  }
  libspectrum_snap_set_divmmc_pages( snap, 16 );
  if( libspectrum_snap_divmmc_pages( snap ) != 16 ) {
    fprintf( stderr, "%s: test_113: expected divmmc_pages=16, got %zu\n",
             progname, libspectrum_snap_divmmc_pages( snap ) );
    goto done;
  }

  if( libspectrum_snap_divmmc_eprom( snap, 0 ) != NULL ) {
    fprintf( stderr, "%s: test_113: default divmmc_eprom[0] should be NULL\n", progname );
    goto done;
  }

  eprom = libspectrum_new( libspectrum_byte, 0x4000 );
  eprom[0]      = 0xbe;
  eprom[0x3fff] = 0xef;

  libspectrum_snap_set_divmmc_eprom( snap, 0, eprom );
  if( libspectrum_snap_divmmc_eprom( snap, 0 ) != eprom ) {
    fprintf( stderr, "%s: test_113: divmmc_eprom[0] pointer mismatch after set\n", progname );
    libspectrum_free( eprom );
    goto done;
  }
  if( libspectrum_snap_divmmc_eprom( snap, 0 )[0]      != 0xbe ||
      libspectrum_snap_divmmc_eprom( snap, 0 )[0x3fff] != 0xef ) {
    fprintf( stderr, "%s: test_113: divmmc_eprom[0] data mismatch\n", progname );
    goto done;
  }

  r = TEST_PASS;

done:
  libspectrum_snap_free( snap );
  return r;
}

/* Test that PZX archive info tags (title + author) are correctly parsed.
   Regression test for the pzx_read_string bug where *ptr was set to end,
   causing all tag-value pairs after the title to be silently ignored. */
test_return_t
test_109( void )
{
  const char *filename = STATIC_TEST_PATH( "pzx-archive-info-tags.pzx" );
  libspectrum_tape *tape = NULL;
  libspectrum_tape_iterator it;
  libspectrum_tape_block *block;
  test_return_t r = TEST_INCOMPLETE;

  if( load_tape( &tape, filename, LIBSPECTRUM_ERROR_NONE ) ) return TEST_INCOMPLETE;

  /* Find the ARCHIVE_INFO block */
  for( block = libspectrum_tape_iterator_init( &it, tape );
       block;
       block = libspectrum_tape_iterator_next( &it ) ) {
    if( libspectrum_tape_block_type( block ) == LIBSPECTRUM_TAPE_BLOCK_ARCHIVE_INFO )
      break;
  }

  if( !block ) {
    fprintf( stderr, "%s: test_104: no ARCHIVE_INFO block found\n", progname );
    goto done;
  }

  /* Expect: title (ID 0x00, "Test Game") and Author (ID 0x02, "Joe Bloggs") */
  if( libspectrum_tape_block_count( block ) != 2 ) {
    fprintf( stderr, "%s: test_104: expected 2 archive info entries, got %zu\n",
             progname, libspectrum_tape_block_count( block ) );
    r = TEST_FAIL;
    goto done;
  }

  if( libspectrum_tape_block_ids( block, 0 ) != 0x00 ) {
    fprintf( stderr, "%s: test_104: expected ID 0x00 for entry 0, got 0x%02x\n",
             progname, libspectrum_tape_block_ids( block, 0 ) );
    r = TEST_FAIL;
    goto done;
  }

  if( strcmp( libspectrum_tape_block_texts( block, 0 ), "Test Game" ) != 0 ) {
    fprintf( stderr, "%s: test_104: expected title 'Test Game', got '%s'\n",
             progname, libspectrum_tape_block_texts( block, 0 ) );
    r = TEST_FAIL;
    goto done;
  }

  if( libspectrum_tape_block_ids( block, 1 ) != 0x02 ) {
    fprintf( stderr, "%s: test_104: expected ID 0x02 (Author) for entry 1, got 0x%02x\n",
             progname, libspectrum_tape_block_ids( block, 1 ) );
    r = TEST_FAIL;
    goto done;
  }

  if( strcmp( libspectrum_tape_block_texts( block, 1 ), "Joe Bloggs" ) != 0 ) {
    fprintf( stderr, "%s: test_104: expected author 'Joe Bloggs', got '%s'\n",
             progname, libspectrum_tape_block_texts( block, 1 ) );
    r = TEST_FAIL;
    goto done;
  }

  r = TEST_PASS;

done:
  libspectrum_tape_free( tape );
  return r;
}

test_return_t
test_114( void )
{
  /* libspectrum_snap: Plus D active, paged, drive_count, custom_rom, direction */
  libspectrum_snap *snap = libspectrum_snap_alloc();
  test_return_t r = TEST_FAIL;

  if( !snap ) {
    fprintf( stderr, "%s: test_114: snap_alloc returned NULL\n", progname );
    return TEST_INCOMPLETE;
  }

  if( libspectrum_snap_plusd_active( snap ) != 0 ) {
    fprintf( stderr, "%s: test_114: default plusd_active should be 0, got %d\n",
             progname, libspectrum_snap_plusd_active( snap ) );
    goto done;
  }
  libspectrum_snap_set_plusd_active( snap, 1 );
  if( libspectrum_snap_plusd_active( snap ) != 1 ) {
    fprintf( stderr, "%s: test_114: expected plusd_active=1, got %d\n",
             progname, libspectrum_snap_plusd_active( snap ) );
    goto done;
  }

  if( libspectrum_snap_plusd_paged( snap ) != 0 ) {
    fprintf( stderr, "%s: test_114: default plusd_paged should be 0, got %d\n",
             progname, libspectrum_snap_plusd_paged( snap ) );
    goto done;
  }
  libspectrum_snap_set_plusd_paged( snap, 1 );
  if( libspectrum_snap_plusd_paged( snap ) != 1 ) {
    fprintf( stderr, "%s: test_114: expected plusd_paged=1, got %d\n",
             progname, libspectrum_snap_plusd_paged( snap ) );
    goto done;
  }

  if( libspectrum_snap_plusd_drive_count( snap ) != 0 ) {
    fprintf( stderr, "%s: test_114: default plusd_drive_count should be 0, got %d\n",
             progname, libspectrum_snap_plusd_drive_count( snap ) );
    goto done;
  }
  libspectrum_snap_set_plusd_drive_count( snap, 2 );
  if( libspectrum_snap_plusd_drive_count( snap ) != 2 ) {
    fprintf( stderr, "%s: test_114: expected plusd_drive_count=2, got %d\n",
             progname, libspectrum_snap_plusd_drive_count( snap ) );
    goto done;
  }

  if( libspectrum_snap_plusd_custom_rom( snap ) != 0 ) {
    fprintf( stderr, "%s: test_114: default plusd_custom_rom should be 0, got %d\n",
             progname, libspectrum_snap_plusd_custom_rom( snap ) );
    goto done;
  }
  libspectrum_snap_set_plusd_custom_rom( snap, 1 );
  if( libspectrum_snap_plusd_custom_rom( snap ) != 1 ) {
    fprintf( stderr, "%s: test_114: expected plusd_custom_rom=1, got %d\n",
             progname, libspectrum_snap_plusd_custom_rom( snap ) );
    goto done;
  }

  if( libspectrum_snap_plusd_direction( snap ) != 0 ) {
    fprintf( stderr, "%s: test_114: default plusd_direction should be 0, got %d\n",
             progname, libspectrum_snap_plusd_direction( snap ) );
    goto done;
  }
  libspectrum_snap_set_plusd_direction( snap, 1 );
  if( libspectrum_snap_plusd_direction( snap ) != 1 ) {
    fprintf( stderr, "%s: test_114: expected plusd_direction=1, got %d\n",
             progname, libspectrum_snap_plusd_direction( snap ) );
    goto done;
  }

  r = TEST_PASS;

done:
  libspectrum_snap_free( snap );
  return r;
}

test_return_t
test_115( void )
{
  /* libspectrum_snap: Plus D FDC byte registers (control, track, sector, data, status) */
  libspectrum_snap *snap = libspectrum_snap_alloc();
  test_return_t r = TEST_FAIL;

  if( !snap ) {
    fprintf( stderr, "%s: test_115: snap_alloc returned NULL\n", progname );
    return TEST_INCOMPLETE;
  }

  if( libspectrum_snap_plusd_control( snap ) != 0 ) {
    fprintf( stderr, "%s: test_115: default plusd_control should be 0, got 0x%02x\n",
             progname, libspectrum_snap_plusd_control( snap ) );
    goto done;
  }
  libspectrum_snap_set_plusd_control( snap, 0xd4 );
  if( libspectrum_snap_plusd_control( snap ) != 0xd4 ) {
    fprintf( stderr, "%s: test_115: expected plusd_control=0xd4, got 0x%02x\n",
             progname, libspectrum_snap_plusd_control( snap ) );
    goto done;
  }

  if( libspectrum_snap_plusd_track( snap ) != 0 ) {
    fprintf( stderr, "%s: test_115: default plusd_track should be 0, got %d\n",
             progname, libspectrum_snap_plusd_track( snap ) );
    goto done;
  }
  libspectrum_snap_set_plusd_track( snap, 39 );
  if( libspectrum_snap_plusd_track( snap ) != 39 ) {
    fprintf( stderr, "%s: test_115: expected plusd_track=39, got %d\n",
             progname, libspectrum_snap_plusd_track( snap ) );
    goto done;
  }

  if( libspectrum_snap_plusd_sector( snap ) != 0 ) {
    fprintf( stderr, "%s: test_115: default plusd_sector should be 0, got %d\n",
             progname, libspectrum_snap_plusd_sector( snap ) );
    goto done;
  }
  libspectrum_snap_set_plusd_sector( snap, 9 );
  if( libspectrum_snap_plusd_sector( snap ) != 9 ) {
    fprintf( stderr, "%s: test_115: expected plusd_sector=9, got %d\n",
             progname, libspectrum_snap_plusd_sector( snap ) );
    goto done;
  }

  if( libspectrum_snap_plusd_data( snap ) != 0 ) {
    fprintf( stderr, "%s: test_115: default plusd_data should be 0, got 0x%02x\n",
             progname, libspectrum_snap_plusd_data( snap ) );
    goto done;
  }
  libspectrum_snap_set_plusd_data( snap, 0x5a );
  if( libspectrum_snap_plusd_data( snap ) != 0x5a ) {
    fprintf( stderr, "%s: test_115: expected plusd_data=0x5a, got 0x%02x\n",
             progname, libspectrum_snap_plusd_data( snap ) );
    goto done;
  }

  if( libspectrum_snap_plusd_status( snap ) != 0 ) {
    fprintf( stderr, "%s: test_115: default plusd_status should be 0, got 0x%02x\n",
             progname, libspectrum_snap_plusd_status( snap ) );
    goto done;
  }
  libspectrum_snap_set_plusd_status( snap, 0x81 );
  if( libspectrum_snap_plusd_status( snap ) != 0x81 ) {
    fprintf( stderr, "%s: test_115: expected plusd_status=0x81, got 0x%02x\n",
             progname, libspectrum_snap_plusd_status( snap ) );
    goto done;
  }

  r = TEST_PASS;

done:
  libspectrum_snap_free( snap );
  return r;
}

test_return_t
test_116( void )
{
  /* libspectrum_snap: Plus D ROM and RAM single-pointer getter/setter */
  libspectrum_snap *snap = libspectrum_snap_alloc();
  libspectrum_byte *rom, *ram;
  test_return_t r = TEST_FAIL;

  if( !snap ) {
    fprintf( stderr, "%s: test_116: snap_alloc returned NULL\n", progname );
    return TEST_INCOMPLETE;
  }

  if( libspectrum_snap_plusd_rom( snap, 0 ) != NULL ) {
    fprintf( stderr, "%s: test_116: default plusd_rom[0] should be NULL\n", progname );
    goto done;
  }

  rom = libspectrum_new( libspectrum_byte, 0x2000 );
  rom[0]      = 0xc3;
  rom[0x1fff] = 0xff;

  libspectrum_snap_set_plusd_rom( snap, 0, rom );
  if( libspectrum_snap_plusd_rom( snap, 0 ) != rom ) {
    fprintf( stderr, "%s: test_116: plusd_rom[0] pointer mismatch after set\n", progname );
    libspectrum_free( rom );
    goto done;
  }
  if( libspectrum_snap_plusd_rom( snap, 0 )[0]      != 0xc3 ||
      libspectrum_snap_plusd_rom( snap, 0 )[0x1fff] != 0xff ) {
    fprintf( stderr, "%s: test_116: plusd_rom[0] data mismatch\n", progname );
    goto done;
  }

  if( libspectrum_snap_plusd_ram( snap, 0 ) != NULL ) {
    fprintf( stderr, "%s: test_116: default plusd_ram[0] should be NULL\n", progname );
    goto done;
  }

  ram = libspectrum_new( libspectrum_byte, 0x2000 );
  ram[0]      = 0x11;
  ram[0x1fff] = 0x22;

  libspectrum_snap_set_plusd_ram( snap, 0, ram );
  if( libspectrum_snap_plusd_ram( snap, 0 ) != ram ) {
    fprintf( stderr, "%s: test_116: plusd_ram[0] pointer mismatch after set\n", progname );
    libspectrum_free( ram );
    goto done;
  }
  if( libspectrum_snap_plusd_ram( snap, 0 )[0]      != 0x11 ||
      libspectrum_snap_plusd_ram( snap, 0 )[0x1fff] != 0x22 ) {
    fprintf( stderr, "%s: test_116: plusd_ram[0] data mismatch\n", progname );
    goto done;
  }

  r = TEST_PASS;

done:
  libspectrum_snap_free( snap );
  return r;
}

test_return_t
test_117( void )
{
  /* libspectrum_snap: ZXATASP RAM page pointer array (SNAPSHOT_ZXATASP_PAGES pages) */
  libspectrum_snap *snap = libspectrum_snap_alloc();
  libspectrum_byte *page0, *page1;
  test_return_t r = TEST_FAIL;

  if( !snap ) {
    fprintf( stderr, "%s: test_117: snap_alloc returned NULL\n", progname );
    return TEST_INCOMPLETE;
  }

  if( libspectrum_snap_zxatasp_ram( snap, 0 ) != NULL ) {
    fprintf( stderr, "%s: test_117: default zxatasp_ram[0] should be NULL\n", progname );
    goto done;
  }

  page0 = libspectrum_new( libspectrum_byte, 0x4000 );
  page0[0]      = 0x11;
  page0[0x3fff] = 0x22;

  libspectrum_snap_set_zxatasp_ram( snap, 0, page0 );
  if( libspectrum_snap_zxatasp_ram( snap, 0 ) != page0 ) {
    fprintf( stderr, "%s: test_117: zxatasp_ram[0] pointer mismatch after set\n", progname );
    libspectrum_free( page0 );
    goto done;
  }
  if( libspectrum_snap_zxatasp_ram( snap, 0 )[0]      != 0x11 ||
      libspectrum_snap_zxatasp_ram( snap, 0 )[0x3fff] != 0x22 ) {
    fprintf( stderr, "%s: test_117: zxatasp_ram[0] data mismatch\n", progname );
    goto done;
  }

  page1 = libspectrum_new( libspectrum_byte, 0x4000 );
  page1[0] = 0x33;
  libspectrum_snap_set_zxatasp_ram( snap, 1, page1 );

  if( libspectrum_snap_zxatasp_ram( snap, 2 ) != NULL ) {
    fprintf( stderr, "%s: test_117: zxatasp_ram[2] should still be NULL\n", progname );
    goto done;
  }

  r = TEST_PASS;

done:
  libspectrum_snap_free( snap );
  return r;
}

test_return_t
test_118( void )
{
  /* libspectrum_snap: Opus Discovery int flags getter/setter */
  libspectrum_snap *snap = libspectrum_snap_alloc();
  test_return_t r = TEST_FAIL;

  if( !snap ) {
    fprintf( stderr, "%s: test_118: snap_alloc returned NULL\n", progname );
    return TEST_INCOMPLETE;
  }

  if( libspectrum_snap_opus_active( snap ) != 0 ) {
    fprintf( stderr, "%s: test_118: default opus_active should be 0, got %d\n",
             progname, libspectrum_snap_opus_active( snap ) );
    goto done;
  }
  libspectrum_snap_set_opus_active( snap, 1 );
  if( libspectrum_snap_opus_active( snap ) != 1 ) {
    fprintf( stderr, "%s: test_118: expected opus_active=1, got %d\n",
             progname, libspectrum_snap_opus_active( snap ) );
    goto done;
  }

  if( libspectrum_snap_opus_paged( snap ) != 0 ) {
    fprintf( stderr, "%s: test_118: default opus_paged should be 0, got %d\n",
             progname, libspectrum_snap_opus_paged( snap ) );
    goto done;
  }
  libspectrum_snap_set_opus_paged( snap, 1 );
  if( libspectrum_snap_opus_paged( snap ) != 1 ) {
    fprintf( stderr, "%s: test_118: expected opus_paged=1, got %d\n",
             progname, libspectrum_snap_opus_paged( snap ) );
    goto done;
  }

  if( libspectrum_snap_opus_drive_count( snap ) != 0 ) {
    fprintf( stderr, "%s: test_118: default opus_drive_count should be 0, got %d\n",
             progname, libspectrum_snap_opus_drive_count( snap ) );
    goto done;
  }
  libspectrum_snap_set_opus_drive_count( snap, 2 );
  if( libspectrum_snap_opus_drive_count( snap ) != 2 ) {
    fprintf( stderr, "%s: test_118: expected opus_drive_count=2, got %d\n",
             progname, libspectrum_snap_opus_drive_count( snap ) );
    goto done;
  }

  if( libspectrum_snap_opus_custom_rom( snap ) != 0 ) {
    fprintf( stderr, "%s: test_118: default opus_custom_rom should be 0, got %d\n",
             progname, libspectrum_snap_opus_custom_rom( snap ) );
    goto done;
  }
  libspectrum_snap_set_opus_custom_rom( snap, 1 );
  if( libspectrum_snap_opus_custom_rom( snap ) != 1 ) {
    fprintf( stderr, "%s: test_118: expected opus_custom_rom=1, got %d\n",
             progname, libspectrum_snap_opus_custom_rom( snap ) );
    goto done;
  }

  if( libspectrum_snap_opus_direction( snap ) != 0 ) {
    fprintf( stderr, "%s: test_118: default opus_direction should be 0, got %d\n",
             progname, libspectrum_snap_opus_direction( snap ) );
    goto done;
  }
  libspectrum_snap_set_opus_direction( snap, 1 );
  if( libspectrum_snap_opus_direction( snap ) != 1 ) {
    fprintf( stderr, "%s: test_118: expected opus_direction=1, got %d\n",
             progname, libspectrum_snap_opus_direction( snap ) );
    goto done;
  }

  r = TEST_PASS;

done:
  libspectrum_snap_free( snap );
  return r;
}

test_return_t
test_119( void )
{
  /* libspectrum_snap: Opus Discovery FDC byte registers getter/setter */
  libspectrum_snap *snap = libspectrum_snap_alloc();
  test_return_t r = TEST_FAIL;

  if( !snap ) {
    fprintf( stderr, "%s: test_119: snap_alloc returned NULL\n", progname );
    return TEST_INCOMPLETE;
  }

  if( libspectrum_snap_opus_track( snap ) != 0 ) {
    fprintf( stderr, "%s: test_119: default opus_track should be 0, got 0x%02x\n",
             progname, libspectrum_snap_opus_track( snap ) );
    goto done;
  }
  libspectrum_snap_set_opus_track( snap, 0x12 );
  if( libspectrum_snap_opus_track( snap ) != 0x12 ) {
    fprintf( stderr, "%s: test_119: expected opus_track=0x12, got 0x%02x\n",
             progname, libspectrum_snap_opus_track( snap ) );
    goto done;
  }

  if( libspectrum_snap_opus_sector( snap ) != 0 ) {
    fprintf( stderr, "%s: test_119: default opus_sector should be 0, got 0x%02x\n",
             progname, libspectrum_snap_opus_sector( snap ) );
    goto done;
  }
  libspectrum_snap_set_opus_sector( snap, 0x34 );
  if( libspectrum_snap_opus_sector( snap ) != 0x34 ) {
    fprintf( stderr, "%s: test_119: expected opus_sector=0x34, got 0x%02x\n",
             progname, libspectrum_snap_opus_sector( snap ) );
    goto done;
  }

  if( libspectrum_snap_opus_data( snap ) != 0 ) {
    fprintf( stderr, "%s: test_119: default opus_data should be 0, got 0x%02x\n",
             progname, libspectrum_snap_opus_data( snap ) );
    goto done;
  }
  libspectrum_snap_set_opus_data( snap, 0x56 );
  if( libspectrum_snap_opus_data( snap ) != 0x56 ) {
    fprintf( stderr, "%s: test_119: expected opus_data=0x56, got 0x%02x\n",
             progname, libspectrum_snap_opus_data( snap ) );
    goto done;
  }

  if( libspectrum_snap_opus_status( snap ) != 0 ) {
    fprintf( stderr, "%s: test_119: default opus_status should be 0, got 0x%02x\n",
             progname, libspectrum_snap_opus_status( snap ) );
    goto done;
  }
  libspectrum_snap_set_opus_status( snap, 0x78 );
  if( libspectrum_snap_opus_status( snap ) != 0x78 ) {
    fprintf( stderr, "%s: test_119: expected opus_status=0x78, got 0x%02x\n",
             progname, libspectrum_snap_opus_status( snap ) );
    goto done;
  }

  if( libspectrum_snap_opus_data_reg_a( snap ) != 0 ) {
    fprintf( stderr, "%s: test_119: default opus_data_reg_a should be 0, got 0x%02x\n",
             progname, libspectrum_snap_opus_data_reg_a( snap ) );
    goto done;
  }
  libspectrum_snap_set_opus_data_reg_a( snap, 0x9a );
  if( libspectrum_snap_opus_data_reg_a( snap ) != 0x9a ) {
    fprintf( stderr, "%s: test_119: expected opus_data_reg_a=0x9a, got 0x%02x\n",
             progname, libspectrum_snap_opus_data_reg_a( snap ) );
    goto done;
  }

  if( libspectrum_snap_opus_data_dir_a( snap ) != 0 ) {
    fprintf( stderr, "%s: test_119: default opus_data_dir_a should be 0, got 0x%02x\n",
             progname, libspectrum_snap_opus_data_dir_a( snap ) );
    goto done;
  }
  libspectrum_snap_set_opus_data_dir_a( snap, 0xbc );
  if( libspectrum_snap_opus_data_dir_a( snap ) != 0xbc ) {
    fprintf( stderr, "%s: test_119: expected opus_data_dir_a=0xbc, got 0x%02x\n",
             progname, libspectrum_snap_opus_data_dir_a( snap ) );
    goto done;
  }

  if( libspectrum_snap_opus_control_a( snap ) != 0 ) {
    fprintf( stderr, "%s: test_119: default opus_control_a should be 0, got 0x%02x\n",
             progname, libspectrum_snap_opus_control_a( snap ) );
    goto done;
  }
  libspectrum_snap_set_opus_control_a( snap, 0xde );
  if( libspectrum_snap_opus_control_a( snap ) != 0xde ) {
    fprintf( stderr, "%s: test_119: expected opus_control_a=0xde, got 0x%02x\n",
             progname, libspectrum_snap_opus_control_a( snap ) );
    goto done;
  }

  if( libspectrum_snap_opus_data_reg_b( snap ) != 0 ) {
    fprintf( stderr, "%s: test_119: default opus_data_reg_b should be 0, got 0x%02x\n",
             progname, libspectrum_snap_opus_data_reg_b( snap ) );
    goto done;
  }
  libspectrum_snap_set_opus_data_reg_b( snap, 0xf0 );
  if( libspectrum_snap_opus_data_reg_b( snap ) != 0xf0 ) {
    fprintf( stderr, "%s: test_119: expected opus_data_reg_b=0xf0, got 0x%02x\n",
             progname, libspectrum_snap_opus_data_reg_b( snap ) );
    goto done;
  }

  if( libspectrum_snap_opus_data_dir_b( snap ) != 0 ) {
    fprintf( stderr, "%s: test_119: default opus_data_dir_b should be 0, got 0x%02x\n",
             progname, libspectrum_snap_opus_data_dir_b( snap ) );
    goto done;
  }
  libspectrum_snap_set_opus_data_dir_b( snap, 0x0f );
  if( libspectrum_snap_opus_data_dir_b( snap ) != 0x0f ) {
    fprintf( stderr, "%s: test_119: expected opus_data_dir_b=0x0f, got 0x%02x\n",
             progname, libspectrum_snap_opus_data_dir_b( snap ) );
    goto done;
  }

  if( libspectrum_snap_opus_control_b( snap ) != 0 ) {
    fprintf( stderr, "%s: test_119: default opus_control_b should be 0, got 0x%02x\n",
             progname, libspectrum_snap_opus_control_b( snap ) );
    goto done;
  }
  libspectrum_snap_set_opus_control_b( snap, 0xaa );
  if( libspectrum_snap_opus_control_b( snap ) != 0xaa ) {
    fprintf( stderr, "%s: test_119: expected opus_control_b=0xaa, got 0x%02x\n",
             progname, libspectrum_snap_opus_control_b( snap ) );
    goto done;
  }

  r = TEST_PASS;

done:
  libspectrum_snap_free( snap );
  return r;
}

test_return_t
test_120( void )
{
  /* libspectrum_snap: Opus Discovery ROM and RAM single-pointer getter/setter */
  libspectrum_snap *snap = libspectrum_snap_alloc();
  libspectrum_byte *rom, *ram;
  test_return_t r = TEST_FAIL;

  if( !snap ) {
    fprintf( stderr, "%s: test_120: snap_alloc returned NULL\n", progname );
    return TEST_INCOMPLETE;
  }

  if( libspectrum_snap_opus_rom( snap, 0 ) != NULL ) {
    fprintf( stderr, "%s: test_120: default opus_rom[0] should be NULL\n", progname );
    goto done;
  }

  rom = libspectrum_new( libspectrum_byte, 0x4000 );
  rom[0]      = 0x11;
  rom[0x3fff] = 0x22;

  libspectrum_snap_set_opus_rom( snap, 0, rom );
  if( libspectrum_snap_opus_rom( snap, 0 ) != rom ) {
    fprintf( stderr, "%s: test_120: opus_rom[0] pointer mismatch after set\n", progname );
    libspectrum_free( rom );
    goto done;
  }
  if( libspectrum_snap_opus_rom( snap, 0 )[0]      != 0x11 ||
      libspectrum_snap_opus_rom( snap, 0 )[0x3fff] != 0x22 ) {
    fprintf( stderr, "%s: test_120: opus_rom[0] data mismatch\n", progname );
    goto done;
  }

  if( libspectrum_snap_opus_ram( snap, 0 ) != NULL ) {
    fprintf( stderr, "%s: test_120: default opus_ram[0] should be NULL\n", progname );
    goto done;
  }

  ram = libspectrum_new( libspectrum_byte, 0x800 );
  ram[0]     = 0x33;
  ram[0x7ff] = 0x44;

  libspectrum_snap_set_opus_ram( snap, 0, ram );
  if( libspectrum_snap_opus_ram( snap, 0 ) != ram ) {
    fprintf( stderr, "%s: test_120: opus_ram[0] pointer mismatch after set\n", progname );
    libspectrum_free( ram );
    goto done;
  }
  if( libspectrum_snap_opus_ram( snap, 0 )[0]     != 0x33 ||
      libspectrum_snap_opus_ram( snap, 0 )[0x7ff] != 0x44 ) {
    fprintf( stderr, "%s: test_120: opus_ram[0] data mismatch\n", progname );
    goto done;
  }

  r = TEST_PASS;

done:
  libspectrum_snap_free( snap );
  return r;
}

test_return_t
test_121( void )
{
  /* libspectrum_snap: Spectranet boolean int flags getter/setter */
  libspectrum_snap *snap = libspectrum_snap_alloc();
  test_return_t r = TEST_FAIL;

  if( !snap ) {
    fprintf( stderr, "%s: test_121: snap_alloc returned NULL\n", progname );
    return TEST_INCOMPLETE;
  }

  if( libspectrum_snap_spectranet_active( snap ) != 0 ) {
    fprintf( stderr, "%s: test_121: default spectranet_active should be 0, got %d\n",
             progname, libspectrum_snap_spectranet_active( snap ) );
    goto done;
  }
  libspectrum_snap_set_spectranet_active( snap, 1 );
  if( libspectrum_snap_spectranet_active( snap ) != 1 ) {
    fprintf( stderr, "%s: test_121: expected spectranet_active=1, got %d\n",
             progname, libspectrum_snap_spectranet_active( snap ) );
    goto done;
  }

  if( libspectrum_snap_spectranet_paged( snap ) != 0 ) {
    fprintf( stderr, "%s: test_121: default spectranet_paged should be 0, got %d\n",
             progname, libspectrum_snap_spectranet_paged( snap ) );
    goto done;
  }
  libspectrum_snap_set_spectranet_paged( snap, 1 );
  if( libspectrum_snap_spectranet_paged( snap ) != 1 ) {
    fprintf( stderr, "%s: test_121: expected spectranet_paged=1, got %d\n",
             progname, libspectrum_snap_spectranet_paged( snap ) );
    goto done;
  }

  if( libspectrum_snap_spectranet_paged_via_io( snap ) != 0 ) {
    fprintf( stderr, "%s: test_121: default spectranet_paged_via_io should be 0, got %d\n",
             progname, libspectrum_snap_spectranet_paged_via_io( snap ) );
    goto done;
  }
  libspectrum_snap_set_spectranet_paged_via_io( snap, 1 );
  if( libspectrum_snap_spectranet_paged_via_io( snap ) != 1 ) {
    fprintf( stderr, "%s: test_121: expected spectranet_paged_via_io=1, got %d\n",
             progname, libspectrum_snap_spectranet_paged_via_io( snap ) );
    goto done;
  }

  if( libspectrum_snap_spectranet_nmi_flipflop( snap ) != 0 ) {
    fprintf( stderr, "%s: test_121: default spectranet_nmi_flipflop should be 0, got %d\n",
             progname, libspectrum_snap_spectranet_nmi_flipflop( snap ) );
    goto done;
  }
  libspectrum_snap_set_spectranet_nmi_flipflop( snap, 1 );
  if( libspectrum_snap_spectranet_nmi_flipflop( snap ) != 1 ) {
    fprintf( stderr, "%s: test_121: expected spectranet_nmi_flipflop=1, got %d\n",
             progname, libspectrum_snap_spectranet_nmi_flipflop( snap ) );
    goto done;
  }

  if( libspectrum_snap_spectranet_programmable_trap_active( snap ) != 0 ) {
    fprintf( stderr, "%s: test_121: default spectranet_programmable_trap_active should be 0, got %d\n",
             progname, libspectrum_snap_spectranet_programmable_trap_active( snap ) );
    goto done;
  }
  libspectrum_snap_set_spectranet_programmable_trap_active( snap, 1 );
  if( libspectrum_snap_spectranet_programmable_trap_active( snap ) != 1 ) {
    fprintf( stderr, "%s: test_121: expected spectranet_programmable_trap_active=1, got %d\n",
             progname, libspectrum_snap_spectranet_programmable_trap_active( snap ) );
    goto done;
  }

  if( libspectrum_snap_spectranet_programmable_trap_msb( snap ) != 0 ) {
    fprintf( stderr, "%s: test_121: default spectranet_programmable_trap_msb should be 0, got %d\n",
             progname, libspectrum_snap_spectranet_programmable_trap_msb( snap ) );
    goto done;
  }
  libspectrum_snap_set_spectranet_programmable_trap_msb( snap, 1 );
  if( libspectrum_snap_spectranet_programmable_trap_msb( snap ) != 1 ) {
    fprintf( stderr, "%s: test_121: expected spectranet_programmable_trap_msb=1, got %d\n",
             progname, libspectrum_snap_spectranet_programmable_trap_msb( snap ) );
    goto done;
  }

  if( libspectrum_snap_spectranet_all_traps_disabled( snap ) != 0 ) {
    fprintf( stderr, "%s: test_121: default spectranet_all_traps_disabled should be 0, got %d\n",
             progname, libspectrum_snap_spectranet_all_traps_disabled( snap ) );
    goto done;
  }
  libspectrum_snap_set_spectranet_all_traps_disabled( snap, 1 );
  if( libspectrum_snap_spectranet_all_traps_disabled( snap ) != 1 ) {
    fprintf( stderr, "%s: test_121: expected spectranet_all_traps_disabled=1, got %d\n",
             progname, libspectrum_snap_spectranet_all_traps_disabled( snap ) );
    goto done;
  }

  if( libspectrum_snap_spectranet_rst8_trap_disabled( snap ) != 0 ) {
    fprintf( stderr, "%s: test_121: default spectranet_rst8_trap_disabled should be 0, got %d\n",
             progname, libspectrum_snap_spectranet_rst8_trap_disabled( snap ) );
    goto done;
  }
  libspectrum_snap_set_spectranet_rst8_trap_disabled( snap, 1 );
  if( libspectrum_snap_spectranet_rst8_trap_disabled( snap ) != 1 ) {
    fprintf( stderr, "%s: test_121: expected spectranet_rst8_trap_disabled=1, got %d\n",
             progname, libspectrum_snap_spectranet_rst8_trap_disabled( snap ) );
    goto done;
  }

  if( libspectrum_snap_spectranet_deny_downstream_a15( snap ) != 0 ) {
    fprintf( stderr, "%s: test_121: default spectranet_deny_downstream_a15 should be 0, got %d\n",
             progname, libspectrum_snap_spectranet_deny_downstream_a15( snap ) );
    goto done;
  }
  libspectrum_snap_set_spectranet_deny_downstream_a15( snap, 1 );
  if( libspectrum_snap_spectranet_deny_downstream_a15( snap ) != 1 ) {
    fprintf( stderr, "%s: test_121: expected spectranet_deny_downstream_a15=1, got %d\n",
             progname, libspectrum_snap_spectranet_deny_downstream_a15( snap ) );
    goto done;
  }

  r = TEST_PASS;

done:
  libspectrum_snap_free( snap );
  return r;
}

test_return_t
test_122( void )
{
  /* libspectrum_snap: Spectranet page_a/b, programmable_trap (word), and memory pointer fields */
  libspectrum_snap *snap = libspectrum_snap_alloc();
  libspectrum_byte *w5100, *flash, *ram;
  test_return_t r = TEST_FAIL;

  if( !snap ) {
    fprintf( stderr, "%s: test_122: snap_alloc returned NULL\n", progname );
    return TEST_INCOMPLETE;
  }

  if( libspectrum_snap_spectranet_page_a( snap ) != 0 ) {
    fprintf( stderr, "%s: test_122: default spectranet_page_a should be 0, got %d\n",
             progname, libspectrum_snap_spectranet_page_a( snap ) );
    goto done;
  }
  libspectrum_snap_set_spectranet_page_a( snap, 3 );
  if( libspectrum_snap_spectranet_page_a( snap ) != 3 ) {
    fprintf( stderr, "%s: test_122: expected spectranet_page_a=3, got %d\n",
             progname, libspectrum_snap_spectranet_page_a( snap ) );
    goto done;
  }

  if( libspectrum_snap_spectranet_page_b( snap ) != 0 ) {
    fprintf( stderr, "%s: test_122: default spectranet_page_b should be 0, got %d\n",
             progname, libspectrum_snap_spectranet_page_b( snap ) );
    goto done;
  }
  libspectrum_snap_set_spectranet_page_b( snap, 7 );
  if( libspectrum_snap_spectranet_page_b( snap ) != 7 ) {
    fprintf( stderr, "%s: test_122: expected spectranet_page_b=7, got %d\n",
             progname, libspectrum_snap_spectranet_page_b( snap ) );
    goto done;
  }

  if( libspectrum_snap_spectranet_programmable_trap( snap ) != 0 ) {
    fprintf( stderr, "%s: test_122: default spectranet_programmable_trap should be 0, got 0x%04x\n",
             progname, libspectrum_snap_spectranet_programmable_trap( snap ) );
    goto done;
  }
  libspectrum_snap_set_spectranet_programmable_trap( snap, 0x1234 );
  if( libspectrum_snap_spectranet_programmable_trap( snap ) != 0x1234 ) {
    fprintf( stderr, "%s: test_122: expected spectranet_programmable_trap=0x1234, got 0x%04x\n",
             progname, libspectrum_snap_spectranet_programmable_trap( snap ) );
    goto done;
  }

  if( libspectrum_snap_spectranet_w5100( snap, 0 ) != NULL ) {
    fprintf( stderr, "%s: test_122: default spectranet_w5100[0] should be NULL\n", progname );
    goto done;
  }
  w5100 = libspectrum_new( libspectrum_byte, 0x400 );
  w5100[0] = 0xab;
  libspectrum_snap_set_spectranet_w5100( snap, 0, w5100 );
  if( libspectrum_snap_spectranet_w5100( snap, 0 ) != w5100 ) {
    fprintf( stderr, "%s: test_122: spectranet_w5100[0] pointer mismatch after set\n", progname );
    libspectrum_free( w5100 );
    goto done;
  }

  if( libspectrum_snap_spectranet_flash( snap, 0 ) != NULL ) {
    fprintf( stderr, "%s: test_122: default spectranet_flash[0] should be NULL\n", progname );
    goto done;
  }
  flash = libspectrum_new( libspectrum_byte, 0x20000 );
  flash[0] = 0xcd;
  libspectrum_snap_set_spectranet_flash( snap, 0, flash );
  if( libspectrum_snap_spectranet_flash( snap, 0 ) != flash ) {
    fprintf( stderr, "%s: test_122: spectranet_flash[0] pointer mismatch after set\n", progname );
    libspectrum_free( flash );
    goto done;
  }

  if( libspectrum_snap_spectranet_ram( snap, 0 ) != NULL ) {
    fprintf( stderr, "%s: test_122: default spectranet_ram[0] should be NULL\n", progname );
    goto done;
  }
  ram = libspectrum_new( libspectrum_byte, 0x20000 );
  ram[0] = 0xef;
  libspectrum_snap_set_spectranet_ram( snap, 0, ram );
  if( libspectrum_snap_spectranet_ram( snap, 0 ) != ram ) {
    fprintf( stderr, "%s: test_122: spectranet_ram[0] pointer mismatch after set\n", progname );
    libspectrum_free( ram );
    goto done;
  }

  r = TEST_PASS;

done:
  libspectrum_snap_free( snap );
  return r;
}

test_return_t
test_123( void )
{
  /* libspectrum_snap: DISCiPLE int flags getter/setter */
  libspectrum_snap *snap = libspectrum_snap_alloc();
  test_return_t r = TEST_FAIL;

  if( !snap ) {
    fprintf( stderr, "%s: test_123: snap_alloc returned NULL\n", progname );
    return TEST_INCOMPLETE;
  }

  if( libspectrum_snap_disciple_active( snap ) != 0 ) {
    fprintf( stderr, "%s: test_123: default disciple_active should be 0, got %d\n",
             progname, libspectrum_snap_disciple_active( snap ) );
    goto done;
  }
  libspectrum_snap_set_disciple_active( snap, 1 );
  if( libspectrum_snap_disciple_active( snap ) != 1 ) {
    fprintf( stderr, "%s: test_123: expected disciple_active=1, got %d\n",
             progname, libspectrum_snap_disciple_active( snap ) );
    goto done;
  }

  if( libspectrum_snap_disciple_paged( snap ) != 0 ) {
    fprintf( stderr, "%s: test_123: default disciple_paged should be 0, got %d\n",
             progname, libspectrum_snap_disciple_paged( snap ) );
    goto done;
  }
  libspectrum_snap_set_disciple_paged( snap, 1 );
  if( libspectrum_snap_disciple_paged( snap ) != 1 ) {
    fprintf( stderr, "%s: test_123: expected disciple_paged=1, got %d\n",
             progname, libspectrum_snap_disciple_paged( snap ) );
    goto done;
  }

  if( libspectrum_snap_disciple_inhibit_button( snap ) != 0 ) {
    fprintf( stderr, "%s: test_123: default disciple_inhibit_button should be 0, got %d\n",
             progname, libspectrum_snap_disciple_inhibit_button( snap ) );
    goto done;
  }
  libspectrum_snap_set_disciple_inhibit_button( snap, 1 );
  if( libspectrum_snap_disciple_inhibit_button( snap ) != 1 ) {
    fprintf( stderr, "%s: test_123: expected disciple_inhibit_button=1, got %d\n",
             progname, libspectrum_snap_disciple_inhibit_button( snap ) );
    goto done;
  }

  if( libspectrum_snap_disciple_drive_count( snap ) != 0 ) {
    fprintf( stderr, "%s: test_123: default disciple_drive_count should be 0, got %d\n",
             progname, libspectrum_snap_disciple_drive_count( snap ) );
    goto done;
  }
  libspectrum_snap_set_disciple_drive_count( snap, 2 );
  if( libspectrum_snap_disciple_drive_count( snap ) != 2 ) {
    fprintf( stderr, "%s: test_123: expected disciple_drive_count=2, got %d\n",
             progname, libspectrum_snap_disciple_drive_count( snap ) );
    goto done;
  }

  if( libspectrum_snap_disciple_custom_rom( snap ) != 0 ) {
    fprintf( stderr, "%s: test_123: default disciple_custom_rom should be 0, got %d\n",
             progname, libspectrum_snap_disciple_custom_rom( snap ) );
    goto done;
  }
  libspectrum_snap_set_disciple_custom_rom( snap, 1 );
  if( libspectrum_snap_disciple_custom_rom( snap ) != 1 ) {
    fprintf( stderr, "%s: test_123: expected disciple_custom_rom=1, got %d\n",
             progname, libspectrum_snap_disciple_custom_rom( snap ) );
    goto done;
  }

  if( libspectrum_snap_disciple_direction( snap ) != 0 ) {
    fprintf( stderr, "%s: test_123: default disciple_direction should be 0, got %d\n",
             progname, libspectrum_snap_disciple_direction( snap ) );
    goto done;
  }
  libspectrum_snap_set_disciple_direction( snap, 1 );
  if( libspectrum_snap_disciple_direction( snap ) != 1 ) {
    fprintf( stderr, "%s: test_123: expected disciple_direction=1, got %d\n",
             progname, libspectrum_snap_disciple_direction( snap ) );
    goto done;
  }

  r = TEST_PASS;

done:
  libspectrum_snap_free( snap );
  return r;
}

test_return_t
test_124( void )
{
  /* libspectrum_snap: DISCiPLE FDC byte registers getter/setter */
  libspectrum_snap *snap = libspectrum_snap_alloc();
  test_return_t r = TEST_FAIL;

  if( !snap ) {
    fprintf( stderr, "%s: test_124: snap_alloc returned NULL\n", progname );
    return TEST_INCOMPLETE;
  }

  if( libspectrum_snap_disciple_control( snap ) != 0 ) {
    fprintf( stderr, "%s: test_124: default disciple_control should be 0, got 0x%02x\n",
             progname, libspectrum_snap_disciple_control( snap ) );
    goto done;
  }
  libspectrum_snap_set_disciple_control( snap, 0x12 );
  if( libspectrum_snap_disciple_control( snap ) != 0x12 ) {
    fprintf( stderr, "%s: test_124: expected disciple_control=0x12, got 0x%02x\n",
             progname, libspectrum_snap_disciple_control( snap ) );
    goto done;
  }

  if( libspectrum_snap_disciple_track( snap ) != 0 ) {
    fprintf( stderr, "%s: test_124: default disciple_track should be 0, got 0x%02x\n",
             progname, libspectrum_snap_disciple_track( snap ) );
    goto done;
  }
  libspectrum_snap_set_disciple_track( snap, 0x34 );
  if( libspectrum_snap_disciple_track( snap ) != 0x34 ) {
    fprintf( stderr, "%s: test_124: expected disciple_track=0x34, got 0x%02x\n",
             progname, libspectrum_snap_disciple_track( snap ) );
    goto done;
  }

  if( libspectrum_snap_disciple_sector( snap ) != 0 ) {
    fprintf( stderr, "%s: test_124: default disciple_sector should be 0, got 0x%02x\n",
             progname, libspectrum_snap_disciple_sector( snap ) );
    goto done;
  }
  libspectrum_snap_set_disciple_sector( snap, 0x56 );
  if( libspectrum_snap_disciple_sector( snap ) != 0x56 ) {
    fprintf( stderr, "%s: test_124: expected disciple_sector=0x56, got 0x%02x\n",
             progname, libspectrum_snap_disciple_sector( snap ) );
    goto done;
  }

  if( libspectrum_snap_disciple_data( snap ) != 0 ) {
    fprintf( stderr, "%s: test_124: default disciple_data should be 0, got 0x%02x\n",
             progname, libspectrum_snap_disciple_data( snap ) );
    goto done;
  }
  libspectrum_snap_set_disciple_data( snap, 0x78 );
  if( libspectrum_snap_disciple_data( snap ) != 0x78 ) {
    fprintf( stderr, "%s: test_124: expected disciple_data=0x78, got 0x%02x\n",
             progname, libspectrum_snap_disciple_data( snap ) );
    goto done;
  }

  if( libspectrum_snap_disciple_status( snap ) != 0 ) {
    fprintf( stderr, "%s: test_124: default disciple_status should be 0, got 0x%02x\n",
             progname, libspectrum_snap_disciple_status( snap ) );
    goto done;
  }
  libspectrum_snap_set_disciple_status( snap, 0x9a );
  if( libspectrum_snap_disciple_status( snap ) != 0x9a ) {
    fprintf( stderr, "%s: test_124: expected disciple_status=0x9a, got 0x%02x\n",
             progname, libspectrum_snap_disciple_status( snap ) );
    goto done;
  }

  r = TEST_PASS;

done:
  libspectrum_snap_free( snap );
  return r;
}

test_return_t
test_125( void )
{
  /* libspectrum_snap: DISCiPLE ROM pointer, ROM length, and RAM pointer getter/setter */
  libspectrum_snap *snap = libspectrum_snap_alloc();
  libspectrum_byte *rom, *ram;
  test_return_t r = TEST_FAIL;

  if( !snap ) {
    fprintf( stderr, "%s: test_125: snap_alloc returned NULL\n", progname );
    return TEST_INCOMPLETE;
  }

  if( libspectrum_snap_disciple_rom( snap, 0 ) != NULL ) {
    fprintf( stderr, "%s: test_125: default disciple_rom[0] should be NULL\n", progname );
    goto done;
  }

  if( libspectrum_snap_disciple_rom_length( snap, 0 ) != 0 ) {
    fprintf( stderr, "%s: test_125: default disciple_rom_length[0] should be 0, got %zu\n",
             progname, libspectrum_snap_disciple_rom_length( snap, 0 ) );
    goto done;
  }

  rom = libspectrum_new( libspectrum_byte, 0x8000 );
  rom[0]      = 0x11;
  rom[0x7fff] = 0x22;

  libspectrum_snap_set_disciple_rom( snap, 0, rom );
  libspectrum_snap_set_disciple_rom_length( snap, 0, 0x8000 );

  if( libspectrum_snap_disciple_rom( snap, 0 ) != rom ) {
    fprintf( stderr, "%s: test_125: disciple_rom[0] pointer mismatch after set\n", progname );
    libspectrum_free( rom );
    goto done;
  }
  if( libspectrum_snap_disciple_rom_length( snap, 0 ) != 0x8000 ) {
    fprintf( stderr, "%s: test_125: expected disciple_rom_length[0]=0x8000, got %zu\n",
             progname, libspectrum_snap_disciple_rom_length( snap, 0 ) );
    goto done;
  }
  if( libspectrum_snap_disciple_rom( snap, 0 )[0]      != 0x11 ||
      libspectrum_snap_disciple_rom( snap, 0 )[0x7fff] != 0x22 ) {
    fprintf( stderr, "%s: test_125: disciple_rom[0] data mismatch\n", progname );
    goto done;
  }

  if( libspectrum_snap_disciple_ram( snap, 0 ) != NULL ) {
    fprintf( stderr, "%s: test_125: default disciple_ram[0] should be NULL\n", progname );
    goto done;
  }

  ram = libspectrum_new( libspectrum_byte, 0x2000 );
  ram[0]      = 0x33;
  ram[0x1fff] = 0x44;

  libspectrum_snap_set_disciple_ram( snap, 0, ram );
  if( libspectrum_snap_disciple_ram( snap, 0 ) != ram ) {
    fprintf( stderr, "%s: test_125: disciple_ram[0] pointer mismatch after set\n", progname );
    libspectrum_free( ram );
    goto done;
  }
  if( libspectrum_snap_disciple_ram( snap, 0 )[0]      != 0x33 ||
      libspectrum_snap_disciple_ram( snap, 0 )[0x1fff] != 0x44 ) {
    fprintf( stderr, "%s: test_125: disciple_ram[0] data mismatch\n", progname );
    goto done;
  }

  r = TEST_PASS;

done:
  libspectrum_snap_free( snap );
  return r;
}

test_return_t
test_126( void )
{
  /* libspectrum_snap: USource int flags getter/setter */
  libspectrum_snap *snap = libspectrum_snap_alloc();
  test_return_t r = TEST_FAIL;

  if( !snap ) {
    fprintf( stderr, "%s: test_126: snap_alloc returned NULL\n", progname );
    return TEST_INCOMPLETE;
  }

  if( libspectrum_snap_usource_active( snap ) != 0 ) {
    fprintf( stderr, "%s: test_126: default usource_active should be 0, got %d\n",
             progname, libspectrum_snap_usource_active( snap ) );
    goto done;
  }
  libspectrum_snap_set_usource_active( snap, 1 );
  if( libspectrum_snap_usource_active( snap ) != 1 ) {
    fprintf( stderr, "%s: test_126: expected usource_active=1, got %d\n",
             progname, libspectrum_snap_usource_active( snap ) );
    goto done;
  }

  if( libspectrum_snap_usource_paged( snap ) != 0 ) {
    fprintf( stderr, "%s: test_126: default usource_paged should be 0, got %d\n",
             progname, libspectrum_snap_usource_paged( snap ) );
    goto done;
  }
  libspectrum_snap_set_usource_paged( snap, 1 );
  if( libspectrum_snap_usource_paged( snap ) != 1 ) {
    fprintf( stderr, "%s: test_126: expected usource_paged=1, got %d\n",
             progname, libspectrum_snap_usource_paged( snap ) );
    goto done;
  }

  if( libspectrum_snap_usource_custom_rom( snap ) != 0 ) {
    fprintf( stderr, "%s: test_126: default usource_custom_rom should be 0, got %d\n",
             progname, libspectrum_snap_usource_custom_rom( snap ) );
    goto done;
  }
  libspectrum_snap_set_usource_custom_rom( snap, 1 );
  if( libspectrum_snap_usource_custom_rom( snap ) != 1 ) {
    fprintf( stderr, "%s: test_126: expected usource_custom_rom=1, got %d\n",
             progname, libspectrum_snap_usource_custom_rom( snap ) );
    goto done;
  }

  r = TEST_PASS;

done:
  libspectrum_snap_free( snap );
  return r;
}

test_return_t
test_127( void )
{
  /* libspectrum_snap: USource ROM pointer and ROM length getter/setter */
  libspectrum_snap *snap = libspectrum_snap_alloc();
  libspectrum_byte *rom;
  test_return_t r = TEST_FAIL;

  if( !snap ) {
    fprintf( stderr, "%s: test_127: snap_alloc returned NULL\n", progname );
    return TEST_INCOMPLETE;
  }

  if( libspectrum_snap_usource_rom( snap, 0 ) != NULL ) {
    fprintf( stderr, "%s: test_127: default usource_rom[0] should be NULL\n", progname );
    goto done;
  }

  if( libspectrum_snap_usource_rom_length( snap, 0 ) != 0 ) {
    fprintf( stderr, "%s: test_127: default usource_rom_length[0] should be 0, got %zu\n",
             progname, libspectrum_snap_usource_rom_length( snap, 0 ) );
    goto done;
  }

  rom = libspectrum_new( libspectrum_byte, 0x4000 );
  rom[0]      = 0xab;
  rom[0x3fff] = 0xcd;

  libspectrum_snap_set_usource_rom( snap, 0, rom );
  libspectrum_snap_set_usource_rom_length( snap, 0, 0x4000 );

  if( libspectrum_snap_usource_rom( snap, 0 ) != rom ) {
    fprintf( stderr, "%s: test_127: usource_rom[0] pointer mismatch after set\n", progname );
    libspectrum_free( rom );
    goto done;
  }
  if( libspectrum_snap_usource_rom_length( snap, 0 ) != 0x4000 ) {
    fprintf( stderr, "%s: test_127: expected usource_rom_length[0]=0x4000, got %zu\n",
             progname, libspectrum_snap_usource_rom_length( snap, 0 ) );
    goto done;
  }
  if( libspectrum_snap_usource_rom( snap, 0 )[0]      != 0xab ||
      libspectrum_snap_usource_rom( snap, 0 )[0x3fff] != 0xcd ) {
    fprintf( stderr, "%s: test_127: usource_rom[0] data mismatch\n", progname );
    goto done;
  }

  r = TEST_PASS;

done:
  libspectrum_snap_free( snap );
  return r;
}

test_return_t
test_128( void )
{
  /* libspectrum_snap: USpeeched active and paged getter/setter */
  libspectrum_snap *snap = libspectrum_snap_alloc();
  test_return_t r = TEST_FAIL;

  if( !snap ) {
    fprintf( stderr, "%s: test_128: snap_alloc returned NULL\n", progname );
    return TEST_INCOMPLETE;
  }

  if( libspectrum_snap_uspeech_active( snap ) != 0 ) {
    fprintf( stderr, "%s: test_128: default uspeech_active should be 0, got %d\n",
             progname, libspectrum_snap_uspeech_active( snap ) );
    goto done;
  }
  libspectrum_snap_set_uspeech_active( snap, 1 );
  if( libspectrum_snap_uspeech_active( snap ) != 1 ) {
    fprintf( stderr, "%s: test_128: expected uspeech_active=1, got %d\n",
             progname, libspectrum_snap_uspeech_active( snap ) );
    goto done;
  }

  if( libspectrum_snap_uspeech_paged( snap ) != 0 ) {
    fprintf( stderr, "%s: test_128: default uspeech_paged should be 0, got %d\n",
             progname, libspectrum_snap_uspeech_paged( snap ) );
    goto done;
  }
  libspectrum_snap_set_uspeech_paged( snap, 1 );
  if( libspectrum_snap_uspeech_paged( snap ) != 1 ) {
    fprintf( stderr, "%s: test_128: expected uspeech_paged=1, got %d\n",
             progname, libspectrum_snap_uspeech_paged( snap ) );
    goto done;
  }

  r = TEST_PASS;

done:
  libspectrum_snap_free( snap );
  return r;
}

test_return_t
test_129( void )
{
  /* libspectrum_snap: Didaktik80 int flags and FDC byte registers getter/setter */
  libspectrum_snap *snap = libspectrum_snap_alloc();
  test_return_t r = TEST_FAIL;

  if( !snap ) {
    fprintf( stderr, "%s: test_129: snap_alloc returned NULL\n", progname );
    return TEST_INCOMPLETE;
  }

  if( libspectrum_snap_didaktik80_active( snap ) != 0 ) {
    fprintf( stderr, "%s: test_129: default didaktik80_active should be 0, got %d\n",
             progname, libspectrum_snap_didaktik80_active( snap ) );
    goto done;
  }
  libspectrum_snap_set_didaktik80_active( snap, 1 );
  if( libspectrum_snap_didaktik80_active( snap ) != 1 ) {
    fprintf( stderr, "%s: test_129: expected didaktik80_active=1, got %d\n",
             progname, libspectrum_snap_didaktik80_active( snap ) );
    goto done;
  }

  if( libspectrum_snap_didaktik80_paged( snap ) != 0 ) {
    fprintf( stderr, "%s: test_129: default didaktik80_paged should be 0, got %d\n",
             progname, libspectrum_snap_didaktik80_paged( snap ) );
    goto done;
  }
  libspectrum_snap_set_didaktik80_paged( snap, 1 );
  if( libspectrum_snap_didaktik80_paged( snap ) != 1 ) {
    fprintf( stderr, "%s: test_129: expected didaktik80_paged=1, got %d\n",
             progname, libspectrum_snap_didaktik80_paged( snap ) );
    goto done;
  }

  if( libspectrum_snap_didaktik80_drive_count( snap ) != 0 ) {
    fprintf( stderr, "%s: test_129: default didaktik80_drive_count should be 0, got %d\n",
             progname, libspectrum_snap_didaktik80_drive_count( snap ) );
    goto done;
  }
  libspectrum_snap_set_didaktik80_drive_count( snap, 2 );
  if( libspectrum_snap_didaktik80_drive_count( snap ) != 2 ) {
    fprintf( stderr, "%s: test_129: expected didaktik80_drive_count=2, got %d\n",
             progname, libspectrum_snap_didaktik80_drive_count( snap ) );
    goto done;
  }

  if( libspectrum_snap_didaktik80_custom_rom( snap ) != 0 ) {
    fprintf( stderr, "%s: test_129: default didaktik80_custom_rom should be 0, got %d\n",
             progname, libspectrum_snap_didaktik80_custom_rom( snap ) );
    goto done;
  }
  libspectrum_snap_set_didaktik80_custom_rom( snap, 1 );
  if( libspectrum_snap_didaktik80_custom_rom( snap ) != 1 ) {
    fprintf( stderr, "%s: test_129: expected didaktik80_custom_rom=1, got %d\n",
             progname, libspectrum_snap_didaktik80_custom_rom( snap ) );
    goto done;
  }

  if( libspectrum_snap_didaktik80_direction( snap ) != 0 ) {
    fprintf( stderr, "%s: test_129: default didaktik80_direction should be 0, got %d\n",
             progname, libspectrum_snap_didaktik80_direction( snap ) );
    goto done;
  }
  libspectrum_snap_set_didaktik80_direction( snap, 1 );
  if( libspectrum_snap_didaktik80_direction( snap ) != 1 ) {
    fprintf( stderr, "%s: test_129: expected didaktik80_direction=1, got %d\n",
             progname, libspectrum_snap_didaktik80_direction( snap ) );
    goto done;
  }

  if( libspectrum_snap_didaktik80_track( snap ) != 0 ) {
    fprintf( stderr, "%s: test_129: default didaktik80_track should be 0, got 0x%02x\n",
             progname, libspectrum_snap_didaktik80_track( snap ) );
    goto done;
  }
  libspectrum_snap_set_didaktik80_track( snap, 0x12 );
  if( libspectrum_snap_didaktik80_track( snap ) != 0x12 ) {
    fprintf( stderr, "%s: test_129: expected didaktik80_track=0x12, got 0x%02x\n",
             progname, libspectrum_snap_didaktik80_track( snap ) );
    goto done;
  }

  if( libspectrum_snap_didaktik80_sector( snap ) != 0 ) {
    fprintf( stderr, "%s: test_129: default didaktik80_sector should be 0, got 0x%02x\n",
             progname, libspectrum_snap_didaktik80_sector( snap ) );
    goto done;
  }
  libspectrum_snap_set_didaktik80_sector( snap, 0x34 );
  if( libspectrum_snap_didaktik80_sector( snap ) != 0x34 ) {
    fprintf( stderr, "%s: test_129: expected didaktik80_sector=0x34, got 0x%02x\n",
             progname, libspectrum_snap_didaktik80_sector( snap ) );
    goto done;
  }

  if( libspectrum_snap_didaktik80_data( snap ) != 0 ) {
    fprintf( stderr, "%s: test_129: default didaktik80_data should be 0, got 0x%02x\n",
             progname, libspectrum_snap_didaktik80_data( snap ) );
    goto done;
  }
  libspectrum_snap_set_didaktik80_data( snap, 0x56 );
  if( libspectrum_snap_didaktik80_data( snap ) != 0x56 ) {
    fprintf( stderr, "%s: test_129: expected didaktik80_data=0x56, got 0x%02x\n",
             progname, libspectrum_snap_didaktik80_data( snap ) );
    goto done;
  }

  if( libspectrum_snap_didaktik80_status( snap ) != 0 ) {
    fprintf( stderr, "%s: test_129: default didaktik80_status should be 0, got 0x%02x\n",
             progname, libspectrum_snap_didaktik80_status( snap ) );
    goto done;
  }
  libspectrum_snap_set_didaktik80_status( snap, 0x78 );
  if( libspectrum_snap_didaktik80_status( snap ) != 0x78 ) {
    fprintf( stderr, "%s: test_129: expected didaktik80_status=0x78, got 0x%02x\n",
             progname, libspectrum_snap_didaktik80_status( snap ) );
    goto done;
  }

  if( libspectrum_snap_didaktik80_aux( snap ) != 0 ) {
    fprintf( stderr, "%s: test_129: default didaktik80_aux should be 0, got 0x%02x\n",
             progname, libspectrum_snap_didaktik80_aux( snap ) );
    goto done;
  }
  libspectrum_snap_set_didaktik80_aux( snap, 0x9a );
  if( libspectrum_snap_didaktik80_aux( snap ) != 0x9a ) {
    fprintf( stderr, "%s: test_129: expected didaktik80_aux=0x9a, got 0x%02x\n",
             progname, libspectrum_snap_didaktik80_aux( snap ) );
    goto done;
  }

  r = TEST_PASS;

done:
  libspectrum_snap_free( snap );
  return r;
}

test_return_t
test_130( void )
{
  /* libspectrum_snap: Didaktik80 ROM pointer, ROM length, and RAM pointer getter/setter */
  libspectrum_snap *snap = libspectrum_snap_alloc();
  libspectrum_byte *rom, *ram;
  test_return_t r = TEST_FAIL;

  if( !snap ) {
    fprintf( stderr, "%s: test_130: snap_alloc returned NULL\n", progname );
    return TEST_INCOMPLETE;
  }

  if( libspectrum_snap_didaktik80_rom( snap, 0 ) != NULL ) {
    fprintf( stderr, "%s: test_130: default didaktik80_rom[0] should be NULL\n", progname );
    goto done;
  }

  if( libspectrum_snap_didaktik80_rom_length( snap, 0 ) != 0 ) {
    fprintf( stderr, "%s: test_130: default didaktik80_rom_length[0] should be 0, got %zu\n",
             progname, libspectrum_snap_didaktik80_rom_length( snap, 0 ) );
    goto done;
  }

  rom = libspectrum_new( libspectrum_byte, 0x4000 );
  rom[0]      = 0x11;
  rom[0x3fff] = 0x22;

  libspectrum_snap_set_didaktik80_rom( snap, 0, rom );
  libspectrum_snap_set_didaktik80_rom_length( snap, 0, 0x4000 );

  if( libspectrum_snap_didaktik80_rom( snap, 0 ) != rom ) {
    fprintf( stderr, "%s: test_130: didaktik80_rom[0] pointer mismatch after set\n", progname );
    libspectrum_free( rom );
    goto done;
  }
  if( libspectrum_snap_didaktik80_rom_length( snap, 0 ) != 0x4000 ) {
    fprintf( stderr, "%s: test_130: expected didaktik80_rom_length[0]=0x4000, got %zu\n",
             progname, libspectrum_snap_didaktik80_rom_length( snap, 0 ) );
    goto done;
  }
  if( libspectrum_snap_didaktik80_rom( snap, 0 )[0]      != 0x11 ||
      libspectrum_snap_didaktik80_rom( snap, 0 )[0x3fff] != 0x22 ) {
    fprintf( stderr, "%s: test_130: didaktik80_rom[0] data mismatch\n", progname );
    goto done;
  }

  if( libspectrum_snap_didaktik80_ram( snap, 0 ) != NULL ) {
    fprintf( stderr, "%s: test_130: default didaktik80_ram[0] should be NULL\n", progname );
    goto done;
  }

  ram = libspectrum_new( libspectrum_byte, 0x2000 );
  ram[0]      = 0x33;
  ram[0x1fff] = 0x44;

  libspectrum_snap_set_didaktik80_ram( snap, 0, ram );
  if( libspectrum_snap_didaktik80_ram( snap, 0 ) != ram ) {
    fprintf( stderr, "%s: test_130: didaktik80_ram[0] pointer mismatch after set\n", progname );
    libspectrum_free( ram );
    goto done;
  }
  if( libspectrum_snap_didaktik80_ram( snap, 0 )[0]      != 0x33 ||
      libspectrum_snap_didaktik80_ram( snap, 0 )[0x1fff] != 0x44 ) {
    fprintf( stderr, "%s: test_130: didaktik80_ram[0] data mismatch\n", progname );
    goto done;
  }

  r = TEST_PASS;

done:
  libspectrum_snap_free( snap );
  return r;
}

test_return_t
test_131( void )
{
  /* libspectrum_snap: ULAplus flags, current_register, palette array, and ff_register getter/setter */
  libspectrum_snap *snap = libspectrum_snap_alloc();
  libspectrum_byte *palette;
  test_return_t r = TEST_FAIL;

  if( !snap ) {
    fprintf( stderr, "%s: test_131: snap_alloc returned NULL\n", progname );
    return TEST_INCOMPLETE;
  }

  if( libspectrum_snap_ulaplus_active( snap ) != 0 ) {
    fprintf( stderr, "%s: test_131: default ulaplus_active should be 0, got %d\n",
             progname, libspectrum_snap_ulaplus_active( snap ) );
    goto done;
  }
  libspectrum_snap_set_ulaplus_active( snap, 1 );
  if( libspectrum_snap_ulaplus_active( snap ) != 1 ) {
    fprintf( stderr, "%s: test_131: expected ulaplus_active=1, got %d\n",
             progname, libspectrum_snap_ulaplus_active( snap ) );
    goto done;
  }

  if( libspectrum_snap_ulaplus_palette_enabled( snap ) != 0 ) {
    fprintf( stderr, "%s: test_131: default ulaplus_palette_enabled should be 0, got %d\n",
             progname, libspectrum_snap_ulaplus_palette_enabled( snap ) );
    goto done;
  }
  libspectrum_snap_set_ulaplus_palette_enabled( snap, 1 );
  if( libspectrum_snap_ulaplus_palette_enabled( snap ) != 1 ) {
    fprintf( stderr, "%s: test_131: expected ulaplus_palette_enabled=1, got %d\n",
             progname, libspectrum_snap_ulaplus_palette_enabled( snap ) );
    goto done;
  }

  if( libspectrum_snap_ulaplus_current_register( snap ) != 0 ) {
    fprintf( stderr, "%s: test_131: default ulaplus_current_register should be 0, got 0x%02x\n",
             progname, libspectrum_snap_ulaplus_current_register( snap ) );
    goto done;
  }
  libspectrum_snap_set_ulaplus_current_register( snap, 0x3f );
  if( libspectrum_snap_ulaplus_current_register( snap ) != 0x3f ) {
    fprintf( stderr, "%s: test_131: expected ulaplus_current_register=0x3f, got 0x%02x\n",
             progname, libspectrum_snap_ulaplus_current_register( snap ) );
    goto done;
  }

  if( libspectrum_snap_ulaplus_ff_register( snap ) != 0 ) {
    fprintf( stderr, "%s: test_131: default ulaplus_ff_register should be 0, got 0x%02x\n",
             progname, libspectrum_snap_ulaplus_ff_register( snap ) );
    goto done;
  }
  libspectrum_snap_set_ulaplus_ff_register( snap, 0xc0 );
  if( libspectrum_snap_ulaplus_ff_register( snap ) != 0xc0 ) {
    fprintf( stderr, "%s: test_131: expected ulaplus_ff_register=0xc0, got 0x%02x\n",
             progname, libspectrum_snap_ulaplus_ff_register( snap ) );
    goto done;
  }

  if( libspectrum_snap_ulaplus_palette( snap, 0 ) != NULL ) {
    fprintf( stderr, "%s: test_131: default ulaplus_palette[0] should be NULL\n", progname );
    goto done;
  }

  palette = libspectrum_new( libspectrum_byte, 64 );
  palette[0]  = 0xaa;
  palette[63] = 0xbb;

  libspectrum_snap_set_ulaplus_palette( snap, 0, palette );
  if( libspectrum_snap_ulaplus_palette( snap, 0 ) != palette ) {
    fprintf( stderr, "%s: test_131: ulaplus_palette[0] pointer mismatch after set\n", progname );
    libspectrum_free( palette );
    goto done;
  }
  if( libspectrum_snap_ulaplus_palette( snap, 0 )[0]  != 0xaa ||
      libspectrum_snap_ulaplus_palette( snap, 0 )[63] != 0xbb ) {
    fprintf( stderr, "%s: test_131: ulaplus_palette[0] data mismatch\n", progname );
    goto done;
  }

  r = TEST_PASS;

done:
  libspectrum_snap_free( snap );
  return r;
}

test_return_t
test_132( void )
{
  /* libspectrum_snap: late_timings getter/setter */
  libspectrum_snap *snap = libspectrum_snap_alloc();
  test_return_t r = TEST_FAIL;

  if( !snap ) {
    fprintf( stderr, "%s: test_132: snap_alloc returned NULL\n", progname );
    return TEST_INCOMPLETE;
  }

  if( libspectrum_snap_late_timings( snap ) != 0 ) {
    fprintf( stderr, "%s: test_132: default late_timings should be 0, got %d\n",
             progname, libspectrum_snap_late_timings( snap ) );
    goto done;
  }
  libspectrum_snap_set_late_timings( snap, 1 );
  if( libspectrum_snap_late_timings( snap ) != 1 ) {
    fprintf( stderr, "%s: test_132: expected late_timings=1, got %d\n",
             progname, libspectrum_snap_late_timings( snap ) );
    goto done;
  }

  r = TEST_PASS;

done:
  libspectrum_snap_free( snap );
  return r;
}

test_return_t
test_133( void )
{
  /* libspectrum_snap: zx_printer_active getter/setter */
  libspectrum_snap *snap = libspectrum_snap_alloc();
  test_return_t r = TEST_FAIL;

  if( !snap ) {
    fprintf( stderr, "%s: test_133: snap_alloc returned NULL\n", progname );
    return TEST_INCOMPLETE;
  }

  if( libspectrum_snap_zx_printer_active( snap ) != 0 ) {
    fprintf( stderr, "%s: test_133: default zx_printer_active should be 0, got %d\n",
             progname, libspectrum_snap_zx_printer_active( snap ) );
    goto done;
  }
  libspectrum_snap_set_zx_printer_active( snap, 1 );
  if( libspectrum_snap_zx_printer_active( snap ) != 1 ) {
    fprintf( stderr, "%s: test_133: expected zx_printer_active=1, got %d\n",
             progname, libspectrum_snap_zx_printer_active( snap ) );
    goto done;
  }

  r = TEST_PASS;

done:
  libspectrum_snap_free( snap );
  return r;
}

test_return_t
test_134( void )
{
  /* libspectrum_snap: covox_active and covox_dac getter/setter */
  libspectrum_snap *snap = libspectrum_snap_alloc();
  test_return_t r = TEST_FAIL;

  if( !snap ) {
    fprintf( stderr, "%s: test_134: snap_alloc returned NULL\n", progname );
    return TEST_INCOMPLETE;
  }

  if( libspectrum_snap_covox_active( snap ) != 0 ) {
    fprintf( stderr, "%s: test_134: default covox_active should be 0, got %d\n",
             progname, libspectrum_snap_covox_active( snap ) );
    goto done;
  }
  libspectrum_snap_set_covox_active( snap, 1 );
  if( libspectrum_snap_covox_active( snap ) != 1 ) {
    fprintf( stderr, "%s: test_134: expected covox_active=1, got %d\n",
             progname, libspectrum_snap_covox_active( snap ) );
    goto done;
  }

  if( libspectrum_snap_covox_dac( snap ) != 0 ) {
    fprintf( stderr, "%s: test_134: default covox_dac should be 0, got 0x%02x\n",
             progname, libspectrum_snap_covox_dac( snap ) );
    goto done;
  }
  libspectrum_snap_set_covox_dac( snap, 0x80 );
  if( libspectrum_snap_covox_dac( snap ) != 0x80 ) {
    fprintf( stderr, "%s: test_134: expected covox_dac=0x80, got 0x%02x\n",
             progname, libspectrum_snap_covox_dac( snap ) );
    goto done;
  }

  r = TEST_PASS;

done:
  libspectrum_snap_free( snap );
  return r;
}

test_return_t
test_135( void )
{
  /* libspectrum_snap: multiface_red_button_disabled getter/setter */
  libspectrum_snap *snap = libspectrum_snap_alloc();
  test_return_t r = TEST_FAIL;

  if( !snap ) {
    fprintf( stderr, "%s: test_135: snap_alloc returned NULL\n", progname );
    return TEST_INCOMPLETE;
  }

  if( libspectrum_snap_multiface_red_button_disabled( snap ) != 0 ) {
    fprintf( stderr, "%s: test_135: default multiface_red_button_disabled should be 0, got %d\n",
             progname, libspectrum_snap_multiface_red_button_disabled( snap ) );
    goto done;
  }
  libspectrum_snap_set_multiface_red_button_disabled( snap, 1 );
  if( libspectrum_snap_multiface_red_button_disabled( snap ) != 1 ) {
    fprintf( stderr, "%s: test_135: expected multiface_red_button_disabled=1, got %d\n",
             progname, libspectrum_snap_multiface_red_button_disabled( snap ) );
    goto done;
  }

  r = TEST_PASS;

done:
  libspectrum_snap_free( snap );
  return r;
}

test_return_t
test_136( void )
{
  /* libspectrum_snap: multiface_ram pointer and multiface_ram_length getter/setter */
  libspectrum_snap *snap = libspectrum_snap_alloc();
  libspectrum_byte *ram;
  test_return_t r = TEST_FAIL;

  if( !snap ) {
    fprintf( stderr, "%s: test_136: snap_alloc returned NULL\n", progname );
    return TEST_INCOMPLETE;
  }

  if( libspectrum_snap_multiface_ram( snap, 0 ) != NULL ) {
    fprintf( stderr, "%s: test_136: default multiface_ram[0] should be NULL\n", progname );
    goto done;
  }

  if( libspectrum_snap_multiface_ram_length( snap, 0 ) != 0 ) {
    fprintf( stderr, "%s: test_136: default multiface_ram_length[0] should be 0, got %zu\n",
             progname, libspectrum_snap_multiface_ram_length( snap, 0 ) );
    goto done;
  }

  ram = libspectrum_new( libspectrum_byte, 0x2000 );
  ram[0]      = 0xde;
  ram[0x1fff] = 0xad;

  libspectrum_snap_set_multiface_ram( snap, 0, ram );
  libspectrum_snap_set_multiface_ram_length( snap, 0, 0x2000 );

  if( libspectrum_snap_multiface_ram( snap, 0 ) != ram ) {
    fprintf( stderr, "%s: test_136: multiface_ram[0] pointer mismatch after set\n", progname );
    libspectrum_free( ram );
    goto done;
  }
  if( libspectrum_snap_multiface_ram_length( snap, 0 ) != 0x2000 ) {
    fprintf( stderr, "%s: test_136: expected multiface_ram_length[0]=0x2000, got %zu\n",
             progname, libspectrum_snap_multiface_ram_length( snap, 0 ) );
    goto done;
  }
  if( libspectrum_snap_multiface_ram( snap, 0 )[0]      != 0xde ||
      libspectrum_snap_multiface_ram( snap, 0 )[0x1fff] != 0xad ) {
    fprintf( stderr, "%s: test_136: multiface_ram[0] data mismatch\n", progname );
    goto done;
  }

  r = TEST_PASS;

done:
  libspectrum_snap_free( snap );
  return r;
}

test_return_t
test_137( void )
{
  /* libspectrum_snap: zxmmc_active getter/setter */
  libspectrum_snap *snap = libspectrum_snap_alloc();
  test_return_t r = TEST_FAIL;

  if( !snap ) {
    fprintf( stderr, "%s: test_137: snap_alloc returned NULL\n", progname );
    return TEST_INCOMPLETE;
  }

  if( libspectrum_snap_zxmmc_active( snap ) != 0 ) {
    fprintf( stderr, "%s: test_137: default zxmmc_active should be 0, got %d\n",
             progname, libspectrum_snap_zxmmc_active( snap ) );
    goto done;
  }
  libspectrum_snap_set_zxmmc_active( snap, 1 );
  if( libspectrum_snap_zxmmc_active( snap ) != 1 ) {
    fprintf( stderr, "%s: test_137: expected zxmmc_active=1, got %d\n",
             progname, libspectrum_snap_zxmmc_active( snap ) );
    goto done;
  }

  r = TEST_PASS;

done:
  libspectrum_snap_free( snap );
  return r;
}

test_return_t
test_138( void )
{
  /* libspectrum_snap: ttx2000s_active getter/setter */
  libspectrum_snap *snap = libspectrum_snap_alloc();
  test_return_t r = TEST_FAIL;

  if( !snap ) {
    fprintf( stderr, "%s: test_138: snap_alloc returned NULL\n", progname );
    return TEST_INCOMPLETE;
  }

  if( libspectrum_snap_ttx2000s_active( snap ) != 0 ) {
    fprintf( stderr, "%s: test_138: default ttx2000s_active should be 0, got %d\n",
             progname, libspectrum_snap_ttx2000s_active( snap ) );
    goto done;
  }
  libspectrum_snap_set_ttx2000s_active( snap, 1 );
  if( libspectrum_snap_ttx2000s_active( snap ) != 1 ) {
    fprintf( stderr, "%s: test_138: expected ttx2000s_active=1, got %d\n",
             progname, libspectrum_snap_ttx2000s_active( snap ) );
    goto done;
  }

  r = TEST_PASS;

done:
  libspectrum_snap_free( snap );
  return r;
}

test_return_t
test_139( void )
{
  /* tape block: TURBO block pilot_length, sync1_length, sync2_length getter/setter */
  libspectrum_tape_block *block =
    libspectrum_tape_block_alloc( LIBSPECTRUM_TAPE_BLOCK_TURBO );
  test_return_t r = TEST_FAIL;

  if( !block ) {
    fprintf( stderr, "%s: test_139: tape_block_alloc returned NULL\n", progname );
    return TEST_INCOMPLETE;
  }

  if( libspectrum_tape_block_type( block ) != LIBSPECTRUM_TAPE_BLOCK_TURBO ) {
    fprintf( stderr, "%s: test_139: expected TURBO block type\n", progname );
    goto done;
  }

  if( libspectrum_tape_block_pilot_length( block ) != 0 ) {
    fprintf( stderr, "%s: test_139: default pilot_length should be 0, got %lu\n",
             progname, (unsigned long)libspectrum_tape_block_pilot_length( block ) );
    goto done;
  }
  libspectrum_tape_block_set_pilot_length( block, 2168 );
  if( libspectrum_tape_block_pilot_length( block ) != 2168 ) {
    fprintf( stderr, "%s: test_139: expected pilot_length=2168, got %lu\n",
             progname, (unsigned long)libspectrum_tape_block_pilot_length( block ) );
    goto done;
  }

  if( libspectrum_tape_block_sync1_length( block ) != 0 ) {
    fprintf( stderr, "%s: test_139: default sync1_length should be 0, got %lu\n",
             progname, (unsigned long)libspectrum_tape_block_sync1_length( block ) );
    goto done;
  }
  libspectrum_tape_block_set_sync1_length( block, 667 );
  if( libspectrum_tape_block_sync1_length( block ) != 667 ) {
    fprintf( stderr, "%s: test_139: expected sync1_length=667, got %lu\n",
             progname, (unsigned long)libspectrum_tape_block_sync1_length( block ) );
    goto done;
  }

  if( libspectrum_tape_block_sync2_length( block ) != 0 ) {
    fprintf( stderr, "%s: test_139: default sync2_length should be 0, got %lu\n",
             progname, (unsigned long)libspectrum_tape_block_sync2_length( block ) );
    goto done;
  }
  libspectrum_tape_block_set_sync2_length( block, 735 );
  if( libspectrum_tape_block_sync2_length( block ) != 735 ) {
    fprintf( stderr, "%s: test_139: expected sync2_length=735, got %lu\n",
             progname, (unsigned long)libspectrum_tape_block_sync2_length( block ) );
    goto done;
  }

  r = TEST_PASS;

done:
  libspectrum_tape_block_free( block );
  return r;
}

test_return_t
test_140( void )
{
  /* tape block: TURBO block bit0_length, bit1_length, pilot_pulses, pause getter/setter */
  libspectrum_tape_block *block =
    libspectrum_tape_block_alloc( LIBSPECTRUM_TAPE_BLOCK_TURBO );
  test_return_t r = TEST_FAIL;

  if( !block ) {
    fprintf( stderr, "%s: test_140: tape_block_alloc returned NULL\n", progname );
    return TEST_INCOMPLETE;
  }

  if( libspectrum_tape_block_bit0_length( block ) != 0 ) {
    fprintf( stderr, "%s: test_140: default bit0_length should be 0, got %lu\n",
             progname, (unsigned long)libspectrum_tape_block_bit0_length( block ) );
    goto done;
  }
  libspectrum_tape_block_set_bit0_length( block, 855 );
  if( libspectrum_tape_block_bit0_length( block ) != 855 ) {
    fprintf( stderr, "%s: test_140: expected bit0_length=855, got %lu\n",
             progname, (unsigned long)libspectrum_tape_block_bit0_length( block ) );
    goto done;
  }

  if( libspectrum_tape_block_bit1_length( block ) != 0 ) {
    fprintf( stderr, "%s: test_140: default bit1_length should be 0, got %lu\n",
             progname, (unsigned long)libspectrum_tape_block_bit1_length( block ) );
    goto done;
  }
  libspectrum_tape_block_set_bit1_length( block, 1710 );
  if( libspectrum_tape_block_bit1_length( block ) != 1710 ) {
    fprintf( stderr, "%s: test_140: expected bit1_length=1710, got %lu\n",
             progname, (unsigned long)libspectrum_tape_block_bit1_length( block ) );
    goto done;
  }

  if( libspectrum_tape_block_pilot_pulses( block ) != 0 ) {
    fprintf( stderr, "%s: test_140: default pilot_pulses should be 0, got %lu\n",
             progname, (unsigned long)libspectrum_tape_block_pilot_pulses( block ) );
    goto done;
  }
  libspectrum_tape_block_set_pilot_pulses( block, 8063 );
  if( libspectrum_tape_block_pilot_pulses( block ) != 8063 ) {
    fprintf( stderr, "%s: test_140: expected pilot_pulses=8063, got %lu\n",
             progname, (unsigned long)libspectrum_tape_block_pilot_pulses( block ) );
    goto done;
  }

  if( libspectrum_tape_block_pause( block ) != 0 ) {
    fprintf( stderr, "%s: test_140: default pause should be 0, got %lu\n",
             progname, (unsigned long)libspectrum_tape_block_pause( block ) );
    goto done;
  }
  libspectrum_tape_block_set_pause( block, 1000 );
  if( libspectrum_tape_block_pause( block ) != 1000 ) {
    fprintf( stderr, "%s: test_140: expected pause=1000, got %lu\n",
             progname, (unsigned long)libspectrum_tape_block_pause( block ) );
    goto done;
  }

  r = TEST_PASS;

done:
  libspectrum_tape_block_free( block );
  return r;
}

test_return_t
test_141( void )
{
  /* tape block: PURE_TONE block pulse_length and count getter/setter */
  libspectrum_tape_block *block =
    libspectrum_tape_block_alloc( LIBSPECTRUM_TAPE_BLOCK_PURE_TONE );
  test_return_t r = TEST_FAIL;

  if( !block ) {
    fprintf( stderr, "%s: test_141: tape_block_alloc returned NULL\n", progname );
    return TEST_INCOMPLETE;
  }

  if( libspectrum_tape_block_type( block ) != LIBSPECTRUM_TAPE_BLOCK_PURE_TONE ) {
    fprintf( stderr, "%s: test_141: expected PURE_TONE block type\n", progname );
    goto done;
  }

  if( libspectrum_tape_block_pulse_length( block ) != 0 ) {
    fprintf( stderr, "%s: test_141: default pulse_length should be 0, got %lu\n",
             progname, (unsigned long)libspectrum_tape_block_pulse_length( block ) );
    goto done;
  }
  libspectrum_tape_block_set_pulse_length( block, 2168 );
  if( libspectrum_tape_block_pulse_length( block ) != 2168 ) {
    fprintf( stderr, "%s: test_141: expected pulse_length=2168, got %lu\n",
             progname, (unsigned long)libspectrum_tape_block_pulse_length( block ) );
    goto done;
  }

  if( libspectrum_tape_block_count( block ) != 0 ) {
    fprintf( stderr, "%s: test_141: default count should be 0, got %lu\n",
             progname, (unsigned long)libspectrum_tape_block_count( block ) );
    goto done;
  }
  libspectrum_tape_block_set_count( block, 3223 );
  if( libspectrum_tape_block_count( block ) != 3223 ) {
    fprintf( stderr, "%s: test_141: expected count=3223, got %lu\n",
             progname, (unsigned long)libspectrum_tape_block_count( block ) );
    goto done;
  }

  r = TEST_PASS;

done:
  libspectrum_tape_block_free( block );
  return r;
}

test_return_t
test_142( void )
{
  /* tape block: PURE_DATA block bit0_length, bit1_length, bits_in_last_byte, pause getter/setter */
  libspectrum_tape_block *block =
    libspectrum_tape_block_alloc( LIBSPECTRUM_TAPE_BLOCK_PURE_DATA );
  test_return_t r = TEST_FAIL;

  if( !block ) {
    fprintf( stderr, "%s: test_142: tape_block_alloc returned NULL\n", progname );
    return TEST_INCOMPLETE;
  }

  if( libspectrum_tape_block_type( block ) != LIBSPECTRUM_TAPE_BLOCK_PURE_DATA ) {
    fprintf( stderr, "%s: test_142: expected PURE_DATA block type\n", progname );
    goto done;
  }

  if( libspectrum_tape_block_bit0_length( block ) != 0 ) {
    fprintf( stderr, "%s: test_142: default bit0_length should be 0, got %lu\n",
             progname, (unsigned long)libspectrum_tape_block_bit0_length( block ) );
    goto done;
  }
  libspectrum_tape_block_set_bit0_length( block, 855 );
  if( libspectrum_tape_block_bit0_length( block ) != 855 ) {
    fprintf( stderr, "%s: test_142: expected bit0_length=855, got %lu\n",
             progname, (unsigned long)libspectrum_tape_block_bit0_length( block ) );
    goto done;
  }

  if( libspectrum_tape_block_bit1_length( block ) != 0 ) {
    fprintf( stderr, "%s: test_142: default bit1_length should be 0, got %lu\n",
             progname, (unsigned long)libspectrum_tape_block_bit1_length( block ) );
    goto done;
  }
  libspectrum_tape_block_set_bit1_length( block, 1710 );
  if( libspectrum_tape_block_bit1_length( block ) != 1710 ) {
    fprintf( stderr, "%s: test_142: expected bit1_length=1710, got %lu\n",
             progname, (unsigned long)libspectrum_tape_block_bit1_length( block ) );
    goto done;
  }

  if( libspectrum_tape_block_bits_in_last_byte( block ) != 0 ) {
    fprintf( stderr, "%s: test_142: default bits_in_last_byte should be 0, got %lu\n",
             progname, (unsigned long)libspectrum_tape_block_bits_in_last_byte( block ) );
    goto done;
  }
  libspectrum_tape_block_set_bits_in_last_byte( block, 8 );
  if( libspectrum_tape_block_bits_in_last_byte( block ) != 8 ) {
    fprintf( stderr, "%s: test_142: expected bits_in_last_byte=8, got %lu\n",
             progname, (unsigned long)libspectrum_tape_block_bits_in_last_byte( block ) );
    goto done;
  }

  if( libspectrum_tape_block_pause( block ) != 0 ) {
    fprintf( stderr, "%s: test_142: default pause should be 0, got %lu\n",
             progname, (unsigned long)libspectrum_tape_block_pause( block ) );
    goto done;
  }
  libspectrum_tape_block_set_pause( block, 500 );
  if( libspectrum_tape_block_pause( block ) != 500 ) {
    fprintf( stderr, "%s: test_142: expected pause=500, got %lu\n",
             progname, (unsigned long)libspectrum_tape_block_pause( block ) );
    goto done;
  }

  r = TEST_PASS;

done:
  libspectrum_tape_block_free( block );
  return r;
}

test_return_t
test_143( void )
{
  /* tape block: PAUSE block pause length and level getter/setter */
  libspectrum_tape_block *block =
    libspectrum_tape_block_alloc( LIBSPECTRUM_TAPE_BLOCK_PAUSE );
  test_return_t r = TEST_FAIL;

  if( !block ) {
    fprintf( stderr, "%s: test_143: tape_block_alloc returned NULL\n", progname );
    return TEST_INCOMPLETE;
  }

  if( libspectrum_tape_block_type( block ) != LIBSPECTRUM_TAPE_BLOCK_PAUSE ) {
    fprintf( stderr, "%s: test_143: expected PAUSE block type\n", progname );
    goto done;
  }

  if( libspectrum_tape_block_pause( block ) != 0 ) {
    fprintf( stderr, "%s: test_143: default pause should be 0, got %lu\n",
             progname, (unsigned long)libspectrum_tape_block_pause( block ) );
    goto done;
  }
  libspectrum_tape_block_set_pause( block, 2000 );
  if( libspectrum_tape_block_pause( block ) != 2000 ) {
    fprintf( stderr, "%s: test_143: expected pause=2000, got %lu\n",
             progname, (unsigned long)libspectrum_tape_block_pause( block ) );
    goto done;
  }

  if( libspectrum_tape_block_level( block ) != 0 ) {
    fprintf( stderr, "%s: test_143: default level should be 0, got %d\n",
             progname, libspectrum_tape_block_level( block ) );
    goto done;
  }
  libspectrum_tape_block_set_level( block, 1 );
  if( libspectrum_tape_block_level( block ) != 1 ) {
    fprintf( stderr, "%s: test_143: expected level=1, got %d\n",
             progname, libspectrum_tape_block_level( block ) );
    goto done;
  }

  r = TEST_PASS;

done:
  libspectrum_tape_block_free( block );
  return r;
}
