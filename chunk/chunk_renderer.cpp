//
// Created by vik on 6/30/25.
//
#include "chunk.h"
Camera3D InitCamera() {
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f }; // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type
    return camera;
}
//TODO: rewrite this function for the new block struct
void render_chunk(const chunk_t chunk, const Vector3_t size, Camera camera) {
    constexpr float maxRenderDistance = 30.0f;
    Vector3 camPos = camera.position;

    for (int x = 0; x < size.x; x++) {
        for (int y = 0; y < size.y; y++) {
            for (int z = 0; z < size.z; z++) {
                int block = chunk[x][y][z];
                if (block == 0 || block == 1 || block == 3) continue;

                Vector3 pos = { (float)x, (float)y, (float)z };

                float dist = Vector3Distance(camPos, pos);
                if (dist > maxRenderDistance) continue;  // Cull far cubes

                Color color = BLACK;
                if (block == 2) color = MAROON;
                else if (block == BLOCK_CANVAS) color = WHITE;

                DrawCube(pos, 1.0f, 1.0f, 1.0f, color);

                DrawCubeWires(pos, 1.0f, 1.0f, 1.0f, BLACK);
            }

        }
    }
}
