#include "raylib.h"

int main(void)
{
    InitWindow(800, 450, "raylib basic window... but for boids someday");

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("maybe, eventually, boids", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}