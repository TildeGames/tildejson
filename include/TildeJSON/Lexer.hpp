#ifndef LEXER_HPP
#define LEXER_HPP

#include <iostream>
#include <cstdlib>
#include <map>
#include <cstdio>
#include <sstream>

namespace Lexer
{
	enum { LBRACE, RBRACE, LBRACKET, RBRACKET, COLON, COMMA, STRING, NUMBER, STRUE, SFALSE, SNULL, EOI};

	extern std::map<std::string,int> symbols;

	extern char ch;
	extern int sym;
	extern float num;
	extern std::string str;

	void init();

	void next_ch();

	void syntax_error();

	void next_sym();

}

#endif