//
// Created by Shahrzad Rafezi on 16/9/19.
//

#include "Player.h"

Player::Player(){}

Player::Player(std::string playerName){
    this->playerName = playerName;
    score = 0;
    hand = new LinkedList();
}

Player::Player(Player& original){
    playerName = original.getName();
    score = original.getScore();
    hand = new LinkedList(*original.getHand());
}
//For loading from a save file
Player::Player(std::string playerName, int score, LinkedList* hand){
    playerName = playerName;
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

//Removes the tile from player's hand
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
    build.append(this->getName() + "\n");
    build.append(std::to_string(this->getScore()) + "\n");
    build.append(this->playerHand());
    return build;
}
