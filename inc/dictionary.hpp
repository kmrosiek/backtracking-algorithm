#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "constraint.hpp"

class Dictionary
{
    public:
    void load_from_file();
    void remove_word(const std::string& word);
    void add_word(const std::string& word);
    bool does_word_exist(const std::string& word);
    std::vector<std::string> create_domain_for_given_constraints(const std::vector<Constraint>&);

    private:
    std::unordered_map<int, std::vector<std::string>> words_by_length;
};
