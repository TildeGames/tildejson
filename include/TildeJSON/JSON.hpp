#ifndef JSON_HPP
#define JSON_HPP

#include <string>

#include "JSONObject.hpp"

class JSON
{
	public:
		JSON();
		std::string toString(bool formatted = false);
		void read();

		JSONObject *object;
};

#endif