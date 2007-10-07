// $Id$

#include <cppunit/extensions/HelperMacros.h>

#include <stx-string.h>

class SimpleTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( SimpleTest );
    CPPUNIT_TEST(test_trim);
    CPPUNIT_TEST(test_toupper_tolower);
    CPPUNIT_TEST(test_compare_icase);
    CPPUNIT_TEST(test_prefix_suffix);
    CPPUNIT_TEST(test_replace);
    CPPUNIT_TEST(test_split_ws);
    CPPUNIT_TEST(test_split);
    CPPUNIT_TEST_SUITE_END();

protected:

    void test_trim()
    {
	// string-copy functions
	CPPUNIT_ASSERT( stx::string("  abc  ").trim_left() == "abc  " );
	CPPUNIT_ASSERT( stx::string("abc  ").trim_left() == "abc  " );
	CPPUNIT_ASSERT( stx::string("  ").trim_left() == "" );

	CPPUNIT_ASSERT( stx::string("  abc  ").trim_right() == "  abc" );
	CPPUNIT_ASSERT( stx::string("  abc").trim_right() == "  abc" );
	CPPUNIT_ASSERT( stx::string("  ").trim_right() == "" );

	CPPUNIT_ASSERT( stx::string("  abc  ").trim() == "abc" );
	CPPUNIT_ASSERT( stx::string("abc  ").trim() == "abc" );
	CPPUNIT_ASSERT( stx::string("  abc").trim() == "abc" );
	CPPUNIT_ASSERT( stx::string("  ").trim() == "" );

	// in-place functions
	stx::string str1 = "  abc  ";
	stx::string str2 = "abc  ";
	stx::string str3 = "  ";

	CPPUNIT_ASSERT( str1.trim_left_inplace() == "abc  " );
	CPPUNIT_ASSERT( str2.trim_left_inplace() == "abc  " );
	CPPUNIT_ASSERT( str3.trim_left_inplace() == "" );

	str1 = "  abc  ";
	str2 = "  abc";
	str3 = "  ";


	CPPUNIT_ASSERT( str1.trim_right_inplace() == "  abc" );
	CPPUNIT_ASSERT( str2.trim_right_inplace() == "  abc" );
	CPPUNIT_ASSERT( str3.trim_right_inplace() == "" );

	str1 = "  abc  ";
	str2 = "  abc";
	str3 = "abc  ";
	stx::string str4 = "  ";

	CPPUNIT_ASSERT( str1.trim_inplace() == "abc" );
	CPPUNIT_ASSERT( str2.trim_inplace() == "abc" );
	CPPUNIT_ASSERT( str3.trim_inplace() == "abc" );
	CPPUNIT_ASSERT( str4.trim_inplace() == "" );
    }

    void test_toupper_tolower()
    {
	// string-copy functions
	CPPUNIT_ASSERT( stx::string(" aBc ").toupper() == " ABC " );
	CPPUNIT_ASSERT( stx::string(" AbCdEfG ").tolower() == " abcdefg " );

	// in-place functions
	stx::string str1 = "  aBc  ";
	stx::string str2 = "AbCdEfGh ";

	CPPUNIT_ASSERT( str1.toupper_inplace() == "  ABC  " );
	CPPUNIT_ASSERT( str2.tolower_inplace() == "abcdefgh " );
    }

    void test_compare_icase()
    {
	CPPUNIT_ASSERT( stx::string("ABC") != stx::string("abc") );

	CPPUNIT_ASSERT( stx::string("ABC").equal_icase("abc") );
	CPPUNIT_ASSERT( !stx::string("ABC").equal_icase("abd") );
	CPPUNIT_ASSERT( !stx::string("ABC").equal_icase("abcedf") );

	CPPUNIT_ASSERT( stx::string("ABC") < stx::string("abc") );
	CPPUNIT_ASSERT( !stx::string("ABC").less_icase("abc") );
	CPPUNIT_ASSERT( stx::string("abc").less_icase("abcdef") );
	CPPUNIT_ASSERT( !stx::string("abcdef").less_icase("abcd") );
    }

    void test_prefix_suffix()
    {
	CPPUNIT_ASSERT( stx::string("abcdef").is_prefix("abc") );
	CPPUNIT_ASSERT( ! stx::string("abcdef").is_prefix("def") );
	CPPUNIT_ASSERT( stx::string("abcdef").is_suffix("def") );
	CPPUNIT_ASSERT( ! stx::string("abcdef").is_suffix("abc") );

	CPPUNIT_ASSERT( ! stx::string("abcdef").is_prefix("ABC") );

	CPPUNIT_ASSERT( stx::string("abcdef").is_prefix_icase("ABC") );
	CPPUNIT_ASSERT( ! stx::string("abcdef").is_prefix_icase("DEF") );
	CPPUNIT_ASSERT( stx::string("abcdef").is_suffix_icase("DEF") );
	CPPUNIT_ASSERT( ! stx::string("abcdef").is_suffix_icase("ABC") );

	CPPUNIT_ASSERT( stx::string("abcdef").is_prefix("") );
	CPPUNIT_ASSERT( stx::string("abcdef").is_suffix("") );

	CPPUNIT_ASSERT( ! stx::string("").is_prefix("abc") );
	CPPUNIT_ASSERT( ! stx::string("").is_suffix("abc") );

	CPPUNIT_ASSERT( stx::string("").is_prefix("") );
	CPPUNIT_ASSERT( stx::string("").is_suffix("") );
    }

    void test_replace()
    {
	// copy variants
	CPPUNIT_ASSERT( stx::string("abcdef abcdef").replace_first("abc", "a") == "adef abcdef" );
	CPPUNIT_ASSERT( stx::string("abcdef abcdef").replace_first("cba", "a") == "abcdef abcdef" );
	CPPUNIT_ASSERT( stx::string("abcdef abcdef").replace_all("abc", "a") == "adef adef" );
	CPPUNIT_ASSERT( stx::string("abcdef abcdef").replace_all("cba", "a") == "abcdef abcdef" );

	CPPUNIT_ASSERT( stx::string("abcdef abcdef").replace_first("a", "aaa") == "aaabcdef abcdef" );
	CPPUNIT_ASSERT( stx::string("abcdef abcdef").replace_all("a", "aaa") == "aaabcdef aaabcdef" );

	// in-place variants
	CPPUNIT_ASSERT( stx::string("abcdef abcdef").replace_first_inplace("abc", "a") == "adef abcdef" );
	CPPUNIT_ASSERT( stx::string("abcdef abcdef").replace_first_inplace("cba", "a") == "abcdef abcdef" );
	CPPUNIT_ASSERT( stx::string("abcdef abcdef").replace_all_inplace("abc", "a") == "adef adef" );
	CPPUNIT_ASSERT( stx::string("abcdef abcdef").replace_all_inplace("cba", "a") == "abcdef abcdef" );

	CPPUNIT_ASSERT( stx::string("abcdef abcdef").replace_first_inplace("a", "aaa") == "aaabcdef abcdef" );
	CPPUNIT_ASSERT( stx::string("abcdef abcdef").replace_all_inplace("a", "aaa") == "aaabcdef aaabcdef" );
    }

    void test_split_ws()
    {
	// simple whitespace split
	std::vector<std::string> sv = stx::string("  ab c df  fdlk f  ").split_ws();

	CPPUNIT_ASSERT( sv.size() == 5 );
	CPPUNIT_ASSERT( sv[0] == "ab" && sv[1] == "c" && sv[2] == "df" && sv[3] == "fdlk" && sv[4] == "f" );

	sv = stx::string("ab c df  fdlk f  ").split_ws();

	CPPUNIT_ASSERT( sv.size() == 5 );
	CPPUNIT_ASSERT( sv[0] == "ab" && sv[1] == "c" && sv[2] == "df" && sv[3] == "fdlk" && sv[4] == "f" );

	sv = stx::string("ab c df  fdlk f").split_ws();

	CPPUNIT_ASSERT( sv.size() == 5 );
	CPPUNIT_ASSERT( sv[0] == "ab" && sv[1] == "c" && sv[2] == "df" && sv[3] == "fdlk" && sv[4] == "f" );

	sv = stx::string("").split_ws();
	CPPUNIT_ASSERT( sv.size() == 0 );

	sv = stx::string("    ").split_ws();
	CPPUNIT_ASSERT( sv.size() == 0 );

	// whitespace split with limit
	sv = stx::string("  ab c   df  fdlk f  ").split_ws(3);

	CPPUNIT_ASSERT( sv.size() == 3 );
	CPPUNIT_ASSERT( sv[0] == "ab" && sv[1] == "c" && sv[2] == "df  fdlk f  " );

	// whitespace split with some strange limits
	sv = stx::string("  ab c df  fdlk f  ").split_ws(0);
	CPPUNIT_ASSERT( sv.size() == 0 );

	sv = stx::string("  ab c df  fdlk f  ").split_ws(1);

	CPPUNIT_ASSERT( sv.size() == 1 );
	CPPUNIT_ASSERT( sv[0] == "ab c df  fdlk f  " );

	// whitespace split with large limit
	sv = stx::string("  ab  c  df  fdlk f  ").split_ws(10);

	CPPUNIT_ASSERT( sv.size() == 5 );
	CPPUNIT_ASSERT( sv[0] == "ab" && sv[1] == "c" && sv[2] == "df" && sv[3] == "fdlk" && sv[4] == "f" );

	// whitespace split with limit at exactly the end
	sv = stx::string("  ab  c  df  fdlk f  ").split_ws(5);

	CPPUNIT_ASSERT( sv.size() == 5 );
	CPPUNIT_ASSERT( sv[0] == "ab" && sv[1] == "c" && sv[2] == "df" && sv[3] == "fdlk" && sv[4] == "f  " );
    }

    void test_split()
    {
	// simple char split
	std::vector<std::string> sv = stx::string("/usr/bin/test").split('/');

	CPPUNIT_ASSERT( sv.size() == 4 );
	CPPUNIT_ASSERT( sv[0] == "" && sv[1] == "usr" && sv[2] == "bin" && sv[3] == "test" );

	sv = stx::string("/usr/bin/test").split('/', 3);

	CPPUNIT_ASSERT( sv.size() == 3 );
	CPPUNIT_ASSERT( sv[0] == "" && sv[1] == "usr" && sv[2] == "bin/test" );

	// char split with some strange limits
	sv = stx::string("/usr//bin/test").split('/', 0);
	CPPUNIT_ASSERT( sv.size() == 0 );

	sv = stx::string("/usr//bin/test").split('/', 1);
	CPPUNIT_ASSERT( sv.size() == 1 );
	CPPUNIT_ASSERT( sv[0] == "/usr//bin/test" );

	// simple str split
	sv = stx::string("/usr/bin/test").split("/");

	CPPUNIT_ASSERT( sv.size() == 4 );
	CPPUNIT_ASSERT( sv[0] == "" && sv[1] == "usr" && sv[2] == "bin" && sv[3] == "test" );

	sv = stx::string("/usr/bin/test").split("/", 3);

	CPPUNIT_ASSERT( sv.size() == 3 );
	CPPUNIT_ASSERT( sv[0] == "" && sv[1] == "usr" && sv[2] == "bin/test" );

	// str split with some strange limits
	sv = stx::string("/usr//bin/test").split("/", 0);
	CPPUNIT_ASSERT( sv.size() == 0 );

	sv = stx::string("/usr//bin/test").split("/", 1);
	CPPUNIT_ASSERT( sv.size() == 1 );
	CPPUNIT_ASSERT( sv[0] == "/usr//bin/test" );

	sv = stx::string("/usr/bin/test").split("");
	CPPUNIT_ASSERT( sv.size() == 0 );

	// str split with parital needle at end
	sv = stx::string("testabcblahabcabcab").split("abc");

	CPPUNIT_ASSERT( sv.size() == 4 );
	CPPUNIT_ASSERT( sv[0] == "test" && sv[1] == "blah" && sv[2] == "" && sv[3] == "ab" );
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION( SimpleTest );
