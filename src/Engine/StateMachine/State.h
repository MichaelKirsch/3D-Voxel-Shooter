

#pragma once

class State {
public:
    virtual void updateFrame(){};
    virtual void updateEntities(){};
    virtual void processInputs(){};
    ~State()= default;
private:
protected:
};



