#include "word_footprint.hpp"
#include "constraint.hpp"
#include "board.hpp"

#include <vector>
#include <string>

#include <iostream> // to be deleted

Constraints::Constraints(const Word_footprint footprint, const std::vector<char> board
        , const std::size_t board_width)
    : m_x(footprint.get_position() % board_width)
    , m_y((footprint.get_position() / board_width) * board_width)
    , m_direction(footprint.get_direction())
    , m_word_length(footprint.get_word_length())
    , m_width(board_width)
    , m_height(board.size() / board_width)
    , m_fields(board)
{
    if(m_x + m_y + m_word_length >= m_width * m_height) // Out of board.
    {}//DEBUG INFO
    create_constraints();
}

//bool Constraints::check_constraint(std::function<bool(const Dictionary&, const std::string&)>, const std::string&) const;
bool Constraints::check_constraint(Dictionary_lookup lookup, const Dictionary& dictionary, const std::string& word) const
{
    for(const std::unique_ptr<Base_constraint>& cons: constraints_container)
        if(!lookup(dictionary, cons->create_word(word)))
            return false;

    return true;
}
void Constraints::create_constraints()
{

    //std::vector<std::unique_ptr<Constraint>> cons;
    std::string begin_constraint;;
    std::string end_constraint;
    std::string path_constraint;
    std::vector<std::pair<std::string, std::size_t>> up_or_left_constr;
    std::vector<std::pair<std::string, std::size_t>> down_or_right_constr;
    if(Board::HORIZONTAL == m_direction)
    {
        create_horizontal_begin_constraint();
        create_horizontal_end_constraint();
        create_horizontal_path_constraint();
        /*auto sides = create_horizontal_sides_constraint(m_x, m_y, word_length);
        up_or_left_constr = sides.first;
        down_or_right_constr = sides.second;*/

    }
    else if(Board::VERTICAL == m_direction)
    {
        create_vertical_begin_constraint();
        create_vertical_end_constraint();
        create_vertical_path_constraint();
        /*auto sides = create_vertical_sides_constraint();
        up_or_left_constr = sides.first;
        down_or_right_constr = sides.second;*/
    }
    else
    {
        //Debug info
    }

    // DEBUG info
    bool output = true;
    if(output){
        std::cout << "Direction: " << m_direction << std::endl;
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

    /*for(auto position_word : up_or_left_constr)
        cons.emplace_back(new Up_left_constraint{position_word.first, position_word.second});
    for(auto position_word : down_or_right_constr)
        cons.emplace_back(new Down_right_constraint{position_word.first, position_word.second});

    return cons;*/
}

void Constraints::create_horizontal_begin_constraint()
{
    std::string begin_constraint;
    for(int i = m_x - 1; i >= 0; --i)
    {
        if(m_fields[i + m_y] == Board::EMPTY_FIELD)
            break;

        begin_constraint += m_fields[i + m_y];
    }

    if(!begin_constraint.empty())
        constraints_container.emplace_back(new Begin_constraint{begin_constraint});
}

void Constraints::create_horizontal_end_constraint()
{
    std::string end_constraint;
    for(std::size_t i = m_x + m_word_length; i < m_width; ++i)
    {
        if(m_fields[i + m_y] == Board::EMPTY_FIELD)
            break;

        end_constraint += m_fields[i + m_y];
    }

    if(!end_constraint.empty())
        constraints_container.emplace_back(new End_constraint{end_constraint});
}

void Constraints::create_horizontal_path_constraint()
{
    std::string path_constraint;
    bool is_path_clear = true;
    for(std::size_t i = 0; i < m_word_length; ++i)
    {
        if(m_fields[m_x + m_y + i] != Board::EMPTY_FIELD)
            is_path_clear = false;

        path_constraint += m_fields[m_x + m_y + i];
    }

    if(is_path_clear)   // If no letter was found on a path, clear string so that redundant
        path_constraint.clear();    // constraint is not kept.

    if(!path_constraint.empty())
        constraints_container.emplace_back(new Path_constraint{path_constraint});
}
/*
std::pair<
std::vector<std::pair<std::string, std::size_t>>,
std::vector<std::pair<std::string, std::size_t>>>
create_horizontal_sides_constraint(std::size_t x, std::size_t y,
        std::size_t word_length) const
{
    std::vector<std::pair<std::string, std::size_t>> up_or_left_constr, down_or_right_constr;
    for(std::size_t letter_pos = 0; letter_pos < m_word_length; ++letter_pos)
    {
        std::string constr;
        for(int shift = 1, expr; (expr = m_x + m_y - (shift * m_width) + letter_pos) >= 0; ++shift)
        {
            if(m_fields[expr] != Board::EMPTY_FIELD)
                constr += m_fields[expr];
            else
                break;
        }
        if(!constr.empty())
            up_or_left_constr.push_back(std::make_pair(constr, letter_pos));

        constr.clear();
        for(std::size_t shift = 1, expr; (expr = m_x + m_y + (shift * m_width) + letter_pos)
                < (m_width * m_height); ++shift)
        {
            if(m_fields[expr] != Board::EMPTY_FIELD)
                constr += m_fields[expr];
            else
                break;
        }
        if(!constr.empty())
            down_or_right_constr.push_back(std::make_pair(constr, letter_pos));
    }

    return std::make_pair(up_or_left_constr, down_or_right_constr);
}
*/
void Constraints::create_vertical_begin_constraint()
{
    std::string begin_constraint;
    for(int i = m_y - m_width; i >= 0; i -= m_width)
    {
        if(m_fields[m_x + i] == Board::EMPTY_FIELD)
            break;

        begin_constraint += m_fields[m_x + i];
    }

    if(!begin_constraint.empty())
        constraints_container.emplace_back(new Begin_constraint{begin_constraint});
}

void Constraints::create_vertical_end_constraint()
{
    std::string end_constraint;
    for(std::size_t i = m_y + (m_word_length * m_width); i < m_height * m_width; i += m_width)
    {
        if(m_fields[m_x + i] == Board::EMPTY_FIELD)
            break;

        end_constraint += m_fields[m_x + i];
    }

    if(!end_constraint.empty())
        constraints_container.emplace_back(new End_constraint{end_constraint});
}

void Constraints::create_vertical_path_constraint()
{
    std::string path_constraint;
    bool is_path_clear = true;
    for(std::size_t i = 0; i < m_word_length; ++i)
    {
        if(m_fields[m_x + m_y + (i * m_width)] != Board::EMPTY_FIELD)
            is_path_clear = false;
        path_constraint += m_fields[m_x + m_y + (i * m_width)];
    }

    if(is_path_clear)   // If no letter was found on a path, clear string so that redundant
        path_constraint.clear();    // constraint is not kept.

    if(!path_constraint.empty())
        constraints_container.emplace_back(new Path_constraint{path_constraint});
}
/*
std::pair<
std::vector<std::pair<std::string, std::size_t>>,
std::vector<std::pair<std::string, std::size_t>>>
create_vertical_sides_constraint(std::size_t x,std::size_t y,
        std::size_t m_word_length) const
{
    std::vector<std::pair<std::string, std::size_t>> up_or_left_constr, down_or_right_constr;

    for(std::size_t letter_pos = 0; letter_pos < m_word_length; ++letter_pos)
    {
        std::string constr;
        for(int shift = 1, expr; ((expr = m_x + m_y - shift + (letter_pos * m_width)) + 1) % m_width != 0 ; ++shift)
        {
            if(m_fields[expr] != Board::EMPTY_FIELD)
                constr += m_fields[expr];
            else
                break;
        }
        if(!constr.empty())
            up_or_left_constr.push_back(std::make_pair(constr, letter_pos));

        constr.clear();
        for(std::size_t shift = 1, expr; (expr = m_x + m_y + shift + (letter_pos * m_width)) % m_width != 0; ++shift)
        {
            if(m_fields[expr] != Board::EMPTY_FIELD)
                constr += m_fields[expr];
            else
                break;
        }
        if(!constr.empty())
            down_or_right_constr.push_back(std::make_pair(constr, letter_pos));
    }

    return std::make_pair(up_or_left_constr, down_or_right_constr);
}
*/
std::string Path_constraint::create_word(const std::string& word) const
{
    std::string composed_word;
    return composed_word;
}

std::string Begin_constraint::create_word(const std::string& word) const
{
    std::string composed_word;
    return composed_word;
}

std::string End_constraint::create_word(const std::string& word) const
{
    std::string composed_word;
    return composed_word;
}

std::string Up_left_constraint::create_word(const std::string& word) const
{
    std::string composed_word;
    return composed_word;
}

std::string Down_right_constraint::create_word(const std::string& word) const
{
    std::string composed_word;
    return composed_word;
}

