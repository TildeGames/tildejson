#ifndef JSONVALUE_HPP
#define JSONVALUE_HPP

#include <iostream>
#include <string>

#include "Lexer.hpp"
#include "JSONObject.hpp"

class JSONObject;

class JSONValue
{
	public:
		JSONValue();
		std::string toString(bool formatted = false, int tabSize = 0);
		bool read();

		std::string type;
		std::string str;
		float  num;
		JSONObject* obj;
		//JSONArray*  arr;
		int sym;
};

#endif