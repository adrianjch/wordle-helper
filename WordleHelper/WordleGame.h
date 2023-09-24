#pragma once
#include <string>
#include <vector>

#include "WordleAttempt.h"
#include "WordleSolver.h"

class WordleGame
{
public:
    WordleGame(int length);
    
    void AddCharacter(char c);
    void RemoveCharacter();
    void AddAttempt(bool autoSelect);
    void DrawBoard();

    std::string GetLastWord();
    std::vector<int> GetLastResult();

private:
    std::vector<Word> availableWords;
    int totalWords;
    int wordLength;
    std::vector<WordleAttempt> attempts;
    static inline int selectedAttempt = -1;
};
