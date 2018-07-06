#include "dictionary.hpp"
#include "constraint.hpp"

#include <fstream>
#include <string>
#include <vector>

void Dictionary::load_words_from_file(const std::string& file_path_and_name)
{
    std::ifstream dictionary_file(file_path_and_name);
    if(dictionary_file)
    {
		int rubbish;	// Used to skip not needed information from the file.
		std::string word;
		std::string word_class;
		while(!dictionary_file.eof())
		{
			// Skip redundant stuff from file.
			dictionary_file >> rubbish;
			dictionary_file >> rubbish;

			dictionary_file >> word;
			dictionary_file >> word_class;

			if(word_class == "adv" || word_class == "v" || word_class == "a" || word_class == "n")
                m_words_by_length[word.size()].insert(word);
        }
    }
    else
    {
        // UI info: file reading failed.
    }
}
void Dictionary::insert_word(const std::string& word)
{
    m_words_by_length[word.size()].insert(word);
}
void Dictionary::remove_word(const std::string& word)
{
    m_words_by_length[word.length()].erase(word);
}
bool Dictionary::does_word_exist(const std::string& word) const
{
    if(0 == m_words_by_length.count(word.size()))
        return false;

    // Extract only words which length is equal to word.size().
    auto set_of_word = m_words_by_length.at(word.size());
    if(set_of_word.find(word) != set_of_word.end())
        return true;

    return false;
}

bool intermediate(const Dictionary& dic, const std::string& word)
{
    return dic.does_word_exist(word);
}

std::vector<std::string> Dictionary::create_domain(const std::size_t word_length,
        const Constraints& constraints)
{
    std::vector<std::string> ordered_domain;
    for(const std::string& word : m_words_by_length[word_length])
    {
        if(constraints.check_constraint(&intermediate, *this, word))
            ordered_domain.push_back(word);
    }

   return ordered_domain;
}
