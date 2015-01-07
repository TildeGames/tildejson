#include <TildeJSON/JSON.hpp>

JSON::JSON()
	: object(NULL)
{

}

std::string JSON::toString(bool formatted)
{
	return object->toString(formatted,0);
}

void JSON::read()
{
	//std::cout << "Read JSON" << std::endl;

	Lexer::next_sym();
	this->object = new JSONObject();
	this->object->read();

	if (Lexer::sym != Lexer::EOI)
		Lexer::syntax_error();
}