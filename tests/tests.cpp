#include "dictionary.hpp"
#include "board.hpp"
#include "word_footprint.hpp"
#include "constraint.hpp"

#include <gtest/gtest.h>
#include <string>


/*--------------------------------------------------------------------------------
------------------------DICTIONARY-CLASS-TESTS------------------------------------
--------------------------------------------------------------------------------*/

/*
 * Tests if does_word_exist function returns false
 * for empty map.
 */
TEST(DictionaryClass, does_word_exist_empty_map)
{
    Dictionary dictionary;
    ASSERT_FALSE(dictionary.does_word_exist("hello"));
}

/*
 * Tests if insert_word works. Tests for lowercase and capital letters.
 * Also for the same and different string sizes.
 */
TEST(DictionaryClass, insert_word)
{
    Dictionary dictionary;
    dictionary.insert_word("hello");
    EXPECT_TRUE(dictionary.does_word_exist("hello"));
    dictionary.insert_word("Abrakadabra");
    EXPECT_TRUE(dictionary.does_word_exist("Abrakadabra"));
    dictionary.insert_word("Abrakadabra");
    EXPECT_TRUE(dictionary.does_word_exist("Abrakadabra"));
    dictionary.insert_word("hello");
    EXPECT_TRUE(dictionary.does_word_exist("hello"));
    EXPECT_FALSE(dictionary.does_word_exist("Hello"));
    EXPECT_TRUE(dictionary.does_word_exist("Abrakadabra"));
}

TEST(DictionaryClass, remove_word)
{
    Dictionary dictionary;
    dictionary.insert_word("hello");
    dictionary.insert_word("Hello");
    dictionary.insert_word("Mega");
    EXPECT_TRUE(dictionary.does_word_exist("hello"));
    EXPECT_TRUE(dictionary.does_word_exist("Hello"));
    EXPECT_TRUE(dictionary.does_word_exist("Mega"));
    dictionary.remove_word("hello");
    dictionary.remove_word("Hello");
    dictionary.remove_word("Mega");
    EXPECT_FALSE(dictionary.does_word_exist("hello"));
    EXPECT_FALSE(dictionary.does_word_exist("Hello"));
    EXPECT_FALSE(dictionary.does_word_exist("Mega"));
}

TEST(DictionaryClass, load_words_from_file)
{
    Dictionary dictionary;
    dictionary.load_words_from_file("../resource/lemma.al");
}

/*--------------------------------------------------------------------------------
----------------------------BOARD-CLASS-TESTS-------------------------------------
--------------------------------------------------------------------------------*/

/** @brief Allows to convert get_printable to string. It lets you compare the board with
 * a given string and perform tests.
 */
std::string printable_to_string(const std::vector<char>& printable)
{
    std::string output;
    for(const char& c : printable)
        output += c;

    return output;
}

/** Almost all tests for board class depened upon Board::EMPTY_FIELD variable, therefore
 *  this test has to success in order to process following tests.
 */
TEST(BoardClass, initial_test)
{
    ASSERT_EQ(Board::EMPTY_FIELD, '~');
}

/** Checks if board.get_printable function prints empty board correctly.
 */
TEST(BoardClass, get_printable)
{
    Board board(4, 4);
    std::string actual_board = printable_to_string(board.get_printable());

    EXPECT_STREQ("~~~~~~~~~~~~~~~~", actual_board.c_str());
}
/*
 * Test for Board::insert_word. Tests if the function does not insert when:
 * - word footprint is different from word.
 * - word would go out of borders.
 * - direction is different from 0 and 1.
 * Tests if vertical and horizontal words will be inserted.
 */
TEST(BoardClass, insert_word)
{
    Board board(5, 5);
    // Word size is larger than one in footprint.
    board.insert_word("ThisIsTooLong", Word_footprint(1,0,3));
    // No string was given.
    board.insert_word("", Word_footprint(1,0,3));
    // "Car" should work.
    board.insert_word("Car", Word_footprint(1,0,3));
    // Round should work.
    board.insert_word("round", Word_footprint(3,1,5));
    // Direction(second param) is wrong.
    board.insert_word("round", Word_footprint(3,4,5));
    // Text would go out of border.
    board.insert_word("border", Word_footprint(3,0,6));
    // Text would go out of border.
    board.insert_word("out", Word_footprint(24,0,3));
    // Single letter in last square should work.
    board.insert_word("z", Word_footprint(24,0,1));
    // Single letter in last square should work.
    board.insert_word("x", Word_footprint(24,1,1));

    std::string output = printable_to_string(board.get_printable());

    EXPECT_STREQ("~Car~~~~o~~~~u~~~~n~~~~dx", output.c_str());
}

TEST(BoardClass, remove_word)
{
    Board board(5, 5);
    board.insert_word("Ink", Word_footprint(0,0,3));
    board.insert_word("kart", Word_footprint(2,1,4));
    board.insert_word("arr", Word_footprint(11,0,3));
    board.insert_word("matma", Word_footprint(15,0,5));

    std::string output = printable_to_string(board.get_printable());

    EXPECT_STREQ("Ink~~~~a~~~arr~matma~~~~~", output.c_str());

    board.remove_word(Word_footprint(2, 1, 4));
    board.remove_word(Word_footprint(15, 0, 5));

    board.insert_word("ebook", Word_footprint(4, 1, 5));
    board.insert_word("spark", Word_footprint(20, 0, 5));

    board.remove_word(Word_footprint(4, 1, 5));
    board.remove_word(Word_footprint(20, 0, 5));

    output = printable_to_string(board.get_printable());

    EXPECT_STREQ("Ink~~~~~~~~arr~~~~~~~~~~~", output.c_str());

}

/*--------------------------------------------------------------------------------
------------------------CONSTRAINTS-CLASS-TESTS------------------------------------
--------------------------------------------------------------------------------*/

/** Allows to test check_constraint functionality.
 */
bool intermediate_for_tests(const Dictionary& dic, const std::string& word)
{
    return dic.does_word_exist(word);
}

/** Almost all tests for board class depened upon Board::EMPTY_FIELD variable, therefore
 *  this test has to success in order to process following tests.
 */
TEST(ConstraintsClass, initial_test)
{
    ASSERT_EQ(Board::EMPTY_FIELD, '~');
}

/** Tests if empty board produces no constraints for a given word.
 *  Checking constraint should return true for whatever word.
 */
TEST(ConstraintsClass, create_constraints_empty_board)
{
    Board board(5, 5);
    Dictionary dic;
    Constraints constraints(Word_footprint(5, Board::HORIZONTAL, 5), board.get_printable(),
            board.get_width());
    EXPECT_TRUE(constraints.check_constraint(intermediate_for_tests, dic, "those"));

    dic.insert_word("those");
    Constraints constraints2(Word_footprint(5, Board::HORIZONTAL, 5), board.get_printable(),
            board.get_width());
    EXPECT_TRUE(constraints2.check_constraint(intermediate_for_tests, dic, "those"));
}

TEST(ConstraintsClass, create_begin_constraints_horizontal)
{
    Dictionary dic;
    dic.insert_word("angel");
    Board board(5, 5);

    // ---- Horizontal left-top corner test
    board.insert_word("an", Word_footprint(0, Board::HORIZONTAL, 2));
    {
        Constraints constraints(Word_footprint(2, Board::HORIZONTAL, 2), board.get_printable(),
                board.get_width());

        EXPECT_FALSE(constraints.check_constraint(intermediate_for_tests, dic, "ant"));
        EXPECT_TRUE(constraints.check_constraint(intermediate_for_tests, dic, "gel"));
    }

    // ---- horizontal left-bottom corner test

    board.insert_word("an", Word_footprint(20, Board::HORIZONTAL, 2));
    {
        Constraints constraints(Word_footprint(22, Board::HORIZONTAL, 2), board.get_printable(),
                board.get_width());

        EXPECT_FALSE(constraints.check_constraint(intermediate_for_tests, dic, "ant"));
        EXPECT_TRUE(constraints.check_constraint(intermediate_for_tests, dic, "gel"));
    }

    // ---- horizontal not continuous constraint.

    dic.insert_word("tgel");
    board.insert_word("a~t", Word_footprint(15, Board::HORIZONTAL, 3));
    {
        Constraints constraints(Word_footprint(18, Board::HORIZONTAL, 2), board.get_printable(),
                board.get_width());

        EXPECT_FALSE(constraints.check_constraint(intermediate_for_tests, dic, "ant"));
        EXPECT_TRUE(constraints.check_constraint(intermediate_for_tests, dic, "gel"));
    }

    // ---- horizontal long constraint

    dic.insert_word("helps");
    board.insert_word("help", Word_footprint(10, Board::HORIZONTAL, 4));
    {
        Constraints constraints(Word_footprint(14, Board::HORIZONTAL, 1), board.get_printable(),
                board.get_width());

        EXPECT_FALSE(constraints.check_constraint(intermediate_for_tests, dic, "x"));
        EXPECT_TRUE(constraints.check_constraint(intermediate_for_tests, dic, "s"));
    }
}

TEST(ConstraintsClass, create_begin_constraints_vertical)
{
    Dictionary dic;
    dic.insert_word("angel");
    Board board(5, 5);

    // ---- vertical left-top corner test

    board.insert_word("an", Word_footprint(0, Board::VERTICAL, 2));
    {
        Constraints constraints(Word_footprint(10, Board::VERTICAL, 2), board.get_printable(),
                board.get_width());

        EXPECT_FALSE(constraints.check_constraint(intermediate_for_tests, dic, "ant"));
        EXPECT_TRUE(constraints.check_constraint(intermediate_for_tests, dic, "gel"));
    }

    // ---- vertical right-top corner test

    board.insert_word("an", Word_footprint(4, Board::VERTICAL, 2));
    {
        Constraints constraints(Word_footprint(14, Board::VERTICAL, 2), board.get_printable(),
                board.get_width());

        EXPECT_FALSE(constraints.check_constraint(intermediate_for_tests, dic, "ant"));
        EXPECT_TRUE(constraints.check_constraint(intermediate_for_tests, dic, "gel"));
    }

    // ---- vertical not continuous constraint

    dic.insert_word("ngel");
    board.insert_word("a~n", Word_footprint(2, Board::VERTICAL, 3));
    {
        Constraints constraints(Word_footprint(17, Board::VERTICAL, 2), board.get_printable(),
                board.get_width());

        EXPECT_FALSE(constraints.check_constraint(intermediate_for_tests, dic, "ant"));
        EXPECT_TRUE(constraints.check_constraint(intermediate_for_tests, dic, "gel"));
    }

    // ---- vertical long constraint

    dic.insert_word("thiss");
    board.insert_word("this", Word_footprint(1, Board::VERTICAL, 4));
    {
        Constraints constraints(Word_footprint(21, Board::VERTICAL, 1), board.get_printable(),
                board.get_width());

        EXPECT_FALSE(constraints.check_constraint(intermediate_for_tests, dic, "a"));
        EXPECT_TRUE(constraints.check_constraint(intermediate_for_tests, dic, "s"));
    }
}

TEST(ConstraintsClass, create_end_constraints_horizontal)
{
    Dictionary dic;
    dic.insert_word("route");
    Board board(5, 5);

    // ---- Horizontal right-top corner test
    board.insert_word("te", Word_footprint(3, Board::HORIZONTAL, 2));
    {
        Constraints constraints(Word_footprint(0, Board::HORIZONTAL, 3), board.get_printable(),
                board.get_width());

        EXPECT_FALSE(constraints.check_constraint(intermediate_for_tests, dic, "hit"));
        EXPECT_TRUE(constraints.check_constraint(intermediate_for_tests, dic, "rou"));
    }

    // ---- horizontal right-bottom corner test

    dic.insert_word("shete");
    board.insert_word("te", Word_footprint(23, Board::HORIZONTAL, 2));
    {
        Constraints constraints(Word_footprint(20, Board::HORIZONTAL, 3), board.get_printable(),
                board.get_width());

        EXPECT_FALSE(constraints.check_constraint(intermediate_for_tests, dic, "pul"));
        EXPECT_TRUE(constraints.check_constraint(intermediate_for_tests, dic, "she"));
    }

    // ---- horizontal not continuous constraint.

    dic.insert_word("na");
    board.insert_word("a~t", Word_footprint(17, Board::HORIZONTAL, 3));
    {
        Constraints constraints(Word_footprint(16, Board::HORIZONTAL, 1), board.get_printable(),
                board.get_width());

        EXPECT_FALSE(constraints.check_constraint(intermediate_for_tests, dic, "p"));
        EXPECT_TRUE(constraints.check_constraint(intermediate_for_tests, dic, "n"));
    }

    // ---- horizontal long constraint

    dic.insert_word("shelp");
    board.insert_word("help", Word_footprint(11, Board::HORIZONTAL, 4));
    {
        Constraints constraints(Word_footprint(10, Board::HORIZONTAL, 1), board.get_printable(),
                board.get_width());

        EXPECT_FALSE(constraints.check_constraint(intermediate_for_tests, dic, "x"));
        EXPECT_TRUE(constraints.check_constraint(intermediate_for_tests, dic, "s"));
    }
}

TEST(ConstraintsClass, create_end_constraints_vertical)
{
    Dictionary dic;
    dic.insert_word("angel");
    Board board(5, 5);

    // ---- vertical left-bottom corner test

    board.insert_word("el", Word_footprint(15, Board::VERTICAL, 2));
    {
        Constraints constraints(Word_footprint(0, Board::VERTICAL, 3), board.get_printable(),
                board.get_width());

        EXPECT_FALSE(constraints.check_constraint(intermediate_for_tests, dic, "ant"));
        EXPECT_TRUE(constraints.check_constraint(intermediate_for_tests, dic, "ang"));
    }

    // ---- vertical right-bottom corner test

    dic.insert_word("ngel");
    board.insert_word("el", Word_footprint(19, Board::VERTICAL, 2));
    {
        Constraints constraints(Word_footprint(9, Board::VERTICAL, 2), board.get_printable(),
                board.get_width());

        EXPECT_FALSE(constraints.check_constraint(intermediate_for_tests, dic, "nt"));
        EXPECT_TRUE(constraints.check_constraint(intermediate_for_tests, dic, "ng"));
    }

    // ---- vertical not continuous constraint

    dic.insert_word("ala");
    board.insert_word("a~n", Word_footprint(12, Board::VERTICAL, 3));
    {
        Constraints constraints(Word_footprint(2, Board::VERTICAL, 2), board.get_printable(),
                board.get_width());

        EXPECT_FALSE(constraints.check_constraint(intermediate_for_tests, dic, "fr"));
        EXPECT_TRUE(constraints.check_constraint(intermediate_for_tests, dic, "al"));
    }

    // ---- vertical long constraint

    dic.insert_word("xthis");
    board.insert_word("this", Word_footprint(8, Board::VERTICAL, 4));
    {
        Constraints constraints(Word_footprint(3, Board::VERTICAL, 1), board.get_printable(),
                board.get_width());

        EXPECT_FALSE(constraints.check_constraint(intermediate_for_tests, dic, "a"));
        EXPECT_TRUE(constraints.check_constraint(intermediate_for_tests, dic, "x"));
    }
}

TEST(ConstraintsClass, create_path_constraints_horizontal)
{
    Dictionary dic;
    Board board(5, 9);

    // ---- horizontal single path test

    dic.insert_word("dod");
    board.insert_word("o", Word_footprint(2, Board::HORIZONTAL, 1));
    {
        Constraints constraints(Word_footprint(1, Board::HORIZONTAL, 3), board.get_printable(),
                board.get_width());

        EXPECT_FALSE(constraints.check_constraint(intermediate_for_tests, dic, "xax"));
        EXPECT_FALSE(constraints.check_constraint(intermediate_for_tests, dic, "xox"));
        EXPECT_TRUE(constraints.check_constraint(intermediate_for_tests, dic, "dod"));
    }

    // ---- horizontal double path test

    dic.insert_word("hello");
    board.insert_word("e", Word_footprint(11, Board::HORIZONTAL, 1));
    board.insert_word("l", Word_footprint(13, Board::HORIZONTAL, 1));
    {
        Constraints constraints(Word_footprint(10, Board::HORIZONTAL, 5), board.get_printable(),
                board.get_width());

        EXPECT_FALSE(constraints.check_constraint(intermediate_for_tests, dic, "jacek"));
        EXPECT_FALSE(constraints.check_constraint(intermediate_for_tests, dic, "mello"));
        EXPECT_TRUE(constraints.check_constraint(intermediate_for_tests, dic, "hello"));
    }


    // ---- horizontal double neighbour path test

    board.insert_word("ll", Word_footprint(22, Board::HORIZONTAL, 2));
    {
        Constraints constraints(Word_footprint(20, Board::HORIZONTAL, 5), board.get_printable(),
                board.get_width());

        EXPECT_FALSE(constraints.check_constraint(intermediate_for_tests, dic, "jacek"));
        EXPECT_FALSE(constraints.check_constraint(intermediate_for_tests, dic, "mello"));
        EXPECT_TRUE(constraints.check_constraint(intermediate_for_tests, dic, "hello"));
    }

    // ---- horizontal first and last letter test

    board.insert_word("h", Word_footprint(30, Board::HORIZONTAL, 1));
    board.insert_word("o", Word_footprint(34, Board::HORIZONTAL, 1));
    {
        Constraints constraints(Word_footprint(30, Board::HORIZONTAL, 5), board.get_printable(),
                board.get_width());

        EXPECT_FALSE(constraints.check_constraint(intermediate_for_tests, dic, "jacek"));
        EXPECT_FALSE(constraints.check_constraint(intermediate_for_tests, dic, "mello"));
        EXPECT_TRUE(constraints.check_constraint(intermediate_for_tests, dic, "hello"));
    }

    // ---- horizontal entire path test

    board.insert_word("hello", Word_footprint(40, Board::HORIZONTAL, 5));
    {
        Constraints constraints(Word_footprint(40, Board::HORIZONTAL, 5), board.get_printable(),
                board.get_width());

        EXPECT_FALSE(constraints.check_constraint(intermediate_for_tests, dic, "jacek"));
        EXPECT_FALSE(constraints.check_constraint(intermediate_for_tests, dic, "mello"));
        EXPECT_TRUE(constraints.check_constraint(intermediate_for_tests, dic, "hello"));
    }

}

TEST(ConstraintsClass, create_path_constraints_vertical)
{
    Dictionary dic;
    Board board(9, 5);

    // ---- vertical single path test

    dic.insert_word("dod");
    board.insert_word("o", Word_footprint(18, Board::VERTICAL, 1));
    {
        Constraints constraints(Word_footprint(9, Board::VERTICAL, 3), board.get_printable(),
                board.get_width());

        EXPECT_FALSE(constraints.check_constraint(intermediate_for_tests, dic, "xax"));
        EXPECT_FALSE(constraints.check_constraint(intermediate_for_tests, dic, "xox"));
        EXPECT_TRUE(constraints.check_constraint(intermediate_for_tests, dic, "dod"));
    }

    // ---- vertical double path test

    dic.insert_word("hello");
    board.insert_word("e", Word_footprint(11, Board::VERTICAL, 1));
    board.insert_word("l", Word_footprint(29, Board::VERTICAL, 1));
    {
        Constraints constraints(Word_footprint(2, Board::VERTICAL, 5), board.get_printable(),
                board.get_width());

        EXPECT_FALSE(constraints.check_constraint(intermediate_for_tests, dic, "jacek"));
        EXPECT_FALSE(constraints.check_constraint(intermediate_for_tests, dic, "mello"));
        EXPECT_TRUE(constraints.check_constraint(intermediate_for_tests, dic, "hello"));
    }


    // ---- vertical double neighbour path test

    board.insert_word("ll", Word_footprint(22, Board::VERTICAL, 2));
    {
        Constraints constraints(Word_footprint(4, Board::VERTICAL, 5), board.get_printable(),
                board.get_width());

        EXPECT_FALSE(constraints.check_constraint(intermediate_for_tests, dic, "jacek"));
        EXPECT_FALSE(constraints.check_constraint(intermediate_for_tests, dic, "mello"));
        EXPECT_TRUE(constraints.check_constraint(intermediate_for_tests, dic, "hello"));
    }

    // ---- vertical first and last letter test

    board.insert_word("h", Word_footprint(6, Board::VERTICAL, 1));
    board.insert_word("o", Word_footprint(42, Board::VERTICAL, 1));
    {
        Constraints constraints(Word_footprint(6, Board::VERTICAL, 5), board.get_printable(),
                board.get_width());

        EXPECT_FALSE(constraints.check_constraint(intermediate_for_tests, dic, "jacek"));
        EXPECT_FALSE(constraints.check_constraint(intermediate_for_tests, dic, "mello"));
        EXPECT_TRUE(constraints.check_constraint(intermediate_for_tests, dic, "hello"));
    }

    // ---- vertical entire path test

    board.insert_word("hello", Word_footprint(8, Board::VERTICAL, 5));
    {
        Constraints constraints(Word_footprint(8, Board::VERTICAL, 5), board.get_printable(),
                board.get_width());

        EXPECT_FALSE(constraints.check_constraint(intermediate_for_tests, dic, "jacek"));
        EXPECT_FALSE(constraints.check_constraint(intermediate_for_tests, dic, "mello"));
        EXPECT_TRUE(constraints.check_constraint(intermediate_for_tests, dic, "hello"));
    }

}

void plan_the_board(Board& board, const std::string& plan)
{
    std::size_t row_length = board.get_width();
    for(std::size_t i = 0; i < plan.size() + row_length; i += row_length)
    {
        const std::string row = plan.substr(i, row_length);
        board.insert_word(row, Word_footprint(i, Board::HORIZONTAL, row_length));
    }
}

TEST(ConstraintsClass, create_sides_constraints_horizontal)
{
    Dictionary dic;
    Board board(6, 6);

    plan_the_board(board,   "l~x~~~"
                            "ol~~a~"
                            "~~~~~~"
                            "~~eo~a"
                            "~xn~~n"
                            "x~~l~o");

    dic.insert_word("lol");
    dic.insert_word("le");
    dic.insert_word("ai");
    dic.insert_word("ten");
    dic.insert_word("to");
    dic.insert_word("nano");
    {
        Constraints constraints(Word_footprint(12, Board::HORIZONTAL, 6), board.get_printable(),
                board.get_width());

        EXPECT_FALSE(constraints.check_constraint(intermediate_for_tests, dic, "raone"));
        EXPECT_FALSE(constraints.check_constraint(intermediate_for_tests, dic, "lettix"));
        EXPECT_TRUE(constraints.check_constraint(intermediate_for_tests, dic, "lettin"));
    }
}

TEST(ConstraintsClass, create_sides_constraints_vertical)
{
    Dictionary dic;
    Board board(6, 5);

    // Test scheme
    // o o $ - - -
    // - o $ - - -
    // o - $ o o o
    // - - $ o - -
    // - - $ o o o

    plan_the_board(board,   "xo~~o~"
                            "al~~a~"
                            "x~~doo"
                            "x~~o~a"
                            "~~~lso");

    dic.insert_word("xor");
    dic.insert_word("ala");
    dic.insert_word("odoo");
    dic.insert_word("no");
    dic.insert_word("also");
    {
        Constraints constraints(Word_footprint(2, Board::VERTICAL, 5), board.get_printable(),
                board.get_width());

        EXPECT_FALSE(constraints.check_constraint(intermediate_for_tests, dic, "raone"));
        EXPECT_FALSE(constraints.check_constraint(intermediate_for_tests, dic, "xoaax"));
        EXPECT_TRUE(constraints.check_constraint(intermediate_for_tests, dic, "raona"));
    }
}
