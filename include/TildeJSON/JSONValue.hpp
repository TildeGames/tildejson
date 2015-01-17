#ifndef JSONVALUE_HPP
#define JSONVALUE_HPP

#include <iostream>
#include <string>

#include "Lexer.hpp"
#include "JSONObject.hpp"
#include "JSONNode.hpp"

class JSONObject;

class JSONValue : public JSONNode
{
	public:
		JSONValue();
		std::string toString(bool formatted = false, int tabSize = 0);
		bool read();
		JSONNode* jsonpath(std::string query);

		void setValueString(std::string string);
		void setValueNumber(int number);
		void setValueSymbol(int symbol);

		std::string type;
		std::string str;
		float  num;
		JSONObject* obj;
		//JSONArray*  arr;
		int sym;
};

#endif