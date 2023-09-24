#include "WordleGame.h"

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
		auto label = "attempt" + std::to_string(i) + "_child";
		ImGui::BeginChild(label.c_str(), ImVec2(0, 30+3));
		// Radio button (selection)
		label = "###attempt_radioButton" + std::to_string(i);
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
		label = "Remove attempt popup##" + std::to_string(i);
		if (ImGui::BeginPopupContextItem(label.c_str()))
		{
			ImGui::Text("Are you sure you want to remove this item?");
			if (ImGui::Button("Yes##removeAttempt_button"))
			{
				removedId = i;
				ImGui::CloseCurrentPopup();
			}
			ImGui::SameLine();
			if (ImGui::Button("No##removeAttempt_button"))
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
