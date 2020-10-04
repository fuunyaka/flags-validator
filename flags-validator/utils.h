#pragma once

#include <string>
#include <iostream>

uint32_t hash_flag(std::string& name)
{
	size_t name_len = name.size();

	if (!name_len || name_len >= 4096)
	{
		return 0;
	}

	uint32_t u32Hash = 0, u32Buf = 0;

	uint8_t* pbData = (uint8_t*)name.c_str();
	int iRemain = (name_len & 3);

	name_len >>= 2;

	for (size_t i = name_len; i > 0; i--)
	{
		u32Hash += *(const uint16_t*)pbData;
		u32Buf = (*(const uint16_t*)(pbData + 2) << 11) ^ u32Hash;
		u32Hash = (u32Hash << 16) ^ u32Buf;
		pbData += (2 * sizeof(uint16_t));
		u32Hash += u32Hash >> 11;
	}

	switch (iRemain)
	{
	case 1:
		u32Hash += *pbData;
		u32Hash ^= u32Hash << 10;
		u32Hash += u32Hash >> 1;
		break;

	case 2:
		u32Hash += *(const uint16_t*)pbData;
		u32Hash ^= u32Hash << 11;
		u32Hash += u32Hash >> 17;
		break;

	case 3:
		u32Hash += *(const uint16_t*)pbData;
		u32Hash ^= u32Hash << 16;
		u32Hash ^= pbData[sizeof(uint16_t)] << 18;
		u32Hash += u32Hash >> 11;
		break;
	}

	u32Hash ^= u32Hash << 3;
	u32Hash += u32Hash >> 5;
	u32Hash ^= u32Hash << 4;
	u32Hash += u32Hash >> 17;
	u32Hash ^= u32Hash << 25;
	u32Hash += u32Hash >> 6;

	return u32Hash;
}


unsigned inp_to_round(std::string round_str) {
	unsigned round = atoi(round_str.c_str());
	if (round < 1 || round > 3 /*4*/) {
		std::cout << "Incorrect round! Bye nasty hackerman.\n";
		exit(0);
	}
	return round;
}