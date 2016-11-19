#include "Command.hpp"

Command::Command(const char* p, const char* i, execute_func f)
{
	plugin = std::string(p);
	identifier = std::string(i);
	func = f;
}

Command::~Command()
{}