#include "dictionary.hpp"
#include "constraint.hpp"

#include <fstream>

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
                m_words_by_length[word.size()].push_back(word);
        }
    }
    else
    {
        // UI info: file reading failed.
    }
}
void Dictionary::insert_word(const std::string& word)
{
    m_words_by_length[word.size()].push_back(word);
}
void Dictionary::remove_word(const std::string& word)
{}
bool Dictionary::does_word_exist(const std::string& word) const
{
    if(m_words_by_length.count(word.size()) == 0)
        return false;

    return true;
}
std::vector<std::string> Dictionary::create_domain_for_given_constraints(const std::vector<Constraint>&)
{
}
