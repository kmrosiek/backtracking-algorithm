#include "crossword.hpp"

int main()
{
    Crossword crossword;
    crossword.prepare_dictionary("../resource/lemma.al");
    crossword.backtracking();
    return 0;
}

