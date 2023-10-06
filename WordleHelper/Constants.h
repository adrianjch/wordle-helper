#pragma once
#include "imgui.h"

// Attempts
const ImVec4 ATTEMPT_GRAY   = { 0.3f, 0.3f, 0.3f, 0.5f };
const ImVec4 ATTEMPT_YELLOW = { 1.0f, 1.0f, 0.0f, 0.5f };
const ImVec4 ATTEMPT_GREEN  = { 0.0f, 1.0f, 0.0f, 0.5f };

const char ATTEMPT_PLACEHOLDER_CHARACTER = '_';
const ImVec2 ATTEMPT_BUTTON_SIZE = { 30, 30 };
const ImVec2 ATTEMPT_CHILD_SIZE = { 0, ATTEMPT_BUTTON_SIZE.y+3 };

const std::string ATTEMPT_LABEL_ID = "{attemptId}";
const std::string ATTEMPT_CHARACTER_LABEL_ID = "{character}";
const std::string ATTEMPT_BUTTON_LABEL_ID = "{buttonId}";
const std::string ATTEMPT_BUTTON_LABEL = ATTEMPT_CHARACTER_LABEL_ID+"###attempt"+ATTEMPT_LABEL_ID+"_button"+ATTEMPT_BUTTON_LABEL_ID;//c###attempt0_button2
const std::string ATTEMPT_CHILD_LABEL = "attempt"+ATTEMPT_LABEL_ID+"_child";//attempt0_child
const std::string ATTEMPT_RADIO_LABEL = "###attempt"+ATTEMPT_LABEL_ID+"_radioButton";//###attempt0_radioButton
const std::string ATTEMPT_POPUP_LABEL = "Remove attempt popup##"+ATTEMPT_LABEL_ID;//Remove attempt popup##0
inline const char* ATTEMPT_POPUP_TEXT = "Are you sure you want to remove this item?";
inline const char* ATTEMPT_POPUP_LABEL_YES = "Yes##removeAttempt_button";
inline const char* ATTEMPT_POPUP_LABEL_NO = "No##removeAttempt_button";

// PATHS
const std::string LANGUAGES_PATH = "../Languages/";
const std::string LETTER_FREQUENCY_FILE_EXTENSION = ".lf";
const std::string DICTIONARY_FILE_EXTENSION = ".dic";

// GENERIC
const ImVec2 WINDOW_SIZE = { 1280, 800 };
const ImVec2 WINDOW_POS = { 100, 100 };//Top-left corner
const ImVec4 BACKGROUND_COLOR = { 0.4f, 0.5f, 0.6f, 1.0f };

// MAIN PANEL
const ImVec2 MAIN_PANEL_MIN_SIZE = { 170, 150 };
const ImVec2 SETTINGS_CHILD_SIZE = { 220, 100 };
const int DEFAULT_WORD_LENGTH = 5;
const int MIN_WORD_LENGTH = 2;
const int MAX_WORD_LENGTH = 15;

inline const char* MAIN_PANEL_NAME = "Main panel";
inline const char* SETTINGS_CHILD_LABEL = "settings_child";
inline const char* SETTINGS_TITLE = "Settings";
inline const char* WORD_LENGTH_SLIDER_LABEL = "##wordLength_slider";
inline const char* LANGUAGES_COMBO_LABEL = "##languages_combo";
inline const char* LANGUAGES_COMBO_PREVIEW = "Select language";
inline const char* START_BUTTON_LABEL = "Start##languages_button";

// SECONDARY PANEL
const ImVec2 SECONDARY_PANEL_MIN_SIZE = { 160, 400 };
const int MAX_WORDS = 200;
const float TABLE_WORD_RELATIVE_WIDTH = 0.7f;
const float TABLE_SCORE_RELATIVE_WIDTH = 1 - TABLE_WORD_RELATIVE_WIDTH;

const std::string TOTAL_WORDS_LABEL_ID = "{totalWords}";
const std::string SECONDARY_PANEL_NAME = "Words list ("+TOTAL_WORDS_LABEL_ID+" words)###words";//Words list (123456 words)###words
inline const char* WORDS_TABLE_LABEL = "availableWords_table";
inline const char* NO_AVAILABLE_WORDS_TEXT = "No word was found with those parameters";