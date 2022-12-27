//
// Created by ronl on 12/24/2022.
//

#ifndef WET2_WCUNIONFIND_H
#define WET2_WCUNIONFIND_H
#include "AVLTree.h"
#include "Player.h"
#include "Team.h"
#include "HashMap.h"

class WCUnionFind {
private:
    AVLTree<int,Team>* sets;
    HashMap<int,Player>* players;
public:
    std::shared_ptr<Team> findPlayersTeam(int playerId); //the UF find func
    void unionTeam(int team1 , int team2); //the UF Union func
    void insertPlayer(const Player& player,int playerId);
    void insertTeam(const Team& team,int teamId);


};


#endif //WET2_WCUNIONFIND_H
