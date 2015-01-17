#include <TildeJSON/JSONObject.hpp>

#include <sstream>

#define FORMATTED_ENDL if (formatted) ss << std::endl;
#define FORMATTED_TABS(t) if (formatted)            \
			              	for (int i=0; i<t; i++) \
				            	ss << '\t';

JSONObject::JSONObject()
{
}

std::string JSONObject::toString(bool formatted, int tabSize)
{
	std::stringstream ss;

	// 1 - Left brace
	FORMATTED_TABS(tabSize);
	ss << '{';
	tabSize++;
	FORMATTED_ENDL;

	// 2 - Key/Value pairs
	std::map<std::string,JSONValue*>::iterator it;
	int last = this->values.size()-1;
	int curr = 0;
	for (it = this->values.begin(); it != this->values.end(); ++it)
	{
		FORMATTED_TABS(tabSize);

		ss << '"' << it->first << "\":" << it->second->toString(formatted,tabSize);
		if (curr != last)
			ss << ',';
		FORMATTED_ENDL;
		curr++;
	}

	// 3 - Right brace
	FORMATTED_TABS(tabSize-1);
	ss << '}';

	return ss.str();
}

bool JSONObject::read()
{
	//std::cout << "Read JSONObject" << std::endl;

	if (Lexer::sym != Lexer::LBRACE)
	{
		Lexer::syntax_error();
		return false;
	}

	Lexer::next_sym();

	if (Lexer::sym != Lexer::STRING && Lexer::sym != Lexer::RBRACE)
	{
		Lexer::syntax_error();
		return false;
	}

	while (Lexer::sym != Lexer::RBRACE)
	{
		if (Lexer::sym == Lexer::COMMA)
		{
			Lexer::next_sym();
		}
		else if (Lexer::sym == Lexer::STRING)
		{
			std::string key = Lexer::str;
			Lexer::next_sym();

			if (Lexer::sym != Lexer::COLON)
			{
				Lexer::syntax_error();
				return false;
			}
			Lexer::next_sym();

			JSONValue* v = new JSONValue();
			if (!v->read())
				return false;

			this->values[key] = v;

			if (Lexer::sym != Lexer::RBRACE && Lexer::sym != Lexer::COMMA)
			{
				Lexer::syntax_error();
				return false;
			}
		}
		else
		{
			Lexer::syntax_error();
			return false;
		}
	}

	Lexer::next_sym();
	return true;
}