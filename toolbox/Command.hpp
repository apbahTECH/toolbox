#pragma once

#include <string>

#include "interface.h"
#include "CommandType.h"

class Command {
public:
	Command(const char* plugin, const char* identifier, execute_func f);
	~Command();

	std::string plugin;
	std::string identifier;
	execute_func func;
};