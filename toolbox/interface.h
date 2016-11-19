#pragma once

/*
 * Interface for plugins to interact with the toolbox core.
 */
#include "CommandType.h"

#ifndef EXPORT
#define EXPORT __declspec(dllexport)
#endif /* ifndef EXPORT */

/* Plugins must define all of the following functions. */
extern "C" typedef int(*startup_func)();
extern "C" typedef int(*shutdown_func)();
extern "C" typedef int(*execute_func)
	(char* args, void* data, unsigned int data_size);
extern "C" typedef int(*register_func)(const char* origin_plugin,
	const char* identifier, execute_func f);
extern "C" typedef int(*unregister_func)(const char* origin_plugin);

extern "C" {
	/* Register a command with the toolbox. */
	EXPORT int register_command(const char* plugin, const char* identifier,
		execute_func f);

	/* Enumerate all plugins loaded in the toolbox. */
	EXPORT int enumerate_plugins(char** plugins, unsigned int* plugins_size,
		char** descriptions, unsigned int* descriptions_size);

	/* Enumerate all commands surfaced by the plugin. */
	EXPORT int enumerate_commands(const char* plugin, char** identifiers,
		unsigned int* identifiers_size);

	/* Load a plugin to the toolbox. */
	EXPORT int load_plugin(const char* plugin);

	/* Unload a plugin from the toolbox. */
	EXPORT int unload_plugin(const char* plugin);

	/* Execute the identified functionality on the plugin. */
	EXPORT int execute(const char* plugin, const char* identifier);
}