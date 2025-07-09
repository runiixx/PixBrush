#include "raylib.h"

#include "gui/windows.h"
#include "logger/logger.h"

int main() {
    logger::info("TEST %d %s", 3, "DAA");
    Vector3 chunkSize = RenderCreateMenu();
    if (chunkSize.x + chunkSize.y + chunkSize.z > 0)
        RenderMainWindow(chunkSize);
    return 0;
}
