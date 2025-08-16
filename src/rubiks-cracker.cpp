extern "C" {
    #include "raylib.h"
}
#include "rubiks.h"
#include "solver.h"
#include <iostream>

// -- Window Settings --
int W_WIDTH = 1080;
int W_HEIGHT = 960;

std::vector<std::string> move_history;

void printMoveString(std::vector<std::string> &move_set) {
    for(const auto& m : move_set) {
        std::cerr << m << " ";
    }
    std::cerr << "\n";
}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{   
    // Initialization
    InitWindow(W_WIDTH, W_HEIGHT, "raylib [core] example - basic window");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    RubiksCube cube;
    Solver solver;
    std::string move_string;
    char lastKeyPressed = '\0';
    char keyPressed;

    std::cerr << "\nCorner Orientation: "<< solver.cornerOrientation(cube);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            if (IsKeyPressed(KEY_U)) {
                if(IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)){
                    cube.rotate(Face::U, true);
                    move_string = "U'";
                    move_history.push_back(move_string);
                    //printMove();
                    
                } else {
                    cube.rotate(Face::U, false);
                    move_string = "U";
                    move_history.push_back(move_string);
                    //printMove();
                }       
            }
            if (IsKeyPressed(KEY_D)) {
                if(IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)){
                    cube.rotate(Face::D, true);
                    move_string = "D'";
                    move_history.push_back(move_string);
                    //printMove();
                } else {
                    cube.rotate(Face::D, false);
                    move_string = "D";
                    move_history.push_back(move_string);
                    //printMove();
                }
            }
            if (IsKeyPressed(KEY_F)) {
                if(IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)){
                    cube.rotate(Face::F, true);
                    move_string = "F'";
                    move_history.push_back(move_string);
                    //printMove();
                } else {
                    cube.rotate(Face::F, false);
                    move_string = "F";
                    move_history.push_back(move_string);
                    //printMove();
                }
            }
            if (IsKeyPressed(KEY_B)) {
                if(IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)){
                    cube.rotate(Face::B, true);
                    move_string = "B'";
                    move_history.push_back(move_string);
                    //printMove();
                } else {
                    cube.rotate(Face::B, false);
                    move_string = "B";
                    move_history.push_back(move_string);
                    //printMove();
                }
            }
            if (IsKeyPressed(KEY_L)) {
                if(IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)){
                    cube.rotate(Face::L, true);
                    move_string = "L'";
                    move_history.push_back(move_string);
                    //printMove();
                } else {
                    cube.rotate(Face::L, false);
                    move_string = "L";
                    move_history.push_back(move_string);
                    //printMove();
                }
            }
            if (IsKeyPressed(KEY_R)) {
                if(IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)){
                    cube.rotate(Face::R, true);
                    move_string = "R'";
                    move_history.push_back(move_string);
                    //printMove();
                } else {
                    cube.rotate(Face::R, false);
                    move_string = "R";
                    move_history.push_back(move_string);
                    //printMove();
                }
            }

            if (IsKeyPressed(KEY_G)) {
                cube.scramble();
                std::cerr << "\nScramble: ";
                printMoveString(cube.scramble_state);
                cube.parse(cube.scramble_state);
                std::cerr << "\nCorner Orientation: "<< solver.cornerOrientation(cube);
                std::cerr << "\nEdge Orienation: "<< solver.edgeOrientation(cube);
                std::cerr << "\nUD Slice: "<< solver.udSliceEdges(cube);
                
            }

            ClearBackground(RAYWHITE);
            cube.render();
            
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

