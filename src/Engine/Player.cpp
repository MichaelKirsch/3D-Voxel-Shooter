

#include "Player.h"

Player::Player(Terrain &terrain) : ter(terrain){
    create();
}

void Player::render() {
    ShaderLoader::useProgramm(PROGRAMM);

    glDisable(GL_CULL_FACE);
    glBindVertexArray(VAO);
    ShaderLoader::setUniform(PROGRAMM,color_according_to_armor,"armorColor");
    ShaderLoader::setUniform(PROGRAMM,glm::vec4(playerPos,1.0),"worldPos");
    ShaderLoader::setUniform(PROGRAMM,StateEssentials::get().camera.GetViewMatrix(),"view");
    ShaderLoader::setUniform(PROGRAMM,model,"model");
    ShaderLoader::setUniform(PROGRAMM,StateEssentials::get().windowManager.perspectiveProjection,"projection");
    glDrawElements(GL_TRIANGLES,playerIndices.size(),GL_UNSIGNED_INT,0);
    glBindVertexArray(0);
    glEnable(GL_CULL_FACE);
}

void Player::update(float &elapsed) {
    model = glm::rotate(model,glm::radians(1.f),{0.f,1.f,0.f});
    if(playerPos.y >1000.f)
        vertical_velocity =-10;

    if(playerPos.y > ter.getY(playerPos.x,playerPos.z))
        vertical_velocity-=0.04f;
    else
        vertical_velocity =0;
}

void Player::create() {
    PROGRAMM = ShaderLoader::createProgram({{"player_fragment.glsl",ShaderLoader::FRAGMENT},{"player_vertex.glsl",ShaderLoader::VERTEX}});
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    glGenBuffers(1,&EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,playerIndices.size()* sizeof(unsigned int),playerIndices.data(),GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,playerVertices.size()*sizeof(glm::vec3),playerVertices.data(),GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3* sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
}

void Player::respawn(glm::vec3 respawnPosition, bool bindToTerrain) {
    if(bindToTerrain)
        respawnPosition.y = ter.getY(respawnPosition.x,respawnPosition.y);
    playerPos = respawnPosition;
}

void Player::processInputs() {

    glm::vec3 playerMovementFront = glm::normalize(glm::cross(up,StateEssentials::get().camera.Right));
    glm::vec3 playerMovementSide = glm::normalize(glm::cross(up,playerMovementFront));

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
        playerSpeed = 0.27;
    else
        playerSpeed =0.16;

    playerPos.y+=vertical_velocity;

    if(playerPos.y<ter.getY(playerPos.x,playerPos.z))
        playerPos.y = ter.getY(playerPos.x,playerPos.z);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)&&playerPos.y==ter.getY(playerPos.x,playerPos.z))
    {
        vertical_velocity +=0.45f;
    }

    glm::vec3 futurePlayerPos = playerPos;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        futurePlayerPos +=playerMovementFront*playerSpeed;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        futurePlayerPos -=playerMovementSide*playerSpeed;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        futurePlayerPos -=playerMovementFront*playerSpeed;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        futurePlayerPos +=playerMovementSide*playerSpeed;
    //playerPos = futurePlayerPos;

    if(playerPos.y>=(ter.getY(futurePlayerPos.x,futurePlayerPos.z))){
        playerPos = futurePlayerPos;
    }
    else
    {
        //TODO: need some sliding function here so no stops occure when the player is not perpendicular
    }

    //if(playerPos.y < ter.getY(futurePlayerPos.x,futurePlayerPos.z))
        //playerPos.y =  ter.getY(futurePlayerPos.x,futurePlayerPos.z);
    float yaw,pitch;
    float x_percent =  (1.f/StateEssentials::get().windowManager.getWindow().getSize().x) * m_Mouse.getPosition(StateEssentials::get().windowManager.getWindow()).x;
    float y_percent =  (1.f/StateEssentials::get().windowManager.getWindow().getSize().y) * m_Mouse.getPosition(StateEssentials::get().windowManager.getWindow()).y;

    x_percent-=0.5f;
    y_percent-=0.5f;
    x_percent*=2;
    y_percent*=2;
    const float mouse_sensitivity = 5.5f;
    yaw = (180.f*x_percent)*mouse_sensitivity;
    pitch = (180.f*-y_percent)*mouse_sensitivity;
    if(!m_Mouse.isButtonPressed(sf::Mouse::Right))
    {

        StateEssentials::get().windowManager.getWindow().setMouseCursorVisible(false);
        StateEssentials::get().camera.ProcessMouseMovement(yaw,pitch);
        m_Mouse.setPosition({static_cast<int>(StateEssentials::get().windowManager.getWindow().getSize().x/2),
                             static_cast<int>(StateEssentials::get().windowManager.getWindow().getSize().y/2)},
                            StateEssentials::get().windowManager.getWindow());
    }

}
