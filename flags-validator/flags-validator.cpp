#include <iostream>
#include <stdint.h>
#include <Windows.h>
#include <codecvt>
#include <fstream>

#include "utils.h"

enum flags_hashes {
	/*dopelganging = 0x2e8563e,*/
	dora = 0xe729b278, tanya = 0xe78eeead, injector = 0x5425aa52
};

uint32_t get_round_flag_hash(unsigned round) {
	switch (round)
	{
	case 1:
		return flags_hashes::dora;
	case 2:
		return flags_hashes::injector;
	case 3:
		return flags_hashes::tanya;
		//case 4:
		//	return flags_hashes::dopelganging;
	}

	return 0;
}

bool flags_are_equal(std::string& inp_flag, unsigned round) {
	uint32_t flag_hash = get_round_flag_hash(round);
	return hash_flag(inp_flag) == flag_hash;

}

void check_flag() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	std::string round_str;

	std::cout << "Oh, great, you're ready to verify yourself.\n\nHere is task map:\n   1) DoraVm\n   2) self-injector\n   3) TanyaVM\n\nEnter the task number you've just solved, please:\n";
	std::cout << "Task number: ";
	std::cin >> round_str;
	std::cout << std::endl;
	unsigned round = inp_to_round(round_str);

	std::string flag;
	std::cout << "And now, please, enter the flag:\n";
	std::cout << "Flag: ";
	std::cin >> flag;
	std::cout << std::endl;

	if (flags_are_equal(flag, round)) {
		SetConsoleTextAttribute(hConsole, 10);
		std::cout << "Congratulations! Flag is correct. Now try re-run the programm with higher difficulty level.\n";
	}
	else {
		SetConsoleTextAttribute(hConsole, 12);
		std::cout << "Sorry, may be next time if you'll try harder. Bye!\n";

	}
	SetConsoleTextAttribute(hConsole, 7);
	return;
}

void hello() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout << "Hello! Welcome to flag verifier by ";
	SetConsoleTextAttribute(hConsole, 9);
	std::cout << "@fuunyaka";
	SetConsoleTextAttribute(hConsole, 7);
	std::cout << " (pm me on telegram if you have any questions about my reverse challenges).\n" << std::endl;
	return;
}

int main()
{
	hello();
	check_flag();
	return 0;
}

