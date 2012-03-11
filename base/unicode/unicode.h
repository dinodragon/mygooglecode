#ifndef __UNICODE_H__
#define __UNICODE_H__

#include <string>
namespace yfbase{
	//ANSI=>UTF8
	std::string string2utf8(const std::string & text);
	//ANSI=>UNICODE
	std::wstring string2w(const std::string & text);
	//UNICDOE->UTF8
	std::string w2utf8(const std::wstring & text);
	//UNICODE=>ANSI
	std::string w2string(const std::wstring & text);
	//UTF8->ANSI
	std::string utf82string(const std::string& text);
	//UTF8->UNICODE
	std::wstring utf82w(const std::string & text);
} // yfbase
#endif // __UNICODE_H__

