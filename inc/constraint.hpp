#pragma once

#include "word_footprint.hpp"

#include <string>
#include <vector>
#include <memory>

class Dictionary;

class Base_constraint
{
    public:
        Base_constraint(std::string s) : constraint(s){}
        virtual std::string create_word(const std::string&) const = 0;
        virtual ~Base_constraint(){}
    protected:
        std::string constraint;
};

class Constraints
{
    public:
        Constraints(Word_footprint, std::vector<char>, std::size_t);
        using Dictionary_lookup = bool (*)(const Dictionary&, const std::string&);
        bool check_constraint(Dictionary_lookup, const Dictionary&, const std::string&) const;

    private:
        void create_constraints();
        void create_horizontal_begin_constraint();
        void create_horizontal_end_constraint();
        void create_horizontal_path_constraint();

        void create_vertical_begin_constraint();
        void create_vertical_end_constraint();
        void create_vertical_path_constraint();

        std::vector<std::unique_ptr<Base_constraint>> constraints_container;

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
        Path_constraint(std::string s) : Base_constraint(s){}
        std::string create_word(const std::string&) const;
};

class Begin_constraint : public Base_constraint
{
    public:
        Begin_constraint(std::string s) : Base_constraint(s){}
        std::string create_word(const std::string&) const;
};
class End_constraint : public Base_constraint
{
    public:
        End_constraint(std::string s) : Base_constraint(s){}
        std::string create_word(const std::string&) const;
};

class Positioned_constraint
{
    protected:
        std::size_t position;
};

class Up_left_constraint : public Base_constraint, public Positioned_constraint
{
    public:
        Up_left_constraint(std::string s, std::size_t pos) : Base_constraint(s)
        {
            position = pos;
        }
        std::string create_word(const std::string&) const;
};

class Down_right_constraint : public Base_constraint, Positioned_constraint
{
    public:
        Down_right_constraint(std::string s, std::size_t pos) : Base_constraint(s)
        {
            position = pos;
        }
        std::string create_word(const std::string&) const;
};
