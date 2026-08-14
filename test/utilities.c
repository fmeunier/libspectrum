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

/* NULL source is invalid */
test_return_t
utilities_zx_string_to_utf8_null_source_is_invalid( void )
{
  char result[ 46 ];

  if( libspectrum_zx_string_to_utf8( result, sizeof( result ), NULL, 5 ) !=
      LIBSPECTRUM_ERROR_INVALID ) {
    fprintf( stderr, "%s: utilities_zx_string_to_utf8_null_source_is_invalid: "
             "expected LIBSPECTRUM_ERROR_INVALID\n", progname );
    return TEST_FAIL;
  }

  return TEST_PASS;
}

/* Plain ASCII text is passed through unchanged */
test_return_t
utilities_zx_string_to_utf8_plain_ascii( void )
{
  static const libspectrum_byte src[] = { 'H', 'E', 'L', 'L', 'O' };
  char result[ sizeof( src ) * 9 + 1 ];

  if( libspectrum_zx_string_to_utf8( result, sizeof( result ), src,
                                     sizeof( src ) ) ) {
    fprintf( stderr, "%s: utilities_zx_string_to_utf8_plain_ascii: "
             "conversion failed\n", progname );
    return TEST_FAIL;
  }

  if( strcmp( result, "HELLO" ) != 0 ) {
    fprintf( stderr, "%s: utilities_zx_string_to_utf8_plain_ascii: "
             "expected \"HELLO\", got \"%s\"\n", progname, result );
    return TEST_FAIL;
  }

  return TEST_PASS;
}

/* Trailing spaces are stripped before conversion */
test_return_t
utilities_zx_string_to_utf8_trailing_spaces_stripped( void )
{
  static const libspectrum_byte src[] = { 'H', 'I', ' ', ' ', ' ' };
  char result[ sizeof( src ) * 9 + 1 ];

  if( libspectrum_zx_string_to_utf8( result, sizeof( result ), src,
                                     sizeof( src ) ) ) {
    fprintf( stderr, "%s: utilities_zx_string_to_utf8_trailing_spaces_stripped: "
             "conversion failed\n", progname );
    return TEST_FAIL;
  }

  if( strcmp( result, "HI" ) != 0 ) {
    fprintf( stderr, "%s: utilities_zx_string_to_utf8_trailing_spaces_stripped: "
             "expected \"HI\", got \"%s\"\n", progname, result );
    return TEST_FAIL;
  }

  return TEST_PASS;
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
  char result[ sizeof( src ) * 9 + 1 ];

  if( libspectrum_zx_string_to_utf8( result, sizeof( result ), src,
                                     sizeof( src ) ) ) {
    fprintf( stderr, "%s: utilities_zx_string_to_utf8_special_chars: "
             "conversion failed\n", progname );
    return TEST_FAIL;
  }

  /* expected: "\\" + "↑" + "£" + "©" */
  if( strcmp( result, "\\\\" "\xe2\x86\x91" "\xc2\xa3" "\xc2\xa9" ) != 0 ) {
    fprintf( stderr, "%s: utilities_zx_string_to_utf8_special_chars: "
             "unexpected result\n", progname );
    return TEST_FAIL;
  }

  return TEST_PASS;
}

/* UDG characters (bytes 144–164) render as \a through \u */
test_return_t
utilities_zx_string_to_utf8_udg_char( void )
{
  /* 0x90 = 144 -> UDG 'a' -> rendered as \a */
  static const libspectrum_byte src[] = { 0x90 };
  char result[ sizeof( src ) * 9 + 1 ];

  if( libspectrum_zx_string_to_utf8( result, sizeof( result ), src,
                                     sizeof( src ) ) ) {
    fprintf( stderr, "%s: utilities_zx_string_to_utf8_udg_char: "
             "conversion failed\n", progname );
    return TEST_FAIL;
  }

  if( strcmp( result, "\\a" ) != 0 ) {
    fprintf( stderr, "%s: utilities_zx_string_to_utf8_udg_char: "
             "expected \"\\\\a\", got \"%s\"\n", progname, result );
    return TEST_FAIL;
  }

  return TEST_PASS;
}

/* Spectrum BASIC keyword tokens (bytes >= 165) expand to keyword text.
   Byte 0xFB = 251 = 165 + 86 -> spectrum_tokens[86] = "RANDOMIZE" */
test_return_t
utilities_zx_string_to_utf8_spectrum_token( void )
{
  static const libspectrum_byte src[] = { 0xfb };
  char result[ sizeof( src ) * 9 + 1 ];

  if( libspectrum_zx_string_to_utf8( result, sizeof( result ), src,
                                     sizeof( src ) ) ) {
    fprintf( stderr, "%s: utilities_zx_string_to_utf8_spectrum_token: "
             "conversion failed\n", progname );
    return TEST_FAIL;
  }

  if( strcmp( result, "RANDOMIZE" ) != 0 ) {
    fprintf( stderr, "%s: utilities_zx_string_to_utf8_spectrum_token: "
             "expected \"RANDOMIZE\", got \"%s\"\n", progname, result );
    return TEST_FAIL;
  }

  return TEST_PASS;
}

/* A buffer without space for the terminating NUL is rejected */
test_return_t
utilities_zx_string_to_utf8_buffer_too_short_is_invalid( void )
{
  static const libspectrum_byte src[] = { 0xfb };
  char result[ 9 ];

  if( libspectrum_zx_string_to_utf8( result, sizeof( result ), src,
                                     sizeof( src ) ) != LIBSPECTRUM_ERROR_INVALID ) {
    fprintf( stderr, "%s: utilities_zx_string_to_utf8_buffer_too_short_is_invalid: "
             "expected LIBSPECTRUM_ERROR_INVALID\n", progname );
    return TEST_FAIL;
  }

  if( strcmp( result, "" ) != 0 ) {
    fprintf( stderr, "%s: utilities_zx_string_to_utf8_buffer_too_short_is_invalid: "
             "expected empty result\n", progname );
    return TEST_FAIL;
  }

  return TEST_PASS;
}

/* libspectrum_version: returns a non-NULL, non-empty string */
test_return_t
utilities_version_returns_nonempty_string( void )
{
  const char *ver = libspectrum_version();
  if( !ver || ver[0] == '\0' ) {
    fprintf( stderr, "%s: utilities_version_returns_nonempty_string: "
             "expected non-empty version string\n", progname );
    return TEST_FAIL;
  }
  return TEST_PASS;
}

/* libspectrum_check_version: current version satisfies itself */
test_return_t
utilities_check_version_current_version_returns_true( void )
{
  const char *ver = libspectrum_version();
  if( !libspectrum_check_version( ver ) ) {
    fprintf( stderr, "%s: utilities_check_version_current_version_returns_true: "
             "expected 1 for version \"%s\"\n", progname, ver );
    return TEST_FAIL;
  }
  return TEST_PASS;
}

/* libspectrum_check_version: very old required version (0.0.0) is satisfied */
test_return_t
utilities_check_version_very_old_required_returns_true( void )
{
  if( !libspectrum_check_version( "0.0.0" ) ) {
    fprintf( stderr, "%s: utilities_check_version_very_old_required_returns_true: "
             "expected 1 for version \"0.0.0\"\n", progname );
    return TEST_FAIL;
  }
  return TEST_PASS;
}

/* libspectrum_check_version: future major version (99.0.0) is not satisfied */
test_return_t
utilities_check_version_future_major_returns_false( void )
{
  if( libspectrum_check_version( "99.0.0" ) ) {
    fprintf( stderr, "%s: utilities_check_version_future_major_returns_false: "
             "expected 0 for version \"99.0.0\"\n", progname );
    return TEST_FAIL;
  }
  return TEST_PASS;
}

/* Graphics block tokens (bytes 128-143) render as four-character \XX sequences */
test_return_t
utilities_zx_string_to_utf8_graphics_token( void )
{
  /* 0x80 = 128 -> graphics_tokens[0] = "\\  " (space-space block) */
  static const libspectrum_byte src[] = { 0x80 };
  char result[ sizeof( src ) * 9 + 1 ];

  if( libspectrum_zx_string_to_utf8( result, sizeof( result ), src,
                                     sizeof( src ) ) ) {
    fprintf( stderr, "%s: utilities_zx_string_to_utf8_graphics_token: "
             "conversion failed\n", progname );
    return TEST_FAIL;
  }

  if( strcmp( result, "\\  " ) != 0 ) {
    fprintf( stderr, "%s: utilities_zx_string_to_utf8_graphics_token: "
             "expected \"\\\\ \", got \"%s\"\n", progname, result );
    return TEST_FAIL;
  }

  return TEST_PASS;
}

/* Control characters (bytes 0-31, excluding handled specials) render as "?" */
test_return_t
utilities_zx_string_to_utf8_control_char( void )
{
  /* 0x01 is a control character, not specially handled */
  static const libspectrum_byte src[] = { 0x01 };
  char result[ sizeof( src ) * 9 + 1 ];

  if( libspectrum_zx_string_to_utf8( result, sizeof( result ), src,
                                     sizeof( src ) ) ) {
    fprintf( stderr, "%s: utilities_zx_string_to_utf8_control_char: "
             "conversion failed\n", progname );
    return TEST_FAIL;
  }

  if( strcmp( result, "?" ) != 0 ) {
    fprintf( stderr, "%s: utilities_zx_string_to_utf8_control_char: "
             "expected \"?\", got \"%s\"\n", progname, result );
    return TEST_FAIL;
  }

  return TEST_PASS;
}

/* Empty source string produces empty output */
test_return_t
utilities_zx_string_to_utf8_empty_source( void )
{
  static const libspectrum_byte src[] = { 0 };
  char result[ 16 ];

  if( libspectrum_zx_string_to_utf8( result, sizeof( result ), src, 0 ) ) {
    fprintf( stderr, "%s: utilities_zx_string_to_utf8_empty_source: "
             "conversion failed\n", progname );
    return TEST_FAIL;
  }

  if( strcmp( result, "" ) != 0 ) {
    fprintf( stderr, "%s: utilities_zx_string_to_utf8_empty_source: "
             "expected empty string, got \"%s\"\n", progname, result );
    return TEST_FAIL;
  }

  return TEST_PASS;
}
