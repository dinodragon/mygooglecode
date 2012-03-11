#include "unicode.h"
#include <windows.h>
#include <assert.h>

namespace yfbase{

	//ANSI=>UTF8
	std::string string2utf8(const std::string & text)
	{
		// ansi => utf16 => utf8
		const int wbuf_len = MultiByteToWideChar(CP_ACP, 0, text.c_str(), (int)text.size(), NULL, 0);
		wchar_t* wbuf = new wchar_t[wbuf_len];
		int cd = MultiByteToWideChar(CP_ACP, 0, text.c_str(), (int)text.size(), wbuf, wbuf_len);
		assert(cd == wbuf_len);
		const int u8_len = WideCharToMultiByte(CP_UTF8, 0, wbuf, wbuf_len, 0, 0, NULL, NULL);
		char * u8 = new char[u8_len + 1];
		cd = WideCharToMultiByte(CP_UTF8, 0, wbuf, wbuf_len, u8, u8_len, NULL, NULL);
		assert(cd == u8_len);
		std::string ret(u8, u8 + u8_len);
		delete [] wbuf;
		delete [] u8;
		return ret;
	}

	//ANSI=>UNICODE
	std::wstring string2w(const std::string & text)
	{
		// ansi => utf16
		const int len = MultiByteToWideChar(CP_ACP, 0, text.c_str(), (int)text.size(), 0, 0);
		wchar_t * w = new wchar_t[len + 1];
		int cd = MultiByteToWideChar(CP_ACP, 0, text.c_str(), (int)text.size(), w, len);
		assert(cd == len);
		std::wstring ret(w, w + len);
		delete [] w;
		return ret;
	}

	//UNICDOE->UTF8
	std::string w2utf8(const std::wstring & text)
	{
		// utf16 => utf8
		const int u8_len = WideCharToMultiByte(CP_UTF8, 0, text.c_str(), (int)text.size(), 0, 0, NULL, NULL);
		char * u8 = new char[u8_len + 1];
		int cd = WideCharToMultiByte(CP_UTF8, 0, text.c_str(), (int)text.size()	, u8, u8_len, NULL, NULL);
		assert(cd == u8_len);
		std::string ret(u8, u8 + u8_len);
		delete [] u8;
		return ret;
	}

	//UNICODE=>ANSI
	std::string w2string(const std::wstring & text)
	{
		// utf16 => ansi
		const int u8_len = WideCharToMultiByte(936, 0, text.c_str(), (int)text.size(), 0, 0, NULL, NULL);
		char * u8 = new char[u8_len + 1];
		int cd = WideCharToMultiByte(936, 0, text.c_str(), (int)text.size(), u8, u8_len, NULL, NULL);
		assert(cd == u8_len);
		std::string ret(u8, u8 + u8_len);
		delete [] u8;
		return ret;
	}

	//UTF8->ANSI
	std::string utf82string(const std::string& text)
	{
		// u8 => utf16 => ansi
		const int wbuf_len = MultiByteToWideChar(CP_UTF8, 0, text.c_str(), (int)text.size(), NULL, 0);
		wchar_t* wbuf = new wchar_t[wbuf_len];
		int cd = MultiByteToWideChar(CP_UTF8, 0, text.c_str(), (int)text.size(), wbuf, wbuf_len);
		assert(cd == wbuf_len);

		const int ansi_len = WideCharToMultiByte(936, 0, wbuf, wbuf_len, 0, 0, NULL, NULL);
		char * ansi = new char[ansi_len + 1];
		cd = WideCharToMultiByte(936, 0, wbuf, wbuf_len, ansi, ansi_len, NULL, NULL);
		assert(cd == ansi_len);
		delete [] wbuf;
		std::string ret(ansi,ansi_len);
		delete [] ansi;
		return ret;
	}

	//UTF8->UNICODE
	std::wstring utf82w(const std::string & text)
	{
		const int wbuf_len = MultiByteToWideChar(CP_UTF8, 0, text.c_str(), (int)text.size(), NULL, 0);
		wchar_t* wbuf = new wchar_t[wbuf_len];
		int cd = MultiByteToWideChar(CP_UTF8, 0,text.c_str(), (int)text.size(), wbuf, wbuf_len);
		assert(cd == wbuf_len);
		std::wstring ret(wbuf,wbuf_len);
		return ret;
	}
} // yfbase


