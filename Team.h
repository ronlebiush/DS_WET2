
#ifndef WET1_TEAM_H
#define WET1_TEAM_H

#include "Player.h"
#include "TeamKey.h"
#include "PlayerNode.h"


class PlayerNode;

class Team{
private:
    int m_TeamId;
    int m_TeamPoints;
    int m_goaKeeperCount;
    int m_TeamAbility;
    PlayerNode* m_rootPlayer;
    permutation_t m_teamSpirit;
    TeamKey m_key;

    static const int DRAW_POINTS=1;
    static const int WIN_POINTS=3;


public:
    //Ctor&Dtor
    Team(int teamid,int points=0);
    Team()=default;
    ~Team()=default;

    //Getters &setters
    int getTeamId() const;
    int getTeamPoints()const;
    int getGoaKeeperCount()const;
    int getTeamAbility()const;
    void setTeamId(int id);
    void setTeamPoints(int points);
    permutation_t& getSpirit();
    void setSpirit(const permutation_t& TeamSpirit);
    PlayerNode* getRootPlayer();
    void setRootPlayer(PlayerNode* playerNode);
    void setGoaKeeperCount(int i);
    void setAbility(int i);
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