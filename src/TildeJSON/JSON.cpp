#include <TildeJSON/JSON.hpp>

JSON::JSON()
	: object(NULL)
{

}

std::string JSON::toString(bool formatted, int tabSize)
{
	return object->toString(formatted,tabSize);
}

bool JSON::read()
{
	//std::cout << "Read JSON" << std::endl;

	Lexer::next_sym();
	this->object = new JSONObject();
	
	if (!this->object->read())
		return false;

	if (Lexer::sym != Lexer::EOI)
	{
		Lexer::syntax_error();
		return false;
	}

	return true;
}

JSONNode* JSON::jsonpath(std::string query)
{
	// Begin with '$'
	if (query[0] != '$')
		return NULL;

	// Query is "$"
	if (query.length() == 1)
		return this;

	// Begin with '$.'
	if (query[1] != '.')
		return NULL;

	// Delegate
	query[0] = '@';
	return this->object->jsonpath(query);
}