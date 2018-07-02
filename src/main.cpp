#include "board.hpp"
#include "dictionary.hpp"

#include <queue>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
#include <random>

Board board(10,10);
Dictionary dictionary;

std::queue<std::string> shuffle_domain(std::vector<std::string> vec_domain)
{

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine e(seed);
    std::shuffle(std::begin(vec_domain), std::end(vec_domain), e);

    std::queue<std::string> shuffled_domain;
    for(std::string word : vec_domain)
        shuffled_domain.push(word);

    return shuffled_domain;
}


bool backtracking()
{

    for(int i = 0; i < 2; i++)//for(number_of_different_position_selection)
    {
        class Word_footprint
        {
            public:
            Word_footprint(uint32_t board_width, uint32_t board_height)
            {
                //randoms();
                position = 3;
                direction = 1;
                word_length = 4;
                /*position = random_position(BOARD_WIDTH, BOARD_HEIGHT);
                  direction = random_direction(); // returns 0 or 1 (LEFT or RIGHT)
                  distance_to_border = calculate_distance_to_border(position, direction);
                  word_length = random_word_length(distance_to_border);*/
            }

            std::tuple<uint32_t, uint32_t, uint32_t> get_data() const noexcept
            {
                return std::make_tuple(position, direction, word_length);
            }

            private:
            uint32_t position;
            uint32_t direction;
            uint32_t word_length;
        };

        Word_footprint random_footprint(10,12);
        std::vector<Constraint> word_footprint_constraint = board.create_constraints_for_word_footprint(random_footprint.get_data());
        std::vector<std::string> ordered_domain = dictionary.create_domain_for_given_constraints(word_footprint_constraint);
        std::queue<std::string> shuffled_domain = shuffle_domain(ordered_domain);

        while(!shuffled_domain.empty())
        {
            //std::string word = random_word_from_domain(domain);
            std::string word = shuffled_domain.front();
            board.insert_word(word, random_footprint.get_data());
            dictionary.remove_word(word); // if removing option enabled.

            //Update_GUI(SDL_Graphics);
            if(true == backtracking())
                return true; // finished

            board.remove_word(random_footprint.get_data());
            dictionary.insert_word(word); // if removing option enabled.
            shuffled_domain.pop();
        }
    }

    return false;
}
int main()
{
    dictionary.load_words_from_file("../resource/lemma.al");
    return 0;
}

