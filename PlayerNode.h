//
// Created by ronl on 12/28/2022.
//

#ifndef WET2_PLAYERNODE_H
#define WET2_PLAYERNODE_H

#include <memory>
#include "Team.h"
#include "Player.h"

class Team;


class PlayerNode{
public:
    PlayerNode* m_dady;
    std::shared_ptr<Team> m_team;
    int m_playerId;
    std::shared_ptr<Player> m_player;
    int size;
    PlayerNode* m_next;
    explicit PlayerNode(int playerId,std::shared_ptr<Player> player,PlayerNode* next);
};
#endif //WET2_PLAYERNODE_H