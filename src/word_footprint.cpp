#include "word_footprint.hpp"
#include "utils.hpp"
#include "board.hpp"

#include <iostream>

Word_footprint::Word_footprint(const uint32_t board_width, const uint32_t board_height)
{
    // Generate direction for 0 - horizontal, 1 - verticall.
    direction = utils::generate_random(0, 1);

    int distance_to_border;
    /** board_width|height - 2, because fields count from 0 and there are no word
     *  with a single letter, therefore, last field is excluded. */
    int pos_x, pos_y;
    if(direction == Board::HORIZONTAL)
    {
        pos_x = utils::generate_random(0, board_width - 2);
        distance_to_border = board_width - pos_x;
        pos_y = utils::generate_random(0, board_height - 1);
    }
    else
    {
        pos_y = utils::generate_random(0, board_height - 2);
        distance_to_border = board_height - pos_y;
        pos_x = utils::generate_random(0, board_width - 1);
    }
    position = pos_x + pos_y * 10;

    const int MINIMAL_WORD_LENGTH = 2;
    word_length = utils::generate_random(MINIMAL_WORD_LENGTH, distance_to_border);

    std::cout << "bwidth: " << board_width << "   .bheight: " << board_height << "  .direction: " << direction;
    std::cout << "  .pos: " << position << "  .dis_to_bord: " << distance_to_border;
    std::cout << "  .word_length: " << word_length << std::endl;
}

Word_footprint::Word_footprint(uint32_t pos, uint32_t dir, uint32_t len) noexcept
    : position(pos)
    , direction(dir)
    , word_length(len)
{}

uint32_t Word_footprint::get_position() const noexcept
{
    return position;
}
uint32_t Word_footprint::get_direction() const noexcept
{
    return direction;
}
uint32_t Word_footprint::get_word_length() const noexcept
{
    return word_length;
}
