#include "raylib.h"

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screen_width = 800;
    const int screen_height = 450;

    InitWindow(screen_width, screen_height, "boid collisions");

    // Define the camera to look into our 3d world
    Camera camera = { { 0.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, 45.0f, 0 };

    Vector3 boid_pos = { 0.0f, 1.0f, 2.0f };
    float boid_size = .2f;
    Color boid_color = GREEN;

    Vector3 obj_1_pos = { -4.0f, 1.0f, 0.0f };
    Vector3 obj_1_size = { 1.0f, 2.0f, 1.0f };

    Vector3 obj_2_pos = { 4.0f, 0.0f, 0.0f };
    Vector3 obj_2_size = { 1.0f, 2.0f, 1.0f };

    bool collision = false;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------

        // Move player
        if (IsKeyDown(KEY_RIGHT)) boid_pos.x += 0.2f;
        else if (IsKeyDown(KEY_LEFT)) boid_pos.x -= 0.2f;
        else if (IsKeyDown(KEY_DOWN)) boid_pos.z += 0.2f;
        else if (IsKeyDown(KEY_UP)) boid_pos.z -= 0.2f;

        collision = false;

        // Check collisions player vs enemy-box
        if (CheckCollisionBoxSphere(
            (BoundingBox){(Vector3){ obj_1_pos.x - obj_1_size.x/2,
                                     obj_1_pos.y - obj_1_size.y/2,
                                     obj_1_pos.z - obj_1_size.z/2 },
                          (Vector3){ obj_1_pos.x + obj_1_size.x/2,
                                     obj_1_pos.y + obj_1_size.y/2,
                                     obj_1_pos.z + obj_1_size.z/2 }},
            boid_pos, boid_size)) collision = true;

        // Check collisions player vs enemy-sphere
        if (CheckCollisionBoxSphere(
            (BoundingBox){(Vector3){ obj_1_pos.x - obj_2_size.x/2,
                                     obj_1_pos.y - obj_2_size.y/2,
                                     obj_1_pos.z - obj_2_size.z/2 },
                          (Vector3){ obj_1_pos.x + obj_2_size.x/2,
                                     obj_1_pos.y + obj_2_size.y/2,
                                     obj_1_pos.z + obj_2_size.z/2 }},
            boid_pos, boid_size)) collision = true;

        if (collision) boid_color = RED;
        else boid_color = GREEN;
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);

                // Draw enemy-box
                DrawCube(obj_1_pos, obj_1_size.x, obj_1_size.y, obj_1_size.z, GRAY);
                DrawCube(obj_2_pos, obj_2_size.x, obj_2_size.y, obj_2_size.z, GRAY);

                // Draw enemy-sphere
                DrawSphere(boid_pos, boid_size, boid_color);

                DrawGrid(10, 1.0f);        // Draw a grid

            EndMode3D();

            DrawText("Move boid with arrows to collide", 220, 40, 20, GRAY);

            DrawFPS(10, 10);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}