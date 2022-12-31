
#ifndef WET1_PLAYER_H
#define WET1_PLAYER_H

#include "wet2util.h"


class Player {

private:
    int  m_playerId;
    permutation_t m_spirit;
    int  m_gamesPlayed;
    int  m_ability;
    int  m_cards;
    int  m_goalKeeper;




public:
    Player(int playerId,permutation_t& spirit,int gamesPlayers,int ability,int m_cards,bool goalKeeper);
    ~Player();

    permutation_t& getSubSpirit();
    void setSubSpirit(permutation_t& subSpirit);
    int getPlayerId() const;
    int getGamesPlayed() const;
    int getCards() const;
    bool getGoalKeeper() const;
    void setPlayerId(int playerId);
    void setGamesPlayed(int gamesPlayed);
    void setCards(int cards);
    void setGoalKeeper(bool goalKeeper);
    bool  operator==(const Player& other) const;
    void playGame();

};


#endif //WET1_PLAYER_H