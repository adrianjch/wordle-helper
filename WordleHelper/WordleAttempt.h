#pragma once
#include <string>
#include <vector>

#include "imgui.h"

struct Box
{
    char c;
    int type;

    Box(char c) : c{ c }, type{ 0 }
    {

    }
};

class WordleAttempt
{
public:
    WordleAttempt(int length, int id);

    void AddCharacter(char c);
    void RemoveCharacter();
    void DrawAttempt();

    std::string GetWord();
    std::vector<int> GetResult();

private:
    int wordLength;
    int id;
	std::vector<Box> boxes;
    std::string word;
    ImVec4 colors[3];
};