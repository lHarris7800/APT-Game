//
// Created by Shahrzad Rafezi on 16/9/19.
//
#include <iostream>
#include "Player.h"
#define HAND_SIZE   7

Player::Player(){}

Player::Player(std::string playerName, Bag* bag){
    this->playerName = playerName;
    score = 0;
    //TODO not implemented
    hand = new LinkedList();
    for(int i = 0; i < HAND_SIZE;i++){
        hand->addBack(bag->getFront());
    }
}

Player::Player(Player& original){
    playerName = original.getName();
    score = original.getScore();
    hand = new LinkedList(*original.getHand());
}
//For loading from a save file
Player::Player(std::string playerName, int score, LinkedList* hand){
    this->playerName = playerName;
    this->score = score;
    this->hand = new LinkedList(*hand);
}

Player::~Player(){

}

std::string Player::getName(){
    return playerName;
}

int Player::getScore(){
    return score;
}

LinkedList* Player::getHand(){
    return hand;
}

//Changes the score (sets the score)
void Player::addScore(){
    this->score += score;
}

//Adds a tile in player's hand. returns true if successful
bool Player::addTile(Tile* tile){
    bool added = false;

    if (hand->getSize() < MAX_TILES) {
        hand->addBack(tile);
        added = true;
    }
    return added;
}

//Removes a tile from player's hand
void Player::removeTile(Tile* tile){
    int position = hand->searchTile(tile->getTileName());
    if(position != -1){
        hand->removeAt(position);
    }
}

//Displays players hand in the game
std::string Player::playerHand(){
    return hand->toString();
}

//Gets the string representation of a player for saving
std::string Player::toString(){
    std::string build;
    build.append(playerName + "\n");
    build.append(std::to_string(score) + "\n");
    build.append(hand->toString());
    return build;
}
