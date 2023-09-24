#include "WordleAttempt.h"

WordleAttempt::WordleAttempt(int length, int id)
	: wordLength{ length }, id{ id }
{
	colors[0] = ImVec4(0.3f, 0.3f, 0.3f, 0.5f);
	colors[1] = ImVec4(1, 1, 0, 0.5f);
	colors[2] = ImVec4(0, 1, 0, 0.5f);

	boxes.reserve(length);
	for (int i = 0; i < length; i++)
	{
		boxes.emplace_back('_');
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
	boxes[word.size()].c = '_';
}

void WordleAttempt::DrawAttempt()
{
	for (int i = 0; i < boxes.size(); i++)
	{
		auto color = colors[boxes[i].type];
		ImGui::PushStyleColor(ImGuiCol_Button, color);
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, color);
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, color);
		std::string label;
		label += boxes[i].c;
		label += "###attempt" + std::to_string(id) + "_button" + std::to_string(i);
		if (ImGui::Button(label.c_str(), ImVec2(30,30)))
		{
			boxes[i].type = (boxes[i].type + 1) % 3;
		}
		ImGui::PopStyleColor(3);

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
