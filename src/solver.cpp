#include "solver.h"
#include "rubiks.h"
#include <array>

int Solver::cornerOrientation(const RubiksCube &cube) {

    struct CornerPiece { 
        Face face_1; int row_1,col_1; 
        Face face_2; int row_2,col_2; 
        Face face_3; int row_3,col_3; 
    };

    std::array<CornerPiece, 8> corners = {{
        {Face::U,2,2, Face::F,0,2, Face::R,0,0}, // UFR
        {Face::U,0,2, Face::R,0,2, Face::B,0,0}, // URB
        {Face::U,0,0, Face::B,0,2, Face::L,0,0}, // UBL
        {Face::U,2,0, Face::L,0,2, Face::F,0,0}, // ULF
        {Face::D,0,2, Face::R,2,0, Face::F,2,2}, // DFR
        {Face::D,0,0, Face::B,2,2, Face::R,2,2}, // DRB
        {Face::D,2,0, Face::L,2,2, Face::B,2,0}, // DBL
        {Face::D,2,2, Face::F,2,0, Face::L,2,0}  // DLF
    }};

    int index = 0;

    for(int i = 0; i < 7; i++) {
        int orientation = 0;
        CornerPiece c = corners[i];

        Colour side_1 = cube.faces[(int)c.face_1][c.row_1][c.col_1];
        Colour side_2 = cube.faces[(int)c.face_2][c.row_2][c.col_2];
        Colour side_3 = cube.faces[(int)c.face_3][c.row_3][c.col_3];

        if(side_1 == Colour::White || side_1 == Colour::Yellow) 
            orientation = (c.face_1 == Face::U || c.face_1 == Face::D) ? 0 : 
                ((c.face_2 == Face::U || c.face_2 == Face::D ? 1 : 2));
        
        else if(side_2 == Colour::White || side_2 == Colour::Yellow)
            orientation = (c.face_2 == Face::U || c.face_2 == Face::D) ? 0 : 
                ((c.face_3 == Face::U || c.face_3 == Face::D ? 1 : 2));

        else if(side_3 == Colour::White || side_3 == Colour::Yellow)
            orientation = (c.face_3 == Face::U || c.face_3 == Face::D) ? 0 : 
                ((c.face_1 == Face::U || c.face_1 == Face::D ? 1 : 2));

        index = index * 3 + orientation;
    }
    return index;
}


int Solver::edgeOrientation(const RubiksCube &cube) {

    struct EdgePiece {
        Face face_1; int row_1, col_1;
        Face face_2; int row_2, col_2;
    };

    std::array<EdgePiece, 12> edges = {{
        {Face::U,2,1, Face::F,0,1}, // UF
        {Face::U,1,2, Face::R,0,1}, // UR
        {Face::U,0,1, Face::B,0,1}, // UB
        {Face::U,1,0, Face::L,0,1}, // UL
        {Face::D,0,1, Face::F,2,1}, // DF
        {Face::D,1,2, Face::R,2,1}, // DR
        {Face::D,2,1, Face::B,2,1}, // DB
        {Face::D,1,0, Face::L,2,1}, // DL
        {Face::F,1,2, Face::R,1,0}, // FR
        {Face::R,1,2, Face::B,1,0}, // RB
        {Face::B,1,2, Face::L,1,0}, // BL
        {Face::L,1,2, Face::F,1,0}  // LF
    }};

    int index = 0;

    for(int i = 0; i < 11; i++) {
        int orientation = 0;
        EdgePiece e = edges[i];

        Colour side_1 = cube.faces[(int)e.face_1][e.row_1][e.col_1];
        Colour side_2 = cube.faces[(int)e.face_2][e.row_2][e.col_2];

        if (side_1 == Colour::White || side_1 == Colour::Yellow){
            orientation = (e.face_1 == Face::U || e.face_1 == Face::D) ? 0 : 1;
        }
        else if (side_2 == Colour::White || side_2 == Colour::Yellow){
            orientation = (e.face_2 == Face::U || e.face_2 == Face::D) ? 0 : 1;
        } 

        else {
            if ((e.face_1 == Face::F || e.face_1 == Face::B) &&
                (side_1 == Colour::White || side_1 == Colour::Yellow))
                orientation = 1;
            if ((e.face_2 == Face::F || e.face_2 == Face::B) &&
                (side_2 == Colour::White || side_2 == Colour::Yellow))
                orientation = 1;
        }

        index = index * 2 + orientation;
    }
    return index;
}

int Solver::udSliceEdges(const RubiksCube &cube) {

    auto isUDSliceEdge = [](Colour side_1, Colour side_2) -> bool { 
        if(side_1 == Colour::Green && side_2 == Colour::Red || side_2 == Colour::Green && side_1 == Colour::Red) return true; 
        if(side_1 == Colour::Red && side_2 == Colour::Blue || side_2 == Colour::Red && side_1 == Colour::Blue) return true; 
        if(side_1 == Colour::Blue && side_2 == Colour::Orange || side_2 == Colour::Blue && side_1 == Colour::Orange) return true; 
        if(side_1 == Colour::Orange && side_2 == Colour::Green || side_2 == Colour::Orange && side_1 == Colour::Green) return true; 

        return false; 
    };
    
    // CHATGPT
    auto nCr = [](int n, int r) -> long long{
        if (r > n) return 0;
        if (r > n - r) r = n - r; // symmetry
        long long result = 1;
        for (int i = 0; i < r; i++) {
            result *= (n - i);
            result /= (i + 1);
        }
        return result;
    };

     struct EdgePiece {
        Face face_1; int row_1, col_1;
        Face face_2; int row_2, col_2;
    };

    std::array<EdgePiece, 12> edges = {{
        {Face::U,2,1, Face::F,0,1}, // UF
        {Face::U,1,2, Face::R,0,1}, // UR
        {Face::U,0,1, Face::B,0,1}, // UB
        {Face::U,1,0, Face::L,0,1}, // UL
        {Face::D,0,1, Face::F,2,1}, // DF
        {Face::D,1,2, Face::R,2,1}, // DR
        {Face::D,2,1, Face::B,2,1}, // DB
        {Face::D,1,0, Face::L,2,1}, // DL
        {Face::F,1,2, Face::R,1,0}, // FR
        {Face::R,1,2, Face::B,1,0}, // RB
        {Face::B,1,2, Face::L,1,0}, // BL
        {Face::L,1,2, Face::F,1,0}  // LF
    }};

    int counter = 0;
    int index = 0;

    for(int i = 0; i < 12; i++) {
        EdgePiece e = edges[i];

        Colour side_1 = cube.faces[(int)e.face_1][e.row_1][e.col_1];
        Colour side_2 = cube.faces[(int)e.face_2][e.row_2][e.col_2];

                
        if(isUDSliceEdge(side_1, side_2)) {
            index += nCr(i, counter + 1);
            counter++;
        }
    }
    return index;
}
