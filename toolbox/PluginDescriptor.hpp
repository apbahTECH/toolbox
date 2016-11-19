#pragma once

#include <string>
#include <map>
#include <vector>

#include "interface.h"
#include "Command.hpp"

class PluginDescriptor {
public:
	PluginDescriptor();
	PluginDescriptor(std::string name, startup_func stf, shutdown_func shf,
		register_func rf, unregister_func uf);
	~PluginDescriptor();

	std::string get_name();
	void set_description(std::string description);
	std::string get_description();
	void get_commands(std::vector<std::string>& commands);
	void shutdown();
	void register_command(Command command);
	void unregister_commands(std::string plugin_name);
private:
	std::string name;
	std::string description;
	std::map<std::string, Command> commands;

	startup_func start_func;
	shutdown_func shut_func;
	register_func reg_func;
	unregister_func unreg_func;
};
