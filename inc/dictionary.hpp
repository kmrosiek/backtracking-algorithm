#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "constraint.hpp"

class Dictionary
{
    public:
    void load_words_from_file(const std::string&);
    void remove_word(const std::string&);
    void add_word(const std::string&);
    bool does_word_exist(const std::string&) const;
    std::vector<std::string> create_domain_for_given_constraints(const std::vector<Constraint>&);

    private:
    std::unordered_map<int, std::vector<std::string>> m_words_by_length;
};
