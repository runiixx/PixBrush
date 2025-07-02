#include "raylib.h"

#include "gui/windows.h"
#include "logger/logger.h"

int main() {
    logger::info("TEST %d %s", 3, "DAA");
    Vector3 chunkSize = RenderCreateMenu();
    RenderMainWindow(chunkSize);
    return 0;
}
