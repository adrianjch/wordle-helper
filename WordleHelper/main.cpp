#include <string>
#include <iostream>
#include "Wordle.h"

/*
*	TODO list
*	- Use Dear ImGUI
*	- - Dropdown showing all available languages with a button to load the selected one
*	- - List with top 100 words and their score (also somewhere show the total amount of possible words)
*	- - A visual simulation of the Wordle game.
*	- - - X boxes, you can click a box to change its color (rotate between gray/yellow/green)
*	- - - Some way to add a character to each box (maybe be able to select a row and just by typing it gets added to the next square on that row)
*	- - - A submit button to calculate the available words based on the visual simulation
*	- Remove config, instead use Dear ImGUI for that
*
*	TODO OPTIONAL
*	- Add strategies (greedy = current one, discovery = tries to discover as many different correct letters, meaning it will try to not repeat correct letters)
**/
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