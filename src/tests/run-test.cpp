#include <TildeJSON/JSON.hpp>

using namespace std;

int main()
{
	Lexer::init();

	JSON *json = new JSON();

	if (!json->read())
		return EXIT_FAILURE;

	cout << "Raw" << endl;
	cout << json->toString(false) << endl;
	
	cout << "Formatted" << endl;
	cout << json->toString(true) << endl;

	return EXIT_SUCCESS;
}