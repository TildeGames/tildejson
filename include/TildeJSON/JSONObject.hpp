#ifndef JSONOBJECT_HPP
#define JSONOBJECT_HPP

#include <string>
#include <map>

#include "JSONValue.hpp"
#include "JSONNode.hpp"

class JSONValue;

class JSONObject : public JSONNode
{
	public:
		JSONObject();
		std::string toString(bool formatted = false, int tabSize = 0);
		bool read();
		JSONNode* jsonpath(std::string query);

		std::map<std::string,JSONValue*> values;
};

#endif