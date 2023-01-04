//
// Created by ronl on 12/24/2022.
//

#include "WCUnionFind.h"

#include <utility>


WCUnionFind::WCUnionFind() = default;

void WCUnionFind::unionTeams(int buyerTeamId, int boughtTeamId)
{
    std::shared_ptr<Team> buyerTeam = m_teams.findValue(buyerTeamId);
    std::shared_ptr<Team> boughtTeam = m_teams.findValue(boughtTeamId);

    PlayerNode* buyerRootPlayer= buyerTeam->getRootPlayer();
    PlayerNode* boughtRootPlayer= boughtTeam->getRootPlayer();

    permutation_t newTeamSpirit = boughtTeam->getSpirit()*buyerTeam->getSpirit();
    int newPlayedGames = boughtRootPlayer->m_player->getGamesPlayed()-buyerRootPlayer->m_player->getGamesPlayed();
    if (buyerRootPlayer->size > boughtRootPlayer->size) //B->A
    {
        boughtRootPlayer->m_dady = buyerRootPlayer;
        boughtRootPlayer->m_player->setGamesPlayed(newPlayedGames);
        //r(b) += h(a) -r(a)
        permutation_t newSpirit = buyerRootPlayer->m_player->getSubSpirit().inv() *buyerRootPlayer->m_team->getSpirit() * boughtRootPlayer->m_player->getSubSpirit();
        boughtRootPlayer->m_player->setSubSpirit(newSpirit);
        buyerRootPlayer->size += boughtRootPlayer->size;
        buyerRootPlayer->m_team->setSpirit(buyerRootPlayer->m_team->getSpirit()*boughtRootPlayer->m_team->getSpirit());
        boughtRootPlayer->m_team.reset();

    }
    else //A->B
    {
        buyerRootPlayer->m_dady = boughtRootPlayer;
        buyerRootPlayer->m_player->setGamesPlayed(-newPlayedGames);
        //r(a) -= r(b)
        //r(b) += H(a)
        buyerRootPlayer->m_player->setSubSpirit(boughtRootPlayer->m_player->getSubSpirit().inv() *buyerRootPlayer->m_player->getSubSpirit());
        boughtRootPlayer->m_player->setSubSpirit(boughtRootPlayer->m_player->getSubSpirit() *buyerRootPlayer->m_team->getSpirit());
        boughtRootPlayer->size += buyerRootPlayer->size;
        buyerRootPlayer->m_team->setSpirit(buyerRootPlayer->m_team->getSpirit()*boughtRootPlayer->m_team->getSpirit());
        boughtRootPlayer->m_team.reset();
        boughtRootPlayer->m_team = buyerRootPlayer->m_team;
    }
    buyerTeam->setSpirit(newTeamSpirit);
}





StatusType WCUnionFind::removeTeam(int teamId){
    if(!m_teams.keyExists(teamId))
        return StatusType::FAILURE;
    PlayerNode* playerNode =m_teams.findValue(teamId)->getRootPlayer();
    if (playerNode)
        playerNode->m_team = nullptr;
    m_teams.remove(teamId);
    return StatusType::SUCCESS;
}

StatusType WCUnionFind::insertTeam(int teamId,std::shared_ptr<Team> team){
    if(m_teams.keyExists(teamId))
        return StatusType::FAILURE;
    m_teams.insert(teamId,team);
    return StatusType::SUCCESS;
}



output_t<std::shared_ptr<Player>> WCUnionFind::getPlayer(int playerId){
    if(m_players.Contains(playerId))
        return m_players.getPlayer(playerId);
    else
        return StatusType::FAILURE;
}

StatusType WCUnionFind::insertPlayer(int teamId,int playerId, std::shared_ptr<Player> player)
{
    if(m_players.Contains(playerId))
        return StatusType::FAILURE;
    m_players.insert( playerId,  player);   //O(1)
    PlayerNode* playerNode = m_players.getNode(playerId);       //O(1)
    std::shared_ptr<Team> playerTeam = m_teams.findValue(teamId); //O(log k)
    PlayerNode* rootPlayer = playerTeam->getRootPlayer();
    if (!rootPlayer){
        playerNode->m_dady = nullptr;
        playerNode->m_team = playerTeam;
        playerTeam->setRootPlayer(playerNode);
        playerTeam->setSpirit(playerNode->m_player->getSubSpirit());
        if(player->getGoalKeeper())
        {playerTeam->setGoaKeeperCount(playerTeam->getGoaKeeperCount()+1);}
        playerTeam->setAbility(playerTeam->getTeamAbility() + player->getAbility());
    }
    else{
        permutation_t newTeamSpirit = playerTeam->getSpirit()*playerNode->m_player->getSubSpirit();
        rootPlayer->size++;
        playerNode->m_dady = rootPlayer;
        playerNode->m_player->setGamesPlayed(playerNode->m_player->getGamesPlayed()-rootPlayer->m_player->getGamesPlayed());
        //r(b) += h(a) -r(a)
        permutation_t newSpirit = rootPlayer->m_player->getSubSpirit().inv() *rootPlayer->m_team->getSpirit() * playerNode->m_player->getSubSpirit();
        playerNode->m_player->setSubSpirit(newSpirit);
        playerTeam->setSpirit(newTeamSpirit);
        if(player->getGoalKeeper())
        {playerTeam->setGoaKeeperCount(playerTeam->getGoaKeeperCount()+1);}
        playerTeam->setAbility(playerTeam->getTeamAbility() + player->getAbility());
    }
    return StatusType::SUCCESS;

}



std::shared_ptr<Team> WCUnionFind::findPlayersTeam(int playerId) {
    PlayerNode *playerNode = m_players.getNode(playerId);
    if (!playerNode)
        return nullptr;

    int gamesSum = 0;
    permutation_t spiritSum = permutation_t::neutral();
    PlayerNode *nodeIterator = playerNode;
    while (nodeIterator->m_dady)//sum branch
    {
        gamesSum += nodeIterator->m_player->getGamesPlayed();
        spiritSum = spiritSum * nodeIterator->m_dady->m_player->getSubSpirit();
        nodeIterator = nodeIterator->m_dady;
    }
    PlayerNode *rootNode = nodeIterator;
    nodeIterator = playerNode;

    while (nodeIterator->m_dady) {
        int currentPlayerGames = nodeIterator->m_player->getGamesPlayed();
        permutation_t currentPlayerSpirit = nodeIterator->m_player->getSubSpirit();

        nodeIterator->m_player->setGamesPlayed(gamesSum);
        nodeIterator->m_player->setSubSpirit(spiritSum);

        nodeIterator->m_dady = rootNode;

        gamesSum -= currentPlayerGames;
        spiritSum = spiritSum * currentPlayerSpirit.inv();
        nodeIterator = nodeIterator->m_dady;
    }
    //return rootNode->m_team;
    std::shared_ptr<Team> team = rootNode->m_team;
    return team;

}



output_t<int> WCUnionFind::num_played_games_for_player(int playerId){
    if (!m_players.Contains(playerId))
        return StatusType::FAILURE;
    findPlayersTeam(playerId);
    PlayerNode* playerNode = m_players.getNode(playerId);
    if(playerNode->m_dady)
        return playerNode->m_player->getGamesPlayed()+playerNode->m_dady->m_player->getGamesPlayed();
    return playerNode->m_player->getGamesPlayed();

}

output_t<permutation_t> WCUnionFind::get_partial_spirit(int playerId){
    if (!m_players.Contains(playerId))
        return StatusType::FAILURE;
    findPlayersTeam(playerId);
    PlayerNode* playerNode = m_players.getNode(playerId);
    if(playerNode->m_dady)
        return playerNode->m_player->getSubSpirit()*playerNode->m_dady->m_player->getSubSpirit();
    return playerNode->m_player->getSubSpirit();
}

output_t<std::shared_ptr<Team>> WCUnionFind:: getTeam(int teamId){
   if(!m_teams.keyExists(teamId))
   {return StatusType::FAILURE;}
   return m_teams.findValue(teamId);

}