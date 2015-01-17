#ifndef JSONNODE_HPP
#define JSONNODE_HPP

class JSONNode
{
	public:
		virtual bool read() = 0;
		virtual std::string toString(bool formatted = false, int tabSize = 0) = 0;
		virtual JSONNode* jsonpath(std::string query) = 0;
};

#endif