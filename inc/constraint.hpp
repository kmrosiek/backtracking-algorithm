#pragma once

#include "word_footprint.hpp"

#include <string>
#include <vector>
#include <memory>

class Dictionary;

class Base_constraint
{
    public:
        Base_constraint(const std::string& s) : m_constraint(s){}
        virtual std::string create_word(const std::string&) const = 0;
        virtual ~Base_constraint(){}
    protected:
        std::string m_constraint;
};

class Constraints
{
    public:
        Constraints(const Word_footprint&, const std::vector<char>, const std::size_t);
        using Dictionary_lookup = bool (*)(const Dictionary&, const std::string&);
        bool check_constraint(Dictionary_lookup, const Dictionary&, const std::string&) const;

    private:
        void create_constraints();
        void create_horizontal_begin_constraint();
        void create_horizontal_end_constraint();
        void create_horizontal_path_constraint();
        void create_horizontal_sides_constraint();

        void create_vertical_begin_constraint();
        void create_vertical_end_constraint();
        void create_vertical_path_constraint();
        void create_vertical_sides_constraint();

        std::vector<std::unique_ptr<Base_constraint>> m_constraints_container;

        uint32_t m_x;
        uint32_t m_y;
        uint32_t m_direction;
        uint32_t m_word_length;
        uint32_t m_width;
        uint32_t m_height;

        std::vector<char> m_fields;
};

class Path_constraint : public Base_constraint
{
    public:
        Path_constraint(const std::string& s) : Base_constraint(s){}
        std::string create_word(const std::string&) const;
};

class Begin_constraint : public Base_constraint
{
    public:
        Begin_constraint(const std::string& s) :
            Base_constraint(std::string(s.rbegin(), s.rend())){} // Reverse the input.
        std::string create_word(const std::string&) const;
};
class End_constraint : public Base_constraint
{
    public:
        End_constraint(const std::string& s) : Base_constraint(s){}
        std::string create_word(const std::string&) const;
};

class Positioned_constraint
{
    protected:
        std::size_t m_position;
};

class Up_left_constraint : public Base_constraint, public Positioned_constraint
{
    public:
        Up_left_constraint(const std::string& s, const std::size_t pos) :
            Base_constraint(std::string(s.rbegin(), s.rend())) // Reverse the input.
        {
            m_position = pos;
        }
        std::string create_word(const std::string&) const;
};

class Down_right_constraint : public Base_constraint, Positioned_constraint
{
    public:
        Down_right_constraint(const std::string& s, const std::size_t pos) : Base_constraint(s)
        {
            m_position = pos;
        }
        std::string create_word(const std::string&) const;
};
