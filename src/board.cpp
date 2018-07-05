#include "board.hpp"
#include "constraint.hpp"

#include <vector>
#include <tuple>
#include <string>
#include <stdint.h>
#include <memory>


#include <iostream>
constexpr char Board::EMPTY_FIELD;
constexpr uint32_t Board::HORIZONTAL;
constexpr uint32_t Board::VERTICAL;

Board::Board(const uint32_t w, const uint32_t h) : m_width(w), m_height(h)
{
    m_fields.resize(w * h, Field());
}

Board::Constraints Board::create_constraints(const Word_footprint word_footprint) const
{
    uint32_t position = std::get<0>(word_footprint);
    uint32_t direction = std::get<1>(word_footprint);
    uint32_t word_length = std::get<2>(word_footprint);

    if(position + word_length >= m_width * m_height) // Out of board.
    {}//DEBUG INFO

    uint32_t x = position % m_width;
    uint32_t y = (position / m_width) * m_width; // Get rid of x. Returns 20 for 24.e.g.if width=5

    std::vector<std::unique_ptr<Constraint>> cons;
    std::string begin_constraint;;
    std::string end_constraint;
    std::string path_constraint;
    std::vector<std::pair<std::string, std::size_t>> up_or_left_constr;
    std::vector<std::pair<std::string, std::size_t>> down_or_right_constr;
    if(HORIZONTAL == direction)
    {
        begin_constraint = create_horizontal_begin_constraint(x, y);
        end_constraint = create_horizontal_end_constraint(x, y, word_length);
        path_constraint = create_horizontal_path_constraint(x, y, word_length);
        auto sides = create_horizontal_sides_constraint(x, y, word_length);
        up_or_left_constr = sides.first;
        down_or_right_constr = sides.second;

    }
    else if(VERTICAL == direction)
    {
        begin_constraint = create_vertical_begin_constraint(x, y);
        end_constraint = create_vertical_end_constraint(x, y, word_length);
        path_constraint = create_vertical_path_constraint(x, y, word_length);
        auto sides = create_vertical_sides_constraint(x, y, word_length);
        up_or_left_constr = sides.first;
        down_or_right_constr = sides.second;
    }
    else
    {
        //Debug info
    }

    bool output = false;
    if(output){
        std::cout << "Direction: " << direction << std::endl;
        std::cout << "Begin: " << begin_constraint << std::endl;
        std::cout << "End~~: " << end_constraint << std::endl;
        std::cout << "Path~: " << path_constraint << std::endl;
        std::cout << "Up or left:\n";
        for(auto upleft : up_or_left_constr)
            std::cout << upleft.second << ": " << upleft.first << std::endl;

        std::cout << "Down or Right:\n";
        for(auto upleft : down_or_right_constr)
            std::cout << upleft.second << ": " << upleft.first << std::endl;
    }

    if(!begin_constraint.empty())
        cons.emplace_back(new Begin_constraint{begin_constraint});
    if(!end_constraint.empty())
        cons.emplace_back(new End_constraint{end_constraint});
    if(!path_constraint.empty())
        cons.emplace_back(new Path_constraint{path_constraint});
    for(auto position_word : up_or_left_constr)
        cons.emplace_back(new Up_left_constraint{position_word.first, position_word.second});
    for(auto position_word : down_or_right_constr)
        cons.emplace_back(new Down_right_constraint{position_word.first, position_word.second});

    return cons;
}

std::string Board::create_horizontal_begin_constraint(std::size_t x, std::size_t y) const
{
    std::string begin_constraint;
    for(int i = x - 1; i >= 0; --i)
    {
        if(m_fields[i + y].character == EMPTY_FIELD)
            break;

        begin_constraint += m_fields[i + y].character;
    }

    return begin_constraint;
}

std::string Board::create_horizontal_end_constraint(std::size_t x, std::size_t y,
        std::size_t word_length) const
{
    std::string end_constraint;
    for(std::size_t i = x + word_length; i < m_width; ++i)
    {
        if(m_fields[i + y].character == EMPTY_FIELD)
            break;

        end_constraint += m_fields[i + y].character;
    }

    return end_constraint;
}

std::string Board::create_horizontal_path_constraint(std::size_t x, std::size_t y,
        std::size_t word_length) const
{
    std::string path_constraint;
    bool is_path_clear = true;
    for(std::size_t i = 0; i < word_length; ++i)
    {
        if(m_fields[x + y + i].character != EMPTY_FIELD)
            is_path_clear = false;
        path_constraint += m_fields[x + y + i].character;
    }

    if(is_path_clear)
        path_constraint.clear();

    return path_constraint;
}

std::pair<
std::vector<std::pair<std::string, std::size_t>>,
std::vector<std::pair<std::string, std::size_t>>>
Board::create_horizontal_sides_constraint(std::size_t x, std::size_t y,
        std::size_t word_length) const
{
    std::vector<std::pair<std::string, std::size_t>> up_or_left_constr, down_or_right_constr;
    for(std::size_t letter_pos = 0; letter_pos < word_length; ++letter_pos)
    {
        std::string constr;
        for(int shift = 1, expr; (expr = x + y - (shift * m_width) + letter_pos) >= 0; ++shift)
        {
            if(m_fields[expr].character != EMPTY_FIELD)
                constr += m_fields[expr].character;
            else
                break;
        }
        if(!constr.empty())
            up_or_left_constr.push_back(std::make_pair(constr, letter_pos));

        constr.clear();
        for(std::size_t shift = 1, expr; (expr = x + y + (shift * m_width) + letter_pos)
                < (m_width * m_height); ++shift)
        {
            if(m_fields[expr].character != EMPTY_FIELD)
                constr += m_fields[expr].character;
            else
                break;
        }
        if(!constr.empty())
            down_or_right_constr.push_back(std::make_pair(constr, letter_pos));
    }

    return std::make_pair(up_or_left_constr, down_or_right_constr);
}

std::string Board::create_vertical_begin_constraint(std::size_t x, std::size_t y) const
{
    std::string begin_constraint;
    for(int i = y - m_width; i >= 0; i -= m_width)
    {
        if(m_fields[x + i].character == EMPTY_FIELD)
            break;

        begin_constraint += m_fields[x + i].character;
    }

    return begin_constraint;
}

std::string Board::create_vertical_end_constraint(std::size_t x, std::size_t y, std::size_t word_length) const
{
    std::string end_constraint;
    for(std::size_t i = y + (word_length * m_width); i < m_height * m_width; i += m_width)
    {
        if(m_fields[x + i].character == EMPTY_FIELD)
            break;

        end_constraint += m_fields[x + i].character;
    }

    return end_constraint;
}

std::string Board::create_vertical_path_constraint(std::size_t x, std::size_t y, std::size_t word_length) const
{
    std::string path_constraint;
    bool is_path_clear = true;
    for(std::size_t i = 0; i < word_length; ++i)
    {
        if(m_fields[x + y + (i * m_width)].character != EMPTY_FIELD)
            is_path_clear = false;
        path_constraint += m_fields[x + y + (i * m_width)].character;
    }

    if(is_path_clear)
        path_constraint.clear();

    return path_constraint;
}

std::pair<
std::vector<std::pair<std::string, std::size_t>>,
std::vector<std::pair<std::string, std::size_t>>>
Board::create_vertical_sides_constraint(std::size_t x,std::size_t y,
        std::size_t word_length) const
{
    std::vector<std::pair<std::string, std::size_t>> up_or_left_constr, down_or_right_constr;

    for(std::size_t letter_pos = 0; letter_pos < word_length; ++letter_pos)
    {
        std::string constr;
        for(int shift = 1, expr; ((expr = x + y - shift + (letter_pos * m_width)) + 1) % m_width != 0 ; ++shift)
        {
            if(m_fields[expr].character != EMPTY_FIELD)
                constr += m_fields[expr].character;
            else
                break;
        }
        if(!constr.empty())
            up_or_left_constr.push_back(std::make_pair(constr, letter_pos));

        constr.clear();
        for(std::size_t shift = 1, expr; (expr = x + y + shift + (letter_pos * m_width)) % m_width != 0; ++shift)
        {
            if(m_fields[expr].character != EMPTY_FIELD)
                constr += m_fields[expr].character;
            else
                break;
        }
        if(!constr.empty())
            down_or_right_constr.push_back(std::make_pair(constr, letter_pos));
    }

    return std::make_pair(up_or_left_constr, down_or_right_constr);
}

void Board::insert_word(const std::string& word, const Word_footprint word_footprint)
{
    uint32_t position = std::get<0>(word_footprint);
    uint32_t direction = std::get<1>(word_footprint);
    uint32_t word_length = std::get<2>(word_footprint);

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

void Board::remove_word(const Word_footprint word_footprint)
{
    uint32_t position = std::get<0>(word_footprint);
    uint32_t direction = std::get<1>(word_footprint);
    uint32_t word_length = std::get<2>(word_footprint);

    uint32_t shift = (direction == HORIZONTAL) ? 1 : m_width;

    for(std::size_t i = 0; i < word_length; ++i)
    {
        m_fields.at(position + shift * i).counter--;
        if(m_fields.at(position + shift * i).counter == 0)
            m_fields.at(position + shift * i).character = EMPTY_FIELD;
    }

}

std::vector<std::vector<char>> Board::get_printable() const
{
    std::vector<std::vector<char>> printable_board;
    for(std::size_t c_height = 0; c_height < m_height; ++c_height)
    {
        std::vector<char> printable_row;
        for(std::size_t c_width = 0; c_width < m_width; ++c_width)
        {
            printable_row.push_back(m_fields.at(c_width + m_width * c_height).character);
        }
        printable_board.push_back(printable_row);
    }

    return printable_board;
}

