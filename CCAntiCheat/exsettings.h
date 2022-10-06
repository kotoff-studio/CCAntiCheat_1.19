#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <stdio.h>

class exset {

	/*  */
	std::string Keys(std::string keys) {
		int keyset = std::stoi(keys);
		if (keyset == NULL) {
			return NULL;
		}
		else {
			size_t ksize = keys.size();
			std::vector<uint8_t> y(sizeof(keys.size()));
			::memcpy(y.data(), &ksize, sizeof(ksize));
			//std::vector<std::string> nn; something missing
		}
	}

	std::string mdKeys[0x80];

	int listcheck(FILE *cfgFile, const char* data) {
		cfgFile = fopen("cfg/config.anticonfig","w");
		if (cfgFile == NULL)
			printf("Something is missing...\n");
		else
			printf("Successfully opened!\n");

		fprintf(cfgFile, data);
		printf("Data has been written!\n");
		fclose(cfgFile);

		return 0;
	}

	bool mdcheck(std::string objstatus) {
		unsigned int fl = mdKeys->size();
		if (mdKeys == NULL) {
			return false;
		}
		else {
			for (int j = 0; j < fl; j++) {
				if (mdcheck(mdKeys[1])) {
					return true;
				}
			}
			return false;
		}
	}

	std::string defaultMd[0x6A];

	bool isNpc;

	std::string bukkitPattern;

	exset exsettings(FILE* Config) {
		listcheck(Config, "COMPATIBILITY_EXEMPTIONS_WILDCARD_DEFAULT_METADATA_ACTIVE");
		listcheck(Config, "COMPATIBILITY_EXEMPTIONS_WILDCARD_NPC_ACTIVE");
		listcheck(Config, "COMPATIBILITY_EXEMPTIONS_WILDCARD_NPC_BUKKITINTERFACE");
		listcheck(Config, "COMPATIBILITY_EXEMPTIONS_WILDCARD_NPC_METADATA_ACTIVE");
		listcheck(Config, "COMPATIBILITY_EXEMPTIONS_WILDCARD_NPC_METADATA_KEYS");
	}
};