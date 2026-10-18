#include <raylib.h>

int main (int argc, char *argv[]) {
    InitWindow(500, 500, "Circles");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        DrawText("raylib is working", 30, 30, 24, WHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
