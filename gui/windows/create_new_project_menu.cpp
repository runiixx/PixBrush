//
// Created by vik on 6/30/25.
//

#include "../windows.h"
#include "../components.h"
void StripNonDigitFromEnd(char *input) {
    size_t len = strlen(input);
    while (len > 0 && (input[len-1] < '0' || input[len-1] > '9')) {
        input[len-1] = 0;
        len--;
    }
}
Vector3 RenderCreateMenu() {
    InitWindow(800, 600, "Raylib + ImGui - Int Inputs");
    rlImGuiSetup(false);

    char widthStr[32] = "";
    char heightStr[32] = "";
    char depthStr[32] = "";

    bool done = false;
    int width = 0,height = 0,depth = 0;
    while (!done && !WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(DARKGRAY);

        rlImGuiBegin();
        ImGui::SetNextWindowSize(ImVec2(800,600), ImGuiCond_Once);
        ImGui::Begin("Create Cube", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar);
        ImGui::GetStyle().ItemSpacing = ImVec2(20.f,15.f);

        ImGui::SetCursorPosY(ImGui::GetWindowWidth()*0.20f);
        ImGui::SetCursorPosX(ImGui::GetWindowWidth()*0.37f);
        ImGui::Text("Set canva size");
        RenderTextBox("Width", widthStr, 600.f,700.f);
        RenderTextBox("Height", heightStr, 600.f,700.f);
        RenderTextBox("Depth", depthStr, 600.f,700.f);

        StripNonDigitFromEnd(widthStr);
        StripNonDigitFromEnd(heightStr);
        StripNonDigitFromEnd(depthStr);
        ImGui::SetCursorPosX((ImGui::GetWindowWidth()-100.f)*0.5f);
        if (ImGui::Button("Create", ImVec2(100, 60))) {
            width = atoi(widthStr);
            height = atoi(heightStr);
            depth = atoi(depthStr);

            printf("Width: %d, Height: %d, Depth: %d\n", width, height, depth);
            done = true;
        }

        ImGui::End();
        rlImGuiEnd();

        EndDrawing();
    }

    rlImGuiShutdown();
    CloseWindow();
    const Vector3 chunkSize = {static_cast<float>(width), static_cast<float>(height), static_cast<float>(depth)};
    return chunkSize;
}