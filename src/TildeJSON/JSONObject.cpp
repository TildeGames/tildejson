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

JSONNode* JSONObject::jsonpath(std::string query)
{
	// Begin with '@'
	if (query[0] != '@')
		return NULL;

	// Query is "@"
	if (query.length() == 1)
		return this;

	// Begin with '@.'
	if (query[1] != '.')
		return NULL;

	// Get child str
	int idx = 2;
	while (idx < query.length() && query[idx] != '.')
		idx++;
	std::string child = query.substr(2,idx-2);

	if (this->values.count(child) > 0)
	{
		// The value is the last node in query
		if (idx == query.length())
			return this->values[child];

		// Delegate query to child
		else
		{
			std::string newQuery = '@' + query.substr(2+idx-2,query.length());
			return this->values[child]->jsonpath(newQuery);
		}
	}

	return NULL;
}