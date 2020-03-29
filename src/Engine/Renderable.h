

#pragma once

class Renderable {
public:
    virtual void render(){};
    virtual void update(float& elapsed){};
    virtual void create(){};
    //~Renderable() = default;
private:
protected:
};



