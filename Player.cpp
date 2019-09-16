//
// Created by Shahrzad Rafezi on 16/9/19.
//

#include "Player.h"

Player::Player(std::string playerName){
    playerName = playerName;
    score = 0;
    hand = new LinkedList();

}
//for loading from a save file
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

void Player::addScore(){
    this->score += score;
}

//Linklist needs to be done first
bool Player::addTile(Tile* tile){

}

//Linklist needs to be done first
Tile Player::placeTile(std::string tileName){

}

std::string Player::playerScore(){

}

//Linklist needs to be done first
std::string Player::playerHand(){

}

std::string Player::toString(){
    std::string build;
    build.append(this->getName() + "\n");
    build.append(std::to_string(this->getScore()) + "\n");
    //add the hand here
    return build;
}
