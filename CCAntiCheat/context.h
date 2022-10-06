#pragma once

#include <cassert>
#include <windows.h>
#include <vector>
#include "ex_b64prov.h"

class excon {
public:
	unsigned int NONTESTED = -1;
	unsigned int CONTEXTVER = 0;

	int* id;

	int ShowACContent() {
		if (id == 0) {
			assert(id);
			(*id)++;
		}
		return *id;
	}

	int GetIdentityInfo() {
		return *id; // memory leaks mm 
	}

	std::string Hash() {
		std::vector<BYTE> data4hash;
		std::string encdata = base64_encode(&data4hash[0], data4hash.size());
		return encdata;
	}

	int combo_eq(bool obj) {
		if (!obj) {
			return false;
		}

		//excon data;
	}
};