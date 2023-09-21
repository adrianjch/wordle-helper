#include "Wordle.h"
#include <string>
#include <fstream>
#include <iostream>
#include <codecvt>

Wordle::Wordle() {
	LoadConfig();
	LoadLetterFrequency();
	LoadDictionary();
}

void Wordle::LoadConfig() {
	std::ifstream config("../config.txt");
	if (!config.is_open()) {
		return;
	}

	std::getline(config, language);
	std::string wordLengthString;
	std::getline(config, wordLengthString);
	auto length = std::stoi(wordLengthString);
	if (length >= 2 && length < 50)
	{
		wordLength = length;
	}
	else
	{
		std::cout << "Invalid configuration\n";
	}
}

void Wordle::LoadLetterFrequency() {
	std::ifstream lf("../Languages/" + language + ".lf");
	if (!lf.is_open())
	{
		return;
	}

	std::string letter;
	std::string frequency;
	while (std::getline(lf, letter)) {
		std::getline(lf, frequency);
		letterFrequency.insert({ letter[0], std::stoi(frequency) });
	}
	lf.close();
}

void Wordle::LoadDictionary() {
	std::ifstream dictionary("../Languages/" + language + ".dic");
	if (!dictionary.is_open())
	{
		return;
	}

	std::string word;
	std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> convert;
	while (std::getline(dictionary, word)) {
		std::u16string word16 = convert.from_bytes(word);
		if (word16.size() == wordLength) {
			word = UnicodeToAscii(word16);
			int priority = CalculatePriority(word);
			possibleWords.push_back({word, priority });
			possibleWordsSorted.push({word, priority });
		}
	}
	dictionary.close();

	std::cout << "Dictionary loaded\n";
}

void Wordle::UpdateDictionary(const std::set<char> &bannedCharacters) {
	std::vector<Word> auxVector;
	// Remove words with banned characters (gray characters)
	for (auto w : possibleWords) {
		bool possible = true;
		for (auto c : bannedCharacters) {
			if (w.word.find(c) != std::string::npos) {
				possible = false;
				break;
			}
		}
		if (possible)
			auxVector.push_back(w);
	}
	possibleWords = auxVector;

	// Only keep words with correct characters (green characters)
	auxVector.clear();
	for (auto w : possibleWords) {
		bool possible = true;
		for (auto c : correctCharacters) {
			if (w.word[c.pos] != c.c) {
				possible = false;
				break;
			}
		}
		if (possible)
			auxVector.push_back(w);
	}
	possibleWords = auxVector;

	// Only keep words that have wrong characters AND not in the right position (yellow characters)
	auxVector.clear();
	for (auto w : possibleWords) {
		bool possible = true;
		for (auto c : wrongCharacters) {
			if (w.word[c.pos] == c.c || w.word.find(c.c) == std::string::npos) {
				possible = false;
				break;
			}
		}
		if (possible)
			auxVector.push_back(w);
	}
	possibleWords = auxVector;

	// Sort by priority
	std::priority_queue<Word> auxQueue;
	for (auto w : possibleWords) {
		auxQueue.push(w);
	}
	possibleWordsSorted = auxQueue;
}

bool Wordle::IsAsciiWord(const std::string &str) {
	for (auto c : str) {
		if (c < 0) {
			return false;
		}
	}
	return true;
}

std::string Wordle::UnicodeToAscii(const std::u16string& str) {
	std::string aux = "";
	for (auto c : str) {
		switch (c) {
		case u'á':
			aux += 'a';
			break;
		case u'à':
			aux += 'a';
			break;
		case u'ä':
			aux += 'a';
			break;
		case u'é':
			aux += 'e';
			break;
		case u'è':
			aux += 'e';
			break;
		case u'ë':
			aux += 'e';
			break;
		case u'í':
			aux += 'i';
			break;
		case u'ì':
			aux += 'i';
			break;
		case u'ï':
			aux += 'i';
			break;
		case u'ó':
			aux += 'o';
			break;
		case u'ò':
			aux += 'o';
			break;
		case u'ö':
			aux += 'o';
			break;
		case u'ù':
			aux += 'u';
			break;
		case u'ú':
			aux += 'u';
			break;
		case u'ü':
			aux += 'u';
			break;
		default:
			aux += c;
			break;
		}
	}
	return aux;
}

int Wordle::CalculatePriority(const std::string &str) {
	std::set<char> usedLetters;
	int sum = 0;
	for (auto c : str) {
		if (usedLetters.find(c) == usedLetters.end()) {
			usedLetters.insert(c);
			sum += letterFrequency[c];
		}
	}
	return sum;
}

std::string Wordle::GetBestWords() {
	std::priority_queue<Word> aux = possibleWordsSorted;
	std::cout << "Best words: ";
	for (int i = 0; i < 5; i++) {
		std::cout << aux.top().word << " ";
		aux.pop();
		if (aux.empty()) {
			break;
		}
	}
	std::cout << "(" << possibleWordsSorted.size() << ")" << std::endl;

	return possibleWordsSorted.top().word;
}

void Wordle::RegisterWord(const std::string &word, const std::string& output) {
	std::set<char> bannedCharacters;
	for (int i = 0; i < output.size(); i++) {
		if (output[i] == '0') {
			bannedCharacters.insert(word[i]);
		}
		else if (output[i] == '1') {
			wrongCharacters.insert({ word[i], i });
		}
		else if (output[i] == '2') {
			correctCharacters.insert({ word[i], i });
		}
	}

	// Check if banned characters are really banned (repetitions)
	std::vector<char> notBanned;
	for (auto banned : bannedCharacters) {
		for (auto correct : correctCharacters) {
			if (banned == correct.c) {
				notBanned.push_back(banned);
				break;
			}
		}
		for (auto wrong : wrongCharacters) {
			if (banned == wrong.c) {
				notBanned.push_back(banned);
				break;
			}
		}
	}
	for (auto c : notBanned) {
		bannedCharacters.erase(c);
	}
	UpdateDictionary(bannedCharacters);
}