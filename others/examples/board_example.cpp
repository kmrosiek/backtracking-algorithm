#include "board.hpp"

#include <iostream>
#include <stdint.h>
#include <vector>

using Word_footprint = std::tuple<uint32_t, uint32_t, uint32_t>;

int main()
{
    Board board(5, 6);
    Word_footprint word_footprint = Word_footprint(10,0,3);
    board.insert_word("car", word_footprint);
    Word_footprint word_footprint2 = Word_footprint(2,1,4);
    board2.insert_word("rand", word_footprint2);

    std::vector<std::vector<char>> printable_board = board.get_printable();
    for(const std::vector<char> v : printable_board)
    {
        for(const char c : v)
            std::cout << c;
        std::cout << std::endl;
    }

    return 0;
}

/** OUTPUT
 * x x x x <br>
 * x x x x <br>
 * x x x x <br>
 * x x x x <br>
 * x x x x <br>
 * x x x x <br>
 */
