//
// Created by vik on 7/1/25.
//
#include "keyboard_input.h"
#include <cmath>
//Rectangle brush
//TODO: rewrite this function for the new block struct
void RenderRectangleBrush(Vector3 firstPoint, Vector3 cubeCursor) {
    for (int x = std::min(firstPoint.x, cubeCursor.x);x <= std::max(firstPoint.x, cubeCursor.x); x++) {
        for (int y = std::min(firstPoint.y, cubeCursor.y);y <= std::max(firstPoint.y, cubeCursor.y); y++) {
            for (int z = std::min(firstPoint.z, cubeCursor.z);z <= std::max(firstPoint.z, cubeCursor.z); z++) {
                Vector3 cubePos = {x, y, z};
                DrawCube(cubePos, 1.0f, 1.0f, 1.0f, Fade(MAROON, 0.3f));
            }
        }
    }
}
//TODO: rewrite this function for the new block struct
void firstPointRectangle(chunk_t chunk, Vector3 cubeCursor,Vector3 &firstPoint, bool &isRectangleBrushFirstPoint) {
    if (IsKeyDown(KEY_LEFT_ALT) && IsKeyPressed(KEY_R)) {
        firstPoint = cubeCursor;
        isRectangleBrushFirstPoint = true;
    }
    if (firstPoint.x != -1.0f && firstPoint.z != -1.0f && firstPoint.y != -1.0f ) {
        RenderRectangleBrush(firstPoint, cubeCursor);
    }
    if (IsKeyDown(KEY_F)) {
        if (isRectangleBrushFirstPoint) {
            for (int x = std::min(firstPoint.x, cubeCursor.x);x <= std::max(firstPoint.x, cubeCursor.x); x++) {
                for (int y = std::min(firstPoint.y, cubeCursor.y);y <= std::max(firstPoint.y, cubeCursor.y); y++) {
                    for (int z = std::min(firstPoint.z, cubeCursor.z);z <= std::max(firstPoint.z, cubeCursor.z); z++) {
                        chunk[x][y][z] = 2;
                    }
                }
            }
        }
        isRectangleBrushFirstPoint = false;
        firstPoint = {-1.0f, -1.0f, -1.0f};
    }
}


//Sphere brush
float CalculateRadius(Vector3 center, Vector3 cubeCursor) {
    double result = sqrt(pow(center.x-cubeCursor.x,2) + pow(center.z-cubeCursor.z,2) + pow(center.y-cubeCursor.y,2));
    return static_cast<float>(result);
}
//TODO: rewrite this function for the new block struct
void RenderSphereBrush(Vector3 chunkSize,Vector3 center, Vector3 cubeCursor) {
    Vector3_t center_t = floatToIntVec3(center);
    float radius = CalculateRadius(center, cubeCursor);
    for (int x = center_t.x - static_cast<int>(ceil(radius)); x <= std::min(center_t.x + static_cast<int>(ceil(radius)), static_cast<int>(chunkSize.x)); x++) {
        for (int y = center_t.y - static_cast<int>(ceil(radius));y <= std::min(center_t.y + static_cast<int>(ceil(radius)), static_cast<int>(chunkSize.y)); y++) {
            for (int z = center_t.z - static_cast<int>(ceil(radius));z <= std::min(center_t.z + static_cast<int>(ceil(radius)), static_cast<int>(chunkSize.z)); z++) {
                Vector3_t point = {x,y,z};
                if (CalculateRadius(intToFloatVec3(point), center) < radius) {
                    DrawCube(intToFloatVec3(point), 1.0f, 1.0f, 1.0f, Fade(MAROON, 0.3f));
                }
            }
        }
    }
}
//TODO: rewrite this function for the new block struct
void firstPointSphere(chunk_t chunk,Vector3 chunkSize, Vector3 cubeCursor, Vector3 &firstPoint, bool &isSphereBrushFirstPoint) {
    if (IsKeyDown(KEY_LEFT_ALT) && IsKeyPressed(KEY_S)) {
        firstPoint = cubeCursor;
        isSphereBrushFirstPoint = true;
    }
    if (firstPoint.x != -1.0f && firstPoint.z != -1.0f && firstPoint.y != -1.0f) {
        RenderSphereBrush(chunkSize,firstPoint, cubeCursor);
    }
    if (IsKeyPressed(KEY_F)) {
        if (isSphereBrushFirstPoint) {
            Vector3_t center_t = floatToIntVec3(firstPoint);
            float radius = CalculateRadius(firstPoint, cubeCursor);
            for (int x = center_t.x - static_cast<int>(ceil(radius)); x <= std::min(center_t.x + static_cast<int>(ceil(radius)), static_cast<int>(chunkSize.x)); x++) {
                for (int y = center_t.y - static_cast<int>(ceil(radius));y <= std::min(center_t.y + static_cast<int>(ceil(radius)), static_cast<int>(chunkSize.y)); y++) {
                    for (int z = center_t.z - static_cast<int>(ceil(radius));z <= std::min(center_t.z + static_cast<int>(ceil(radius)), static_cast<int>(chunkSize.z)); z++) {
                        Vector3_t point = {x,y,z};
                        if (CalculateRadius(intToFloatVec3(point), firstPoint) < radius) {
                            chunk[x][y][z] = 2;
                        }
                    }
                }
            }
        }
            isSphereBrushFirstPoint = false;
            firstPoint = {-1.0f, -1.0f, -1.0f};

    }
}
//TODO: add proper eraser brush