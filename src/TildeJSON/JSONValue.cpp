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


void JSONValue::read()
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
		this->obj->read();
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
		Lexer::syntax_error();
}