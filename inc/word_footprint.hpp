#pragma once

#include <tuple>
#include <stdint.h>

class Word_footprint
{
    public:
        Word_footprint(const uint32_t, const uint32_t);
        Word_footprint(const uint32_t, const uint32_t, const uint32_t) noexcept;

        uint32_t get_position() const noexcept;
        uint32_t get_direction() const noexcept;
        uint32_t get_word_length() const noexcept;

        /** Describes word footprint - a place on the board where the word will be placed.
         *  @param position in letter units.
         *  @param direction horizontal = 0 or vertical = 1.
         *  @param word_length
         */

    private:
        uint32_t position;
        uint32_t direction;
        uint32_t word_length;
};
