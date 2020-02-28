

#pragma once

#include <iostream>
#include "StateMachine/State.h"

class GameOver : public State {
public:
    GameOver(ShaderLoader& shloader);
    void updateFrame(){
        std::cout <<"Frame\n";
    };
    void updateEntities(){
        std::cout <<"Update\n";
    };
    void processInputs(){
        std::cout <<"Input\n";
    };
    ~GameOver() = default;

private:
    unsigned int programm;
protected:
};



