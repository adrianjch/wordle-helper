#include <string>
#include <iostream>
#include "Configuration.h"


int main() {
	Wordle wordle;
	
	for (int i = 0; i < 6; i++) {
		wordle.GetBestWords();

		std::cout << "Word registered: ";
		std::string word;
		std::cin >> word;
		std::cout << "Output: ";
		std::string output;
		std::cin >> output;
		wordle.RegisterWord(word, output);
	}

	return 0;
}