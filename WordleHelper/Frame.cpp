#include "Frame.h"
#include <filesystem>
#include <iostream>

#include "WordleGame.h"
#include "WordleSolver.h"

Frame::Frame(ImGuiIO* io)
    : io{ io }
{
    showDemoWindow = false;
    clearColor = { 0.45f, 0.55f, 0.60f, 1.00f };
    
    for (const auto& entry : std::filesystem::directory_iterator("../Languages"))
    {
        if (entry.path().extension() == ".lf")
        {
            availableLanguages.push_back(entry.path().stem().string());
        }
    }
}

void Frame::Update()
{
    ImGui::NewFrame();
	ManageInputs();

    if (showDemoWindow)
        ImGui::ShowDemoWindow(&showDemoWindow);

    ImGuiWindowFlags flags = ImGuiWindowFlags_NoCollapse;
    // Main panel
    ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(160, 150));
    {
	    ImGui::Begin("Main pannel", nullptr, flags);
	    ImGui::Checkbox("Demo Window", &showDemoWindow);
        if (!started)
        {
			ShowSettings();
        }
		else
		{
			ShowSimulation();
		}
    }
    ImGui::End();
    ImGui::PopStyleVar();

    ImGui::Render();
}

void Frame::ManageInputs()
{
	if (!started)
	{
		return;
	}

	for (int i = 0; i < io->InputQueueCharacters.Size; i++)
	{
		ImWchar c = io->InputQueueCharacters[i];
		if (std::isalpha(c))
		{
			game->AddCharacter(std::toupper(c));
		}
		else if (c == 8)
		{
			game->RemoveCharacter();
		}
	}
}

void Frame::ShowSettings()
{
	ImGui::BeginChild("settings_child", ImVec2(220, 200), false);
	// Text
	ImGui::Text("Settings");
	// Slider
	static int characters = 5;
	ImGui::SliderInt("##characters_slider", &characters, 2, 15, "%d characters", ImGuiSliderFlags_NoInput);
	// Dropdown
	static int languageId = -1;
	std::string preview = (languageId == -1) ? "Select language" : availableLanguages[languageId];
	if (ImGui::BeginCombo("##languages_combo", preview.c_str()))
	{
		for (int i = 0; i < availableLanguages.size(); i++)
		{
			bool selected = (languageId == i);
			if (ImGui::Selectable(availableLanguages[i].c_str(), selected))
				languageId = i;
			// Set focus
			if (selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}
	// Button
	if (languageId != -1)
	{
		if (ImGui::Button("Start##languages_button"))
		{
			solver = std::make_shared<WordleSolver>(availableLanguages[languageId], characters);
			game = std::make_shared<WordleGame>(characters);
			availableWords = solver->GetBestWords(200);
			totalWords = solver->GetTotalWords();
			game->AddAttempt(true);
			started = true;
		}
	}
	ImGui::EndChild();
}

void Frame::ShowSimulation()
{
	ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(160, 400));
	// First window
	game->DrawBoard();
	if (ImGui::Button("Submit"))
	{
		solver->RegisterWord(game->GetLastWord(), game->GetLastResult());
		// TODO this is repeated, move to function
		availableWords = solver->GetBestWords(200);
		totalWords = solver->GetTotalWords();
		game->AddAttempt(true);
	}
	// Second window
	std::string title = "Words list (" + std::to_string(totalWords) + " words)" + "###words";
	ImGui::Begin(title.c_str(), nullptr, ImGuiWindowFlags_NoCollapse);
	if (ImGui::BeginTable("table1", 2, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg))
	{
		ImGui::TableSetupColumn("Word", ImGuiTableColumnFlags_WidthStretch, 0.7f);
		ImGui::TableSetupColumn("Score", ImGuiTableColumnFlags_WidthStretch, 0.3f);
		ImGui::TableHeadersRow();

		for (auto word : availableWords)
		{
			ImGui::TableNextRow();
			ImGui::TableSetColumnIndex(0);
			ImGui::Text("%s", word.word.c_str());
			ImGui::TableSetColumnIndex(1);
			ImGui::Text("%d", word.score);
		}
		ImGui::EndTable();
	}
	if (availableWords.empty())
	{
		ImGui::TextWrapped("No word was found with those parameters");
	}
	ImGui::End();
	ImGui::PopStyleVar();
}
