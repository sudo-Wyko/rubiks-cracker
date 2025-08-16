extern "C" {
    #include "raylib.h"
}
#include "raymath.h"
#include <vector>
#include <string>
#include <iostream>

// -- Window Settings --
int W_WIDTH = 1080;
int W_HEIGHT = 960;
int tileSize = 40;

// -- Rubik's Cube --
enum class Face { U         , D         , F     , B         , L     , R };
enum class Sticker {White   , Yellow    , Green  , Blue    , Orange  , Red };
std::vector<std::string> moves;

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

        auto r_URotation = [&] {
            Sticker buffer[3];

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

        };
        auto r_DRotation = [&] {
            Sticker buffer[3];

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
        };

        auto r_FRotation = [&] {
            Sticker buffer[3];

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
        };
        auto r_BRotation = [&] {
            Sticker buffer[3];

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
        };

        auto r_LRotation = [&] {
            Sticker buffer[3];

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
        };
        auto r_RRotation = [&] {
            Sticker buffer[3];

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
        };

        auto resolveEdges = [&](Face face) {
            Sticker buffer[3];
            
            switch(face) {
                
                case Face::U:
                    r_URotation();
                    break;


                case Face::D:
                    r_DRotation();          
                    break;


                case Face::F:
                    r_FRotation();
                    break;


                case Face::B:
                    r_BRotation();
                    break;


                case Face::L:
                    r_LRotation();
                    break;


                case Face::R:
                    r_RRotation();
                    break;
                }

            };

        if(prime) {
            for(int ctr = 0; ctr < 3; ctr++)  {
                rotateFace(faces[(int)face]);
                resolveEdges(face);
            }
       
        } else {
            rotateFace(faces[(int)face]);
            resolveEdges(face);   
        }
        
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

            float qbPosition_x;
            float qbPosition_y;
            float qbPadding = 3.0f;

            float radius = 0.135f;
            float lineThickness = 4.0f;


            for(int row = 0; row < 3; row++) {
                for(int col = 0; col < 3; col++) {

                    qbPosition_x = float(x + col * (tileSize + qbPadding));
                    qbPosition_y = float(y + row * (tileSize + qbPadding));

                    Color color = toRaylibColor(this->faces[(int)face][row][col]);
                    DrawRectangleRounded({qbPosition_x, qbPosition_y , float(tileSize), float(tileSize)}, radius, 4, color);
                    DrawRectangleRoundedLinesEx({qbPosition_x, qbPosition_y, float(tileSize), float(tileSize)}, radius, 4, lineThickness, BLACK);
                }
            }
        };

        float facePadding = 4.0f;
        
        drawFace(Face::U, (tileSize + facePadding - 1) * 3, (tileSize + facePadding) * 0);
        drawFace(Face::L, (tileSize + facePadding - 1) * 0, (tileSize + facePadding) * 3);
        drawFace(Face::F, (tileSize + facePadding - 1) * 3, (tileSize + facePadding) * 3);
        drawFace(Face::R, (tileSize + facePadding - 1) * 6, (tileSize + facePadding) * 3);
        drawFace(Face::B, (tileSize + facePadding - 1) * 9, (tileSize + facePadding) * 3);
        drawFace(Face::D, (tileSize + facePadding - 1) * 3, (tileSize + facePadding) * 6);

    }

};

void printMove() {
    std::cerr << "Your moves: ";
    for(const auto& m : moves) {
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
    std::string moveString;
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
                    moveString = "U'";
                    moves.push_back(moveString);
                    printMove();
                    
                } else {
                    cube.rotate(Face::U, false);
                    moveString = "U";
                    moves.push_back(moveString);
                    printMove();
                }       
            }
            if (IsKeyPressed(KEY_D)) {
                if(IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)){
                    cube.rotate(Face::D, true);
                    moveString = "D'";
                    moves.push_back(moveString);
                    printMove();
                } else {
                    cube.rotate(Face::D, false);
                    moveString = "D";
                    moves.push_back(moveString);
                    printMove();
                }
            }
            if (IsKeyPressed(KEY_F)) {
                if(IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)){
                    cube.rotate(Face::F, true);
                    moveString = "F'";
                    moves.push_back(moveString);
                    printMove();
                } else {
                    cube.rotate(Face::F, false);
                    moveString = "F";
                    moves.push_back(moveString);
                    printMove();
                }
            }
            if (IsKeyPressed(KEY_B)) {
                if(IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)){
                    cube.rotate(Face::B, true);
                    moveString = "B'";
                    moves.push_back(moveString);
                    printMove();
                } else {
                    cube.rotate(Face::B, false);
                    moveString = "B";
                    moves.push_back(moveString);
                    printMove();
                }
            }
            if (IsKeyPressed(KEY_L)) {
                if(IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)){
                    cube.rotate(Face::L, true);
                    moveString = "L'";
                    moves.push_back(moveString);
                    printMove();
                } else {
                    cube.rotate(Face::L, false);
                    moveString = "L";
                    moves.push_back(moveString);
                    printMove();
                }
            }
            if (IsKeyPressed(KEY_R)) {
                if(IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)){
                    cube.rotate(Face::R, true);
                    moveString = "R'";
                    moves.push_back(moveString);
                    printMove();
                } else {
                    cube.rotate(Face::R, false);
                    moveString = "R";
                    moves.push_back(moveString);
                    printMove();
                }
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

