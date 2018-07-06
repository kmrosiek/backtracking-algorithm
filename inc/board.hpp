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
#pragma once

#include "word_footprint.hpp"

#include <vector>
#include <string>
#include <stdint.h>


class Board
{
    public:
        /// Defines character which will be placed on the board when field is empty.
        constexpr static char EMPTY_FIELD = '~';
        /// Used to determine a direction of the word on the board.
        constexpr static uint32_t HORIZONTAL = 0;
        /// Used to determine a direction of the word on the board.
        constexpr static uint32_t VERTICAL = 1;

        /** @brief Resizes vector of fields to board size. Fields are assigned with '~' character.
         *  @param w - board width given in letters.
         *  @param h - board height given in letters.
         */
        Board(const uint32_t, const uint32_t);
        //using Constraints = std::vector<std::unique_ptr<Constraint>>;
        //Constraints create_constraints(const Word_footprint) const;
        /// Inserts a given word into the board in a given footprint(Word_footprint).
        void insert_word(const std::string&, const Word_footprint&);
        /// Removes word from the board.
        void remove_word(const Word_footprint&);

        /** @brief Allows to get the board in a form of a sequence of characters.
         *  @return Vector of characters, containing m_width * m_height characters.
         *  In order to print the board properly m_width will be needed.
         */
        std::vector<char> get_printable() const;
        /// @return m_width - the board width, number of characters in a row.
        uint32_t get_width() const noexcept { return m_width;}

    private:
        /** @brief Describes a single field on the board.
         *  Each field can contain a character and number of times the character was placed there.
         *  The character will be placed twice e.g. on word crossing.<br>
         *  - c -<br>
         *  c a t<br>
         *  - r -<br>
         *  The middle field with the character 'a' will have counter = 2.
         */
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

        /* Fields on the board. Number of fields = m_width * m_height. When the board is created
         * fields are filled with EMPTY_BOARD character.
         */
        std::vector<Field> m_fields;

        /// The board width  - number of characters in a row.
        uint32_t m_width;
        /// The board height - number of characters in a column.
        uint32_t m_height;
};

