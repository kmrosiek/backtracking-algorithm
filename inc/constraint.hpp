#pragma once

class Constraint
{
    public:
        Constraint(std::string s) : constraint(s){}
        using dictionary_lookup = bool (*)(std::string);
        virtual void check_constraint(dictionary_lookup, std::string) = 0;
        virtual ~Constraint(){}
    protected:
        std::string constraint;
};


class Path_constraint : public Constraint
{
    public:
        Path_constraint(std::string s) : Constraint(s){}
        void check_constraint(dictionary_lookup, std::string)
        {
        }
};

class Begin_constraint : public Constraint
{
    public:
        Begin_constraint(std::string s) : Constraint(s){}
        void check_constraint(dictionary_lookup, std::string)
        {
        }
};
class End_constraint : public Constraint
{
    public:
        End_constraint(std::string s) : Constraint(s){}
        void check_constraint(dictionary_lookup, std::string)
        {
        }
};

class Positioned_constraint
{
    protected:
        std::size_t position;
};

class Up_left_constraint : public Constraint, public Positioned_constraint
{
    public:
        Up_left_constraint(std::string s, std::size_t pos) : Constraint(s)
        {
            position = pos;
        }
        void check_constraint(dictionary_lookup, std::string)
        {
        }
};

class Down_right_constraint : public Constraint, Positioned_constraint
{
    public:
        Down_right_constraint(std::string s, std::size_t pos) : Constraint(s)
        {
            position = pos;
        }
        void check_constraint(dictionary_lookup, std::string)
        {
        }
};
