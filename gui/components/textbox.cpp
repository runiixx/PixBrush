//
// Created by vik on 6/30/25.
//
#include "../components.h"
void RenderTextBox(const char* label, char* input, const float itemWidth, const float offset) {
    ImGui::SetNextItemWidth(itemWidth);
    ImGui::SetCursorPosX((ImGui::GetWindowWidth() - offset)*0.5f);
    ImGui::InputText(label, input,sizeof(input));
}