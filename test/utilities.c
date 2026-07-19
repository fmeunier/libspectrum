/* utilities.c: unit tests for libspectrum utility functions
   Copyright (c) 2026 Philip Kendall

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License along
   with this program; if not, write to the Free Software Foundation, Inc.,
   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

   Author contact information:

   E-mail: philip-fuse@shadowmagic.org.uk

*/

#include "config.h"

#include <stdio.h>
#include <string.h>

#include "internals.h"
#include "test.h"

/* TZX_HZ is 3500000, so tstates_per_ms = 3500 */
#define TSTATES_PER_MS 3500

/* ms_to_tstates: 0ms -> 0 t-states */
test_return_t
utilities_ms_to_tstates_zero( void )
{
  libspectrum_dword result = libspectrum_ms_to_tstates( 0 );
  if( result != 0 ) {
    fprintf( stderr, "%s: utilities_ms_to_tstates_zero: expected 0, got %lu\n",
             progname, (unsigned long)result );
    return TEST_FAIL;
  }
  return TEST_PASS;
}

/* ms_to_tstates: 1ms -> 3500 t-states */
test_return_t
utilities_ms_to_tstates_one_ms( void )
{
  libspectrum_dword result = libspectrum_ms_to_tstates( 1 );
  if( result != TSTATES_PER_MS ) {
    fprintf( stderr, "%s: utilities_ms_to_tstates_one_ms: expected %d, got %lu\n",
             progname, TSTATES_PER_MS, (unsigned long)result );
    return TEST_FAIL;
  }
  return TEST_PASS;
}

/* ms_to_tstates: 1000ms -> 3500000 t-states */
test_return_t
utilities_ms_to_tstates_one_second( void )
{
  libspectrum_dword result = libspectrum_ms_to_tstates( 1000 );
  if( result != 3500000 ) {
    fprintf( stderr, "%s: utilities_ms_to_tstates_one_second: expected 3500000, got %lu\n",
             progname, (unsigned long)result );
    return TEST_FAIL;
  }
  return TEST_PASS;
}

/* tstates_to_ms: 0 t-states -> 0ms */
test_return_t
utilities_tstates_to_ms_zero( void )
{
  libspectrum_dword result = libspectrum_tstates_to_ms( 0 );
  if( result != 0 ) {
    fprintf( stderr, "%s: utilities_tstates_to_ms_zero: expected 0, got %lu\n",
             progname, (unsigned long)result );
    return TEST_FAIL;
  }
  return TEST_PASS;
}

/* tstates_to_ms: 3500 t-states -> 1ms */
test_return_t
utilities_tstates_to_ms_one_ms( void )
{
  libspectrum_dword result = libspectrum_tstates_to_ms( TSTATES_PER_MS );
  if( result != 1 ) {
    fprintf( stderr, "%s: utilities_tstates_to_ms_one_ms: expected 1, got %lu\n",
             progname, (unsigned long)result );
    return TEST_FAIL;
  }
  return TEST_PASS;
}

/* tstates_to_ms: fractional (3499 t-states) truncates to 0ms */
test_return_t
utilities_tstates_to_ms_truncates( void )
{
  libspectrum_dword result = libspectrum_tstates_to_ms( TSTATES_PER_MS - 1 );
  if( result != 0 ) {
    fprintf( stderr, "%s: utilities_tstates_to_ms_truncates: expected 0, got %lu\n",
             progname, (unsigned long)result );
    return TEST_FAIL;
  }
  return TEST_PASS;
}

/* tstates_to_ms: 3500000 t-states -> 1000ms */
test_return_t
utilities_tstates_to_ms_one_second( void )
{
  libspectrum_dword result = libspectrum_tstates_to_ms( 3500000 );
  if( result != 1000 ) {
    fprintf( stderr, "%s: utilities_tstates_to_ms_one_second: expected 1000, got %lu\n",
             progname, (unsigned long)result );
    return TEST_FAIL;
  }
  return TEST_PASS;
}

/* bits_to_bytes: 0 bits -> 0 bytes */
test_return_t
utilities_bits_to_bytes_zero( void )
{
  size_t result = libspectrum_bits_to_bytes( 0 );
  if( result != 0 ) {
    fprintf( stderr, "%s: utilities_bits_to_bytes_zero: expected 0, got %zu\n",
             progname, result );
    return TEST_FAIL;
  }
  return TEST_PASS;
}

/* bits_to_bytes: 1 bit -> 1 byte (rounds up) */
test_return_t
utilities_bits_to_bytes_one_bit( void )
{
  size_t result = libspectrum_bits_to_bytes( 1 );
  if( result != 1 ) {
    fprintf( stderr, "%s: utilities_bits_to_bytes_one_bit: expected 1, got %zu\n",
             progname, result );
    return TEST_FAIL;
  }
  return TEST_PASS;
}

/* bits_to_bytes: 8 bits -> 1 byte (exact) */
test_return_t
utilities_bits_to_bytes_exact_byte( void )
{
  size_t result = libspectrum_bits_to_bytes( 8 );
  if( result != 1 ) {
    fprintf( stderr, "%s: utilities_bits_to_bytes_exact_byte: expected 1, got %zu\n",
             progname, result );
    return TEST_FAIL;
  }
  return TEST_PASS;
}

/* bits_to_bytes: 9 bits -> 2 bytes (rounds up) */
test_return_t
utilities_bits_to_bytes_nine_bits( void )
{
  size_t result = libspectrum_bits_to_bytes( 9 );
  if( result != 2 ) {
    fprintf( stderr, "%s: utilities_bits_to_bytes_nine_bits: expected 2, got %zu\n",
             progname, result );
    return TEST_FAIL;
  }
  return TEST_PASS;
}

/* bits_to_bytes: 24 bits -> 3 bytes (exact) */
test_return_t
utilities_bits_to_bytes_twenty_four_bits( void )
{
  size_t result = libspectrum_bits_to_bytes( 24 );
  if( result != 3 ) {
    fprintf( stderr, "%s: utilities_bits_to_bytes_twenty_four_bits: expected 3, got %zu\n",
             progname, result );
    return TEST_FAIL;
  }
  return TEST_PASS;
}

/* NULL source returns NULL */
test_return_t
utilities_zx_string_to_utf8_null_returns_null( void )
{
  char *result = libspectrum_zx_string_to_utf8( NULL, 5 );

  if( result != NULL ) {
    fprintf( stderr, "%s: utilities_zx_string_to_utf8_null_returns_null: "
             "expected NULL, got non-NULL\n", progname );
    libspectrum_free( result );
    return TEST_FAIL;
  }

  return TEST_PASS;
}

/* Plain ASCII text is passed through unchanged */
test_return_t
utilities_zx_string_to_utf8_plain_ascii( void )
{
  static const libspectrum_byte src[] = { 'H', 'E', 'L', 'L', 'O' };
  char *result;
  test_return_t r = TEST_FAIL;

  result = libspectrum_zx_string_to_utf8( src, sizeof( src ) );
  if( !result ) {
    fprintf( stderr, "%s: utilities_zx_string_to_utf8_plain_ascii: "
             "returned NULL\n", progname );
    return TEST_INCOMPLETE;
  }

  if( strcmp( result, "HELLO" ) != 0 ) {
    fprintf( stderr, "%s: utilities_zx_string_to_utf8_plain_ascii: "
             "expected \"HELLO\", got \"%s\"\n", progname, result );
    goto done;
  }

  r = TEST_PASS;

done:
  libspectrum_free( result );
  return r;
}

/* Trailing spaces are stripped before conversion */
test_return_t
utilities_zx_string_to_utf8_trailing_spaces_stripped( void )
{
  static const libspectrum_byte src[] = { 'H', 'I', ' ', ' ', ' ' };
  char *result;
  test_return_t r = TEST_FAIL;

  result = libspectrum_zx_string_to_utf8( src, sizeof( src ) );
  if( !result ) {
    fprintf( stderr, "%s: utilities_zx_string_to_utf8_trailing_spaces_stripped: "
             "returned NULL\n", progname );
    return TEST_INCOMPLETE;
  }

  if( strcmp( result, "HI" ) != 0 ) {
    fprintf( stderr, "%s: utilities_zx_string_to_utf8_trailing_spaces_stripped: "
             "expected \"HI\", got \"%s\"\n", progname, result );
    goto done;
  }

  r = TEST_PASS;

done:
  libspectrum_free( result );
  return r;
}

/* ZX Spectrum special characters convert to Unicode equivalents:
   0x5C (\) -> \\, 0x5E (^) -> U+2191 (↑), 0x60 (`) -> U+00A3 (£),
   0x7F -> U+00A9 (©) */
test_return_t
utilities_zx_string_to_utf8_special_chars( void )
{
  static const libspectrum_byte src[] = {
    '\\', '^', '`', 0x7f
  };
  char *result;
  test_return_t r = TEST_FAIL;

  result = libspectrum_zx_string_to_utf8( src, sizeof( src ) );
  if( !result ) {
    fprintf( stderr, "%s: utilities_zx_string_to_utf8_special_chars: "
             "returned NULL\n", progname );
    return TEST_INCOMPLETE;
  }

  /* expected: "\\" + "↑" + "£" + "©" */
  if( strcmp( result, "\\\\" "\xe2\x86\x91" "\xc2\xa3" "\xc2\xa9" ) != 0 ) {
    fprintf( stderr, "%s: utilities_zx_string_to_utf8_special_chars: "
             "unexpected result\n", progname );
    goto done;
  }

  r = TEST_PASS;

done:
  libspectrum_free( result );
  return r;
}

/* UDG characters (bytes 144–164) render as \a through \u */
test_return_t
utilities_zx_string_to_utf8_udg_char( void )
{
  /* 0x90 = 144 -> UDG 'a' -> rendered as \a */
  static const libspectrum_byte src[] = { 0x90 };
  char *result;
  test_return_t r = TEST_FAIL;

  result = libspectrum_zx_string_to_utf8( src, sizeof( src ) );
  if( !result ) {
    fprintf( stderr, "%s: utilities_zx_string_to_utf8_udg_char: "
             "returned NULL\n", progname );
    return TEST_INCOMPLETE;
  }

  if( strcmp( result, "\\a" ) != 0 ) {
    fprintf( stderr, "%s: utilities_zx_string_to_utf8_udg_char: "
             "expected \"\\\\a\", got \"%s\"\n", progname, result );
    goto done;
  }

  r = TEST_PASS;

done:
  libspectrum_free( result );
  return r;
}

/* Spectrum BASIC keyword tokens (bytes >= 165) expand to keyword text.
   Byte 0xFB = 251 = 165 + 86 -> spectrum_tokens[86] = "RANDOMIZE" */
test_return_t
utilities_zx_string_to_utf8_spectrum_token( void )
{
  static const libspectrum_byte src[] = { 0xfb };
  char *result;
  test_return_t r = TEST_FAIL;

  result = libspectrum_zx_string_to_utf8( src, sizeof( src ) );
  if( !result ) {
    fprintf( stderr, "%s: utilities_zx_string_to_utf8_spectrum_token: "
             "returned NULL\n", progname );
    return TEST_INCOMPLETE;
  }

  if( strcmp( result, "RANDOMIZE" ) != 0 ) {
    fprintf( stderr, "%s: utilities_zx_string_to_utf8_spectrum_token: "
             "expected \"RANDOMIZE\", got \"%s\"\n", progname, result );
    goto done;
  }

  r = TEST_PASS;

done:
  libspectrum_free( result );
  return r;
}
