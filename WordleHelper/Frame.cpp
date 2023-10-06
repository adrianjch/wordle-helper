#include "Frame.h"
#include <filesystem>
#include <iostream>

#include "Constants.h"
#include "Utilities.h"
#include "WordleGame.h"
#include "WordleSolver.h"

Frame::Frame(ImGuiIO* io)
    : io{ io }
{
    clearColor = BACKGROUND_COLOR;
    
    for (const auto& entry : std::filesystem::directory_iterator(LANGUAGES_PATH))
    {
        if (entry.path().extension() == LETTER_FREQUENCY_FILE_EXTENSION)
        {
            availableLanguages.push_back(entry.path().stem().string());
        }
    }
}

void Frame::Update()
{
    ImGui::NewFrame();
	ManageInputs();

    ImGuiWindowFlags flags = ImGuiWindowFlags_NoCollapse;
    // Main panel
    ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, MAIN_PANEL_MIN_SIZE);
    {
	    ImGui::Begin(MAIN_PANEL_NAME, nullptr, flags);
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
	ImGui::BeginChild(SETTINGS_CHILD_LABEL, SETTINGS_CHILD_SIZE, false);
	// Text
	ImGui::Text(SETTINGS_TITLE);
	// Slider
	static int characters = DEFAULT_WORD_LENGTH;
	ImGui::SliderInt(WORD_LENGTH_SLIDER_LABEL, &characters, MIN_WORD_LENGTH, MAX_WORD_LENGTH, "%d characters", ImGuiSliderFlags_NoInput);
	// Dropdown
	static int languageId = -1;
	std::string preview = (languageId == -1) ? LANGUAGES_COMBO_PREVIEW : availableLanguages[languageId];
	if (ImGui::BeginCombo(LANGUAGES_COMBO_LABEL, preview.c_str()))
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
		if (ImGui::Button(START_BUTTON_LABEL))
		{
			solver = std::make_shared<WordleSolver>(availableLanguages[languageId], characters);
			game = std::make_shared<WordleGame>(characters);
			availableWords = solver->GetBestWords(MAX_WORDS);
			totalWords = solver->GetTotalWords();
			game->AddAttempt(true);
			started = true;
		}
	}
	ImGui::EndChild();
}

void Frame::ShowSimulation()
{
	// First window
	game->DrawBoard();
	if (ImGui::Button("Submit"))
	{
		solver->RegisterWord(game->GetLastWord(), game->GetLastResult());
		// TODO this is repeated, move to function
		availableWords = solver->GetBestWords(MAX_WORDS);
		totalWords = solver->GetTotalWords();
		game->AddAttempt(true);
	}
	// Second window
	ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, SECONDARY_PANEL_MIN_SIZE);
	auto title = ReplaceString(SECONDARY_PANEL_NAME, TOTAL_WORDS_LABEL_ID, std::to_string(totalWords));
	ImGui::Begin(title.c_str(), nullptr, ImGuiWindowFlags_NoCollapse);
	if (ImGui::BeginTable(WORDS_TABLE_LABEL, 2, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg))
	{
		ImGui::TableSetupColumn("Word", ImGuiTableColumnFlags_WidthStretch, TABLE_WORD_RELATIVE_WIDTH);
		ImGui::TableSetupColumn("Score", ImGuiTableColumnFlags_WidthStretch, TABLE_SCORE_RELATIVE_WIDTH);
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
		ImGui::TextWrapped(NO_AVAILABLE_WORDS_TEXT);
	}
	ImGui::End();
	ImGui::PopStyleVar();
}
