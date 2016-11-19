#include "interface.h"
#include "PluginManager.hpp"
#include "PluginDescriptor.hpp"

#include <algorithm>
#include <stdio.h> /* sprintf_s - Windows specific. */

int register_command(const char* plugin, const char* identifier,
	execute_func f)
{
	Command command = Command(plugin, identifier, f);

	/* 
	 * Register the Command with all loaded plugins.
	 * For the plugin this command belongs to, it will register as a command
	 * this plugin supports. For all other plugins it will register as a
	 * consumer that plugin can take advantage of.
	 */
	std::map<std::string, PluginDescriptor> ps;
	PluginManager::instance()->enumerate(ps);
	for (std::map<std::string, PluginDescriptor>::iterator iter = ps.begin();
		iter != ps.end(); ++iter) {
		iter->second.register_command(command);
	}

	return 0;
}

int enumerate_plugins(char** plugins, unsigned int* plugins_size,
	char** descriptions, unsigned int* descriptions_size)
{
	std::map<std::string, PluginDescriptor> ps;
	PluginManager::instance()->enumerate(ps);

	unsigned int size = std::min(*plugins_size, *descriptions_size);
	if (size < ps.size()) {
		return EINVALID;
	}
	else {
		size = ps.size();
	}

	unsigned int i = 0;
	for (std::map<std::string, PluginDescriptor>::iterator iter = ps.begin();
		iter != ps.end(); ++iter, ++i) {
		/* TODO: define size for plugin name and description and snprintf */
		sprintf_s(plugins[i], 128, "%s", iter->second.get_name().c_str());
		sprintf_s(descriptions[i], 128, "%s", iter->second.get_description().c_str());
	}
	*plugins_size = size;
	*descriptions_size = size;

	return EOK;
}

int load_plugin(const char* plugin)
{
	return PluginManager::instance()->load(std::string(plugin));
}

int unload_plugin(const char* plugin)
{
	return PluginManager::instance()->unload(std::string(plugin));
}

int enumerate_commands(const char* plugin, char** identifiers,
	unsigned int* identifiers_size)
{
	/* Find the Plugin Descriptor for this plugin. */

	/* Fill the input array with all of the supported identifiers. */
}