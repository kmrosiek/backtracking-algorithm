#pragma once

#include "board.hpp"
#include "dictionary.hpp"

#include <string>
#include <stdint.h>

class Crossword
{
    public:
        Crossword() : board(10, 10) {}
        bool backtracking();
        void prepare_dictionary(const std::string&);

    private:
        Board board;
        Dictionary dictionary;

        const uint32_t NO_OF_DIFF_POSITION_SELECTION = 20;
};
