#pragma once

#include <string>
#include <map>

#include "ecode.h"
#include "PluginDescriptor.hpp"

class PluginManager {
public:
	static PluginManager* instance();

	ECODE load(std::string name);
	ECODE unload(std::string name);
	ECODE describe(std::string name, PluginDescriptor* plugin);
	ECODE enumerate(std::map<std::string, PluginDescriptor>& plugins);

private:
	PluginManager();
	~PluginManager();

	static PluginManager* inst; 
	std::map<std::string, PluginDescriptor> plugins;
};