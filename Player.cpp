//
// Created by Shahrzad Rafezi on 16/9/19.
//

#include "Player.h"

Player::Player(std::string playerName){
    playerName = playerName;
    score = 0;
    hand = new LinkedList();

}
//For loading from a save file
Player::Player(std::string playerName, int score, LinkedList hand){
    playerName = playerName;
    score = score;
    hand = hand;
}

Player::~Player(){

}

std::string Player::getName(){
    return playerName;
}

int Player::getScore(){
    return score;
}

//Changes the score (sets the score)
void Player::addScore(){
    this->score += score;
}

//Adds a tile in player's hand. returns true if successful
bool Player::addTile(Tile& tile){
    bool added = false;

    if (hand->getSize() < MAX_TILES) {
        hand->addBack(tile);
        return true;
    }
    return added;
}

Tile Player::placeTile(std::string tileName){

}

std::string Player::playerScore(){

}

//Displays players hand in the game
std::string Player::playerHand(){
    std::string build = std::string("");

    int handSize = hand->getSize();
    for (int i = 0; i < handSize; i++) {
        build.append(hand->getAt(i)->getTileName());

        if (i != handSize - 1) {
            build.append(",");
        }
    }
    return build;
}

//Gets the string representation of a player for saving
std::string Player::toString(){
    std::string build;
    build.append(this->getName() + "\n");
    build.append(std::to_string(this->getScore()) + "\n");
    build.append(this->playerHand());
    return build;
}
