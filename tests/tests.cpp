#include "dictionary.hpp"
#include "board.hpp"
#include "word_footprint.hpp"

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


TEST(BoardClass, get_printable)
{
    Board board(4, 4);
    std::vector<char> printable_board;
    printable_board = board.get_printable();

    std::string actual_board = printable_to_string(printable_board);

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
    ASSERT_EQ(Board::EMPTY_FIELD, '~');

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

    std::vector<char> printable_board = board.get_printable();
    std::string output = printable_to_string(printable_board);

    EXPECT_STREQ("~Car~~~~o~~~~u~~~~n~~~~dx", output.c_str());
}

TEST(BoardClass, remove_word)
{
    ASSERT_EQ(Board::EMPTY_FIELD, '~');

    Board board(5, 5);
    board.insert_word("Ink", Word_footprint(0,0,3));
    board.insert_word("kart", Word_footprint(2,1,4));
    board.insert_word("arr", Word_footprint(11,0,3));
    board.insert_word("matma", Word_footprint(15,0,5));

    std::vector<char> printable_board = board.get_printable();
    std::string output = printable_to_string(printable_board);

    EXPECT_STREQ("Ink~~~~a~~~arr~matma~~~~~", output.c_str());

    board.remove_word(Word_footprint(2, 1, 4));
    board.remove_word(Word_footprint(15, 0, 5));

    board.insert_word("ebook", Word_footprint(4, 1, 5));
    board.insert_word("spark", Word_footprint(20, 0, 5));

    board.remove_word(Word_footprint(4, 1, 5));
    board.remove_word(Word_footprint(20, 0, 5));

    printable_board = board.get_printable();
    output = printable_to_string(printable_board);

    EXPECT_STREQ("Ink~~~~~~~~arr~~~~~~~~~~~", output.c_str());

}

/** Tests if empty board produces no constraints for a given word.
 */
TEST(BoardClass, create_constraints_empty_board)
{
    ASSERT_EQ(Board::EMPTY_FIELD, '~');

    Board board(5, 5);
    Constraints constraints(Word_footprint(5, Board::HORIZONTAL, 5), board.get_printable(),
            board.get_width());

}
/** a s - -
 *  $ - - -
 *  $ - - -
 *  $ - - -
 */
/*TEST(BoardClass, create_begin_constraints)
{
    ASSERT_EQ(Board::EMPTY_FIELD, '~');
    using Word_footprint = std::tuple<uint32_t, uint32_t, uint32_t>;
    using Constraints = std::vector<std::unique_ptr<Constraint>>;

    Board board(4, 4);
    board.insert_word("as", Word_footprint(0, Board::HORIZONTAL, 2));
    Constraints constraints = board.create_constraints(
            Word_footprint(2, Board::HORIZONTAL, 2));

    EXPECT_EQ(constraints.size(), 1);
    std::cout << typeid(constraints.at(0)).name() << std::endl;

    //std::vector<std::vector<char>> printable_board = board.get_printable();
    //std::string output = printable_to_string(printable_board);

    //EXPECT_STREQ("~~t", output.c_str());
}*/

/*TEST(BoardClass, create_begin_constraints_vert)
{
    ASSERT_EQ(Board::EMPTY_FIELD, '~');
    using Word_footprint = std::tuple<uint32_t, uint32_t, uint32_t>;
    using Constraints = std::vector<std::unique_ptr<Constraint>>;

    Board board(4, 4);
    board.insert_word("as", Word_footprint(0, Board::VERTICAL, 2));
    Constraints constraints = board.create_constraints(
            Word_footprint(8, Board::VERTICAL, 2));

    EXPECT_EQ(constraints.size(), 1);
    std::cout << typeid(constraints.at(0)).name() << std::endl;

    //std::vector<std::vector<char>> printable_board = board.get_printable();
    //std::string output = printable_to_string(printable_board);

    //EXPECT_STREQ("~~t", output.c_str());
}


TEST(BoardClass, create_constraints)
{
    ASSERT_EQ(Board::EMPTY_FIELD, '~');
    using Word_footprint = std::tuple<uint32_t, uint32_t, uint32_t>;
    using Constraints = std::vector<std::unique_ptr<Constraint>>;

    Board board(5, 5);
    board.insert_word("this", Word_footprint(2, Board::VERTICAL, 4));
    Constraints constraints = board.create_constraints(
            Word_footprint(5, Board::HORIZONTAL, 5));

    EXPECT_EQ(constraints.size(), 1);
    std::cout << typeid(constraints.at(0)).name() << std::endl;

    //std::vector<std::vector<char>> printable_board = board.get_printable();
    //std::string output = printable_to_string(printable_board);

    //EXPECT_STREQ("~~t", output.c_str());
}

TEST(BoardClass, create_constraintsaa)
{
    ASSERT_EQ(Board::EMPTY_FIELD, '~');
    using Word_footprint = std::tuple<uint32_t, uint32_t, uint32_t>;
    using Constraints = std::vector<std::unique_ptr<Constraint>>;

    Board board(5, 5);
    board.insert_word("to~ls", Word_footprint(0, Board::HORIZONTAL, 5));
    board.insert_word("am~go", Word_footprint(5, Board::HORIZONTAL, 5));
    board.insert_word("~~~~~", Word_footprint(10, Board::HORIZONTAL, 5));
    board.insert_word("pu~ls", Word_footprint(15, Board::HORIZONTAL, 5));
    board.insert_word("tr~ge", Word_footprint(20, Board::HORIZONTAL, 5));
    Constraints constraints = board.create_constraints(
            Word_footprint(7, Board::HORIZONTAL, 2));
    //constraints = board.create_constraints(Word_footprint(20, Board::HORIZONTAL, 5));
    //constraints = board.create_constraints(Word_footprint(4, Board::VERTICAL, 2));
    //constraints = board.create_constraints(Word_footprint(13, Board::VERTICAL, 2));

    EXPECT_EQ(constraints.size(), 1);
    for(auto& c : constraints)
    std::cout << typeid(*c).name() << std::endl;

    //std::vector<std::vector<char>> printable_board = board.get_printable();
    //std::string output = printable_to_string(printable_board);

    //EXPECT_STREQ("~~t", output.c_str());
}*/
