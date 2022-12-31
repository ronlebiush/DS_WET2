
#ifndef WET1_TEAM_H
#define WET1_TEAM_H

#include "AVLTree.h"
#include "Player.h"
#include "PlayerKey.h"
#include "node.h"
#include "TeamKey.h"
class Player;

class Team{
private:
    int m_TeamId;
    int m_TeamPoints;
    int m_gamesPlayed;
    int m_TeamGoals;
    int m_TeamCards;
    int m_goaKeeperCount;
    Node* m_rootPlayer;
    permutation_t m_teamSpirit;
    TeamKey m_key

    static const int DRAW_POINTS=1;
    static const int WIN_POINTS=3;


public:
    //Ctor&Dtor
    Team(int teamid,int points=0);
    Team()=default;
    ~Team()=default;

    //Getters &setters
    int getTeamId() const;
    int getGamePlayed() const;
    int getTeamPoints()const;
    int getTeamGoals() const;
    int getTeamCards() const ;
    int getNumOfPlayers() const;
    int getTopScorerId() const;
    void setTeamId(int id);
    void setGamePlayed(int gamePlayed);
    void setTeamPoints(int points);
    void setTeamGoals(int goals);
    void setTeamCards(int Cards);
    permutation_t& getSpirit();
    void setSpirit(const permutation_t& TeamSpirit);
    PlayerNode* getRootPlayer();
    void setRootPlayer(PlayerNode* playerNode);
    TeamKey& getTeamKey();

    void playGame();
    void winGame();
    void drawGame();
    void addGoalKeeper();
    void removeGoalKeeper();
    int getScore() const;
    bool isTeamKosher() const;
    bool isEmpty() const;
    void addSpirit(const permutation_t& playerSpirit);
};



#endif //WET1_TEAM_H
