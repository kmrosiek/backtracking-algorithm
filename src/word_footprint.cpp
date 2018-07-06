#include "word_footprint.hpp"

Word_footprint::Word_footprint(uint32_t board_width, uint32_t board_height)
{
    //randoms();
    position = 3;
    direction = 1;
    word_length = 4;
    /*position = random_position(BOARD_WIDTH, BOARD_HEIGHT);
      direction = random_direction(); // returns 0 or 1 (LEFT or RIGHT)
      distance_to_border = calculate_distance_to_border(position, direction);
      word_length = random_word_length(distance_to_border);*/
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
