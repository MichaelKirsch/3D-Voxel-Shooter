

#include "GameOver.h"

GameOver::GameOver(ShaderLoader &shloader) : State(shloader) {
    programm=shloader.createProgram({{"platform_fragment",ShaderLoader::FRAGMENT},{"platform_vertex",ShaderLoader::VERTEX}});
}
