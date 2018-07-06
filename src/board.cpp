#include "board.hpp"
#include "word_footprint.hpp"

#include <vector>
#include <tuple>
#include <string>
#include <stdint.h>


constexpr char Board::EMPTY_FIELD;
constexpr uint32_t Board::HORIZONTAL;
constexpr uint32_t Board::VERTICAL;

Board::Board(const uint32_t w, const uint32_t h) : m_width(w), m_height(h)
{
    m_fields.resize(w * h, Field());
}

void Board::insert_word(const std::string& word, const Word_footprint& word_footprint)
{
    uint32_t position = word_footprint.get_position();
    uint32_t direction = word_footprint.get_direction();
    uint32_t word_length = word_footprint.get_word_length();

    if(word.size() != word_length)
        //DEBUG info
        return;

    if(direction == HORIZONTAL)
    {
        uint32_t horizontal_pos = (position % m_width);
        if((horizontal_pos + word_length) > m_width)
            // DEBUG info
            return;

        for(std::size_t i = 0; i < word.size(); ++i)
        {
            if(m_fields.at(i + position).character != EMPTY_FIELD &&
                    m_fields[i + position].character != word[i])
            {}// DEBUG INFO
            m_fields[i + position].character = word[i];
            m_fields.at(i + position).counter++;
        }

    }
    else if(direction == VERTICAL)
    {
        uint32_t vertical_pos = static_cast<int>(position/m_width);
        if((vertical_pos + word_length) > m_height)
            // DEBUG info
            return;

        for(std::size_t i = 0; i < word.size(); ++i)
        {
            std::size_t current = i * m_width + position;
            if(m_fields.at(current).character != EMPTY_FIELD &&
                    m_fields[current].character != word[i])
            {} // DEBUG INFO
            m_fields[current].character = word[i];
            m_fields.at(current).counter++;
        }
    }
    else    // Direction is incorrect.
        // DEBUG info
        return;

}

void Board::remove_word(const Word_footprint& word_footprint)
{
    uint32_t position = word_footprint.get_position();
    uint32_t direction = word_footprint.get_direction();
    uint32_t word_length = word_footprint.get_word_length();

    uint32_t shift = (direction == HORIZONTAL) ? 1 : m_width;

    for(std::size_t i = 0; i < word_length; ++i)
    {
        m_fields.at(position + shift * i).counter--;
        if(m_fields.at(position + shift * i).counter == 0)
            m_fields.at(position + shift * i).character = EMPTY_FIELD;
    }

}

std::vector<char> Board::get_printable() const
{
    std::vector<char> printable_board;
    for(const Field& f : m_fields)
        printable_board.push_back(f.character);

    return printable_board;
}

