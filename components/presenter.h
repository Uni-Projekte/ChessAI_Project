#include <string>
#include "Board.h"

#ifndef PRESENTER_CLASS
#define PRESENTER_CLASS

class Presenter {
public:
    std::string ToString(Board &board);
    void HTMLFromBoard(Board &board, std::string filename);
    void displayUINT64(uint64_t);

private:
    
};

#endif // PRESENTER_CLASS