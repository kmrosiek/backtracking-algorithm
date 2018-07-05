#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "constraint.hpp"

class Dictionary
{
    public:
    void load_words_from_file(const std::string&);
    void insert_word(const std::string&);
    void remove_word(const std::string&);
    bool does_word_exist(const std::string&);
    std::vector<std::string> create_domain(const std::vector<Constraint>&);

    private:
    std::unordered_map<int, std::unordered_set<std::string>> m_words_by_length;
};
