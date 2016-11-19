
#include "PluginManager.hpp"

#include "interface.h"
#include "Windows.h" /* DLL management functions. */

PluginManager::PluginManager()
{
}

PluginManager::~PluginManager()
{
}

PluginManager* PluginManager::inst = NULL;
PluginManager* PluginManager::instance()
{
	if (!inst) {
		inst = new PluginManager();
	}
	return inst;
}

ECODE PluginManager::load(std::string name)
{
	/* Find the plugin and load. */
	HINSTANCE dll_instance;
	dll_instance = LoadLibrary(name.c_str());
	if (!dll_instance) {
		return EDLLLOAD;
	}

	/*
	 * Load up the plugin descriptor with the functions we need.
	 * The pointer casting here is implementation dependent, so we cannot
	 * be too comfortable that this is working on all targets.
	 */
	startup_func stf = (startup_func)GetProcAddress(dll_instance, "startup");
	shutdown_func shf = (shutdown_func)GetProcAddress(dll_instance, "shutdown");
	register_func rf = (register_func)GetProcAddress(dll_instance,
		"plugin_register_command");
	unregister_func uf = (unregister_func)GetProcAddress(dll_instance,
		"plugin_unregister_command");

	/*
	* Register the plugin descriptor before actually starting
	* up the plugin. The plugin startup needs to have the plugin
	* descriptor available to register commands with.
	*/
	plugins.insert(std::pair<std::string, PluginDescriptor>(name,
		PluginDescriptor(name, stf, shf, rf, uf)));

	/* Startup the plugin. */
	return static_cast<ECODE>(stf());
}

ECODE PluginManager::unload(std::string name)
{
	/* Find the plugin descriptor. */
	PluginDescriptor* pd = 0;
	describe(name, pd);

	/* Un-register the plugin with the manager. */
	plugins.erase(name);

	/* Un-register the plugin with all other plugins. */
	for (std::map<std::string, PluginDescriptor>::iterator iter = plugins.begin();
		iter != plugins.end(); ++iter) {
		iter->second.unregister_commands(name);
	}

	/* Shutdown the plugin. */
	pd->shutdown();

	/* TODO: free the related DLL */

	return EOK;
}

ECODE PluginManager::describe(std::string name, PluginDescriptor* plugin)
{
	PluginDescriptor& pd = plugins[name];
	plugin = &pd;
	return EOK;
}

ECODE PluginManager::enumerate(std::map<std::string, PluginDescriptor>& ps)
{
	ps = plugins;
	return EOK;
}