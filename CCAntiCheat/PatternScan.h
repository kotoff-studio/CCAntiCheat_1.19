#pragma once

#include <Windows.h>
#include <string>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <psapi.h>

namespace CCAC_Widgets {
	inline size_t FindPatternDump(const UCHAR* dump, const size_t length, const UCHAR* pattern, const char* mask, size_t& outOffset) {
		const size_t maskLength = std::strlen(mask);
		size_t patternPos = 0;
		size_t tmpOffset = -1;
		for (size_t offset; offset < length - 1; ++offset) {
			if (dump[offset] == pattern[patternPos] || mask[patternPos] == '?') {
				if (mask[patternPos + 1] == '\0') {
					outOffset = (offset - maskLength);
					return true;
				}
				if (tmpOffset == static_cast<size_t>(-1)) {
					tmpOffset = offset;
				}
				patternPos++;
			}
			else
			{
				if (tmpOffset > static_cast<size_t>(-1)) {
					offset = tmpOffset;
					tmpOffset = static_cast<size_t>(-1);
				}
				patternPos = 0;
			}
		}
		return false;
	}

	inline uintptr_t FindPatternExternal(HANDLE procHandle, HMODULE mHandle, const UCHAR* pattern, const char* mask) {
		uintptr_t result = 0;
		MODULEINFO info = { };
		const auto moduleAddress = reinterpret_cast<uintptr_t>(mHandle);
		
		if (GetModuleInformation(procHandle, mHandle, &info, sizeof(MODULEINFO))) {
			auto buffer = new unsigned char[info.SizeOfImage];
			if (ReadProcessMemory(procHandle, mHandle, buffer, info.SizeOfImage, nullptr) != 0) {
				size_t outOffset;
				if (FindPatternDump(buffer, info.SizeOfImage, pattern, mask, outOffset))
					result = moduleAddress + outOffset;
			}
			delete[] buffer;
		}
		return result;
	}

	inline uintptr_t FindPattern(const uintptr_t start, const size_t length, const unsigned char* pattern, const char* mask)
	{
		size_t pos = 0;
		const auto maskLength = std::strlen(mask) - 1;

		uintptr_t tmpAddress = 0;
		const auto moduleLength = start + length - 1;
		for (auto it = start; it < moduleLength; ++it)
		{
			if (*reinterpret_cast<unsigned char*>(it) == pattern[pos] || mask[pos] == '?')
			{
				if (mask[pos + 1] == '\0')
				{
					return it - maskLength;
				}
				if (tmpAddress == 0)
				{
					tmpAddress = it;
				}
				pos++;
			}
			else
			{
				if (tmpAddress > 0)
				{
					it = tmpAddress;
					tmpAddress = 0;
				}
				pos = 0;
			}
		}

		return 0;
	}

	inline uintptr_t FindPattern(const HANDLE processHanlde, const HMODULE moduleHandle, const unsigned char* pattern, const char* mask)
	{
		uintptr_t result;
		MODULEINFO info = { };
		if (GetModuleInformation(processHanlde, moduleHandle, &info, sizeof(MODULEINFO)))
		{
			result = FindPattern(reinterpret_cast<uintptr_t>(moduleHandle), info.SizeOfImage, pattern, mask);
		}
		return result;
	}

	inline uintptr_t FindPattern(const HMODULE moduleHandle, const unsigned char* pattern, const char* mask)
	{
		return FindPattern(GetCurrentProcess(), moduleHandle, pattern, mask);
	}

	inline uintptr_t ReadRIPAddress(HANDLE processHanlde, const uintptr_t address, const uint32_t firstOffset, const uint32_t secondOffset)
	{
		uintptr_t result = 0;
		uint32_t offset;
		if (ReadProcessMemory(processHanlde, reinterpret_cast<LPCVOID>(address + firstOffset), &offset, sizeof(uint32_t), nullptr) != 0)
		{
			result = address + offset + secondOffset;
		}
		return result;
	}

	inline uintptr_t ReadRIPAddressPtr(HANDLE processHanlde, const uintptr_t address, const uint32_t firstOffset, const uint32_t secondOffset)
	{
		uintptr_t result = 0;
		uint32_t offset;
		if (ReadProcessMemory(processHanlde, reinterpret_cast<LPCVOID>(address + firstOffset), &offset, sizeof(uint32_t), nullptr) != 0)
		{
			uintptr_t tmpResult;
			if (ReadProcessMemory(processHanlde, reinterpret_cast<LPCVOID>(address + offset + secondOffset), &tmpResult, sizeof(uintptr_t), nullptr) != 0)
			{
				result = tmpResult;
			}
		}
		return result;
	}
}