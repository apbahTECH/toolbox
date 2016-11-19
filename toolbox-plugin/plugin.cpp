#include "../toolbox/interface.h"

#include "plugin.hpp"
#include <cstdio>

static const char* plugin_name = "toolbox-plugin";
static const char* command_identifier = "toolbox-command";

int test_command(char* args, void* data, unsigned int data_size)
{
	std::printf("Executing test command.\n");
	return 0;
}

int startup()
{
	std::printf("Starting up plugin.\n");
	/* Register test_command with the plugin system. */
	register_command(plugin_name, command_identifier, test_command);
	return 0;
}

int shutdown()
{
	std::printf("Shutting down plugin.\n");
	return 0;
}

int plugin_register_command(const char* origin_plugin, const char* identifier,
	execute_func f)
{
	std::printf("Register command %s from plugin %s.\n", identifier,
		origin_plugin);
	return 0;
}

int plugin_unregister_commands(const char* origin_plugin)
{
	std::printf("Unregister commands from plugin %s.\n", origin_plugin);
	return 0;
}