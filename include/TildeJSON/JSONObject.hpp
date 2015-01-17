#ifndef JSONOBJECT_HPP
#define JSONOBJECT_HPP

#include <string>
#include <map>

#include "JSONValue.hpp"

class JSONValue;

class JSONObject
{
	public:
		JSONObject();
		std::string toString(bool formatted = false, int tabSize = 0);
		bool read();

		std::map<std::string,JSONValue*> values;
};

#endif