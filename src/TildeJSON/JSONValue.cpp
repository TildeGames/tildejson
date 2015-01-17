#include <TildeJSON/JSONValue.hpp>

#include <sstream>

#define FORMATTED_ENDL if (formatted) ss << std::endl;

JSONValue::JSONValue() : type(""), str(""), num(0), obj(NULL), sym(0)
{

}

std::string JSONValue::toString(bool formatted, int tabSize)
{
	std::stringstream ss;

	if (this->type == "STRING")
		ss << '"' << this->str << '"';
	else if (this->type == "NUMBER")
		ss << this->num;
	else if (this->type == "OBJECT")
	{	
		FORMATTED_ENDL;
		ss << this->obj->toString(formatted,tabSize);
	}
	else if (this->type == "ARRAY")
		std::cout << "NYI" << std::endl;
	else if (this->type == "SYMBOL")
	{
		if (this->sym == Lexer::STRUE) ss << "true";
		else if (this->sym == Lexer::SFALSE) ss << "false";
		else if (this->sym == Lexer::SNULL) ss << "null";
	}

	return ss.str();
}


bool JSONValue::read()
{
	//std::cout << "Read JSONValue" << std::endl;

	if (Lexer::sym == Lexer::STRING)
	{
		this->str = Lexer::str;
		this->type = "STRING";
		Lexer::next_sym();
	}
	else if (Lexer::sym == Lexer::NUMBER)
	{
		this->num = Lexer::num;
		this->type = "NUMBER";
		Lexer::next_sym();
	}
	else if (Lexer::sym == Lexer::LBRACE)
	{
		this->obj = new JSONObject();
		if (!this->obj->read())
			return false;
		this->type = "OBJECT";
	}
	else if (Lexer::sym == Lexer::RBRACKET)
		std::cout << "NYI" << std::endl;
	else if (Lexer::sym == Lexer::STRUE || Lexer::sym == Lexer::SFALSE || Lexer::sym == Lexer::SNULL)
	{
		this->sym = Lexer::sym;
		this->type = "SYMBOL";
		Lexer::next_sym();
	}
	else
	{
		Lexer::syntax_error();
		return false;
	}

	return true;
}

JSONNode* JSONValue::jsonpath(std::string query)
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

	// Can't get child of literal
	if (this->type == "STRING" || this->type == "NUMBER" || this->type == "SYMBOL")
		return NULL;

	// Delegate
	if (type == "OBJECT")
		return this->obj->jsonpath(query);
	else
		std::cout << "NYI" << std::endl;

	return NULL;
}

void JSONValue::setValueString(std::string string)
{
	this->num = 0;
	this->obj = NULL;
	this->sym = 0;

	this->type = "STRING";
	this->str = string;
}

void JSONValue::setValueNumber(int number)
{
	this->str = "";
	this->obj = NULL;
	this->sym = 0;

	this->type = "NUMBER";
	this->num = number;
}

void JSONValue::setValueSymbol(int symbol)
{
	this->str = "";
	this->obj = NULL;
	this->num = 0;

	this->type = "SYMBOL";
	this->sym = symbol;
}