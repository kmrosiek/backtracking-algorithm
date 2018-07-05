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
bool Dictionary::does_word_exist(const std::string& word)
{
    // Extract only words which length is equal to word.size().
    auto set_of_word = m_words_by_length[word.size()];
    if(set_of_word.find(word) != set_of_word.end())
        return true;

    return false;
}
std::vector<std::string> Dictionary::create_domain(const std::vector<Constraint>&)
{
}
