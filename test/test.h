#ifndef TEST_TEST_H
#define TEST_TEST_H

#include "libspectrum.h"

extern const char *progname;

typedef enum test_return_t {
  TEST_PASS,
  TEST_FAIL,
  TEST_INCOMPLETE,
  TEST_SKIPPED,
} test_return_t;

typedef struct test_edge_sequence_t {

  libspectrum_dword length;
  size_t count;
  int flags;

} test_edge_sequence_t;

#define STATIC_TEST_PATH(x) SRCDIR "/test/" x
#define DYNAMIC_TEST_PATH(x) "test/" x

int read_file( libspectrum_byte **buffer, size_t *length,
	       const char *filename );

test_return_t check_edges( const char *filename, test_edge_sequence_t *edges,
			   int flags_mask );

test_return_t test_1( void );
test_return_t test_2( void );
test_return_t test_3( void );
test_return_t test_4( void );
test_return_t test_5( void );
test_return_t test_6( void );
test_return_t test_7( void );
test_return_t test_8( void );
test_return_t test_9( void );
test_return_t test_10( void );
test_return_t test_11( void );
test_return_t test_12( void );
test_return_t test_13( void );
test_return_t test_14( void );
test_return_t test_15( void );
test_return_t test_16( void );
test_return_t test_17( void );
test_return_t test_18( void );
test_return_t test_19( void );
test_return_t test_20( void );
test_return_t test_21( void );
test_return_t test_22( void );
test_return_t test_23( void );
test_return_t test_24( void );
test_return_t test_25( void );
test_return_t test_26( void );
test_return_t test_27( void );
test_return_t test_28( void );
test_return_t test_29( void );
test_return_t test_30( void );
test_return_t test_31( void );
test_return_t test_32( void );
test_return_t test_33( void );
test_return_t test_34( void );
test_return_t test_35( void );
test_return_t test_36( void );
test_return_t test_37( void );
test_return_t test_38( void );
test_return_t test_39( void );
test_return_t test_40( void );
test_return_t test_41( void );
test_return_t test_42( void );
test_return_t test_43( void );
test_return_t test_44( void );
test_return_t test_45( void );
test_return_t test_46( void );
test_return_t test_47( void );
test_return_t test_48( void );
test_return_t test_49( void );
test_return_t test_50( void );
test_return_t test_51( void );
test_return_t test_52( void );
test_return_t test_53( void );
test_return_t test_54( void );
test_return_t test_55( void );
test_return_t test_56( void );
test_return_t test_57( void );
test_return_t test_58( void );
test_return_t test_59( void );
test_return_t test_60( void );
test_return_t test_61( void );
test_return_t test_62( void );
test_return_t test_63( void );
test_return_t test_64( void );
test_return_t test_65( void );
test_return_t test_66( void );
test_return_t test_67( void );
test_return_t test_68( void );
test_return_t test_69( void );
test_return_t test_70( void );
test_return_t test_71( void );
test_return_t test_72( void );
test_return_t test_73( void );
test_return_t test_74( void );
test_return_t test_75( void );
test_return_t test_76( void );
test_return_t test_77( void );
test_return_t test_78( void );
test_return_t test_79( void );
test_return_t test_80( void );
test_return_t test_81( void );
test_return_t test_82( void );
test_return_t test_83( void );
test_return_t test_84( void );
test_return_t test_85( void );
test_return_t test_86( void );
test_return_t test_87( void );
test_return_t test_88( void );
test_return_t test_89( void );
test_return_t test_90( void );
test_return_t test_91( void );
test_return_t test_92( void );
test_return_t test_93( void );
test_return_t test_94( void );
test_return_t test_95( void );
test_return_t test_96( void );
test_return_t test_97( void );
test_return_t test_98( void );
test_return_t test_99( void );
test_return_t test_100( void );
test_return_t test_101( void );
test_return_t test_102( void );
test_return_t test_103( void );
test_return_t test_104( void );
test_return_t test_105( void );
test_return_t test_106( void );
test_return_t test_107( void );
test_return_t test_108( void );
test_return_t test_109( void );
test_return_t test_110( void );
test_return_t test_111( void );
test_return_t test_112( void );
test_return_t test_113( void );
test_return_t test_114( void );
test_return_t test_115( void );
test_return_t test_116( void );
test_return_t test_117( void );
test_return_t test_118( void );
test_return_t test_119( void );
test_return_t test_120( void );
test_return_t test_121( void );
test_return_t test_122( void );
test_return_t test_123( void );
test_return_t test_124( void );
test_return_t test_125( void );
test_return_t test_126( void );
test_return_t test_127( void );
test_return_t test_128( void );
test_return_t test_129( void );
test_return_t test_130( void );
test_return_t test_131( void );
test_return_t test_132( void );
test_return_t test_133( void );
test_return_t test_134( void );
test_return_t test_135( void );
test_return_t test_136( void );
test_return_t test_137( void );
test_return_t test_138( void );
test_return_t test_139( void );
test_return_t test_140( void );
test_return_t test_141( void );
test_return_t test_142( void );
test_return_t test_143( void );

#endif
