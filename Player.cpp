//
// Created by ronl on 11/27/2022.
//

#include "Player.h"


Player :: Player(permutation_t spirit,
                 int playerId,
                 int  teamId,
                 int gamesPlayed,
                 int goals,
                 int cards,
                 bool goalKeeper,
                 int gamesHasNotPlayed):
                    m_spirit(spirit),
                    m_playerId(playerId),
                    m_teamId(teamId),
                    m_gamesPlayed(gamesPlayed),
                    m_gamesHasNotPlayed(gamesHasNotPlayed),
                    m_goals(goals),
                    m_cards(cards),
                    m_goalKeeper(goalKeeper),
                    m_teamOfPlayer(nullptr),
                    m_biggerPlayer(nullptr),
                    m_smallerPlayer(nullptr),
                    m_key(nullptr)
{}


Player ::~Player() {
    if(m_key)
        delete m_key;
}

PlayerKey* Player ::getThePlayerKey()
{
    if(m_key== nullptr)
        m_key = new PlayerKey(m_playerId , m_goals ,m_cards);
    return m_key;
}
void Player ::updateKey() {
    if(m_key)
        delete m_key;
    m_key= nullptr;
}


int Player ::  getPlayerId() const
{
    return m_playerId;
}

int Player ::  getTeamId() const
{
    return m_teamId;
}

int Player ::  getGamesPlayed() const
{
    return m_gamesPlayed;
}

int Player ::  getGoals() const
{
    return m_goals;
}

int Player ::  getCards() const
{
    return m_cards;
}

bool Player ::  getGoalKeeper() const
{
    return m_goalKeeper;
}

Team* Player ::  getTeam()
{
    return m_teamOfPlayer;
}

Player* Player ::  getBiggerPlayer()
{
    return m_biggerPlayer;
}

Player* Player :: getSmallerPlayer()
{
    return m_smallerPlayer;
}

void Player ::  setPlayerId(int playerId)
{
    m_playerId = playerId;
}

void Player ::  setTeamId(int teamId )
{
    m_teamId = teamId ;
}

void Player ::  setGamesPlayed(int gamesPlayed)
{
    m_gamesPlayed = gamesPlayed ;
}
void Player ::  playGame()
{
    m_gamesPlayed++ ;
}


void Player ::  setGamesHasNotPlayed(int gamesHasNotPlayed)
{
    m_gamesHasNotPlayed = gamesHasNotPlayed ;
}


void Player ::  setGoals(int goals)
{
    m_goals = goals;
}

void Player :: setCards(int cards)
{
    m_cards =cards;
}

void Player ::  setGoalKeeper(bool goalkeeper)
{
    m_goalKeeper = goalkeeper;
}

void Player ::  setTeam(Team * team)
{
    m_teamOfPlayer = team;
}

void Player ::  setBiggerPlayer(Player * biggerPlayer)
{
    m_biggerPlayer = biggerPlayer ;
}

void Player ::  setSmallerPlayer(Player * smallerPlayer)
{
    m_smallerPlayer = smallerPlayer;
}


bool Player :: operator<(const Player& other)const
{
    if(m_goals < other.m_goals)
    {return true;}
    else if(m_goals == other.m_goals)
    {
        if(m_cards < other.m_cards)
        {
            return true;
        }
        else if(m_cards == other.m_cards)
        {
            if(m_playerId < other.m_playerId)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }

    }
    else
    {
        return false;
    }
}

bool Player :: operator==(const Player& other)const
{
    if(m_playerId == other.m_playerId)
    {return true;}
    else
    {return false;}
}


int Player::getGamesHasNotPlayed() const {
    return m_gamesHasNotPlayed;
}
