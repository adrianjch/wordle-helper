#include "WordleGame.h"

#include "Constants.h"
#include "Utilities.h"

WordleGame::WordleGame(int length)
	: wordLength{ length }
{
}

void WordleGame::AddCharacter(char c)
{
	attempts[selectedAttempt].AddCharacter(c);
}

void WordleGame::RemoveCharacter()
{
	attempts[selectedAttempt].RemoveCharacter();
}

void WordleGame::AddAttempt(bool autoSelect)
{
	attempts.emplace_back(wordLength, attempts.size());

	if (autoSelect)
	{
		selectedAttempt = attempts.size() - 1;
	}
}

void WordleGame::DrawBoard()
{
	int removedId = -1;
	for (int i = 0; i < attempts.size(); i++)
	{
		// Creating child as a zone for the right click popup
		auto label = ReplaceString(ATTEMPT_CHILD_LABEL, ATTEMPT_LABEL_ID, std::to_string(i));
		ImGui::BeginChild(label.c_str(), ATTEMPT_CHILD_SIZE);
		// Radio button (selection)
		label = ReplaceString(ATTEMPT_RADIO_LABEL, ATTEMPT_LABEL_ID, std::to_string(i));
		ImGui::RadioButton(label.c_str(), &selectedAttempt, i);
		ImGui::SameLine();
		// Attempt
		attempts[i].DrawAttempt();
		ImGui::EndChild();
		// Right click popup (if there's only 1 element then don't)
		if (attempts.size() == 1)
		{
			break;
		}
		label = ReplaceString(ATTEMPT_POPUP_LABEL, ATTEMPT_LABEL_ID, std::to_string(i));
		if (ImGui::BeginPopupContextItem(label.c_str()))
		{
			ImGui::Text(ATTEMPT_POPUP_TEXT);
			if (ImGui::Button(ATTEMPT_POPUP_LABEL_YES))
			{
				removedId = i;
				ImGui::CloseCurrentPopup();
			}
			ImGui::SameLine();
			if (ImGui::Button(ATTEMPT_POPUP_LABEL_NO))
			{
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}
	}

	if (removedId != -1)
	{
		attempts.erase(attempts.begin()+removedId);
		// Make sure that there's always one option selected
		if (selectedAttempt >= attempts.size())
		{
			selectedAttempt = attempts.size() - 1;
		}
	}
}

std::string WordleGame::GetLastWord()
{
	return attempts.back().GetWord();
}

std::vector<int> WordleGame::GetLastResult()
{
	return attempts.back().GetResult();
}
