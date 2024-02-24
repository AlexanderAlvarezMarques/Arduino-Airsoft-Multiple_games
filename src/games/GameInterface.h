#ifndef GAMEINTERFACE_H_INCLUDED
#define GAMEINTERFACE_H_INCLUDED

class GameInterface {

  public:

    enum GameStatus {
        MENU = 1,
        CONFIG = 2,
        IN_GAME = 3,
        PAUSED = 4,
        ENDED = 5
    };

    virtual const char* getName() = 0;

    virtual void init() = 0;

    virtual void showMenu() = 0;

    virtual bool start() = 0;

    virtual bool end() = 0;

    virtual int updateStatus(int key) = 0;

};

#endif