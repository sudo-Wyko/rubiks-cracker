#include "rubiks.h"

RubiksCube::RubiksCube() {
   for(int face = 0; face < 6; face++) {
        for(int row = 0; row < 3; row++) {
            for(int col = 0; col < 3; col++) {
                
                switch(face) {
                    case 0:
                        faces[face][row][col] = Colour::White;
                        break;
                    case 1:
                        faces[face][row][col] = Colour::Yellow;
                        break;
                    case 2:
                        faces[face][row][col] = Colour::Green;
                        break;
                    case 3:
                        faces[face][row][col] = Colour::Blue;
                        break;
                    case 4:
                        faces[face][row][col] = Colour::Orange;
                        break;
                    case 5:
                        faces[face][row][col] = Colour::Red;
                        break;
                    default:
                        break;
                }
            }
        }
    } 
}

void RubiksCube::rotate(Face face, bool isPrime) {

    auto rotateFace = [&](Colour face[3][3]) {
        Colour buffer[3][3];

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
        Colour buffer[3];

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
        Colour buffer[3];

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
        Colour buffer[3];

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
        Colour buffer[3];

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
        Colour buffer[3];

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
        Colour buffer[3];

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
        Colour buffer[3];
        
        switch(face) {
            case Face::U:   r_URotation(); break;
            case Face::D:   r_DRotation(); break;
            case Face::F:   r_FRotation(); break;
            case Face::B:   r_BRotation(); break;
            case Face::L:   r_LRotation(); break;
            case Face::R:   r_RRotation(); break;
        }
    };

    if(isPrime) {
        for(int ctr = 0; ctr < 3; ctr++) {
            rotateFace(faces[(int)face]);
            resolveEdges(face);
        }
    } else {
        rotateFace(faces[(int)face]);
        resolveEdges(face);
    }
}

void RubiksCube::scramble() {
    int scrambleLength = 20;
    std::string moves [] = {"U", "D", "F", "B", "L", "R"};
    std::string modifiers[] = {"", "'", "2"};
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> moveDist(0, 5);
    std::uniform_int_distribution<int> modifierDist(0, 2);

    int lastMove = -1;
    int move;
    int modifier;
    for(int i = 0; i < scrambleLength; i++) {
        do {
            move = moveDist(gen);
        } while(move == lastMove);

        lastMove = move;
        
        modifier = modifierDist(gen);
        scramble_state.push_back(moves[move] + modifiers[modifier]);
    }
}

void RubiksCube::parse(std::vector<std::string> &move_set) {
    std::string translateMoves;

    for(const auto &m : move_set) 
        translateMoves += m + " ";

    std::istringstream ss(translateMoves);
    std::string move;

    while(ss >> move) {
        Face face;
        bool prime = false;
        int turns = 1;

        switch(move[0]) {
            case 'U' :  face = Face::U; break;
            case 'D' :  face = Face::D; break;
            case 'F' :  face = Face::F; break;
            case 'B' :  face = Face::B; break;
            case 'L' :  face = Face::L; break;
            case 'R' :  face = Face::R; break;
            default  :   continue;
        }

        if(move.size() > 1) {
            switch(move[1]) {
                case '\'' : prime = true; break;
                case '2'  : turns = 2; break;
            }
        }

        for(int ctr = 0; ctr < turns; ctr++) {
            rotate(face, prime);
        }
    }
}

void RubiksCube::render() {
    auto toRaylibColor = [&](Colour sticker) {
        switch(sticker) {
            case Colour::White: return WHITE;
            case Colour::Yellow: return YELLOW;
            case Colour::Red: return RED;
            case Colour::Orange: return ORANGE;
            case Colour::Blue: return BLUE;
            case Colour::Green: return GREEN;
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

                qbPosition_x = float(x + col * (qb_size + qbPadding));
                qbPosition_y = float(y + row * (qb_size + qbPadding));

                Color color = toRaylibColor(this->faces[(int)face][row][col]);
                DrawRectangleRounded({qbPosition_x, qbPosition_y , float(qb_size), float(qb_size)}, radius, 4, color);
                DrawRectangleRoundedLinesEx({qbPosition_x, qbPosition_y, float(qb_size), float(qb_size)}, radius, 4, lineThickness, BLACK);
            }
        }
    };

    float facePadding = 4.0f;
    
    drawFace(Face::U, (qb_size + facePadding - 1) * 3, (qb_size + facePadding) * 0);
    drawFace(Face::L, (qb_size + facePadding - 1) * 0, (qb_size + facePadding) * 3);
    drawFace(Face::F, (qb_size + facePadding - 1) * 3, (qb_size + facePadding) * 3);
    drawFace(Face::R, (qb_size + facePadding - 1) * 6, (qb_size + facePadding) * 3);
    drawFace(Face::B, (qb_size + facePadding - 1) * 9, (qb_size + facePadding) * 3);
    drawFace(Face::D, (qb_size + facePadding - 1) * 3, (qb_size + facePadding) * 6);

}


