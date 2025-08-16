#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <random>
#include <raylib.h>

enum class Face { U, D, F, B, L, R};
enum class Colour { White, Yellow, Green, Blue, Orange, Red };

struct RubiksCube {
    int qb_size = 40;
    Colour faces[6][3][3];
    std::vector<std::string> scramble_state;

    RubiksCube();


    void rotate(Face face, bool isPrime);
    void scramble();
    void parse(std::vector<std::string> &move_set);
    void render();

};
