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

/** @brief Contains all constraints for a given board and a given word_footprint.
 *  Allows to test whether particular word satisfies constraints for a given dictionary.
 */
class Constraints
{
    public:
        /** @brief Creates constarints for a given board and a given word footprint.
         *  @param footprint - the place where the word would be inserted.
         *  @param vec<char> - the board in a sequence of characters.
         *  @param board_width - the board width in a character units.
         */
        Constraints(const Word_footprint&, const std::vector<char>, const std::size_t);
        using Dictionary_lookup = bool (*)(const Dictionary&, const std::string&);

        /** @brief checks whether a given word satisfies constraints in a given dictionary.
         *  Allows to test if a word created from a given word and added constraints exists
         *  in a dictionary. E.g. If begin_constraint: "pre" and the given word: "bin", then
         *  the word "prebin" has to exist in dictionary for the constraints to be satisfied.
         *  @param Function that will check if the word exists in a dictionary
         *  @param The dictionary.
         *  @param word to be tested.
         *  @return true if the constraint is satisfied, false if the constraint is not satisfied.
         */
        bool check_constraint(Dictionary_lookup, const Dictionary&, const std::string&) const;

    private:
        /** @brief runs all following create_ methods depending on direction(horizon, vertical)
         */
        void create_constraints();
        void create_horizontal_begin_constraint();
        void create_horizontal_end_constraint();
        void create_horizontal_path_constraint();
        void create_horizontal_sides_and_crossing_constraint();

        void create_vertical_begin_constraint();
        void create_vertical_end_constraint();
        void create_vertical_path_constraint();
        void create_vertical_sides_and_crossing_constraint();

        /// Contains all constraints that were created for a given board and a given footprint.
        std::vector<std::unique_ptr<Base_constraint>> m_constraints_container;

        /// x position of the first character of the word footprint. Range(0, board.width)
        uint32_t m_x;

        /// y position of the first character of the word footprint. Is a multiple of board.width.
        uint32_t m_y;

        /// The direction of footprint. Can be horizontal or vertical.
        uint32_t m_direction;

        /// The word footprint length.
        uint32_t m_word_length;

        /// The board width.
        uint32_t m_width;

        /// The board height.
        uint32_t m_height;

        /// All characters of the board.
        std::vector<char> m_fields;
};

/** @brief Letters that appear on the word footprint will create a path_constraint.
 *  Example:<br>
 *  - - - - - - -<br>
 *  - $ o - a - %<br>
 *  - - - - - - -<br>
 *  If the footprint starts at $ and ends at %, then the path constraint would be ("~o~a~~").
 *  For constraint to be satisfied, the inserted word would have to have 'o' as the second letter and
 *  a as 'a' fourth letter.
 */
class Path_constraint : public Base_constraint
{
    public:
        Path_constraint(const std::string& s) : Base_constraint(s){}
        std::string create_word(const std::string&) const;
};

/// @brief Created from letters that appear before the word footprint.
class Begin_constraint : public Base_constraint
{
    public:
        Begin_constraint(const std::string& s) :
            Base_constraint(s){}
        std::string create_word(const std::string&) const;
};

/// @brief Created from letters that appear after the word footprint.
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

/** @brief Created from letters that appear on both sides of the word at the same letter(position).
 *  Example:<br>
 *  - - $ - -<br>
 *  a l - h a<br>
 *  - - % - -<br>
 *  "al-ha" is the constraint.
 */
class Crossing_constraint : public Base_constraint, public Positioned_constraint
{
    public:
        Crossing_constraint(const std::string& begin, const std::string& end,
                const std::size_t pos) : Base_constraint(begin)
        {
            m_position = pos;
            m_ending = end;
        }
        std::string create_word(const std::string&) const;
    private:
        std::string m_ending;
};

/** Created from letters that appear on the left or above the footprint (Assuming no letters below
*   or on the right at the same position. Example:<br>
 *  - - a - -<br>
 *  - - l - -<br>
 *  $ - - % -<br>
 *  "al" is the constraint.
*/
class Up_left_constraint : public Base_constraint, public Positioned_constraint
{
    public:
        Up_left_constraint(const std::string& s, const std::size_t pos) :
            Base_constraint(s)
        {
            m_position = pos;
        }
        std::string create_word(const std::string&) const;
};

/** Created from letters that appear below or on the right of the footprint. Assuming no letters
 *  above or on the left at the same position.
 *  - - $ - -<br>
 *  - - - h a<br>
 *  - - % - -<br>
 *  "ha" is the constraint.
 */
class Down_right_constraint : public Base_constraint, Positioned_constraint
{
    public:
        Down_right_constraint(const std::string& s, const std::size_t pos) : Base_constraint(s)
        {
            m_position = pos;
        }
        std::string create_word(const std::string&) const;
};
