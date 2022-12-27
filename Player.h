
#ifndef WET1_PLAYER_H
#define WET1_PLAYER_H

#include "PlayerKey.h"
#include "Team.h"
#include "wet2util.h"

class Team;

class Player {

private:
    int  m_playerId;
    int  m_teamId;
    int  m_gamesPlayed;
    int  m_gamesHasNotPlayed;
    int  m_goals;
    int  m_cards;
    int  m_goalKeeper;

    permutation_t m_spirit;
    Team* m_teamOfPlayer ;
    Player* m_biggerPlayer;
    Player* m_smallerPlayer;
    PlayerKey* m_key;


public:
    Player(permutation_t spirit, int playerId ,int  teamId ,int gamesPlayers , int goals , int m_cards ,bool goalKeeper,int gamesHasNotPlayed=0 );



    ~Player();

    int getPlayerId() const;
    int getTeamId() const;
    int getGamesPlayed() const;
    int getGamesHasNotPlayed() const;
    int getGoals() const ;
    int getCards() const;
    bool getGoalKeeper() const;
    Team* getTeam();
    Player* getBiggerPlayer();
    Player* getSmallerPlayer();
    void setPlayerId(int playerId);
    void setTeamId(int teamId );
    void setGamesPlayed(int gamesPlayed);
    void setGamesHasNotPlayed(int gamesPlayed);
    void setGoals(int goals);
    void setCards(int cards);
    void setGoalKeeper(bool goalKeeper);
    void setTeam(Team * team);
    void setBiggerPlayer(Player * biggerPlayer);
    void setSmallerPlayer(Player * smallerPlayer);
    bool  operator<(const Player& other) const;
    bool  operator==(const Player& other) const;
    PlayerKey* getThePlayerKey();
    void playGame();
    void updateKey();
//    void findSmallerClosest (const V& value ,const K& key) const ;
//    V& findBiggerClosest (const V& value ,const K& key) const ;


};


#endif //WET1_PLAYER_H