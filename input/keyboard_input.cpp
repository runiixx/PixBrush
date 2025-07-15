//
// Created by vik on 6/30/25.
//
#include "keyboard_input.h"
void ClampCubeCursor(Vector3 *cursor, Vector3_t chunkSize)
{
    if (cursor->x < 0) cursor->x = 0;
    if (cursor->y < 0) cursor->y = 0;
    if (cursor->z < 0) cursor->z = 0;

    if (cursor->x >= (float)chunkSize.x) cursor->x = (float)chunkSize.x - 1;
    if (cursor->y >= (float)chunkSize.y) cursor->y = (float)chunkSize.y - 1;
    if (cursor->z >= (float)chunkSize.z) cursor->z = (float)chunkSize.z - 1;
}
//TODO: rewerite this abomination to be more optimise and more readable

void UpdateCubeCursor(const chunk_new &chunk, Vector3 &cubeCursor, Camera3D &camera) {
    Vector3 rawForward = Vector3Subtract(camera.target, camera.position);
    rawForward.y = 0;

    Vector3 forward = Vector3Normalize(rawForward);
    int dx = static_cast<int>(roundf(forward.x));
    int dz = static_cast<int>(roundf(forward.z));

    Vector3 right = Vector3Normalize(Vector3CrossProduct(forward, camera.up));
    int strafeX = static_cast<int>(roundf(right.x));
    int strafeZ = static_cast<int>(roundf(right.z));

    if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_O)) camera.position = cubeCursor;
    if (IsKeyPressed(KEY_F)) {
        if (cubeCursor.x >=0.0f && cubeCursor.x < static_cast<float>(chunk.size.x) &&
            cubeCursor.y >= 0.0f && cubeCursor.y < static_cast<float>(chunk.size.y) &&
            cubeCursor.z >= 0.0f && cubeCursor.z < static_cast<float>(chunk.size.z)) {
            Vector3_t pos = {static_cast<int>(cubeCursor.x), static_cast<int>(cubeCursor.y), static_cast<int>(cubeCursor.z)};
            logger::info("placing a block");
        }
    }
    if (IsKeyPressed(KEY_W)) {
        cubeCursor.x += static_cast<float>(dx);
        cubeCursor.z += static_cast<float>(dz);
    }
    if (IsKeyPressed(KEY_S)) {
        cubeCursor.x += static_cast<float>(-dx);
        cubeCursor.z += static_cast<float>(-dz);

    }
    if (IsKeyPressed(KEY_D)) {
        cubeCursor.x += static_cast<float>(strafeX);
        cubeCursor.z += static_cast<float>(strafeZ);
    }
    if (IsKeyPressed(KEY_A)) {
        cubeCursor.x += static_cast<float>(-strafeX);
        cubeCursor.z += static_cast<float>(-strafeZ);
    }
    if (IsKeyPressed(KEY_E) && cubeCursor.y < static_cast<float>(chunk.size.y)) {
        cubeCursor.y +=1.0f;
    }
    if (IsKeyPressed(KEY_Q) && cubeCursor.y > 1.0f) cubeCursor.y -= 1.0f;
    ClampCubeCursor(&cubeCursor, chunk.size);
    logger::warning("Cube cursor: %f, %f, %f", cubeCursor.x, cubeCursor.y, cubeCursor.z);
}
void update_cube_cursor(chunk_t *chunk,Vector3_t *chunkSize, Vector3 *cube_cursor, Camera3D *camera) {
    Vector3 rawForward = Vector3Subtract(camera->target, camera->position);
    rawForward.y = 0;  // Zero out Y component to prevent vertical movement
    Vector3 forward = Vector3Normalize(rawForward);
    int dx = (int)roundf(forward.x);
    int dz = (int)roundf(forward.z);
    Vector3 right = Vector3Normalize(Vector3CrossProduct(forward, camera->up));
    int strafeX = (int)roundf(right.x);
    int strafeZ = (int)roundf(right.z);
    if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_O)) {
        camera->position = *cube_cursor;
    }
    if (IsKeyPressed(KEY_F)) {

        if ((int)cube_cursor->x >=0 && (int)cube_cursor->x < chunkSize->x &&
            (int)cube_cursor->y >=0 && (int)cube_cursor->y < chunkSize->y &&
            (int)cube_cursor->z >=0 && (int)cube_cursor->z < chunkSize->z) {
            if ((*chunk)[(int)cube_cursor->x][(int)cube_cursor->y][(int)cube_cursor->z] ==0) {
                Vector3_t cube_cursor_int;
                cube_cursor_int.x = (int)cube_cursor->x;
                cube_cursor_int.y = (int)cube_cursor->y;
                cube_cursor_int.z = (int)cube_cursor->z;
                place_block(*chunk, *chunkSize,cube_cursor_int, 2);
            }
            else {
                Vector3_t cube_cursor_int;
                cube_cursor_int.x = (int)cube_cursor->x;
                cube_cursor_int.y = (int)cube_cursor->y;
                cube_cursor_int.z = (int)cube_cursor->z;
                place_block(*chunk, *chunkSize,cube_cursor_int, 0);
            }
        }
    }
    if (IsKeyPressed(KEY_W)) {
            cube_cursor->x += (float)dx;
        cube_cursor->z += (float)dz;
    }
    if (IsKeyPressed(KEY_S)) {
            cube_cursor->x -= (float)dx;
            cube_cursor->z -= (float)dz;
    }

    if (IsKeyPressed(KEY_D)) {
            cube_cursor->x += (float)strafeX;
            cube_cursor->z += (float)strafeZ;
    }
    if (IsKeyPressed(KEY_A)) {
            cube_cursor->x -= (float)strafeX;
            cube_cursor->z -= (float)strafeZ;
    }
    if (IsKeyPressed(KEY_E)) {
        if (cube_cursor->y < (float)chunkSize->y)
            cube_cursor->y +=1;
    }
    if (IsKeyPressed(KEY_Q)) {
        if (cube_cursor->y >1.0f)
            cube_cursor->y -=1;
    }
    if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_R)) {
        cube_cursor->x = 0;
        cube_cursor->z = 0;
        cube_cursor->y = 0;
    }
    ClampCubeCursor(cube_cursor, *chunkSize);
}