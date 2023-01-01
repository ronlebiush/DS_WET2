//
// Created by ronl on 11/27/2022.
//

#include "Team.h"





Team::Team(int teamId, int points):
        m_TeamId(teamId),
        m_TeamPoints(points),
        m_goaKeeperCount(0),
        m_TeamAbility(0),
        m_rootPlayer(nullptr),
        m_teamSpirit(),
        m_key(m_TeamAbility,teamId)
        {}



int Team::getTeamId() const{return m_TeamId;}
int Team::getTeamPoints()const {return m_TeamPoints;}

void Team::setTeamId(int id){ m_TeamId=id;}
void Team::setTeamPoints(int points){m_TeamPoints=points;}




void Team::playGame() {
    m_rootPlayer->m_player->setGamesPlayed(m_rootPlayer->m_player->getGamesPlayed()+1);
}
void Team::winGame(){
    m_TeamPoints+=WIN_POINTS;
}
void Team::drawGame(){
    m_TeamPoints+=DRAW_POINTS;
}



bool Team::isTeamKosher() const
{
    return ( m_goaKeeperCount > 0);
}


int Team::getScore() const {
    return m_TeamPoints + m_TeamAbility;
}

bool Team::isEmpty() const {
    return m_rootPlayer== nullptr;
}

