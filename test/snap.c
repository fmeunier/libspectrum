#include "config.h"

#include <stdio.h>
#include <string.h>

#include "internals.h"
#include "common.h"
#include "test.h"

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
