#include <vector>
#include <tuple>
#include <string>
#include <stdint.h>

#include "board.hpp"
#include "constraint.hpp"

#include <iostream>
constexpr char Board::EMPTY_FIELD;
Board::Board(const uint32_t w, const uint32_t h) : m_width(w), m_height(h)
{
    m_fields.resize(w * h, Field());
}
std::vector<Constraint> Board::create_constraints_for_word_footprint(Word_footprint)
{}
void Board::insert_word(const std::string& word, Word_footprint word_footprint)
{
    uint32_t position = std::get<0>(word_footprint);
    uint32_t direction = std::get<1>(word_footprint);
    uint32_t word_length = std::get<2>(word_footprint);

    if(word.size() != word_length)
        //DEBUG info
        return;
    /// \todo replace 0 and 1 with HORIZONTAL and VERTICAL
    if(direction == 0)
    {
        uint32_t horizontal_pos = (position % m_width);
        if((horizontal_pos + word_length) > m_width)
            // DEBUG info
            return;

        for(std::size_t i = 0; i < word.size(); ++i)
        {
            if(m_fields[i + position].character != EMPTY_FIELD &&
                    m_fields[i + position].character != word[i])
            {}// DEBUG INFO
            m_fields[i + position].character = word[i];
            m_fields[i + position].counter++;
        }

    }
    else if(direction == 1)
    {
        uint32_t vertical_pos = static_cast<int>(position/m_width);
        if((vertical_pos + word_length) > m_height)
            // DEBUG info
            return;

        for(std::size_t i = 0; i < word.size(); ++i)
        {
            std::size_t current = i * m_width + position;
            if(m_fields[current].character != EMPTY_FIELD &&
                    m_fields[current].character != word[i])
            {} // DEBUG INFO
            m_fields[current].character = word[i];
            m_fields[current].counter++;
        }
    }
    else    // Direction is incorrect.
            // DEBUG info
        return;

}
void Board::remove_word(Word_footprint)
{}
std::vector<std::vector<char>> Board::get_printable()
{
    std::vector<std::vector<char>> printable_board;
    for(std::size_t c_height = 0; c_height < m_height; ++c_height)
    {
        std::vector<char> printable_row;
        for(std::size_t c_width = 0; c_width < m_width; ++c_width)
        {
            printable_row.push_back(m_fields[c_width + m_width * c_height].character);
        }
        printable_board.push_back(printable_row);
    }

    return printable_board;
}

