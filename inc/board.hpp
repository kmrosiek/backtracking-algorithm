#include <vector>
#include <tuple>
#include <string>
#include <stdint.h>

#include "constraint.hpp"

class Board
{
    public:
        using word_data = std::tuple<uint32_t, uint32_t, uint32_t>;
        std::vector<Constraint> create_constraints_for_word_footprint(word_data);
        void insert_word(std::string, word_data);
        void remove_word(word_data);
        std::vector<char> get_printable();

    private:
        struct Field
        {
            char character;
            unsigned int counter;
        };

        std::vector<Field> fields;

};

