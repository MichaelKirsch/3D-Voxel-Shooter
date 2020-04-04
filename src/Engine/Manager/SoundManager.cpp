

#include "SoundManager.h"

SoundManager::SoundManager() {

}

sf::Int16 SoundManager::findInMap(std::string name) {
    if(loadedSounds.find(name)!=loadedSounds.end())
        return loadedSounds.at(name);
    return -1;
}

void SoundManager::playSound(std::string name) {
}
