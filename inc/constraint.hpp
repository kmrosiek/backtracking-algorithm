#pragma once

class Constraint
{
    public:
        using dictionary_lookup = bool (*)(std::string);
        virtual void check_constraint(dictionary_lookup, std::string) = 0;
};

class Single_constraint
{
    protected:
        std::string constraint;
};

class Multiple_constraint
{
    protected:
        std::vector<std::string> constraints;
};

class Path_Constraint : public Constraint, public Single_constraint
{
    public:
        void check_constraint(dictionary_lookup, std::string)
        {
        }
};

class Begin_constraint : public Constraint, public Single_constraint
{
    public:
        void check_constraint(dictionary_lookup, std::string)
        {
        }
};
class End_constraint : public Constraint, public Single_constraint
{
    public:
        void check_constraint(dictionary_lookup, std::string)
        {
        }
};
class Left_side_constraint : public Constraint, public Multiple_constraint
{
    public:
        void check_constraint(dictionary_lookup, std::string)
        {
        }
};
class Right_side_constraint : public Constraint, public Multiple_constraint
{
    public:
        void check_constraint(dictionary_lookup, std::string)
        {
        }
};
