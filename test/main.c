#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "registry.h"
#include "test.h"

const char *progname;
static const char *LIBSPECTRUM_MIN_VERSION = "0.4.0";

static void
parse_test_specs( char **specs, int count )
{
  int i, j;

  for( i = 0; i < count; i++ ) {

    const char *spec = specs[i];
    const char *dash = strchr( spec, '-' );

    if( dash ) {
      int begin = atoi( spec ), end = atoi( dash + 1 );
      if( begin < 1 ) begin = 1;
      if( end == 0 || end > test_count ) end = test_count;
      for( j = begin; j <= end; j++ ) tests[j-1].active = 1;
    } else {
      int test = atoi( spec );
      if( test < 1 || test > test_count ) continue;
      tests[ test - 1 ].active = 1;
    }

  }
}

int
main( int argc, char *argv[] )
{
  test_description *test;
  size_t i;
  int tests_done = 0, tests_skipped = 0;
  int pass = 0, fail = 0, incomplete = 0;

  progname = argv[0];

  if( libspectrum_check_version( LIBSPECTRUM_MIN_VERSION ) ) {
    if( libspectrum_init() ) return 2;
  } else {
    fprintf( stderr, "%s: libspectrum version %s found, but %s required",
	     progname, libspectrum_version(), LIBSPECTRUM_MIN_VERSION );
    return 2;
  }

  if( argc < 2 ) {
    for( i = 0; i < test_count; i++ ) tests[i].active = 1;
  } else {
    parse_test_specs( &argv[1], argc - 1 );
  }

  for( i = 0, test = tests;
       i < test_count;
       i++, test++ ) {
    printf( "Test %d: %s... ", (int)i + 1, test->description );
    if( test->active ) {
      tests_done++;
      switch( test->test() ) {
      case TEST_PASS:
        /* Test executed completely and passed */
	      printf( "passed\n" );
	      pass++;
	      break;
      case TEST_FAIL:
        /* Test executed completely but failed */
	      printf( "FAILED\n" );
	      fail++;
	      break;
      case TEST_INCOMPLETE:
        /* Error occurred while executing test */
	      printf( "NOT COMPLETE\n" );
	      incomplete++;
	      break;
      case TEST_SKIPPED:
        /* Not possible to run this test (missing dependencies) */
	      printf( "skipped\n" );
	      tests_skipped++;
	      break;
      }
    } else {
      tests_skipped++;
      printf( "skipped\n" );
    }

  }

  /* Stop silly divisions occuring */
  if( !tests_done ) tests_done = 1;

  printf( "\n%3d tests run\n\n", (int)test_count );
  printf( "%3d     passed (%6.2f%%)\n", pass, 100 * (float)pass/tests_done );
  printf( "%3d     failed (%6.2f%%)\n", fail, 100 * (float)fail/tests_done );
  printf( "%3d incomplete (%6.2f%%)\n", incomplete, 100 * (float)incomplete/tests_done );
  printf( "%3d    skipped\n", tests_skipped );

  if( fail == 0 && incomplete == 0 ) {
    return 0;
  } else {
    return 1;
  }
}
