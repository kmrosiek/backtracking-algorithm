#pragma once

#include "constraint.hpp"

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>


class Dictionary
{
    public:
    void load_words_from_file(const std::string&);
    void insert_word(const std::string&);
    void remove_word(const std::string&);
    bool does_word_exist(const std::string&) const;
    std::vector<std::string> create_domain(const std::size_t, const Constraints&);

    private:
    std::unordered_map<int, std::unordered_set<std::string>> m_words_by_length;
};
