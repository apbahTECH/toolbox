
#include "PluginManager.hpp"
#include "PluginDescriptor.hpp"

/*
 * Toolbox is actually at its core a plugin library,
 * so the main method does not actually make sense. This is
 * just here to aid in testing before testing is formalized.
 */
int main(int argc, char** argv)
{
	// Load test plugin.
	PluginManager::instance()->load("toolbox-plugin");

	// Describe plugin.
	PluginDescriptor* plugin = 0;
	PluginManager::instance()->describe("toolbox-plugin", plugin);

	// Enumerate plugins.
	std::map<std::string, PluginDescriptor> plugins;
	PluginManager::instance()->enumerate(plugins);

	// Use plugin for some operations.

	// Unload test plugin.
	PluginManager::instance()->unload("toolbox-plugin");

	// Enumerate plugins.
	PluginManager::instance()->enumerate(plugins);
}
