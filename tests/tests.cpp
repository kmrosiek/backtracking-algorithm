#include "dictionary.hpp"

#include <gtest/gtest.h>

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
    EXPECT_TRUE(dictionary.does_word_exist("Hello"));
    EXPECT_TRUE(dictionary.does_word_exist("Abrakadabra"));
}

TEST(DictionaryClass, load_words_from_file)
{
    Dictionary dictionary;
    dictionary.load_words_from_file("../resource/lemma.al");
}
