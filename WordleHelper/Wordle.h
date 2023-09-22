#pragma once
#include <string>
#include <queue>
#include <set>
#include <map>

struct Word
{
	std::string word;
	int score;

	bool operator> (const Word &a) const
	{
		return score > a.score;
	}
	bool operator< (const Word& a) const
	{
		return score < a.score;
	}
};

struct Character
{
	char c;
	int pos;

	bool operator< (const Character& rhs) const
	{
		return pos*100 + c < rhs.pos*100 + rhs.c;
	}
};

class Wordle
{
public:
	Wordle(const std::string& lang, int length);
	
	std::vector<Word> GetBestWords(int size);
	int GetTotalWords();
	void RegisterWord(const std::string &, const std::string &);

private:
	void LoadLetterFrequency();
	void LoadDictionary();
	void UpdateDictionary(const std::set<char> &);

	bool IsAsciiWord(const std::string &);
	std::string UnicodeToAscii(const std::u16string&);
	int CalculatePriority(const std::string &);

private:
	std::string language;
	int wordLength;

	std::map<char, int> letterFrequency;

	std::set<Character> correctCharacters;// green
	std::set<Character> wrongCharacters;// yellow

	std::vector<Word> possibleWords;
	std::priority_queue<Word> possibleWordsSorted;
};