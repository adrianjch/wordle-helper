#pragma once
#include <memory>

#include "imgui.h"
#include "Wordle.h"

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
    bool showDemoWindow;
    ImVec4 clearColor;

    // Phase 1
    std::shared_ptr<Wordle> wordle;
    std::vector<std::string> availableLanguages;
    bool started { false };
    // Phase 2
    std::vector<Word> availableWords;
    int totalWords;
    std::string currentWord;
};
#pragma once
