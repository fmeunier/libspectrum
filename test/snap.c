#include "config.h"

#include <stdio.h>
#include <string.h>

#include "internals.h"
#include "common.h"
#include "test.h"

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

/* Test that PZX archive info tags (title + author) are correctly parsed.
   Regression test for the pzx_read_string bug where *ptr was set to end,
   causing all tag-value pairs after the title to be silently ignored. */

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
