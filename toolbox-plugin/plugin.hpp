#pragma once

#include "../toolbox/interface.h"

#ifndef EXPORT
#define EXPORT __declspec(dllexport)
#endif /* ifndef EXPORT */

/*
 * Define plugin API with C linkage.
 */
extern "C"
{
	EXPORT int startup();
	EXPORT int shutdown();
	EXPORT int plugin_register_command(const char* origin_plugin,
		const char* identifier, execute_func f);
	EXPORT int plugin_unregister_commands(const char* origin_plugin);
}