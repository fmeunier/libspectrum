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
