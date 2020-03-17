

#pragma once

class Renderable {
public:
    virtual void render(){};
    virtual void update(float elapsed){};
    ~Renderable() = default;
private:
protected:
};



