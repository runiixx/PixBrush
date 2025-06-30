//
// Created by vik on 6/30/25.
//

#ifndef WINDOWS_H
#define WINDOWS_H
#include <raylib/raylib.h>
#include <rlImGui.h>
#include <imgui.h>
#include <cstdlib>
#include <cstdio>
#include "../chunk/chunk.h"
Vector3 RenderCreateMenu();
void RenderMainWindow(Vector3 chunkSize);
#endif //WINDOWS_H
