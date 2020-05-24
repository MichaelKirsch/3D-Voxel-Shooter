

#pragma once

class Renderable {
public:
    virtual void render()=0;
    virtual void update(float& elapsed){};
    virtual void create(){};
    ~Renderable() = default;
private:
protected:
};



