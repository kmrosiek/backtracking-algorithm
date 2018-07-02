#include "dictionary.hpp"
#include "board.hpp"

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

TEST(BoardClass, get_printable)
{
    Board board(4, 4);
    std::vector<std::vector<char>> printable_board;
    printable_board = board.get_printable();

    std::string actual_board;
    for(std::size_t c_height = 0; c_height < printable_board.size(); ++c_height)
        for(std::size_t c_width = 0; c_width < printable_board[c_height].size(); ++c_width)
            actual_board += printable_board[c_height][c_width];

    EXPECT_STREQ("~~~~~~~~~~~~~~~~", actual_board.c_str());
}

TEST(BoardClass, insert_word)
{
    ASSERT_EQ(Board::EMPTY_FIELD, '~');
    using word_data = std::tuple<uint32_t, uint32_t, uint32_t>;

    Board board(5, 5);
    // Word size is larger than one in footprint.
    word_data word_footprint = word_data(1,0,3);
    board.insert_word("ThisIsTooLong", word_footprint);
    // No string was given.
    board.insert_word("", word_footprint);
    // "Car" should work.
    board.insert_word("Car", word_footprint);
    // Round should work.
    word_data round_footprint = word_data(3,1,5);
    board.insert_word("round", round_footprint);
    // Direction(second param) is wrong.
    word_data wrong_direct = word_data(3,4,5);
    board.insert_word("round", wrong_direct);
    // Text would go out of border.
    word_data out_of_border = word_data(3,0,6);
    board.insert_word("border", out_of_border);
    // Text would go out of border.
    word_data last_field_too_long = word_data(24,0,3);
    board.insert_word("out", last_field_too_long);
    // Single letter in last square should work.
    word_data last_field = word_data(24,0,1);
    board.insert_word("z", last_field);
    // Single letter in last square should work.
    word_data last_field_vert = word_data(24,1,1);
    board.insert_word("x", last_field_vert);

    std::vector<std::vector<char>> printable_board = board.get_printable();
    std::string output;
    for(const std::vector<char> v : printable_board)
        for(const char c : v)
            output += c;

    EXPECT_STREQ("~Car~~~~o~~~~u~~~~n~~~~dx", output.c_str());
}

