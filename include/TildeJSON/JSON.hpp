#ifndef JSON_HPP
#define JSON_HPP

#include <string>

#include "JSONObject.hpp"
#include "JSONNode.hpp"

class JSON : public JSONNode
{
	public:
		JSON();
		std::string toString(bool formatted = false, int tabSize = 0);
		bool read();
		JSONNode* jsonpath(std::string query);
		bool write(std::string path);

		JSONObject *object;
};

#endif