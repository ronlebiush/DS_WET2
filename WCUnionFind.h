//
// Created by ronl on 12/24/2022.
//

#ifndef WET2_WCUNIONFIND_H
#define WET2_WCUNIONFIND_H
#include <utility>

#include "AVLTree.h"
#include "Player.h"
#include "Team.h"
#include "PlayersHashTable.h"
//#include "HashMap.h"
#include "PlayerNode.h"


class WCUnionFind {
private:
    AVLTree<int,std::shared_ptr<Team>> m_teams; //sets
    PlayersHashTable m_players;
    //HashMap<int,std::shared_ptr<Player>>* m_players; //items
public:
    WCUnionFind();
    std::shared_ptr<Team> findPlayersTeam(int playerId); //the UF find func
    void unionTeams(int buyerTeamId, int boughtTeamId); //the UF Union func
    StatusType insertTeam(int teamId,std::shared_ptr<Team> team);
    StatusType removeTeam(int teamId);
    output_t<std::shared_ptr<Team>> getTeam(int teamId);
    StatusType insertPlayer(int teamId,int playerId, std::shared_ptr<Player> player);
    output_t<std::shared_ptr<Player>> getPlayer(int playerId);
    output_t<int> num_played_games_for_player(int playerId);
    output_t<permutation_t> get_partial_spirit(int playerId);
    bool playerExist(int playerId) const;
    bool teamExist(int playerId) const;


};


#endif //WET2_WCUNIONFIND_H