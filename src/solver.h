#pragma once
#include "rubiks.h"

struct Solver {
    static std::vector<std::string> solve(RubiksCube &cube);

    // -- Phase 1: Reach G1 subgroup --
    static int cornerOrientation(const RubiksCube &cube);
    static int edgeOrientation(const RubiksCube &cube);
    static int udSliceEdges(const RubiksCube &cube);

    std::vector<std::string> p1Search(RubiksCube &cube, int depth);

    // -- Phase 2: Find optimal solution from G1 --
}; 
