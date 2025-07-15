//
// Created by vik on 6/30/25.
//
#include <imgui.h>

#include "../windows.h"
#include "../../input/keyboard_input.h"
//TODO add panel with shortcuts
//TODO add save to file
void RenderMainWindow(Vector3 chunkSize) {
    Vector3_t chunkSize_t = floatToIntVec3(chunkSize);
    //chunk_t chunk = init_chunk(&chunkSize_t);
    chunk_new chunk = InitChunk(chunkSize_t);
    //configure the window
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SetConfigFlags(FLAG_VSYNC_HINT);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    SetConfigFlags(FLAG_WINDOW_MAXIMIZED);
    SetWindowState(FLAG_WINDOW_ALWAYS_RUN);

    const int screenWidth = GetMonitorWidth(0);
    const int screenHeight = GetMonitorHeight(0);
    //spdlog::info("Width: {} Height: {}", screenWidth, screenHeight);
    InitWindow(screenWidth, screenHeight, "PixBrush");
    rlImGuiSetup(false);
    Camera3D camera = InitCamera();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |=ImGuiConfigFlags_NavEnableKeyboard;
    //camera.position = camera_position;
    //camera.target = camera_position;
    //Vector3 cubePosition = {0.0f, 0.0f, 0.0f};

    SetTargetFPS(120);

    Vector3 cubeCursor = {chunkSize.x/2, 1.0f, chunkSize.y/2};
    bool isThirdMode = true;
    bool isRectangleBrushFirstPoint = false;
    Vector3 rectangleBrushFirstPoint = {-1.0f, -1.0f, -1.0f};

    bool isSphereBrushFirstPoint = false;
    Vector3 sphereBrushFirstPoint = {-1.0f, -1.0f, -1.0f};

    float color[3] = {0.0f , 0.0f , 0.0f};
    bool cameraActive = true;
    while (!WindowShouldClose()) {

        bool blockRaylibInput = io.WantCaptureMouse || io.WantCaptureKeyboard;
        if (!blockRaylibInput && IsKeyPressed(KEY_TAB)) {
            cameraActive = !cameraActive;
            if (cameraActive) DisableCursor();
            else EnableCursor();
        }
        if (cameraActive && !blockRaylibInput) UpdateCamera(&camera, CAMERA_FREE);
        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode3D(camera);
        RenderChunk(chunk, camera);
        DrawCubeWires(cubeCursor, 1.0f, 1.0f, 1.0f, MAROON);
        EndMode3D();

        if (IsKeyPressed(KEY_X)) isThirdMode = !isThirdMode;

        if (isThirdMode) {
            UpdateCamera(&camera, CAMERA_FREE);
            DisableCursor();
        } else {
            EnableCursor();
            if (!ImGui::GetIO().WantCaptureMouse) {
                UpdateCubeCursor(chunk, cubeCursor, camera);
            }
        }

        // Always render ImGui (but it will only accept input when in cursor mode)
        rlImGuiBegin();
        ImGuiIO& io = ImGui::GetIO();
        io.MousePos = ImVec2(GetMouseX(), GetMouseY());
        io.MouseDown[0] = IsMouseButtonDown(MOUSE_LEFT_BUTTON);
        // Repeat for other inputs...


        ImGui::SetNextWindowSize(ImVec2(500, 500), ImGuiCond_Once);
        if (ImGui::Begin("Color Picker")) {
            ImGui::ColorPicker3("Color", color);
            if (ImGui::Button("Test Button")) {
                logger::info("Button clicked! Color: %f,%f,%f", color[0], color[1], color[2]);
            }
            ImGui::End();
        }

        rlImGuiEnd();

        EndDrawing();
    }
    rlImGuiShutdown();
    CloseWindow();
}
