//
// Created by Pasha on 03/01/2023.
//
//
// Created by ronl on 1/1/2023.
//
#include "PlayerNode.h"

PlayerNode::PlayerNode(int playerId,std::shared_ptr<Player> player,PlayerNode* next):
        m_dady(nullptr),
        m_team(nullptr),
        m_playerId(playerId),
        m_player(std::move(player)),
        size(1),
        m_next(next){}