#include "raylib.h"
#include "rlImGui.h"
#include "imgui.h"
#include <cstring>
#include <cstdio>
#include <cstdlib> // for atoi

// Utility: strip any non-digit chars from the end
#include "gui/windows.h"
void menu() {

}

int main() {
    Vector3 chunkSize = RenderCreateMenu();
    RenderMainWindow(chunkSize);
    return 0;
}
