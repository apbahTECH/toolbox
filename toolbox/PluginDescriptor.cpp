#include "PluginDescriptor.hpp"

#include <algorithm>

/* TODO: where are we using this? */
PluginDescriptor::PluginDescriptor() {}

PluginDescriptor::PluginDescriptor(std::string n, startup_func stf,
	shutdown_func shf, register_func rf, unregister_func uf)
{
	name = n;
	start_func = stf;
	shut_func = shf;
	reg_func = rf;
	unreg_func = uf;
}

PluginDescriptor::~PluginDescriptor()
{
}

std::string PluginDescriptor::get_name()
{
	return name;
}

void PluginDescriptor::set_description(std::string d)
{
	description = d;
}

std::string PluginDescriptor::get_description()
{
	return description;
}

void PluginDescriptor::shutdown()
{
	shut_func();
}

void PluginDescriptor::register_command(Command c)
{
	/*
	 * If we are registering a command with this plugin as the origin then
	 * insert into our command map.
	 */
	if (c.plugin == name) {
		commands.insert(std::pair<std::string, Command>(c.identifier, c));
	}
	/*
	 * Otherwise, register this command with the plugin library.
	 */
	else {
		reg_func(c.plugin.c_str(), c.identifier.c_str(), c.func);
	}
}

void PluginDescriptor::unregister_commands(std::string plugin_name)
{
	unregister_func(plugin_name.c_str());
}

void PluginDescriptor::get_commands(std::vector<std::string>& cs)
{
	for (std::map<std::string, Command>::iterator iter = commands.begin();
		iter != commands.end(); ++iter) {
		cs.push_back(iter->first);
	}
}
