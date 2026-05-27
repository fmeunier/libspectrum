#include "config.h"

#include <stdio.h>
#include <string.h>

#include "internals.h"
#include "common.h"
#include "test.h"

test_return_t
tape_with_unknown_block( void )
{
  return read_tape( STATIC_TEST_PATH( "invalid.tzx" ), LIBSPECTRUM_ERROR_UNKNOWN );
}

/* Test for bugs #84: TZX turbo blocks with zero pilot pulses and #85: freeing
   a turbo block with no data produces segfault */
test_return_t
tzx_turbo_data_with_zero_pilot_pulses_and_zero_data( void )
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
writing_empty_tap_file( void )
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

/* Test for bug #105: lack of sanity check in GDB code */
test_return_t
invalid_tzx_gdb( void )
{
  return read_tape( STATIC_TEST_PATH( "invalid-gdb.tzx" ), LIBSPECTRUM_ERROR_CORRUPT );
}

/* Test for bug #106: empty DRB causes segfault */
test_return_t
empty_tzx_drb( void )
{
  return read_tape( STATIC_TEST_PATH( "empty-drb.tzx" ), LIBSPECTRUM_ERROR_NONE );
}

/* Test for bug #107: problems with invalid archive info block */
test_return_t
invalid_tzx_archive_info_block( void )
{
  return read_tape( STATIC_TEST_PATH( "invalid-archiveinfo.tzx" ), LIBSPECTRUM_ERROR_CORRUPT );
}

/* Test for bug #108: invalid hardware info blocks can leak memory */
test_return_t
invalid_hardware_info_block_causes_memory_leak( void )
{
  return read_tape( STATIC_TEST_PATH( "invalid-hardwareinfo.tzx" ), LIBSPECTRUM_ERROR_CORRUPT );
}

/* Test for bug #111: invalid Warajevo tape block offset causes segfault */
test_return_t
invalid_warajevo_tape_file( void )
{
  return read_tape( STATIC_TEST_PATH( "invalid-warajevo-blockoffset.tap" ), LIBSPECTRUM_ERROR_CORRUPT );
}

/* Test for bug #112: invalid custom info block causes memory leak */
test_return_t
invalid_tzx_custom_info_block_causes_memory_leak( void )
{
  return read_tape( STATIC_TEST_PATH( "invalid-custominfo.tzx" ), LIBSPECTRUM_ERROR_CORRUPT );
}

/* Test for bug #113: loop end without a loop start block accesses uninitialised
   memory */
test_return_t
tzx_loop_end_block_with_loop_start_block( void )
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
tzx_loop_blocks( void )
{
  return play_tape( STATIC_TEST_PATH( "loop.tzx" ) );
}

/* Test for bug #118: TZX loop blocks still broken */
test_return_t
tzx_loop_blocks_2( void )
{
  return play_tape( STATIC_TEST_PATH( "loop2.tzx" ) );
}

/* Test for bug #119: TZX jump blocks broken */
test_return_t
tzx_jump_blocks( void )
{
  return play_tape( STATIC_TEST_PATH( "jump.tzx" ) );
}

/* Test for bug #121: crashes writing and reading empty CSW files */
test_return_t
csw_empty_file( void )
{
  return play_tape( STATIC_TEST_PATH( "empty.csw" ) );
}

/* Test for bug #125: .tap writing code does not handle all block types */
test_return_t
complete_tzx_to_tap_conversion( void )
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

test_return_t
complete_tzx_timings( void )
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

/* Test for bug #379: converting .tap file to .csw causes crash */
test_return_t
csw_conversion( void )
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
tape_peek_next_block( void )
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
read_mono_wav_threshold_fixture( void )
{
#ifndef HAVE_WAV_BACKEND
  return TEST_SKIPPED;
#else
  return check_wav_block( DYNAMIC_TEST_PATH( "wav-mono-threshold.wav" ),
                          3500000 / 22050, 0xa9 );
#endif
}

test_return_t
read_stereo_wav_mixdown_fixture( void )
{
#ifndef WAV_INTERNAL_MACOS
  return TEST_SKIPPED;
#else
  return check_wav_block( DYNAMIC_TEST_PATH( "wav-stereo-mixdown.wav" ),
                          3500000 / 22050, 0x8d );
#endif
}

/* Test that PZX archive info tags (title + author) are correctly parsed.
   Regression test for the pzx_read_string bug where *ptr was set to end,
   causing all tag-value pairs after the title to be silently ignored. */
test_return_t
pzx_archive_info_tags_title_and_author_correctly_parsed( void )
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
    fprintf( stderr, "%s: snap_ay_registers_array_getter_setter_all_16_registers: no ARCHIVE_INFO block found\n", progname );
    goto done;
  }

  /* Expect: title (ID 0x00, "Test Game") and Author (ID 0x02, "Joe Bloggs") */
  if( libspectrum_tape_block_count( block ) != 2 ) {
    fprintf( stderr, "%s: snap_ay_registers_array_getter_setter_all_16_registers: expected 2 archive info entries, got %zu\n",
             progname, libspectrum_tape_block_count( block ) );
    r = TEST_FAIL;
    goto done;
  }

  if( libspectrum_tape_block_ids( block, 0 ) != 0x00 ) {
    fprintf( stderr, "%s: snap_ay_registers_array_getter_setter_all_16_registers: expected ID 0x00 for entry 0, got 0x%02x\n",
             progname, libspectrum_tape_block_ids( block, 0 ) );
    r = TEST_FAIL;
    goto done;
  }

  if( strcmp( libspectrum_tape_block_texts( block, 0 ), "Test Game" ) != 0 ) {
    fprintf( stderr, "%s: snap_ay_registers_array_getter_setter_all_16_registers: expected title 'Test Game', got '%s'\n",
             progname, libspectrum_tape_block_texts( block, 0 ) );
    r = TEST_FAIL;
    goto done;
  }

  if( libspectrum_tape_block_ids( block, 1 ) != 0x02 ) {
    fprintf( stderr, "%s: snap_ay_registers_array_getter_setter_all_16_registers: expected ID 0x02 (Author) for entry 1, got 0x%02x\n",
             progname, libspectrum_tape_block_ids( block, 1 ) );
    r = TEST_FAIL;
    goto done;
  }

  if( strcmp( libspectrum_tape_block_texts( block, 1 ), "Joe Bloggs" ) != 0 ) {
    fprintf( stderr, "%s: snap_ay_registers_array_getter_setter_all_16_registers: expected author 'Joe Bloggs', got '%s'\n",
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
tape_turbo_block_pilot_length_sync1_length_sync2_length_getter_setter( void )
{
  /* tape block: TURBO block pilot_length, sync1_length, sync2_length getter/setter */
  libspectrum_tape_block *block =
    libspectrum_tape_block_alloc( LIBSPECTRUM_TAPE_BLOCK_TURBO );
  test_return_t r = TEST_FAIL;

  if( !block ) {
    fprintf( stderr, "%s: tape_turbo_block_pilot_length_sync1_length_sync2_length_getter_setter: tape_block_alloc returned NULL\n", progname );
    return TEST_INCOMPLETE;
  }

  if( libspectrum_tape_block_type( block ) != LIBSPECTRUM_TAPE_BLOCK_TURBO ) {
    fprintf( stderr, "%s: tape_turbo_block_pilot_length_sync1_length_sync2_length_getter_setter: expected TURBO block type\n", progname );
    goto done;
  }

  if( libspectrum_tape_block_pilot_length( block ) != 0 ) {
    fprintf( stderr, "%s: tape_turbo_block_pilot_length_sync1_length_sync2_length_getter_setter: default pilot_length should be 0, got %lu\n",
             progname, (unsigned long)libspectrum_tape_block_pilot_length( block ) );
    goto done;
  }
  libspectrum_tape_block_set_pilot_length( block, 2168 );
  if( libspectrum_tape_block_pilot_length( block ) != 2168 ) {
    fprintf( stderr, "%s: tape_turbo_block_pilot_length_sync1_length_sync2_length_getter_setter: expected pilot_length=2168, got %lu\n",
             progname, (unsigned long)libspectrum_tape_block_pilot_length( block ) );
    goto done;
  }

  if( libspectrum_tape_block_sync1_length( block ) != 0 ) {
    fprintf( stderr, "%s: tape_turbo_block_pilot_length_sync1_length_sync2_length_getter_setter: default sync1_length should be 0, got %lu\n",
             progname, (unsigned long)libspectrum_tape_block_sync1_length( block ) );
    goto done;
  }
  libspectrum_tape_block_set_sync1_length( block, 667 );
  if( libspectrum_tape_block_sync1_length( block ) != 667 ) {
    fprintf( stderr, "%s: tape_turbo_block_pilot_length_sync1_length_sync2_length_getter_setter: expected sync1_length=667, got %lu\n",
             progname, (unsigned long)libspectrum_tape_block_sync1_length( block ) );
    goto done;
  }

  if( libspectrum_tape_block_sync2_length( block ) != 0 ) {
    fprintf( stderr, "%s: tape_turbo_block_pilot_length_sync1_length_sync2_length_getter_setter: default sync2_length should be 0, got %lu\n",
             progname, (unsigned long)libspectrum_tape_block_sync2_length( block ) );
    goto done;
  }
  libspectrum_tape_block_set_sync2_length( block, 735 );
  if( libspectrum_tape_block_sync2_length( block ) != 735 ) {
    fprintf( stderr, "%s: tape_turbo_block_pilot_length_sync1_length_sync2_length_getter_setter: expected sync2_length=735, got %lu\n",
             progname, (unsigned long)libspectrum_tape_block_sync2_length( block ) );
    goto done;
  }

  r = TEST_PASS;

done:
  libspectrum_tape_block_free( block );
  return r;
}

test_return_t
tape_turbo_block_bit0_length_bit1_length_pilot_pulses_pause_getter_setter( void )
{
  /* tape block: TURBO block bit0_length, bit1_length, pilot_pulses, pause getter/setter */
  libspectrum_tape_block *block =
    libspectrum_tape_block_alloc( LIBSPECTRUM_TAPE_BLOCK_TURBO );
  test_return_t r = TEST_FAIL;

  if( !block ) {
    fprintf( stderr, "%s: tape_turbo_block_bit0_length_bit1_length_pilot_pulses_pause_getter_setter: tape_block_alloc returned NULL\n", progname );
    return TEST_INCOMPLETE;
  }

  if( libspectrum_tape_block_bit0_length( block ) != 0 ) {
    fprintf( stderr, "%s: tape_turbo_block_bit0_length_bit1_length_pilot_pulses_pause_getter_setter: default bit0_length should be 0, got %lu\n",
             progname, (unsigned long)libspectrum_tape_block_bit0_length( block ) );
    goto done;
  }
  libspectrum_tape_block_set_bit0_length( block, 855 );
  if( libspectrum_tape_block_bit0_length( block ) != 855 ) {
    fprintf( stderr, "%s: tape_turbo_block_bit0_length_bit1_length_pilot_pulses_pause_getter_setter: expected bit0_length=855, got %lu\n",
             progname, (unsigned long)libspectrum_tape_block_bit0_length( block ) );
    goto done;
  }

  if( libspectrum_tape_block_bit1_length( block ) != 0 ) {
    fprintf( stderr, "%s: tape_turbo_block_bit0_length_bit1_length_pilot_pulses_pause_getter_setter: default bit1_length should be 0, got %lu\n",
             progname, (unsigned long)libspectrum_tape_block_bit1_length( block ) );
    goto done;
  }
  libspectrum_tape_block_set_bit1_length( block, 1710 );
  if( libspectrum_tape_block_bit1_length( block ) != 1710 ) {
    fprintf( stderr, "%s: tape_turbo_block_bit0_length_bit1_length_pilot_pulses_pause_getter_setter: expected bit1_length=1710, got %lu\n",
             progname, (unsigned long)libspectrum_tape_block_bit1_length( block ) );
    goto done;
  }

  if( libspectrum_tape_block_pilot_pulses( block ) != 0 ) {
    fprintf( stderr, "%s: tape_turbo_block_bit0_length_bit1_length_pilot_pulses_pause_getter_setter: default pilot_pulses should be 0, got %lu\n",
             progname, (unsigned long)libspectrum_tape_block_pilot_pulses( block ) );
    goto done;
  }
  libspectrum_tape_block_set_pilot_pulses( block, 8063 );
  if( libspectrum_tape_block_pilot_pulses( block ) != 8063 ) {
    fprintf( stderr, "%s: tape_turbo_block_bit0_length_bit1_length_pilot_pulses_pause_getter_setter: expected pilot_pulses=8063, got %lu\n",
             progname, (unsigned long)libspectrum_tape_block_pilot_pulses( block ) );
    goto done;
  }

  if( libspectrum_tape_block_pause( block ) != 0 ) {
    fprintf( stderr, "%s: tape_turbo_block_bit0_length_bit1_length_pilot_pulses_pause_getter_setter: default pause should be 0, got %lu\n",
             progname, (unsigned long)libspectrum_tape_block_pause( block ) );
    goto done;
  }
  libspectrum_tape_block_set_pause( block, 1000 );
  if( libspectrum_tape_block_pause( block ) != 1000 ) {
    fprintf( stderr, "%s: tape_turbo_block_bit0_length_bit1_length_pilot_pulses_pause_getter_setter: expected pause=1000, got %lu\n",
             progname, (unsigned long)libspectrum_tape_block_pause( block ) );
    goto done;
  }

  r = TEST_PASS;

done:
  libspectrum_tape_block_free( block );
  return r;
}

test_return_t
tape_pure_tone_block_pulse_length_and_count_getter_setter( void )
{
  /* tape block: PURE_TONE block pulse_length and count getter/setter */
  libspectrum_tape_block *block =
    libspectrum_tape_block_alloc( LIBSPECTRUM_TAPE_BLOCK_PURE_TONE );
  test_return_t r = TEST_FAIL;

  if( !block ) {
    fprintf( stderr, "%s: tape_pure_tone_block_pulse_length_and_count_getter_setter: tape_block_alloc returned NULL\n", progname );
    return TEST_INCOMPLETE;
  }

  if( libspectrum_tape_block_type( block ) != LIBSPECTRUM_TAPE_BLOCK_PURE_TONE ) {
    fprintf( stderr, "%s: tape_pure_tone_block_pulse_length_and_count_getter_setter: expected PURE_TONE block type\n", progname );
    goto done;
  }

  if( libspectrum_tape_block_pulse_length( block ) != 0 ) {
    fprintf( stderr, "%s: tape_pure_tone_block_pulse_length_and_count_getter_setter: default pulse_length should be 0, got %lu\n",
             progname, (unsigned long)libspectrum_tape_block_pulse_length( block ) );
    goto done;
  }
  libspectrum_tape_block_set_pulse_length( block, 2168 );
  if( libspectrum_tape_block_pulse_length( block ) != 2168 ) {
    fprintf( stderr, "%s: tape_pure_tone_block_pulse_length_and_count_getter_setter: expected pulse_length=2168, got %lu\n",
             progname, (unsigned long)libspectrum_tape_block_pulse_length( block ) );
    goto done;
  }

  if( libspectrum_tape_block_count( block ) != 0 ) {
    fprintf( stderr, "%s: tape_pure_tone_block_pulse_length_and_count_getter_setter: default count should be 0, got %lu\n",
             progname, (unsigned long)libspectrum_tape_block_count( block ) );
    goto done;
  }
  libspectrum_tape_block_set_count( block, 3223 );
  if( libspectrum_tape_block_count( block ) != 3223 ) {
    fprintf( stderr, "%s: tape_pure_tone_block_pulse_length_and_count_getter_setter: expected count=3223, got %lu\n",
             progname, (unsigned long)libspectrum_tape_block_count( block ) );
    goto done;
  }

  r = TEST_PASS;

done:
  libspectrum_tape_block_free( block );
  return r;
}

test_return_t
tape_pure_data_block_bit0_length_bit1_length_bits_in_last_byte_pause_getter_setter( void )
{
  /* tape block: PURE_DATA block bit0_length, bit1_length, bits_in_last_byte, pause getter/setter */
  libspectrum_tape_block *block =
    libspectrum_tape_block_alloc( LIBSPECTRUM_TAPE_BLOCK_PURE_DATA );
  test_return_t r = TEST_FAIL;

  if( !block ) {
    fprintf( stderr, "%s: tape_pure_data_block_bit0_length_bit1_length_bits_in_last_byte_pause_getter_setter: tape_block_alloc returned NULL\n", progname );
    return TEST_INCOMPLETE;
  }

  if( libspectrum_tape_block_type( block ) != LIBSPECTRUM_TAPE_BLOCK_PURE_DATA ) {
    fprintf( stderr, "%s: tape_pure_data_block_bit0_length_bit1_length_bits_in_last_byte_pause_getter_setter: expected PURE_DATA block type\n", progname );
    goto done;
  }

  if( libspectrum_tape_block_bit0_length( block ) != 0 ) {
    fprintf( stderr, "%s: tape_pure_data_block_bit0_length_bit1_length_bits_in_last_byte_pause_getter_setter: default bit0_length should be 0, got %lu\n",
             progname, (unsigned long)libspectrum_tape_block_bit0_length( block ) );
    goto done;
  }
  libspectrum_tape_block_set_bit0_length( block, 855 );
  if( libspectrum_tape_block_bit0_length( block ) != 855 ) {
    fprintf( stderr, "%s: tape_pure_data_block_bit0_length_bit1_length_bits_in_last_byte_pause_getter_setter: expected bit0_length=855, got %lu\n",
             progname, (unsigned long)libspectrum_tape_block_bit0_length( block ) );
    goto done;
  }

  if( libspectrum_tape_block_bit1_length( block ) != 0 ) {
    fprintf( stderr, "%s: tape_pure_data_block_bit0_length_bit1_length_bits_in_last_byte_pause_getter_setter: default bit1_length should be 0, got %lu\n",
             progname, (unsigned long)libspectrum_tape_block_bit1_length( block ) );
    goto done;
  }
  libspectrum_tape_block_set_bit1_length( block, 1710 );
  if( libspectrum_tape_block_bit1_length( block ) != 1710 ) {
    fprintf( stderr, "%s: tape_pure_data_block_bit0_length_bit1_length_bits_in_last_byte_pause_getter_setter: expected bit1_length=1710, got %lu\n",
             progname, (unsigned long)libspectrum_tape_block_bit1_length( block ) );
    goto done;
  }

  if( libspectrum_tape_block_bits_in_last_byte( block ) != 0 ) {
    fprintf( stderr, "%s: tape_pure_data_block_bit0_length_bit1_length_bits_in_last_byte_pause_getter_setter: default bits_in_last_byte should be 0, got %lu\n",
             progname, (unsigned long)libspectrum_tape_block_bits_in_last_byte( block ) );
    goto done;
  }
  libspectrum_tape_block_set_bits_in_last_byte( block, 8 );
  if( libspectrum_tape_block_bits_in_last_byte( block ) != 8 ) {
    fprintf( stderr, "%s: tape_pure_data_block_bit0_length_bit1_length_bits_in_last_byte_pause_getter_setter: expected bits_in_last_byte=8, got %lu\n",
             progname, (unsigned long)libspectrum_tape_block_bits_in_last_byte( block ) );
    goto done;
  }

  if( libspectrum_tape_block_pause( block ) != 0 ) {
    fprintf( stderr, "%s: tape_pure_data_block_bit0_length_bit1_length_bits_in_last_byte_pause_getter_setter: default pause should be 0, got %lu\n",
             progname, (unsigned long)libspectrum_tape_block_pause( block ) );
    goto done;
  }
  libspectrum_tape_block_set_pause( block, 500 );
  if( libspectrum_tape_block_pause( block ) != 500 ) {
    fprintf( stderr, "%s: tape_pure_data_block_bit0_length_bit1_length_bits_in_last_byte_pause_getter_setter: expected pause=500, got %lu\n",
             progname, (unsigned long)libspectrum_tape_block_pause( block ) );
    goto done;
  }

  r = TEST_PASS;

done:
  libspectrum_tape_block_free( block );
  return r;
}

test_return_t
tape_pause_block_pause_length_and_level_getter_setter( void )
{
  /* tape block: PAUSE block pause length and level getter/setter */
  libspectrum_tape_block *block =
    libspectrum_tape_block_alloc( LIBSPECTRUM_TAPE_BLOCK_PAUSE );
  test_return_t r = TEST_FAIL;

  if( !block ) {
    fprintf( stderr, "%s: tape_pause_block_pause_length_and_level_getter_setter: tape_block_alloc returned NULL\n", progname );
    return TEST_INCOMPLETE;
  }

  if( libspectrum_tape_block_type( block ) != LIBSPECTRUM_TAPE_BLOCK_PAUSE ) {
    fprintf( stderr, "%s: tape_pause_block_pause_length_and_level_getter_setter: expected PAUSE block type\n", progname );
    goto done;
  }

  if( libspectrum_tape_block_pause( block ) != 0 ) {
    fprintf( stderr, "%s: tape_pause_block_pause_length_and_level_getter_setter: default pause should be 0, got %lu\n",
             progname, (unsigned long)libspectrum_tape_block_pause( block ) );
    goto done;
  }
  libspectrum_tape_block_set_pause( block, 2000 );
  if( libspectrum_tape_block_pause( block ) != 2000 ) {
    fprintf( stderr, "%s: tape_pause_block_pause_length_and_level_getter_setter: expected pause=2000, got %lu\n",
             progname, (unsigned long)libspectrum_tape_block_pause( block ) );
    goto done;
  }

  if( libspectrum_tape_block_level( block ) != 0 ) {
    fprintf( stderr, "%s: tape_pause_block_pause_length_and_level_getter_setter: default level should be 0, got %d\n",
             progname, libspectrum_tape_block_level( block ) );
    goto done;
  }
  libspectrum_tape_block_set_level( block, 1 );
  if( libspectrum_tape_block_level( block ) != 1 ) {
    fprintf( stderr, "%s: tape_pause_block_pause_length_and_level_getter_setter: expected level=1, got %d\n",
             progname, libspectrum_tape_block_level( block ) );
    goto done;
  }

  r = TEST_PASS;

done:
  libspectrum_tape_block_free( block );
  return r;
}

test_return_t
tape_rom_block_data_data_length_and_pause_getter_setter( void )
{
  /* tape block: ROM block data, data_length, and pause getter/setter */
  libspectrum_tape_block *block =
    libspectrum_tape_block_alloc( LIBSPECTRUM_TAPE_BLOCK_ROM );
  test_return_t r = TEST_FAIL;
  libspectrum_byte *data;

  if( !block ) {
    fprintf( stderr, "%s: tape_rom_block_data_data_length_and_pause_getter_setter: tape_block_alloc returned NULL\n", progname );
    return TEST_INCOMPLETE;
  }

  if( libspectrum_tape_block_type( block ) != LIBSPECTRUM_TAPE_BLOCK_ROM ) {
    fprintf( stderr, "%s: tape_rom_block_data_data_length_and_pause_getter_setter: expected ROM block type\n", progname );
    goto done;
  }

  if( libspectrum_tape_block_data( block ) != NULL ) {
    fprintf( stderr, "%s: tape_rom_block_data_data_length_and_pause_getter_setter: default data should be NULL\n", progname );
    goto done;
  }

  if( libspectrum_tape_block_data_length( block ) != 0 ) {
    fprintf( stderr, "%s: tape_rom_block_data_data_length_and_pause_getter_setter: default data_length should be 0, got %lu\n",
             progname, (unsigned long)libspectrum_tape_block_data_length( block ) );
    goto done;
  }

  data = libspectrum_malloc( 3 );
  data[0] = 0x00; data[1] = 0x01; data[2] = 0x02;
  libspectrum_tape_block_set_data_length( block, 3 );
  libspectrum_tape_block_set_data( block, data );

  if( libspectrum_tape_block_data_length( block ) != 3 ) {
    fprintf( stderr, "%s: tape_rom_block_data_data_length_and_pause_getter_setter: expected data_length=3, got %lu\n",
             progname, (unsigned long)libspectrum_tape_block_data_length( block ) );
    goto done;
  }

  if( libspectrum_tape_block_data( block ) != data ) {
    fprintf( stderr, "%s: tape_rom_block_data_data_length_and_pause_getter_setter: data pointer mismatch\n", progname );
    goto done;
  }

  if( libspectrum_tape_block_pause( block ) != 0 ) {
    fprintf( stderr, "%s: tape_rom_block_data_data_length_and_pause_getter_setter: default pause should be 0, got %lu\n",
             progname, (unsigned long)libspectrum_tape_block_pause( block ) );
    goto done;
  }

  libspectrum_tape_block_set_pause( block, 1000 );
  if( libspectrum_tape_block_pause( block ) != 1000 ) {
    fprintf( stderr, "%s: tape_rom_block_data_data_length_and_pause_getter_setter: expected pause=1000, got %lu\n",
             progname, (unsigned long)libspectrum_tape_block_pause( block ) );
    goto done;
  }

  r = TEST_PASS;

done:
  libspectrum_tape_block_free( block );
  return r;
}
