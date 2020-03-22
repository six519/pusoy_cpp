#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_
using namespace std;

class GameException {
    public:
        string message();
};

class FileGameException: public GameException {
    public:
        string message();
};

#endif