

#include "Player.h"

Player::Player(Terrain &terrain, StateEssentials& es) : ter(terrain), essentials(es){

}

void Player::render() {

}

void Player::update(float &elapsed) {
    if(playerPos.y >1000.f)
        vertical_velocity =-10;

    if(playerPos.y > ter.getY(playerPos.x,playerPos.z))
        vertical_velocity-=0.04f;
    else
        vertical_velocity =0;
}

void Player::create() {

}

void Player::respawn(glm::vec3 respawnPosition, bool bindToTerrain) {
    if(bindToTerrain)
        respawnPosition.y = ter.getY(respawnPosition.x,respawnPosition.y);
    playerPos = respawnPosition;
}

void Player::processInputs() {

    glm::vec3 playerMovementFront = glm::normalize(glm::cross(up,essentials.camera.Right));
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
        //vertical_velocity +=0.2f;
    else
    {

    }

    //if(playerPos.y < ter.getY(futurePlayerPos.x,futurePlayerPos.z))
        //playerPos.y =  ter.getY(futurePlayerPos.x,futurePlayerPos.z);
    float yaw,pitch;
    float x_percent =  (1.f/essentials.windowManager.getWindow().getSize().x) * m_Mouse.getPosition(essentials.windowManager.getWindow()).x;
    float y_percent =  (1.f/essentials.windowManager.getWindow().getSize().y) * m_Mouse.getPosition(essentials.windowManager.getWindow()).y;

    x_percent-=0.5f;
    y_percent-=0.5f;
    x_percent*=2;
    y_percent*=2;
    const float mouse_sensitivity = 5.5f;
    yaw = (180.f*x_percent)*mouse_sensitivity;
    pitch = (180.f*-y_percent)*mouse_sensitivity;
    if(!m_Mouse.isButtonPressed(sf::Mouse::Right))
    {

        essentials.windowManager.getWindow().setMouseCursorVisible(false);
        essentials.camera.ProcessMouseMovement(yaw,pitch);
        m_Mouse.setPosition({static_cast<int>(essentials.windowManager.getWindow().getSize().x/2),
                             static_cast<int>(essentials.windowManager.getWindow().getSize().y/2)},
                essentials.windowManager.getWindow());
    }

}
