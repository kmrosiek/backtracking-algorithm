#include "board.hpp"
#include "dictionary.hpp"
#include "word_footprint.hpp"
#include "constraint.hpp"

#include <queue>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
#include <random>

Board board(10,10);
Dictionary dictionary;

std::queue<std::string> shuffle_domain(std::vector<std::string>& vec_domain)
{

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine e(seed);
    std::shuffle(std::begin(vec_domain), std::end(vec_domain), e);

    std::queue<std::string> shuffled_domain;
    for(const std::string& word : vec_domain)
        shuffled_domain.push(word);

    return shuffled_domain;
}

#include <iostream>
void visualise_board(std::vector<char> board)
{
    for(int y = 0; y < 10; y++)
    {
        for(int x = 0; x < 10; x++)
        {
            std::cout << board[y * 10 + x] << " ";
        }
        std::cout << std::endl;
    }
}

bool backtracking()
{

    for(int i = 0; i < 2; i++)//for(number_of_different_position_selection)
    {
        // Create random footprint - position, direction and word_length for current iteration.
        Word_footprint random_footprint(10, 10);
        // Create constraints for footprint. Needs footprint and board. Returns Constraint class that takes
        // pointer to dictionary lookup function and word to be checked.
        Constraints constraints(random_footprint, board.get_printable(), board.get_width());
        // Create domain - set of words with a given length and that satisfy given constraints.
        std::vector<std::string> ordered_domain = dictionary.create_domain(
                random_footprint.get_word_length(), constraints);
        std::queue<std::string> shuffled_domain = shuffle_domain(ordered_domain);

        while(!shuffled_domain.empty())
        {
            std::string word = shuffled_domain.front();
            board.insert_word(word, random_footprint);
            dictionary.remove_word(word); // if removing option enabled.

            //Update_GUI(SDL_Graphics);
            visualise_board(board.get_printable());
            if(true == backtracking())
                return true; // finished

            board.remove_word(random_footprint);
            dictionary.insert_word(word); // if removing option enabled.
            shuffled_domain.pop();
        }
    }

    return false;
}
int main()
{
    dictionary.load_words_from_file("../resource/lemma.al");
    backtracking();
    return 0;
}

