#pragma once
#include <string>
#include <queue>
#include <set>
#include <map>

struct Word {
	std::string word;
	int priority;

	bool operator> (const Word &a) const{
		return priority > a.priority;
	}
	bool operator< (const Word& a) const {
		return priority < a.priority;
	}
};

struct Character {
	char c;
	int pos;

	bool operator< (const Character& rhs) const {
		return pos*100 + c < rhs.pos*100 + rhs.c;
	}
};

class Wordle {
private:
	std::string language;
	int wordLength;

	std::map<char, int> letterFrequency;

	std::set<Character> correctCharacters;
	std::set<Character> wrongCharacters;

	std::vector<Word> possibleWords;
	std::priority_queue<Word> possibleWordsSorted;

public:
	Wordle();
	std::string GetBestWords();
	void RegisterWord(const std::string &, const std::string &);

private:
	void ReadConfig();
	void LoadLetterFrequency();
	void SaveDictionary();
	void UpdateDictionary(const std::set<char> &);

	bool IsAsciiWord(const std::string &);
	std::string UnicodeToAscii(const std::u16string &);
	int CalculatePriority(const std::string &);
};