#include "WordleAttempt.h"
#include "Constants.h"
#include "Utilities.h"

WordleAttempt::WordleAttempt(int length, int id)
	: wordLength{ length }, id{ id }
{
	colors[0] = ATTEMPT_GRAY;
	colors[1] = ATTEMPT_YELLOW;
	colors[2] = ATTEMPT_GREEN;

	boxes.reserve(length);
	for (int i = 0; i < length; i++)
	{
		boxes.emplace_back(ATTEMPT_PLACEHOLDER_CHARACTER);
	}
}

void WordleAttempt::AddCharacter(char c)
{
	if (word.size() >= wordLength)
	{
		return;
	}

	word += c;
	boxes[word.size() - 1].c = c;
}

void WordleAttempt::RemoveCharacter()
{
	if (word.empty())
	{
		return;
	}

	word.pop_back();
	boxes[word.size()].c = ATTEMPT_PLACEHOLDER_CHARACTER;
}

void WordleAttempt::DrawAttempt()
{
	for (int i = 0; i < boxes.size(); i++)
	{
		auto color = colors[boxes[i].type];
		ImGui::PushStyleColor(ImGuiCol_Button, color);
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, color);
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, color);
		
		auto label = ReplaceString(ATTEMPT_BUTTON_LABEL, ATTEMPT_CHARACTER_LABEL_ID, std::string(1, boxes[i].c));
		label = ReplaceString(label, ATTEMPT_LABEL_ID, std::to_string(id));
		label = ReplaceString(label, ATTEMPT_BUTTON_LABEL_ID, std::to_string(i));
		if (ImGui::Button(label.c_str(), ATTEMPT_BUTTON_SIZE))
		{
			boxes[i].type = (boxes[i].type + 1) % 3;
		}
		ImGui::PopStyleColor(3);//ImGuiCol_Button + ImGuiCol_ButtonHovered + ImGuiCol_ButtonActive

		if (i < boxes.size()-1)
		{
			ImGui::SameLine();
		}
	}
}

std::string WordleAttempt::GetWord()
{
	return word;
}

std::vector<int> WordleAttempt::GetResult()
{
	std::vector<int> ret;
	for (auto box : boxes)
	{
		ret.push_back(box.type);
	}
	return ret;
}
