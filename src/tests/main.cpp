#include <TildeJSON/JSON.hpp>

using namespace std;

int main()
{
	Lexer::init();

	JSON *json = new JSON();
	json->read();

	cout << "Raw" << endl;
	cout << json->toString(false) << endl;
	
	cout << "Formatted" << endl;
	cout << json->toString(true) << endl;

	return 0;
}