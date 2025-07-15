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

#include "raymath.h" // For math utilities

void RenderChunk(const chunk_new &chunk,Camera camera) {
    constexpr float maxRenderDistance = 30.0f;
    Vector3 camPos = camera.position;
    for (int x = 0; x < chunk.size.x; x++) {
        for (int y = 0; y < chunk.size.y; y++) {
            for (int z = 0; z < chunk.size.z; z++) {
                Vector3 pos = {static_cast<float>(x), static_cast<float>(y), static_cast<float>(z)};
                float dist = Vector3Distance(camPos, pos);
                if (dist > maxRenderDistance) continue;

                Color color;
                color.r = static_cast<unsigned char>(chunk.chunkData[x][y][z].color[0] * 255);
                color.g = static_cast<unsigned char>(chunk.chunkData[x][y][z].color[1] * 255);
                color.b = static_cast<unsigned char>(chunk.chunkData[x][y][z].color[2] * 255);
                color.a = static_cast<unsigned char>(chunk.chunkData[x][y][z].alpha );
                //logger::info("X:%f Y:%f Z:%f",pos.x, pos.y, pos.z);
                //DrawCube(pos, 1.0f, 1.0f, 1.0f,MAROON);

                if (color.a != 0) {
                    DrawCube(pos,1.0f, 1.0f, 1.0f,color);
                    DrawCubeWires(pos, 1.0f, 1.0f, 1.0f, BLACK);
                }
            }
        }
    }
}
void render_chunk(const chunk_t chunk, const Vector3_t size, Camera camera) {
    constexpr float maxRenderDistance = 30.0f;
    Vector3 camPos = camera.position;
    //std::lock_guard<std::mutex> lock(renderMutex);
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
                else if (block == 10) color = WHITE;

                DrawCube(pos, 1.0f, 1.0f, 1.0f, color);

                DrawCubeWires(pos, 1.0f, 1.0f, 1.0f, BLACK);
            }

        }
    }
}