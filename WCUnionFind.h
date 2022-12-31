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

//class PlayerNode{
//public:
//    PlayerNode* m_dady;
//    std::shared_ptr<Team> m_team;
//    std::shared_ptr<Player> m_player;
//    int size;
//    PlayerNode* m_next;
//    explicit PlayerNode(std::shared_ptr<Player> player): m_dady(nullptr), m_team(nullptr),m_player(std::move(player)), size(1),m_next(
//            nullptr){}
//};



class WCUnionFind {
private:
    AVLTree<int,std::shared_ptr<Team>>* m_teams; //sets
    PlayersHashTable m_players;
    //HashMap<int,std::shared_ptr<Player>>* m_players; //items
public:
    std::shared_ptr<Team> findPlayersTeam(int playerId); //the UF find func
    void unionTeams(int buyerTeamId, int boughtTeamId); //the UF Union func
    void insertTeam(int teamId,std::shared_ptr<Team> team);
    void removeTeam(int teamId);
    void insertPlayer(int teamId,int playerId, std::shared_ptr<Player> player);
    std::shared_ptr<Player> getPlayer(int playerId);
    output_t<int> num_played_games_for_player(int playerId);
    output_t<permutation_t> get_partial_spirit(int playerId);



};


#endif //WET2_WCUNIONFIND_H
