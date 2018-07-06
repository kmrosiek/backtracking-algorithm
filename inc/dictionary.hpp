#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

class Constraints;


class Dictionary
{
    public:
        /** @brief Loads dictionary from file.
         *  @param source path and filename.
         *  @TODO Error handling.
         */
        void load_words_from_file(const std::string&);

        /** @brief Puts a given word into map (word.size() is the map key)
         *  @param word to be inserted.
         *  No effect if word already exists.
         */
        void insert_word(const std::string&);

        /** @brief Removes a word from map.
         *  @param word to be removed.
         *  No effect if word does not exist.
         */
        void remove_word(const std::string&);

        /** @brief Searches for a given word in a map.
         *  @param word to be searched for.
         *  @return true if found, false if not found.
         */
        bool does_word_exist(const std::string&) const;

        /** @brief creates a bundle of words that satisfy given constraints.
         *  @param word_length - all words (if any) in the domain will be this given length.
         *  @param Constraints - class containing constraints created upon current board.
         *  @return vector of wods with word_length length and that satisfy all constraints.
         */
        std::vector<std::string> create_domain(const std::size_t, const Constraints&);

    private:
        /** @brief Structure that keeps all dictionary words.
         *  Words cannot repeat. Unordered map sorts words according to length.
         *  It speeds up processing, as only words with given length are processed.
         */
        std::unordered_map<int, std::unordered_set<std::string>> m_words_by_length;
};
