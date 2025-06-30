//
// Created by vik on 6/30/25.
//

#ifndef KEYBOARD_INPUT_H
#define KEYBOARD_INPUT_H
#include <raylib/raylib.h>
#include <raylib/raymath.h>
#include "../chunk/chunk.h"
void update_cube_cursor(chunk_t *chunk,Vector3_t *chunkSize, Vector3 *cube_cursor, Camera3D *camera);
#endif //KEYBOARD_INPUT_H
