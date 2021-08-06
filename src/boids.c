#include "raylib.h"

int main(void) {
    const int screen_width = 800;
    const int screen_height = 450;
    int world_size = 35;
    float resolution = 1.0f;
    float bounds = world_size * resolution / 2;
    InitWindow(screen_width, screen_height, "boid collisions");

    Camera camera = {{0.0f, 20.0f, 40.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, 45.0f, 0};
    Vector3 boid_pos = {0.0f, 1.0f, 2.0f};
    float boid_size = .2f;
    Color boid_color = GREEN;

    Vector3 obj_1_pos = {-2.0f, 1.0f, -3.0f};
    Vector3 obj_1_size = {1.0f, 2.0f, 1.0f};

    Vector3 obj_2_pos = {2.0f, 1.0f, 2.0f};
    Vector3 obj_2_size = {1.0f, 2.0f, 1.0f};

    bool collision = false;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        Vector3 maybe_boid_pos = {boid_pos.x, boid_pos.y, boid_pos.z};

        if (IsKeyDown(KEY_RIGHT)) {
            maybe_boid_pos.x += 0.2f;
        } else if (IsKeyDown(KEY_LEFT)) {
            maybe_boid_pos.x -= 0.2f;
        } else if (IsKeyDown(KEY_DOWN)
                ) {
            maybe_boid_pos.z += 0.2f;
        } else if (
                IsKeyDown(KEY_UP)
                ) {
            maybe_boid_pos.z -= 0.2f;
        }

        collision = false;

        if (CheckCollisionBoxSphere(
                (BoundingBox) {(Vector3) {obj_1_pos.x - obj_1_size.x / 2,
                                          obj_1_pos.y - obj_1_size.y / 2,
                                          obj_1_pos.z - obj_1_size.z / 2},
                               (Vector3) {obj_1_pos.x + obj_1_size.x / 2,
                                          obj_1_pos.y + obj_1_size.y / 2,
                                          obj_1_pos.z + obj_1_size.z / 2}},
                maybe_boid_pos, boid_size))
            collision = true;

        if (CheckCollisionBoxSphere(
                (BoundingBox) {(Vector3) {obj_2_pos.x - obj_2_size.x / 2,
                                          obj_2_pos.y - obj_2_size.y / 2,
                                          obj_2_pos.z - obj_2_size.z / 2},
                               (Vector3) {obj_2_pos.x + obj_2_size.x / 2,
                                          obj_2_pos.y + obj_2_size.y / 2,
                                          obj_2_pos.z + obj_2_size.z / 2}},
                maybe_boid_pos, boid_size))
            collision = true;

        if (maybe_boid_pos.x > bounds || maybe_boid_pos.x < -bounds ||
        maybe_boid_pos.z > bounds || maybe_boid_pos.z < -bounds) {
            collision = true;
        }

        if (!collision) {
            boid_pos.x = maybe_boid_pos.x;
            boid_pos.y = maybe_boid_pos.y;
            boid_pos.z = maybe_boid_pos.z;
        }

        BeginDrawing();

        ClearBackground(RAYWHITE);

        BeginMode3D(camera);

        DrawCube(obj_1_pos, obj_1_size.x, obj_1_size.y, obj_1_size.z, GRAY);
        DrawCube(obj_2_pos, obj_2_size.x, obj_2_size.y, obj_2_size.z, GRAY);

        DrawSphere(boid_pos, boid_size, boid_color);

        DrawGrid(world_size, resolution);

        EndMode3D();

//        DrawText("← ↑ ↓ →", 220, 40, 20, GRAY);

        DrawFPS(10, 10);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}