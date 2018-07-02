/**
 * @class Board
 * Allows to create a board which consists of width*height characters.
 * User can insert and remove words. Constraints can be also created based on what is already
 * on the board.
 * @code
 * Board board(5, 6);
 * word_data word_footprint = word_data(10,0,3);
 * board.insert_word("car", word_footprint);
 * word_data word_footprint = word_data(2,1,4);
 * board.insert_word("rand", word_footprint);
 * std::vector<std::vector<char>> printable_board = board.get_printable();
 * for(std::vector v : printable_board
 * @endcode
 * @example board_example.cpp
 */
#include <vector>
#include <tuple>
#include <string>
#include <stdint.h>

#include "constraint.hpp"

class Board
{
    public:
        /// Defines character which will be placed on the board when field is empty.
        constexpr static char EMPTY_FIELD = '~';
        /// Used to determine a direction of the word on the board.
        constexpr static uint32_t HORIZONTAL = 0;
        /// Used to determine a direction of the word on the board.
        constexpr static uint32_t VERTICAL = 1;
        /** Describes word footprint - a place on the board where the word will be placed.
         *  @param position in letter units.
         *  @param direction horizontal = 0 or vertical = 1.
         *  @param word_length
         */
        using Word_footprint = std::tuple<uint32_t, uint32_t, uint32_t>;
        /** @brief Resizes vector of fields to board size. Fields are assigned with '~' character.
         *  @param w - board width given in letters.
         *  @param h - board height given in letters.
         */
        Board(const uint32_t, const uint32_t);
        std::vector<Constraint> create_constraints_for_word_footprint(const Word_footprint);
        /// Inserts a given word into the board in a given footprint(Word_footprint).
        void insert_word(const std::string&, const Word_footprint);
        /// Removes word from the board.
        void remove_word(const Word_footprint);
        /** @brief Allows to get the board in a form of set of characters.
         *  @return Vector of vectors of characters, where main vector contains columns
         *  and vectors contain rows. If the board is of size 3x4 then the main vector will be
         *  of size 4 (containing 4 vectors). Each sub vector will contain 3 characters.<br>
         *  x x x<br>
         *  x x x<br>
         *  x x x<br>
         *  x x x<br>
         */
        std::vector<std::vector<char>> get_printable();

    private:
        struct Field
        {
            Field()
            {
                character = EMPTY_FIELD;
                counter = 0;
            }
            char character;
            uint32_t counter;
        };

        std::vector<Field> m_fields;

        uint32_t m_width;
        uint32_t m_height;

};

