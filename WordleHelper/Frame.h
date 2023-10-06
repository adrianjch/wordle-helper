#pragma once
#include <memory>
#include <string>
#include <vector>
#include "imgui.h"
#include "WordleSolver.h"

class WordleGame;
class WordleSolver;

class Frame
{
public:
    Frame(ImGuiIO* io);

    void Update();
    ImVec4 GetClearColor() const { return clearColor; }

private:
    void ManageInputs();
	void ShowSettings();
	void ShowSimulation();

private:
    ImGuiIO* io;
    ImVec4 clearColor;

    // Phase 1
    std::shared_ptr<WordleSolver> solver;
    std::shared_ptr<WordleGame> game;
    std::vector<std::string> availableLanguages;
    bool started { false };
    // Phase 2
    std::vector<Word> availableWords;
    int totalWords;
};
#pragma once
