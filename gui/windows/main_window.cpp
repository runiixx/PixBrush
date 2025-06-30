//
// Created by vik on 6/30/25.
//
#include "../windows.h"
#include <spdlog/spdlog.h>

#include "../../input/keyboard_input.h"

void RenderMainWindow(Vector3 chunkSize) {
    Vector3_t chunkSize_t = floatToIntVec3(chunkSize);
    chunk_t chunk = init_chunk(&chunkSize_t);
    //configure the window
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SetConfigFlags(FLAG_VSYNC_HINT);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SetConfigFlags(FLAG_MSAA_4X_HINT);

    SetWindowState(FLAG_WINDOW_ALWAYS_RUN);

    constexpr int screenWidth = 1000;
    constexpr int screenHeight = 1000;

    InitWindow(screenWidth, screenHeight, "PixBrush");

    Camera3D camera = InitCamera();
    //camera.position = camera_position;
    //camera.target = camera_position;
    //Vector3 cubePosition = {0.0f, 0.0f, 0.0f};

    SetTargetFPS(120);

    Vector3 cubeCursor = {chunkSize.x/2, 1.0f, chunkSize.y/2};
    bool isThirdMode = true;
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode3D(camera);
        if (IsKeyPressed(KEY_X)) isThirdMode = !isThirdMode;
        if (isThirdMode) {
            UpdateCamera(&camera, CAMERA_FREE);
            DisableCursor();
            spdlog::info("{} {} {}",camera.target.x, camera.target.y, camera.target.z);

        }
        else {
            EnableCursor();
            update_cube_cursor(&chunk, &chunkSize_t, &cubeCursor, &camera);
        }
        render_chunk(chunk, chunkSize_t, camera);
        DrawCubeWires(cubeCursor, 1.0f, 1.0f, 1.0f, MAROON);
        EndMode3D();
        EndDrawing();

    }

    CloseWindow();
}
