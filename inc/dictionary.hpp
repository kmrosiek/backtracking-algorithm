#pragma once

#include <string>
#include <vector>
#include <unordered_map>

class Dictionary
{
    public:
    void load_from_file();
    void remove_from_dictionary(std::string word);
    void add_to_dictionary(std::string word);
    bool does_word_exist(std::string word);

    private:
    std::unordered_map<int, std::vector<std::string>> words_by_length;
};
