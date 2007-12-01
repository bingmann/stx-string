// $Id$

#ifndef _STX_STRING_H_
#define _STX_STRING_H_

#include <string>
#include <cctype>
#include <stdexcept>
#include <sstream>
#include <vector>

namespace stx {

class string : public std::string
{
public:

    // ***                              ***
    // *** Constructors for stx::string ***
    // ***                              ***

    /** Default constructor. Creates an empty string. */
    string()
	: std::string()
    {
    }

    /** Copy-Constructor. Duplicates the enclosed STL string. */
    string(const string &s)
	: std::string(s)
    {
    }

    /** Automatic type-cast Constructor. Duplicates the given STL string. */
    string(const std::string &s)
	: std::string(s)
    {
    }

    /** Repeating constructor. Creates a string which contains the charater ch
     * repeated length times. */
    string(size_type length, const char& ch)
	: std::string(length, ch)
    {
    }

    /** C-style string constructor. Fills the new string with the given C-style
     * string. */
    string(const char* str)
	: std::string(str)
    {
    }

    /** C-style string constructor with length. Fills the new string with data
     * of length bytes. */
    string(const char* str, size_type length)
	: std::string(str, length)
    {
    }

    /** Substring constructor. Creates a new string containing the substring
     * specified by index and length. */
    string(const string& str, size_type index, size_type length)
	: std::string(str, index, length)
    {
    }

    /** Template-Iterator range constructor. Fills the new string with the
     * character in the start-end range. */
    template <typename input_iterator>
    string(input_iterator start, input_iterator end)
	: std::string(start, end)
    {
    }

    // ***                           ***
    // *** Whitespace Trim Functions ***
    // ***                           ***

    // *** generic std::string versions ***

    /** Trims the given string on the left and right. Removes all characters in
     * the given drop array, which defaults to " ". Returns a copy of the
     * string.
     *
     * @param str	string to process
     * @param drop	remove these characters
     * @return		new trimmed string
     */
    static std::string trim(const std::string& str, const std::string& drop = " ")
    {
	std::string::size_type pos1 = str.find_first_not_of(drop);
	if (pos1 == std::string::npos) return std::string();

	std::string::size_type pos2 = str.find_last_not_of(drop);
	if (pos2 == std::string::npos) return std::string();

	return str.substr(pos1 == std::string::npos ? 0 : pos1,
			  pos2 == std::string::npos ? (str.size() - 1) : (pos2 - pos1 + 1));
    }

    /** Trims the given string only on the left. Removes all characters in the
     * given drop array, which defaults to " ". Returns a copy of the string.
     *
     * @param str	string to process
     * @param drop	remove these characters
     * @return		new trimmed string
     */
    static std::string trim_left(const std::string& str, const std::string& drop = " ")
    {
	std::string::size_type pos = str.find_first_not_of(drop);
	if (pos == std::string::npos) return std::string();

	return str.substr(pos, std::string::npos);
    }

    /** Trims the given string only on the right. Removes all characters in the
     * given drop array, which defaults to " ". Returns a copy of the string.
     *
     * @param str	string to process
     * @param drop	remove these characters
     * @return	new trimmed string
     */
    static std::string trim_right(const std::string& str, const std::string& drop = " ")
    {
	std::string::size_type pos = str.find_last_not_of(drop);
	if (pos == std::string::npos) return std::string();

	return str.substr(0, pos + 1);
    }

    /** Trims the given string in-place on the left and right. Removes all
     * characters in the given drop array, which defaults to " ".
     *
     * @param str	string to process
     * @param drop	remove these characters
     * @return	reference to the modified string
     */
    static std::string& trim_inplace(std::string& str, const std::string& drop = " ")
    {
	std::string::size_type pos = str.find_last_not_of(drop);
	if (pos != std::string::npos) {
	    str.erase(pos + 1);
	    pos = str.find_first_not_of(drop);
	    if (pos != std::string::npos) str.erase(0, pos);
	}
	else
	    str.erase(str.begin(), str.end());

	return str;
    }

    /** Trims the given string in-place only on the left. Removes all
     * characters in the given drop array, which defaults to " ".
     *
     * @param str	string to process
     * @param drop	remove these characters
     * @return	reference to the modified string
     */
    static std::string& trim_left_inplace(std::string& str, const std::string &drop = " ")
    {
	str.erase(0, str.find_first_not_of(drop));
	return str;
    }

    /** Trims the given string in-place only on the right. Removes all
     * characters in the given drop array, which defaults to " ".
     *
     * @param str	string to process
     * @param drop	remove these characters
     * @return	reference to the modified string
     */
    static std::string& trim_right_inplace(std::string &str, const std::string &drop = " ")
    {
	str.erase(str.find_last_not_of(drop) + 1, std::string::npos);
	return str;
    }

    // *** class stx::string methods versions ***

    /** Trims the contained string on the left and right. Removes all
     * characters in the given drop array, which defaults to " ". Returns a
     * copy of this string.
     *
     * @param drop	remove these characters
     * @return		new trimmed string
     */
    string trim(const string& drop = " ") const
    {
	return trim(*this, drop);
    }

    /** Trims the contained string only on the left. Removes all characters in
     * the given drop array, which defaults to " ". Returns a copy of this
     * string.
     *
     * @param drop	remove these characters
     * @return		new trimmed string
     */
    string trim_left(const string& drop = " ") const
    {
	return trim_left(*this, drop);
    }

    /** Trims the contained string only on the right. Removes all characters in
     * the given drop array, which defaults to " ". Returns a copy of this
     * string.
     *
     * @param drop	remove these characters
     * @return		new trimmed string
     */
    string trim_right(const string& drop = " ") const
    {
	return trim_right(*this, drop);
    }

    /** Trims this string in-place on the left and right. Removes all
     * characters in the given drop array, which defaults to " ".
     *
     * @param drop	remove these characters
     * @return		reference to this string
     */
    string& trim_inplace(const string& drop = " ")
    {
	trim_inplace(*this, drop);
	return *this;
    }

    /** Trims this string in-place only on the left. Removes all characters in
     * the given drop array, which defaults to " ".
     *
     * @param drop	remove these characters
     * @return		reference to this string
     */
    string& trim_left_inplace(const string &drop = " ")
    {
	trim_left_inplace(*this, drop);
	return *this;
    }

    /** Trims this string in-place only on the right. Removes all characters in
     * the given drop array, which defaults to " ".
     *
     * @param drop	remove these characters
     * @return		reference to this string
     */
    string& trim_right_inplace(const string &drop = " ")
    {
	trim_right_inplace(*this, drop);
	return *this;
    }

    // ***                                 ***
    // ***  Upper and Lower Case Functions ***
    // ***                                 ***

    // *** functionals ***

    /** toupper() functional for std::transform with correct signature. */
    static char char_toupper_functional(char c)
    {
	return std::toupper(c);
    }

    /** tolower() functional for std::transform with correct signature. */
    static char char_tolower_functional(char c)
    {
	return std::tolower(c);
    }

    // *** generic std::string versions ***

    /** Returns a copy of the given string converted to uppercase.
     * @param str	string to process
     * @return		new string uppercased
     */
    static std::string toupper(const std::string& str)
    {
	std::string strcopy(str.size(), 0);
	std::transform(str.begin(), str.end(), strcopy.begin(), char_toupper_functional);
	return strcopy;
    }

    /** Returns a copy of the given string converted to lowercase.
     * @param str	string to process
     * @return		new string lowercased
     */
    static std::string tolower(const std::string& str)
    {
	std::string strcopy(str.size(), 0);
	std::transform(str.begin(), str.end(), strcopy.begin(), char_tolower_functional);
	return strcopy;
    }

    /** Transforms the enclosed string to uppercase and returns a reference to
     * this. */
    static std::string& toupper_inplace(std::string& str)
    {
	std::transform(str.begin(), str.end(), str.begin(), char_toupper_functional);
	return str;
    }

    /** Transforms the enclosed string to lowercase and returns a reference to
     * this. */
    static std::string& tolower_inplace(std::string& str)
    {
	std::transform(str.begin(), str.end(), str.begin(), char_tolower_functional);
	return str;
    }

    // *** class stx::string method versions ***

    /** Returns a copy of the enclosed string converted to uppercase.
     * @return		new string uppercased
     */
    string toupper() const
    {
	string strcopy(size(), 0);
	std::transform(begin(), end(), strcopy.begin(), char_toupper_functional);
	return strcopy;
    }

    /** Returns a copy of the enclosed string converted to lowercase.
     * @return		new string lowercased
     */
    string tolower() const
    {
	string strcopy(size(), 0);
	std::transform(begin(), end(), strcopy.begin(), char_tolower_functional);
	return strcopy;
    }

    /** Transforms the enclosed string to uppercase and returns a reference to
     * this. */
    string& toupper_inplace()
    {
	std::transform(begin(), end(), begin(), char_toupper_functional);
	return *this;
    }

    /** Transforms the enclosed string to lowercase and returns a reference to
     * this. */
    string& tolower_inplace()
    {
	std::transform(begin(), end(), begin(), char_tolower_functional);
	return *this;
    }

    // ***                              ***
    // *** Case-insensitive Comparision ***
    // ***                              ***

    // *** functional classes ***

    /** Binary class functional which compares two characters
     * case-insensitively. Returns true if they are equal. */
    struct char_icase_equal : public std::binary_function<char, char, bool>
    {
	bool operator() (const char& c1, const char& c2) const
	{ return std::tolower(c1) == std::tolower(c2); }
    };

    /** Binary class functional which compares two characters
     * case-insensitively. Returns true if the first is less than the
     * second. */
    struct char_icase_less : public std::binary_function<char, char, bool>
    {
	bool operator() (const char& c1, const char& c2) const
	{ return std::tolower(c1) < std::tolower(c2); }
    };

    // *** std::string comparison operators ***

    /** Compare two strings case-insensitively. Return true if they are
     * equal. */
    static bool equal_icase(const std::string& a, const std::string& b)
    {
	if (a.size() != b.size()) return false;

	return std::equal( a.begin(), a.end(), b.begin(),
			   char_icase_equal() );
    }

    /** Compare two string case-insensitively. Return true if this one is less
     * than the other. */
    static bool less_icase(const std::string& a, const std::string& b)
    {
	return std::lexicographical_compare( a.begin(), a.end(),
					     b.begin(), b.end(),
					     char_icase_less() );
    }

    /** Compare two string case-insensitively. Returns 0 if they are equal, -1
     * if a is lexicographical before b, +1 if a is after b. */
    static int compare_icase(const std::string& a, const std::string& b)
    {
	std::string::const_iterator ai = a.begin();
	std::string::const_iterator bi = b.begin();

	while( ai != a.end() && bi != b.end() )
	{
	    char ca = std::tolower(*ai++);
	    char cb = std::tolower(*bi++);

	    if (ca == cb) continue;
	    if (ca < cb) return -1;
	    else return +1;
	}

	if (ai == a.end() && bi != b.end()) return +1;
	else if (ai != a.end() && bi == b.end()) return -1;
	else return 0;
    }

    // *** class stx::string method versions ***

    /** Compare this string to the other case-insensitively. Return true if
     * they are equal. */
    bool equal_icase(const string& other) const
    {
	return equal_icase(*this, other);
    }

    /** Compare this string to the other case-insensitively. Return true if
     * this one is less than the other. */
    bool less_icase(const string& other) const
    {
	return less_icase(*this, other);
    }

    /** Compare this string to the other case-insensitively. Returns 0 if they
     * are equal, -1 if a is lexicographical before b, +1 if a is after b. */
    int compare_icase(const string& other) const
    {
	return compare_icase(*this, other);
    }

    // *** case-insenstive less-relation functional class for std::map ***

    /** Case-sensitive less order relation functional class for std::map. */
    struct order_less {
	inline bool operator()(const std::string &a, const std::string &b) const {
	    return (a < b);
	}
    };

    /** Case-insensitive less order relation functional class for std::map. */
    struct order_less_icase {
	inline bool operator()(const std::string &a, const std::string &b) const {
	    return less_icase(a, b);
	}
    };

    /** Descending case-sensitive less order relation functional class for
     * std::map. */
    struct order_less_desc {
	inline bool operator()(const std::string &a, const std::string &b) const {
	    return !(a < b);
	}
    };

    /** Descending case-insensitive less order relation functional class for
     * std::map. */
    struct order_less_icase_desc {
	inline bool operator()(const std::string &a, const std::string &b) const {
	    return !less_icase(a, b);
	}
    };

    // ***                             ***
    // *** Prefix and Suffix Functions ***
    // ***                             ***

    // *** static std::string functions ***

    /** Checks if the given match string is located at the start of this
     * string. */
    static bool is_prefix(const std::string& str, const std::string& match)
    {
	if (match.size() > str.size()) return false;
	return std::equal( match.begin(), match.end(), str.begin() );
    }

    /** Checks if the given match string is located at the end of this
     * string. */
    static bool is_suffix(const std::string& str, const std::string& match)
    {
	if (match.size() > str.size()) return false;
	return std::equal( match.begin(), match.end(),
			   str.end() - match.size() );
    }

    /** Checks if the given match string is located at the start of this
     * string. Compares the characters case-insensitively. */
    static bool is_prefix_icase(const std::string& str, const std::string& match)
    {
	if (match.size() > str.size()) return false;
	return std::equal( match.begin(), match.end(), str.begin(),
			   char_icase_equal() );
    }

    /** Checks if the given match string is located at the end of this
     * string. Compares the characters case-insensitively. */
    static bool is_suffix_icase(const std::string& str, const std::string& match)
    {
	if (match.size() > str.size()) return false;
	return std::equal( match.begin(), match.end(),
			   str.end() - match.size(),
			   char_icase_equal() );
    }

    // *** class stx::string method versions ***

    /** Checks if the given match string is located at the start of this
     * string. */
    bool is_prefix(const string& match) const
    {
	return is_prefix(*this, match);
    }

    /** Checks if the given match string is located at the end of this
     * string. */
    bool is_suffix(const string& match) const
    {
	return is_suffix(*this, match);
    }

    /** Checks if the given match string is located at the start of this
     * string. Compares the characters case-insensitively. */
    bool is_prefix_icase(const string& match) const
    {
	return is_prefix_icase(*this, match);
    }

    /** Checks if the given match string is located at the end of this
     * string. Compares the characters case-insensitively. */
    bool is_suffix_icase(const string& match) const
    {
	return is_suffix_icase(*this, match);
    }

    // ***                              ***
    // *** Search and Replace Functions ***
    // ***                              ***

    // *** static std::string functions ***

    /** Replace only the first occurrence of needle in str. The needle will be
     * replaced with instead, if found. Returns a copy of the string with the
     * possible replacement.
     *
     * @param str	the string to process
     * @param needle	string to search for in str
     * @param instead	replace needle with instead
     * @return		copy of string possibly with replacement
     */
    static std::string replace_first(const std::string& str, const std::string& needle, const std::string& instead)
    {
	std::string newstr = str;
	std::string::size_type firstpos = newstr.find(needle);

	if ( firstpos != std::string::npos)
	    newstr.replace(firstpos, needle.size(), instead);

	return newstr;
    }

    /** Replace all occurrences of needle in str. Each needle will be replaced
     * with instead, if found. Returns a copy of the string with possible
     * replacements.
     *
     * @param str	the string to process
     * @param needle	string to search for in str
     * @param instead	replace needle with instead
     * @return		copy of string possibly with replacements
     */
    static std::string replace_all(const std::string& str, const std::string& needle, const std::string& instead)
    {
	std::string newstr = str;
	std::string::size_type lastpos = 0, thispos;

	while ( (thispos = newstr.find(needle, lastpos)) != std::string::npos)
	{
	    newstr.replace(thispos, needle.size(), instead);
	    lastpos = thispos + instead.size();
	}
	return newstr;
    }

    /** Replace only the first occurrence of needle in str. The needle will be
     * replaced with instead, if found. The replacement is done in the given
     * string and a reference to the same is returned.
     *
     * @param str	the string to process
     * @param needle	string to search for in str
     * @param instead	replace needle with instead
     * @return		reference to str
     */
    static std::string& replace_first_inplace(std::string& str, const std::string& needle, const std::string& instead)
    {
	std::string::size_type firstpos = str.find(needle);

	if ( firstpos != std::string::npos)
	    str.replace(firstpos, needle.size(), instead);

	return str;
    }

    /** Replace all occurrences of needle in str. Each needle will be replaced
     * with instead, if found. The replacement is done in the given string and
     * a reference to the same is returned.
     *
     * @param str	the string to process
     * @param needle	string to search for in str
     * @param instead	replace needle with instead
     * @return		reference to str
     */
    static std::string& replace_all_inplace(std::string& str, const std::string& needle, const std::string& instead)
    {
	std::string::size_type lastpos = 0, thispos;

	while ( (thispos = str.find(needle, lastpos)) != std::string::npos)
	{
	    str.replace(thispos, needle.size(), instead);
	    lastpos = thispos + instead.size();
	}
	return str;
    }

    // *** class stx::string method versions ***

    /** Replace only the first occurrence of needle in the enclosed string. The
     * needle will be replaced with instead, if found. Returns a copy of this
     * string with the possible replacement.
     *
     * @param needle	string to search for
     * @param instead	replace needle with instead
     * @return		copy of this string possibly with replacement
     */
    string replace_first(const string& needle, const string& instead) const
    {
	return replace_first(*this, needle, instead);
    }

    /** Replace all occurrences of needle in the enclosed string. Each needle
     * will be replaced with instead, if found. Returns a copy of the string
     * with possible replacements.
     *
     * @param needle	string to search for
     * @param instead	replace needle with instead
     * @return		copy of this string possibly with replacements
     */
    string replace_all(const string& needle, const string& instead) const
    {
	return replace_all(*this, needle, instead);
    }

    /** Replace only the first occurrence of needle in the enclosed string. The
     * needle will be replaced with instead, if found. The replacement is done
     * in the enclosed string and a reference to this is returned.
     *
     * @param needle	string to search for in str
     * @param instead	replace needle with instead
     * @return		reference to this
     */
    string& replace_first_inplace(const string& needle, const string& instead)
    {
	replace_first_inplace(*this, needle, instead);
	return *this;
    }

    /** Replace all occurrences of needle in the enclosed string. Each needle
     * will be replaced with instead, if found. The replacement is done in the
     * enclosed string and a reference to this is returned.
     *
     * @param needle	string to search for in str
     * @param instead	replace needle with instead
     * @return		reference to this
     */
    string& replace_all_inplace(const string& needle, const string& instead)
    {
	replace_all_inplace(*this, needle, instead);
	return *this;
    }

    // ***                                    ***
    // *** Split, Join and Contains Functions ***
    // ***                                    ***

    // *** static std::string functions ***

    /** Split the given string by whitespaces into distinct words. Multiple
     * consecutive whitespaces are considered as one split point. Whitespaces
     * are space, tab, newline and carriage-return.
     *
     * @param str	string to split
     * @param limit	maximum number of parts returned
     * @return		vector containing each split substring
     */
    static std::vector<std::string> split_ws(const std::string& str, std::string::size_type limit = std::string::npos)
    {
	std::vector<std::string> out;
	if (limit == 0) return out;

	std::string::const_iterator it = str.begin(), last = it;

	for (; it != str.end(); ++it)
	{
	    if (*it == ' ' || *it == '\n' || *it == '\t' || *it == '\r')
	    {
		if (it == last) { // skip over empty split substrings
		    last = it+1;
		    continue;
		}

		if (out.size() + 1 >= limit)
		{
		    out.push_back(std::string(last, str.end()));
		    return out;
		}

		out.push_back(std::string(last, it));
		last = it + 1;
	    }
	}

	if (last != it)
	    out.push_back(std::string(last, it));

	return out;
    }

    /** Split the given string at each separator character into distinct
     * substrings. Multiple consecutive separators are considered individually
     * and will result in empty split substrings.
     *
     * @param str	string to split
     * @param sep	separator character
     * @param limit	maximum number of parts returned
     * @return		vector containing each split substring
     */
    static std::vector<std::string> split(const std::string& str, char sep, std::string::size_type limit = std::string::npos)
    {
	std::vector<std::string> out;
	if (limit == 0) return out;

	std::string::const_iterator it = str.begin(), last = it;

	for (; it != str.end(); ++it)
	{
	    if (*it == sep)
	    {
		if (out.size() + 1 >= limit)
		{
		    out.push_back(std::string(last, str.end()));
		    return out;
		}

		out.push_back(std::string(last, it));
		last = it + 1;
	    }
	}

	if (last != it)
	    out.push_back(std::string(last, it));

	return out;
    }

    /** Split the given string at each separator string into distinct
     * substrings. Multiple consecutive separators are considered individually
     * and will result in empty split substrings.
     *
     * @param str	string to split
     * @param sepstr	separator string
     * @param limit	maximum number of parts returned
     * @return		vector containing each split substring
     */
    static std::vector<std::string> split(const std::string& str, const std::string& sepstr, std::string::size_type limit = std::string::npos)
    {
	std::vector<std::string> out;
	if (limit == 0) return out;
	if (sepstr.empty()) return out;

	std::string::const_iterator it = str.begin(), last = it;

	for (; it + sepstr.size() <= str.end(); ++it)
	{
	    if (std::equal(sepstr.begin(), sepstr.end(), it))
	    {
		if (out.size() + 1 >= limit)
		{
		    out.push_back(std::string(last, str.end()));
		    return out;
		}

		out.push_back(std::string(last, it));
		last = it + sepstr.size();
	    }
	}

	if (last != str.end())
	    out.push_back(std::string(last, str.end()));

	return out;
    }

    /** Search the given string for a whitespace-delimited word. It works as if
     * the str was split_ws() and the resulting vector checked for a given
     * word. However this function does not create a vector, it scans the
     * string directly. Whitespace is space, tab, newline or carriage-return.
     *
     * @param str	whitespace-delimited string to check
     * @param word	word to find
     * @return		true if the word was found
     */
    static bool contains_word(const std::string& str, const std::string& word)
    {
	std::string::const_iterator it = str.begin(), last = it;

	while (it != str.end())
	{
	    // skip over whitespace
	    while (*it == ' ' || *it == '\n' || *it == '\t' || *it == '\r') {
		if (++it == str.end()) return false;
	    }

	    // check if this non-whitespace matches the string
	    std::string::const_iterator wi = word.begin();
	    while (*it == *wi) {
		++it; ++wi;
		if (wi == word.end()) {
		    if (it == str.end() || *it == ' ' || *it == '\n' || *it == '\t' || *it == '\r')
			return true;
		    else break;
		}
		if (it == str.end()) return false;
	    }

	    // skip over not matching whitespace
	    while (*it != ' ' && *it != '\n' && *it != '\t' && *it != '\r') {
		if (++it == str.end()) return false;
	    }
	}

	return false;
    }

    /** Search the contained string for a whitespace-delimited word. It works
     * as if the string was split_ws() and the resulting vector checked for a
     * given word. However this function does not create a vector, it scans the
     * string directly. Whitespace is space, tab, newline or carriage-return.
     *
     * @param word	word to find
     * @return		true if the word was found
     */
    bool contains_word(const string& word) const	
    {
	return contains_word(*this, word);
    }

    /** Join a sequence of strings by some glue string between each pair from
     * the sequence. The sequence in given as a range between two iterators.
     *
     * @param glue	string to glue
     * @param first	the beginning iterator of the range to join
     * @param last	the ending iterator of the range to join
     * @return		string constructed from the range with the glue between two strings.
     */
    template <typename input_iterator>
    static std::string join(const std::string& glue, input_iterator first, input_iterator last)
    {
	std::string out;
	if (first == last) return out;

	out.append(*first);
	++first;

	while( first != last )
	{
	    out.append(glue);
	    out.append(*first);
	    ++first;
	}

	return out;
    }

    /** Join a vector of strings by some glue string between each pair from
     * the sequence.
     *
     * @param glue	string to glue
     * @param parts	the vector of strings to join
     * @return		string constructed from the vector with the glue between two strings.
     */
    static std::string join(const std::string& glue, const std::vector<std::string>& parts)
    {
	return join(glue, parts.begin(), parts.end());
    }

    // *** class stx::string method versions ***

    /** Split the enclosed string by whitespaces into distinct words. Multiple
     * consecutive whitespaces are considered as one split point.
     *
     * @param limit	maximum number of parts returned
     * @return		vector containing each split substring
     */
    std::vector<std::string> split_ws(size_type limit = npos) const
    {
	return split_ws(*this, limit);
    }

    /** Split the enclosed string at each separator character into distinct
     * substrings. Multiple consecutive separators are considered individually
     * and will result in empty split substrings.
     *
     * @param sep	separator character
     * @param limit	maximum number of parts returned
     * @return		vector containing each split substring
     */
    std::vector<std::string> split(char sep, size_type limit = npos) const
    {
	return split(*this, sep, limit);
    }

    /** Split the enclosed string at each separator string into distinct
     * substrings. Multiple consecutive separators are considered individually
     * and will result in empty split substrings.
     *
     * @param sepstr	separator string
     * @param limit	maximum number of parts returned
     * @return		vector containing each split substring
     */
    std::vector<std::string> split(const std::string& sepstr, size_type limit = npos) const
    {
	return split(*this, sepstr, limit);
    }

    /** Split the enclosed string at each separator string into distinct
     * substrings. Multiple consecutive separators are considered individually
     * and will result in empty split substrings. This function fixes ambiguous
     * calls with C-style strings.
     *
     * @param sepstr	separator C-style string
     * @param limit	maximum number of parts returned
     * @return		vector containing each split substring
     */
    std::vector<std::string> split(const char* sepstr, size_type limit = npos) const
    {
	return split(*this, std::string(sepstr), limit);
    }

    /** Join a sequence of strings by gluing each pair together with the
     * enclosed glue string. The sequence in given as a range between two
     * iterators.
     *
     * @param first	the beginning iterator of the range to join
     * @param last	the ending iterator of the range to join
     * @return		string constructed from the range with the glue between two strings.
     */
    template <typename input_iterator>
    stx::string join(input_iterator first, input_iterator last) const
    {
	return join(*this, first, last);
    }

    /** Join a vector of strings by gluing each pair together with the enclosed
     * glue string.
     *
     * @param parts	the vector of strings to join
     * @return		string constructed from the vector with the glue between two strings.
     */
    stx::string join(const std::vector<std::string>& parts) const
    {
	return join(*this, parts.begin(), parts.end());
    }

    /** Join a vector of strings by gluing each pair together with the enclosed
     * glue string.
     *
     * @param parts	the vector of strings to join
     * @return		string constructed from the vector with the glue between two strings.
     */
    stx::string join(const std::vector<stx::string>& parts) const
    {
	return join(*this, parts.begin(), parts.end());
    }

    // ***                         ***
    // *** Random String Functions ***
    // ***                         ***

    // *** static std::string functions ***

    /** Generate a random binary string of given length. Any byte from 0-256 is
     * equally probable. Uses the pseudo-random number generator from stdlib;
     * take care to seed it using srand() before calling this function.
     *
     * @param size	length of result
     * @return		random binary string of given length
     */
    static std::string random_binary(size_type size)
    {
	std::string out;
	out.resize(size);

	for (unsigned int i = 0; i < size; ++i)
	    out[i] = static_cast<unsigned char>(rand() % 256);

	return out;
    }

    /** Generate a random string of given length. The set of available
     * bytes/characters is given as the second argument. Each byte is equally
     * probable. Uses the pseudo-random number generator from stdlib; take care
     * to seed it using srand() before calling this function.
     *
     * @param size	length of result
     * @param cset	character set to choose from
     * @return		random string of given length
     */
    static std::string random(size_type size, const std::string& cset)
    {
	std::string out;
	out.resize(size);

	for (unsigned int i = 0; i < size; ++i)
	    out[i] = cset[ rand() % cset.size() ];

	return out;
    }

    /** Generate a random string of given length. Any letter A-Z and a-z is
     * equally probable to occur. Uses the pseudo-random number generator from
     * stdlib; take care to seed it using srand() before calling this function.
     *
     * @param size	length of result
     * @return		random string of given length
     */
    static std::string random_alpha(size_type size)
    {
	static const std::string letters =
	    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

	return random(size, letters);
    }

    /** Generate a random string of given length. Any letter A-Z and a-z or
     * digit 0-9 is equally probable to occur. Uses the pseudo-random number
     * generator from stdlib; take care to seed it using srand() before calling
     * this function.
     *
     * @param size	length of result
     * @return		random string of given length
     */
    static std::string random_alphanumeric(size_type size)
    {
	static const std::string letters =
	    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

	return random(size, letters);
    }

    // *** class stx::string method versions ***

    /** Generate a random binary string of given length and replace the current
     * object with it. Any byte from 0-256 is equally probable. Uses the
     * pseudo-random number generator from stdlib; take care to seed it using
     * srand() before calling this function.
     *
     * @param size	length of result
     * @return		reference to this, now a random binary string of given length
     */
    stx::string& random_binary_inplace(size_type size)
    {
	*this = random_binary(size);
	return *this;
    }

    /** Generate a random string of given length and replace the current object
     * with it. The set of available bytes/characters is given as the second
     * argument. Each byte is equally probable. Uses the pseudo-random number
     * generator from stdlib; take care to seed it using srand() before calling
     * this function.
     *
     * @param size	length of result
     * @param cset	character set to choose from
     * @return		reference to this, now a random string of given length
     */
    stx::string& random_inplace(size_type size, const std::string& cset)
    {
	*this = random(size, cset);
	return *this;
    }

    /** Generate a random string of given length and replace the current object
     * with it. Any letter A-Z and a-z is equally probable to occur. Uses the
     * pseudo-random number generator from stdlib; take care to seed it using
     * srand() before calling this function.
     *
     * @param size	length of result
     * @return		reference to this, now a random string of given length
     */
    stx::string& random_alpha_inplace(size_type size)
    {
	*this = random_alpha(size);
	return *this;
    }

    /** Generate a random string of given length and replace the current object
     * with it. Any letter A-Z and a-z or digit 0-9 is equally probable to
     * occur. Uses the pseudo-random number generator from stdlib; take care to
     * seed it using srand() before calling this function.
     *
     * @param size	length of result
     * @return		reference to this, now a random string of given length
     */
    stx::string& random_alphanumeric_inplace(size_type size)
    {
	*this = random_alphanumeric(size);
	return *this;
    }

    // ***                           ***
    // *** Hexadecimal Dump and Load ***
    // ***                           ***

    // *** static std::string functions ***

    /** Dump a (binary) string as a sequence of hexadecimal pairs.
     *
     * @param str	string to output in hex
     * @return		string of hexadecimal pairs
     */
    static std::string hexdump(const std::string& str)
    {
	std::string out;
	out.resize( str.size() * 2 );

	static const char xdigits[16] = {
	    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
	};

	std::string::iterator oi = out.begin();
	for (std::string::const_iterator si = str.begin();
	     si != str.end(); ++si)
	{
	    *oi++ = xdigits[ (*si & 0xF0) >> 4 ];
	    *oi++ = xdigits[ (*si & 0x0F) ];
	}

	return out;
    }

    /** Read a string as a sequence of hexadecimal pairs. Converts each pair of
     * hexadecimal digits into a byte of the output string. Throws
     * std::runtime_error() if an unknown letter is encountered.
     *
     * @param str	string to parse as hex digits
     * @return		string of read bytes
     */
    static std::string parse_hexdump(const std::string& str)
    {
	std::string out;
	int n = 0;
	unsigned char c = 0;

	for (std::string::const_iterator si = str.begin();
	     si != str.end(); ++si)
	{
	    switch(*si)
	    {
	    case '0': c |= 0; break;
	    case '1': c |= 1; break;
	    case '2': c |= 2; break;
	    case '3': c |= 3; break;
	    case '4': c |= 4; break;
	    case '5': c |= 5; break;
	    case '6': c |= 6; break;
	    case '7': c |= 7; break;
	    case '8': c |= 8; break;
	    case '9': c |= 9; break;
	    case 'A': case 'a': c |= 10; break;
	    case 'B': case 'b': c |= 11; break;
	    case 'C': case 'c': c |= 12; break;
	    case 'D': case 'd': c |= 13; break;
	    case 'E': case 'e': c |= 14; break;
	    case 'F': case 'f': c |= 15; break;
	    default:
		throw(std::runtime_error("Invalid string for hex conversion"));
	    }

	    if (n == 0) {
		c *= 0x10;
	    }
	    else if (n == 1) {
		out.append(1, c);
		c = 0;
	    }
	    n = (n+1) % 2;
	}

	if (n != 0) throw(std::runtime_error("Invalid string for hex conversion"));

	return out;
    }

    /** Dump a (binary) string into a C source code snippet. The snippet
     * defines an array of const char holding the data of the string. Cannot
     * set a default argument for varname, because it leads to ambiguous calls
     * with the object method below.
     *
     * @param str	string to output as C source array
     * @param varname	name of the array variable in the outputted code snippet
     * @return		string holding C source snippet
     */
    static std::string hexdump_sourcecode(const std::string& str, const std::string& varname)
    {
	std::ostringstream header;
	header << "const char " << varname << "[" << str.size() << "] = {\n";

	static const int perline = 16;

	std::string out = header.str();
	out.reserve( out.size() + (str.size() * 5) - 1 + (str.size() / 16) + 4 );

	static const char xdigits[16] = {
	    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
	};

	size_type ci = 0;

	for (std::string::const_iterator si = str.begin();
	     si != str.end(); ++si, ++ci)
	{
	    out.append("0x");
	    out.append(1, xdigits[ (*si & 0xF0) >> 4 ]);
	    out.append(1, xdigits[ (*si & 0x0F) ]);

	    if (ci+1 < str.size()) {
		out.append(1, ',');

		if (ci % perline == perline-1) {
		    out.append(1, '\n');
		}
	    }
	}

	out.append("\n};\n");

	return out;
    }

    // *** class stx::string method versions ***

    /** Dump the (binary) enclosed string as a sequence of hexadecimal pairs.
     *
     * @return		string of hexadecimal pairs
     */
    stx::string hexdump() const
    {
	return hexdump(*this);
    }

    /** Reads this string as a sequence of hexadecimal pairs. Converts each
     * pair of hexadecimal digits into a byte of the output string. Throws
     * std::runtime_error() if an unknown letter is encountered.
     *
     * @return		string of parsed bytes
     */
    stx::string parse_hexdump() const
    {
	return parse_hexdump(*this);
    }

    /** Dump a (binary) string into a C source code snippet. The snippet
     * defines an array of const char holding the data of the string.
     *
     * @param varname	name of the array variable in the outputted code snippet
     * @return		string holding C source snippet
     */
    stx::string hexdump_sourcecode(const std::string& varname = "hexdump") const
    {
	return hexdump_sourcecode(*this, varname);
    }

    // ***                              ***
    // *** Base64 Encoding and Decoding ***
    // ***                              ***

    // *** static std::string functions ***

    /** Encode the given binary string into Base64 representation as described
     * in RFC 2045 or RFC 3548. The output string contains only characters
     * [A-Za-z0-9+/] and is roughly 33% longer than the input. The output
     * string can be broken into lines after n characters, where n must be a
     * multiple of 4. The function's code is based on code from the libb64
     * project (see http://sourceforge.net/projects/libb64).
     *
     * @param instr	input string to encode
     * @param linebreak	break the output string every n characters
     * @return		base64 encoded string
     */
    static std::string base64_encode(const std::string& instr, unsigned int linebreak = 0)
    {
	std::string::const_iterator inchar = instr.begin();
	std::string outstr;

	if (instr.size() == 0) return outstr;

	// calculate output string's size in advance
	unsigned int outsize = (((instr.size() - 1) / 3) + 1) * 4;
	if (linebreak > 0) outsize += outsize / linebreak;
	outstr.reserve( outsize );

	static const char encoding64[65]
	    = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	char result = 0;
	unsigned int linebegin = 0;

	while (1)
	{
	    // step 0: if the string is finished here, no padding is needed
	    if (inchar == instr.end()) {
		return outstr;
	    }

	    // step 0: process first byte, write first letter
	    char fragment = *inchar++;
	    result = (fragment & 0xFC) >> 2;
	    outstr += encoding64[static_cast<int>(result)];
	    result = (fragment & 0x03) << 4;

	    // step 1: if string finished here, add two padding '='s
	    if (inchar == instr.end()) {
		outstr += encoding64[static_cast<int>(result)];
		outstr += '=';
		outstr += '=';
		return outstr;
	    }

	    // step 1: process second byte together with first, write second
	    // letter
	    fragment = *inchar++;
	    result |= (fragment & 0xF0) >> 4;
	    outstr += encoding64[static_cast<int>(result)];
	    result = (fragment & 0x0F) << 2;

	    // step 2: if string finished here, add one padding '='
	    if (inchar == instr.end()) {
		outstr += encoding64[static_cast<int>(result)];
		outstr += '=';
		return outstr;
	    }

	    // step 2: process third byte and write third and fourth letters.
	    fragment = *inchar++;

	    result |= (fragment & 0xC0) >> 6;
	    outstr += encoding64[static_cast<int>(result)];

	    result  = (fragment & 0x3F) >> 0;
	    outstr += encoding64[static_cast<int>(result)];

	    // wrap base64 encoding into lines if desired, but only after whole
	    // blocks of 4 letters.
	    if (linebreak > 0 && outstr.size() - linebegin >= linebreak)
	    {
		outstr += '\n';
		linebegin = outstr.size();
	    }
	}
    }

    /** Decode a stringin Base64 representation as described in RFC 2045 or RFC
     * 3548 and return the original data. If a non-whitespace invalid Base64
     * character is encountered _and_ the parameter "strict" is true, then this
     * function will throw a std::runtime_error. If "strict" is false, the
     * character is silently ignored. The function's code is based on code from
     * the libb64 project (see http://sourceforge.net/projects/libb64).
     *
     * @param instr	input string to encode
     * @param strict	throw exception on invalid character
     * @return		decoded binary data
     */
    static std::string base64_decode(const std::string& instr, bool strict = false)
    {
	std::string::const_iterator inchar = instr.begin();
	std::string outstr;

	// estimate the output size, assume that the whole input string is
	// base64 encoded.
	outstr.reserve( instr.size() * 3 / 4 );

	// value lookup table: -1 -> exception, -2 -> skip whitespace
	const char decoding64[256] = {
	    -1, -1, -1, -1, -1, -1, -1, -1, -1, -2, -2, -1, -1, -2, -1, -1,
	    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	    -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 62, -1, -1, -1, 63,
	    52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -1, -1, -1, -2, -1, -1,
	    -1,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
	    15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -1, -1, -1, -1, -1,
	    -1, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
	    41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, -1, -1, -1, -1, -1,
	    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	};

	char outchar;
	char fragment;

	while (1)
	{
	    // step 0: save first valid letter. do not output a byte, yet.
	    do {
		if (inchar == instr.end()) return outstr;

		fragment = decoding64[ static_cast<int>(*inchar++) ];

		if (fragment == -1 && strict)
		    throw(std::runtime_error("Invalid character encountered during Base64 decoding."));

	    } while (fragment < 0);

	    outchar = (fragment & 0x3F) << 2;

	    // step 1: get second valid letter. output the first byte.
	    do {
		if (inchar == instr.end()) return outstr;

		fragment = decoding64[ static_cast<int>(*inchar++) ];

		if (fragment == -1 && strict)
		    throw(std::runtime_error("Invalid character encountered during Base64 decoding."));

	    } while (fragment < 0);

	    outchar |= (fragment & 0x30) >> 4;
	    outstr += outchar;

	    outchar = (fragment & 0x0F) << 4;

	    // step 2: get third valid letter. output the second byte.
	    do {
		if (inchar == instr.end())  return outstr;

		fragment = decoding64[ static_cast<int>(*inchar++) ];

		if (fragment == -1 && strict)
		    throw(std::runtime_error("Invalid character encountered during Base64 decoding."));

	    } while (fragment < 0);

	    outchar |= (fragment & 0x3C) >> 2;
	    outstr += outchar;

	    outchar = (fragment & 0x03) << 6;

	    // step 3: get fourth valid letter. output the third byte.
	    do {
		if (inchar == instr.end()) return outstr;

		fragment = decoding64[ static_cast<int>(*inchar++) ];

		if (fragment == -1 && strict)
		    throw(std::runtime_error("Invalid character encountered during Base64 decoding."));

	    } while (fragment < 0);

	    outchar |= (fragment & 0x3F);
	    outstr += outchar;
	}
    }

    // *** class stx::string method versions ***

    /** Encode the enclosed binary string into Base64 representation as
     * described in RFC 2045 or RFC 3548. The output string contains only
     * characters [A-Za-z0-9+/] and is roughly 33% longer than the input. The
     * output string can be broken into lines after n characters, where n must
     * be a multiple of 4. The function's code is based on code from the libb64
     * project (see http://sourceforge.net/projects/libb64).
     *
     * @param linebreak	break the output string every n characters
     * @return		base64 encoded string
     */
    stx::string base64_encode(unsigned int linebreak = 0) const
    {
	return base64_encode(*this, linebreak);
    }

    /** Decode the enclosed string in Base64 representation as described in RFC
     * 2045 or RFC 3548 and return the original data. If a non-whitespace
     * invalid Base64 character is encountered _and_ the parameter "strict" is
     * true, then this function will throw a std::runtime_error. If "strict" is
     * false, the character is silently ignored. The function's code is based
     * on code from the libb64 project (see
     * http://sourceforge.net/projects/libb64).
     *
     * @param strict	throw exception on invalid character
     * @return		decoded binary data
     */
    stx::string base64_decode(bool strict = false) const
    {
	return base64_decode(*this, strict);
    }

    // ***                                              ***
    // *** Compress and Uncompress Functions using zlib ***
    // ***                                              ***

    // *** static std::string functions ***

    /** Compress a string using zlib with given compression level and return
     * the binary data.
     *
     * @param str	(binary) string to compress
     * @param compressionlevel	ranging 0-9
     * @return		(binary) compressed image
     */
    static std::string compress(const std::string& str,
				int compressionlevel = 9);

    /** Compress a string using zlib in gzip mode with given compression level
     * and return the binary data. The function adds simple gzip header and
     * footer structures so that gzip will accept the file.
     *
     * @param str	(binary) string to compress
     * @param compressionlevel	ranging 0-9
     * @return		(binary) compressed gzip image
     */
    static std::string gzcompress(const std::string& str,
				  int compressionlevel = 9);

    /** Decompress a string using zlib and return the original data. Throws
     * std::runtime_error if an error occurred during decompression.
     *
     * @param str	(binary) compressed image to decompress
     * @return		uncompressed string
     */
    static std::string decompress(const std::string& str);

    // *** class stx::string method versions ***

    /** Compress the enclosed string using zlib with given compression level
     * and return a copy of the binary compressed data.
     *
     * @param compressionlevel	ranging 0-9
     * @return		(binary) compressed image
     */
    stx::string compress(int compressionlevel = 9) const
    {
	return compress(*this, compressionlevel);
    }

    /** Compress the enclosed string using zlib in gzip mode with given
     * compression level and return the binary data. The function adds simple
     * gzip header and footer structures so that gzip will accept the file.
     *
     * @param compressionlevel	ranging 0-9
     * @return		(binary) compressed gzip image
     */
    stx::string gzcompress(int compressionlevel = 9) const
    {
	return gzcompress(*this, compressionlevel);
    }

    /** Decompress the enclosed string using zlib and return the original
     * data. Throws std::runtime_error if an error occurred during
     * decompression.
     *
     * @return		uncompressed string
     */
    stx::string decompress() const
    {
	return decompress(*this);
    }

    /** Compress the enclosed string using zlib with given compression level
     * and store the result in this string object, deleting the old data.
     *
     * @param compressionlevel	ranging 0-9
     * @return		reference to this, now (binary) compressed string
     */
    stx::string& compress_inplace(int compressionlevel = 9)
    {
	*this = compress(*this, compressionlevel);
	return *this;
    }

    /** Compress the enclosed string using zlib in gzip mode with given
     * compression level and store the result in this string object. The
     * function adds simple gzip header and footer structures so that gzip will
     * accept the file.
     *
     * @param compressionlevel	ranging 0-9
     * @return		reference to this, now (binary) compressed gzip image
     */
    stx::string& gzcompress_inplace(int compressionlevel = 9)
    {
	*this = gzcompress(*this, compressionlevel);
	return *this;
    }

    /** Decompress the enclosed string using zlib and store the result in this
     * string object, deleting the old data. Throws std::runtime_error if an
     * error occurred during decompression.
     *
     * @return		reference to this, now uncompressed string
     */
    stx::string& decompress_inplace()
    {
	*this = decompress(*this);
	return *this;
    }

    // ***                             ***
    // *** Levenshtein String Distance ***
    // ***                             ***

    // *** Parameter Struct and Algorithm ***

    /** Standard parameters to levenshtein distance function. Costs are all 1
     * and characters are compared directly. */
    struct LevenshteinStandard
    {
	static const unsigned int cost_insert_delete	= 1;
	static const unsigned int cost_replace		= 1;

	static bool char_equal(const char& a, const char& b)
	{ return (a == b); }
    };

    /** Standard parameters to Levenshtein distance function. Costs are all 1
     * and characters are compared case-insensitively. */
    struct LevenshteinStandardICase
    {
	static const unsigned int cost_insert_delete	= 1;
	static const unsigned int cost_replace		= 1;

	static bool char_equal(const char& a, const char& b)
	{ return std::tolower(a) == std::tolower(b); }
    };

    /** Computes the Levenshtein string distance between two strings. The
     * distance is the minimum number of replacements/inserts/deletes needed to
     * change one string into the other. Implemented with time complexity
     * O(|n|+|m|) and memory complexity O(2*max(|n|,|m|))
     *
     * @param a		first string
     * @param b		second string
     * @return		Levenshtein distance
     */
    template <typename levenshtein_param>
    static unsigned int levenshtein_algorithm(const std::string& a, const std::string& b)
    {
	// if one of the strings is zero, then all characters of the other must
	// be inserted.
	if (a.empty()) return b.size();
	if (b.empty()) return a.size();

	// make "as" the longer string and "bs" the shorter.
	const std::string &as = (a.size() > b.size()) ? a : b;
	const std::string &bs = (a.size() > b.size()) ? b : a;

	// only allocate two rows of the needed matrix.
	unsigned int matrix[2][as.size() + 1];

	// fill first row with ascending ordinals.
	for(unsigned int i = 0; i < as.size() + 1; i++) {
	    matrix[0][i] = i;
	}

	// compute distance
	for(unsigned int j = 1; j < bs.size() + 1; j++)
	{
	    // switch rows each time
	    unsigned int *lastrow = matrix[(j - 1) % 2];
	    unsigned int *thisrow = matrix[j % 2];

	    thisrow[0] = j;

	    for(unsigned int i = 1; i < as.size() + 1; i++)
	    {
		// three-way mimimum of
		thisrow[i] = std::min(
		    std::min(
			// left plus insert cost
			thisrow[i-1] + levenshtein_param::cost_insert_delete,
			// top plus delete cost
			lastrow[i] + levenshtein_param::cost_insert_delete),
		    // top left plus replacement cost
		    lastrow[i-1] + (levenshtein_param::char_equal(as[i-1], bs[j-1]) ? 0 : levenshtein_param::cost_replace)
		    );
	    }
	}

	// result is in the last cell of the last computed row
	return matrix[ bs.size() % 2 ][ as.size() ];
    }

    // *** static std::string functions ***

    /** Computes the Levenshtein string distance between two strings. The
     * distance is the minimum number of replacements/inserts/deletes needed to
     * change one string into the other.
     *
     * @param a		first string
     * @param b		second string
     * @return		Levenshtein distance
     */
    static unsigned int levenshtein(const std::string& a, const std::string& b)
    {
	return levenshtein_algorithm<LevenshteinStandard>(a, b);
    }

    /** Computes the Levenshtein string distance between two strings. The
     * distance is the minimum number of replacements/inserts/deletes needed to
     * change one string into the other. Character comparison is done
     * case-insensitively.
     *
     * @param a		first string
     * @param b		second string
     * @return		Levenshtein distance
     */
    static unsigned int levenshtein_icase(const std::string& a, const std::string& b)
    {
	return levenshtein_algorithm<LevenshteinStandardICase>(a, b);
    }

    // *** class stx::string method versions ***

    /** Computes the Levenshtein string distance between two strings. The
     * distance is the number of replacements/inserts/deletes needed to change
     * one string into the other.
     *
     * @param other	string to compare this one with
     * @return		Levenshtein distance
     */
    unsigned int levenshtein(const std::string& other) const
    {
	return levenshtein_algorithm<LevenshteinStandard>(*this, other);
    }

    /** Computes the Levenshtein string distance between two strings. The
     * distance is the number of replacements/inserts/deletes needed to change
     * one string into the other. Character comparison is done
     * case-insensitively.
     *
     * @param other	string to compare this one with
     * @return		Levenshtein distance
     */
    unsigned int levenshtein_icase(const std::string& other) const
    {
	return levenshtein_algorithm<LevenshteinStandardICase>(*this, other);
    }

    // ***                            ***
    // *** 'Natural Order' Comparison ***
    // ***                            ***

    // *** Algorithm and Helper Functions ***

    /** Function to compare two STL (binary) strings using the 'natural order'
     * comparison algorithm written by Martin Pool. I converted the C code
     * using C-style strings to STL-style string processing. The equivalence to
     * the original algorithm is verified in the test suite.
     *
     * Based on:
     *
     * strnatcmp.c -- Perform 'natural order' comparisons of strings in C.
     * Copyright (C) 2000, 2004 by Martin Pool &lt;mbp sourcefrog net&gt;
     *
     * This software is provided 'as-is', without any express or implied
     * warranty.  In no event will the authors be held liable for any damages
     * arising from the use of this software.
     *
     * Permission is granted to anyone to use this software for any purpose,
     * including commercial applications, and to alter it and redistribute it
     * freely, subject to the following restrictions:
     *
     * 1. The origin of this software must not be misrepresented; you must not
     *    claim that you wrote the original software. If you use this software
     *    in a product, an acknowledgment in the product documentation would be
     *    appreciated but is not required.
     * 2. Altered source versions must be plainly marked as such, and must not be
     *    misrepresented as being the original software.
     * 3. This notice may not be removed or altered from any source distribution.
     *
     * @param a		first string to compare
     * @param b		second string to compare
     * @param fold_case	ignore alphabetic case in comparison
     * @return		0 if (a == b), -1 if (a < b) and +1 if (a > b).
     */
    static int natcmp_algorithm(const std::string& a, const std::string& b, bool fold_case)
    {
	std::string::const_iterator ai = a.begin();
	std::string::const_iterator bi = b.begin();

	while (ai != a.end() || bi != b.end())
	{
	    // skip over leading spaces or zeros
	    while (ai != a.end() && std::isspace(*ai))
		++ai;

	    while (bi != b.end() && std::isspace(*bi))
		++bi;

	    if (ai == a.end() || bi == b.end())
		break;

	    // process run of digits
	    if (std::isdigit(*ai) && std::isdigit(*bi))
	    {
		if (*ai == '0' || *bi == '0') // fractional
		{
		    // Compare two left-aligned numbers: the first to have a
		    // different value wins.

		    while (ai != a.end() && bi != b.end())
		    {
			if (!std::isdigit(*ai) && !std::isdigit(*bi))
			    break;
			else if (!std::isdigit(*ai))
			    return -1;
			else if (!std::isdigit(*bi))
			    return +1;
			else if (*ai < *bi)
			    return -1;
			else if (*ai > *bi)
			    return +1;

			++ai; ++bi;
		    }

		    continue;
		}
		else
		{
		    // The longest run of digits wins.  That aside, the
		    // greatest value wins, but we can't know that it will
		    // until we've scanned both numbers to know that they have
		    // the same magnitude, so we remember it in BIAS.

		    int bias = 0;

		    while(ai != a.end() && bi != b.end())
		    {
			if (!std::isdigit(*ai) && !std::isdigit(*bi)) {
			    if (bias) return bias;
			    else break;
			}
			else if (!std::isdigit(*ai))
			    return -1;
			else if (!std::isdigit(*bi))
			    return +1;
			else if (*ai < *bi) {
			    if (!bias) bias = -1;
			}
			else if (*ai > *bi) {
			    if (!bias) bias = +1;
			}

			++ai; ++bi;
		    }

		    // check for the longer sequence of digits
		    if (ai == a.end() && bi != b.end() && std::isdigit(*bi)) return -1;
		    if (bi == b.end() && ai != a.end() && std::isdigit(*ai)) return +1;

		    if (bias) return bias;

		    continue;
		}
	    }

	    char ca = fold_case ? std::toupper(*ai) : *ai;
	    char cb = fold_case ? std::toupper(*bi) : *bi;

	    if (ca < cb)
		return -1;
	    else if (ca > cb)
		return +1;

	    ++ai; ++bi;
	}

	if (ai == a.end() && bi == b.end()) {
	    // The strings compare the same.  Perhaps the caller will want to
	    // call strcmp to break the tie.
	    return 0;
	}
	else if (ai == a.end() && bi != b.end())
	    return -1;
	else if (ai != a.end() && bi == b.end())
	    return +1;

	return 0; // never reached
    }

    // *** static std::string functions ***

    /** Function to compare two STL (binary) strings using the 'natural order'
     * comparison algorithm. It orders strings so that "rfc1.txt" <
     * "rfc822.txt" < "rfc2086.txt". The comparison is done case-sensitive.
     *
     * @param a		first string to compare
     * @param b		second string to compare
     * @return		0 if (a == b), -1 if (a < b) and +1 if (a > b).
     */
    static int natcmp(const std::string& a, const std::string& b)
    {
	return natcmp_algorithm(a, b, false);
    }

    /** Function to compare two STL (binary) strings using the 'natural order'
     * comparison algorithm. It orders strings so that "rfc1.txt" <
     * "rfc822.txt" < "rfc2086.txt". The comparison is done case-insensitive.
     *
     * @param a		first string to compare
     * @param b		second string to compare
     * @return		0 if (a == b), -1 if (a < b) and +1 if (a > b).
     */
    static int natcmp_icase(const std::string& a, const std::string& b)
    {
	return natcmp_algorithm(a, b, true);
    }

    // *** class stx::string method versions ***

    /** Function to compare two (binary) strings using the 'natural order'
     * comparison algorithm. It orders strings so that "rfc1.txt" <
     * "rfc822.txt" < "rfc2086.txt". The comparison is done case-sensitive.
     *
     * @param b		string to compare with
     * @return		0 if (this == b), -1 if (this < b) and +1 if (this > b).
     */
    int natcmp(const stx::string& b) const
    {
	return natcmp_algorithm(*this, b, false);
    }

    /** Function to compare two STL (binary) strings using the 'natural order'
     * comparison algorithm. It orders strings so that "rfc1.txt" <
     * "rfc822.txt" < "rfc2086.txt". The comparison is done case-insensitive.
     *
     * @param b		string to compare with
     * @return		0 if (this == b), -1 if (this < b) and +1 if (this > b).
     */
    int natcmp_icase(const stx::string& b) const
    {
	return natcmp_algorithm(*this, b, true);
    }

    // *** std::string natural order comparison operators ***

    /** Compare two strings case-sensitively using the 'natural order'
     * algorithm. Return true if they are equal. */
    static bool natequal(const std::string& a, const std::string& b)
    {
	return (natcmp(a, b) == 0);
    }

    /** Compare two strings case-insensitively using the 'natural order'
     * algorithm. Return true if they are equal. */
    static bool natequal_icase(const std::string& a, const std::string& b)
    {
	return (natcmp_icase(a, b) == 0);
    }

    /** Compare two string case-sensitively using the 'natural order'
     * algorithm. Strings that are equal in the 'natural order' are compared
     * using the binary less operator to break ties. Return true if this one is
     * less than the other. */
    static bool natless(const std::string& a, const std::string& b)
    {
	int r = natcmp(a, b);
	if (r != 0) return (r < 0);
	return (a < b);
    }

    /** Compare two string case-insensitively using the 'natural order'
     * algorithm. Strings that are equal in the 'natural order' are compared
     * using the binary less operator to break ties. Return true if this one is
     * less than the other. */
    static bool natless_icase(const std::string& a, const std::string& b)
    {
	int r = natcmp_icase(a, b);
	if (r != 0) return (r < 0);
	return less_icase(a, b);
    }

    // *** class stx::string method versions ***

    /** Compare this string to the other case-sensitively using the 'natural
     * order' algorithm. Return true if they are equal. */
    bool natequal(const string& b) const
    {
	return natequal(*this, b);
    }

    /** Compare this string to the other case-insensitively using the 'natural
     * order' algorithm. Return true if they are equal. */
    bool natequal_icase(const string& b) const
    {
	return natequal_icase(*this, b);
    }

    /** Compare this string to the other case-sensitively using the 'natural
     * order' algorithm. Strings that are equal in the 'natural order' are
     * compared using the binary less operator to break ties. Return true if
     * this one is less than the other. */
    bool natless(const std::string& b) const
    {
	int r = natcmp(*this, b);
	if (r != 0) return (r < 0);
	return (*this < b);
    }

    /** Compare this string to the other case-insensitively using the 'natural
     * order' algorithm. Strings that are equal in the 'natural order' are
     * compared using the binary less operator to break ties. Return true if
     * this one is less than the other. */
    bool natless_icase(const std::string& b) const
    {
	int r = natcmp_icase(*this, b);
	if (r != 0) return (r < 0);
	return less_icase(*this, b);
    }

    // *** 'natural order' less-relation functional class for std::map and
    // *** others ***

    /** 'Natural order' case-sensitive less order relation functional class for
     * std::map and others. */
    struct order_natless {
	inline bool operator()(const std::string &a, const std::string &b) const {
	    return natless(a, b);
	}
    };

    /** 'Natural order' case-insensitive less order relation functional class
     * for std::map and others. */
    struct order_natless_icase {
	inline bool operator()(const std::string &a, const std::string &b) const {
	    return natless_icase(a, b);
	}
    };

    /** Descending 'natural order' case-sensitive less order relation
     * functional class for std::map and others. */
    struct order_natless_desc {
	inline bool operator()(const std::string &a, const std::string &b) const {
	    return !natless(a, b);
	}
    };

    /** Descending 'natural order' case-insensitive less order relation
     * functional class for std::map and others. */
    struct order_natless_icase_desc {
	inline bool operator()(const std::string &a, const std::string &b) const {
	    return !natless_icase(a, b);
	}
    };

}; // class string

} // namespace stx

#ifndef STX_STRING_NO_ZLIB

#include <zlib.h>

inline std::string stx::string::compress(const std::string& str, int compressionlevel)
{
    z_stream zs;         // z_stream is zlib's control structure
    memset(&zs, 0, sizeof(zs));

    if (deflateInit(&zs, compressionlevel) != Z_OK)
	throw(std::runtime_error("deflateInit failed while compressing."));

    zs.next_in = const_cast<Bytef*>(reinterpret_cast<const Bytef*>(str.data()));
    zs.avail_in = str.size();           // set the z_stream's input

    int ret;
    char outbuffer[32768];
    std::string outstring;

    // retrieve the compressed bytes blockwise
    do {
	zs.next_out = reinterpret_cast<Bytef*>(outbuffer);
	zs.avail_out = sizeof(outbuffer);

	ret = deflate(&zs, Z_FINISH);

	if (outstring.size() < zs.total_out) {
	    // append the block to the output string
	    outstring.append(outbuffer,
			     zs.total_out - outstring.size());
	}
    } while (ret == Z_OK);

    deflateEnd(&zs);

    if (ret != Z_STREAM_END) {          // an error occurred that was not EOF
	std::ostringstream oss;
	oss << "Exception during zlib compression: (" << ret << ") " << zs.msg;
	throw(std::runtime_error(oss.str()));
    }

    return outstring;
}

inline std::string stx::string::gzcompress(const std::string& str, int compressionlevel)
{
    std::string outstring;

    // add simple gzip header of 10 bytes length
    static const unsigned int header_size = 10;
    outstring += '\x1F';	// ID1 (IDentification 1)
    outstring += '\x8B';	// ID2 (IDentification 2)
    outstring += '\x08';	// CM (Compression Method). 8 = deflate.
    outstring += '\x00';	// FLG (FLaGs). None set.
    outstring.append(4, '\0');	// MTIME (Modification TIME). Zeroed.
    outstring += '\x02';	// XFL (eXtra FLags). Set maximum compression.
    outstring += '\x03';	// OS (Operating System). 3 = Unix.

    // perform deflation
    z_stream zs;         // z_stream is zlib's control structure
    memset(&zs, 0, sizeof(zs));

    // use advance initialization routine with windowBits < 0 to suppress zlib
    // deflate header and footer.
    if (deflateInit2(&zs, compressionlevel, Z_DEFLATED, -MAX_WBITS, MAX_MEM_LEVEL, Z_DEFAULT_STRATEGY) != Z_OK)
	throw(std::runtime_error("deflateInit failed while compressing."));

    zs.next_in = const_cast<Bytef*>(reinterpret_cast<const Bytef*>(str.data()));
    zs.avail_in = str.size();           // set the z_stream's input

    int ret;
    char outbuffer[32768];

    // retrieve the compressed bytes blockwise
    do {
	zs.next_out = reinterpret_cast<Bytef*>(outbuffer);
	zs.avail_out = sizeof(outbuffer);

	ret = deflate(&zs, Z_FINISH);

	if (outstring.size() < header_size + zs.total_out) {
	    // append the block to the output string
	    outstring.append(outbuffer,
			     zs.total_out - outstring.size() + header_size);
	}
    } while (ret == Z_OK);

    deflateEnd(&zs);

    if (ret != Z_STREAM_END) {          // an error occurred that was not EOF
	std::ostringstream oss;
	oss << "Exception during zlib compression: (" << ret << ") " << zs.msg;
	throw(std::runtime_error(oss.str()));
    }

    // add gzip footer: calculate crc32 of original data

    uLong crc = crc32(0L, Z_NULL, 0);
    crc = crc32(crc, reinterpret_cast<const Bytef*>(str.data()), str.size());
    uLong datasize = str.size();

    // output crc and total uncompressed data size
    outstring.append(1, (crc >> 0)  & 0xFF);
    outstring.append(1, (crc >> 8)  & 0xFF);
    outstring.append(1, (crc >> 16) & 0xFF);
    outstring.append(1, (crc >> 24) & 0xFF);
    outstring.append(1, (datasize >> 0)  & 0xFF);
    outstring.append(1, (datasize >> 8)  & 0xFF);
    outstring.append(1, (datasize >> 16) & 0xFF);
    outstring.append(1, (datasize >> 24) & 0xFF);

    return outstring;
}

inline std::string stx::string::decompress(const std::string& str)
{
    z_stream zs;	// z_stream is zlib's control structure
    memset(&zs, 0, sizeof(zs));

    if (inflateInit(&zs) != Z_OK)
	throw(std::runtime_error("inflateInit failed while decompressing."));

    zs.next_in = const_cast<Bytef*>(reinterpret_cast<const Bytef*>(str.data()));
    zs.avail_in = str.size();

    int ret;
    char outbuffer[32768];
    std::string outstring;

    // get the uncompressed bytes blockwise using repeated calls to inflate
    do {
	zs.next_out = reinterpret_cast<Bytef*>(outbuffer);
	zs.avail_out = sizeof(outbuffer);

	ret = inflate(&zs, 0);

	if (outstring.size() < zs.total_out) {
	    outstring.append(outbuffer,
			     zs.total_out - outstring.size());
	}

    } while (ret == Z_OK);

    inflateEnd(&zs);

    if (ret != Z_STREAM_END) {          // an error occurred that was not EOF
	std::ostringstream oss;
	oss << "Exception during zlib uncompression: (" << ret << ") "
	    << zs.msg;
	throw(std::runtime_error(oss.str()));
    }

    return outstring;
}

#endif

#endif // _STX_STRING_H_
