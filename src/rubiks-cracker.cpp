extern "C" {
    #include "raylib.h"
}
#include "raymath.h"
#include <vector>
#include <string>

// -- Window Settings --
int W_WIDTH = 1080;
int W_HEIGHT = 960;
int tileSize = 40;

// -- Rubik's Cube --
enum class Face { U         , D         , F     , B         , L     , R };
enum class Sticker {White   , Yellow    , Green  , Blue    , Orange  , Red };

struct RubiksCube {
    Sticker faces[6][3][3];

    RubiksCube() {
        for(int face = 0; face < 6; face++) {
            for(int row = 0; row < 3; row++) {
                for(int col = 0; col < 3; col++) {
                    
                    switch(face) {
                        case 0:
                            faces[face][row][col] = Sticker::White;
                            break;
                        case 1:
                            faces[face][row][col] = Sticker::Yellow;
                            break;
                        case 2:
                            faces[face][row][col] = Sticker::Green;
                            break;
                        case 3:
                            faces[face][row][col] = Sticker::Blue;
                            break;
                        case 4:
                            faces[face][row][col] = Sticker::Orange;
                            break;
                        case 5:
                            faces[face][row][col] = Sticker::Red;
                            break;
                        default:
                            break;
                    }
                }
            }
        }
    }

    void rotate(Face face, bool prime) {

        auto rotateFace = [&](Sticker face[3][3]) {
            Sticker buffer[3][3];

            for(int row = 0; row < 3; row++) {
                for(int col = 0; col < 3; col++) {
                    buffer[col][2 - row] = face[row][col];
                }
            }

            for(int row = 0; row < 3; row++) {
                for(int col = 0; col < 3; col++) {
                    face[row][col] = buffer[row][col];
                }
            }
        };

        auto resolveEdges = [&](Face face) {
            Sticker buffer[3];
            
            switch(face) {
                
                case Face::U:
                    // save the left
                    for (int col = 0; col < 3; col++)
                        buffer[col] = faces[(int)Face::L][0][col];

                    // new left
                    for (int col = 0; col < 3; col++)
                        faces[(int)Face::L][0][col] = faces[(int)Face::F][0][col];

                    // new front
                    for (int col = 0; col < 3; col++)
                        faces[(int)Face::F][0][col] = faces[(int)Face::R][0][col];

                    // new right
                    for (int col = 0; col < 3; col++)
                        faces[(int)Face::R][0][col] = faces[(int)Face::B][0][col];

                    // new back
                    for (int col = 0; col < 3; col++)
                        faces[(int)Face::B][0][col] = buffer[col];
                    break;


                case Face::D:
                    // save the back
                    for (int col = 0; col < 3; col++)
                        buffer[col] = faces[(int)Face::B][2][col];

                    // new back
                    for (int col = 0; col < 3; col++)
                        faces[(int)Face::B][2][col] = faces[(int)Face::R][2][col];

                    // new right
                    for (int col = 0; col < 3; col++)
                        faces[(int)Face::R][2][col] = faces[(int)Face::F][2][col];

                    // new front
                    for (int col = 0; col < 3; col++)
                        faces[(int)Face::F][2][col] = faces[(int)Face::L][2][col];

                    // new left
                    for (int col = 0; col < 3; col++)
                        faces[(int)Face::L][2][col] = buffer[col];
                    break;


                case Face::L:
                    // save the back
                    for (int row = 0; row < 3; row++)
                        buffer[row] = faces[(int)Face::B][2 - row][2];

                    // new back
                    for (int row = 0; row < 3; row++)
                        faces[(int)Face::B][2 - row][2] = faces[(int)Face::D][row][0];

                    // new down
                    for (int row = 0; row < 3; row++)
                        faces[(int)Face::D][row][0] = faces[(int)Face::F][row][0];

                    // new front
                    for (int row = 0; row < 3; row++)
                        faces[(int)Face::F][row][0] = faces[(int)Face::U][row][0];

                    // new up
                    for (int row = 0; row < 3; row++)
                        faces[(int)Face::U][row][0] = buffer[row];
                    break;


                case Face::R:
                    // save the back
                    for (int row = 0; row < 3; row++)
                        buffer[row] = faces[(int)Face::B][2 - row][0];

                    // new back
                    for (int row = 0; row < 3; row++)
                        faces[(int)Face::B][2 - row][0] = faces[(int)Face::U][row][2];

                    // new up
                    for (int row = 0; row < 3; row++)
                        faces[(int)Face::U][row][2] = faces[(int)Face::F][row][2];

                    // new front
                    for (int row = 0; row < 3; row++)
                        faces[(int)Face::F][row][2] = faces[(int)Face::D][row][2];

                    // new down
                    for (int row = 0; row < 3; row++)
                        faces[(int)Face::D][row][2] = buffer[row];
                    break;


                case Face::F:
                    // save the up
                    for (int col = 0; col < 3; col++)
                        buffer[col] = faces[(int)Face::U][2][col];

                    // new up
                    for (int col = 0; col < 3; col++)
                        faces[(int)Face::U][2][col] = faces[(int)Face::L][2 - col][2];

                    // new left
                    for (int col = 0; col < 3; col++)
                        faces[(int)Face::L][col][2] = faces[(int)Face::D][0][col];

                    // new down
                    for (int col = 0; col < 3; col++)
                        faces[(int)Face::D][0][col] = faces[(int)Face::R][2 - col][0];

                    // new right
                    for (int col = 0; col < 3; col++)
                        faces[(int)Face::R][col][0] = buffer[col];
                    break;


                case Face::B:
                    // save the up
                    for (int col = 0; col < 3; col++)
                        buffer[col] = faces[(int)Face::U][0][col];

                    // new up
                    for (int col = 0; col < 3; col++)
                        faces[(int)Face::U][0][col] = faces[(int)Face::R][col][2];

                    // new right
                    for (int col = 0; col < 3; col++)
                        faces[(int)Face::R][col][2] = faces[(int)Face::D][2][2 - col];

                    // new down
                    for (int col = 0; col < 3; col++)
                        faces[(int)Face::D][2][col] = faces[(int)Face::L][col][0];

                    // new left
                    for (int col = 0; col < 3; col++)
                        faces[(int)Face::L][col][0] = buffer[2 - col];
                    break;
                }

            };
        
        rotateFace(faces[(int)face]);
        resolveEdges(face);   
        
    }

    void render() {

        auto toRaylibColor = [&](Sticker sticker) {
            switch(sticker) {
                case Sticker::White: return WHITE;
                case Sticker::Yellow: return YELLOW;
                case Sticker::Red: return RED;
                case Sticker::Orange: return ORANGE;
                case Sticker::Blue: return BLUE;
                case Sticker::Green: return GREEN;
                default: return BLACK;

            }
        };

        // using a lambda function
        auto drawFace = [&](Face face, int x, int y) {
            for(int row = 0; row < 3; row++) {
                for(int col = 0; col < 3; col++) {
                    Color color = toRaylibColor(this->faces[(int)face][row][col]);
                    DrawRectangle(x + col * tileSize, y + row * tileSize, tileSize, tileSize, color);
                    DrawRectangleLines(x + col * tileSize, y + row * tileSize, tileSize, tileSize, BLACK);
                }
            }
        };
        
        drawFace(Face::U, tileSize * 3, tileSize * 0);
        drawFace(Face::L, tileSize * 0, tileSize * 3);
        drawFace(Face::F, tileSize * 3, tileSize * 3);
        drawFace(Face::R, tileSize * 6, tileSize * 3);
        drawFace(Face::B, tileSize * 9, tileSize * 3);
        drawFace(Face::D, tileSize * 3, tileSize * 6);

    }

};

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    InitWindow(W_WIDTH, W_HEIGHT, "raylib [core] example - basic window");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    RubiksCube cube;
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
                cube.rotate(Face::U, true);
            }
            if (IsKeyPressed(KEY_D)) {
                cube.rotate(Face::D, true);
            }
            if (IsKeyPressed(KEY_F)) {
                cube.rotate(Face::F, true);
            }
            if (IsKeyPressed(KEY_B)) {
                cube.rotate(Face::B, true);
            }
            if (IsKeyPressed(KEY_L)) {
                cube.rotate(Face::L, true);
            }
            if (IsKeyPressed(KEY_R)) {
                cube.rotate(Face::R, true);
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

