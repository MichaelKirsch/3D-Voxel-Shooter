

#include "Platform.h"

Platform::Platform(unsigned int size, glm::vec3 origin) {
    for(int x =0;x<size;x++)
    {
        for(int z =0;z<size;z++)
        {
            auto color = 0.01f*(rand()%30);
            blocks.emplace_back(glm::vec4((float)x,0.f,(float)z,color));
        }
    }
}
