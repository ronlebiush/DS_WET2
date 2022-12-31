//
// Created by ronl on 11/27/2022.
//

#include "Player.h"


Player :: Player(int playerId,permutation_t& spirit,int gamesPlayed,int ability,int cards,bool goalKeeper):
                    m_playerId(playerId),m_spirit(spirit),m_gamesPlayed(gamesPlayed),m_ability(ability),m_cards(cards),m_goalKeeper(goalKeeper){}


Player ::~Player() =default;

int Player ::  getPlayerId() const
{
    return m_playerId;
}


int Player ::  getGamesPlayed() const
{
    return m_gamesPlayed;
}


int Player ::  getCards() const
{
    return m_cards;
}

bool Player ::  getGoalKeeper() const
{
    return m_goalKeeper;
}




void Player ::  setPlayerId(int playerId)
{
    m_playerId = playerId;
}



void Player ::  setGamesPlayed(int gamesPlayed)
{
    m_gamesPlayed = gamesPlayed ;
}

void Player ::  playGame()
{
    m_gamesPlayed++ ;
}



void Player :: setCards(int cards)
{
    m_cards =cards;
}

void Player ::  setGoalKeeper(bool goalkeeper)
{
    m_goalKeeper = goalkeeper;
}



bool Player :: operator==(const Player& other)const
{
    if(m_playerId == other.m_playerId)
        return true;
    else
        return false;
}

permutation_t& Player::getSubSpirit(){
    return m_spirit;
}
void Player::setSubSpirit(permutation_t& subSpirit){
    m_spirit=subSpirit;
}