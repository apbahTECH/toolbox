
#include "../toolbox/interface.h"

#include <cstdio>
#include <iostream>

int main(int argc, char** argv)
{
	std::printf("toolbox console\n");

	/* Load plugin. */
	int l = load_plugin("toolbox-plugin");
	std::printf("Load Plugin return %d\n", l);

	/* Enumerate plugin. */
	char plugin[128] = { '\0' };
	char* plugins[1] = { plugin };
	unsigned int plugins_size = 1;
	char description[256] = { '\0' };
	char* descriptions[1] = { description };
	unsigned int descriptions_size = 1;
	enumerate_plugins(plugins, &plugins_size, descriptions, &descriptions_size);
	std::printf("Plugins Size: %d\n", plugins_size);
	std::printf("Descriptions Size: %d\n", descriptions_size);
	if (plugins_size >= 1 && descriptions_size >= 1) {
		std::printf("Plugin: %s\n", plugins[0]);
		std::printf("Description: %s\n", descriptions[0]);
	}

	/* Enumerate commands on plugin. */
	char identifier[128] = { '\0' };
	char* identifiers[1] = { identifier };
	unsigned int identifiers_size = 1;
	enumerate_commands("toolbox-plugin", identifiers, &identifiers_size);
	for (int i = 0; i < identifiers_size; ++i) {
		std::printf("toolbox-plugin command identifier: %s\n", identifiers[i]);
	}

	/* Do some operations. */

	int n = 0;
	std::cin >> n;
}