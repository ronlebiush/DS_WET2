//
// Created by ronl on 11/27/2022.
//

#include "Team.h"





Team::Team(int teamId, int points):
    m_TeamId(teamId),
    m_TeamPoints(points),
    m_gamesPlayed(0),
    m_TeamGoals(0),
    m_TeamCards(0),
    m_goaKeeperCount(0),
    m_topScorer(nullptr),
    m_PlayersById(),
    m_PlayersByStats(){}

Team::Team(int TeamId,
     int gamesPlayed,
     int TeamPoints,
     int TeamGoals,
     int TeamCards,
     int goaKeeperCount):
        m_TeamId(TeamId),
        m_TeamPoints(TeamPoints),
        m_gamesPlayed(gamesPlayed),
        m_TeamGoals(TeamGoals),
        m_TeamCards(TeamCards),
        m_goaKeeperCount(goaKeeperCount),
        m_topScorer(nullptr),
        m_PlayersById(),
        m_PlayersByStats(){}



int Team::getTeamId() const{return m_TeamId;}
int Team::getGamePlayed() const {return m_gamesPlayed;}
int Team::getTeamPoints()const {return m_TeamPoints;}
int Team::getTeamGoals() const {return m_TeamGoals;}
int Team::getTeamCards() const {return m_TeamCards;}
int Team::getNumOfPlayers() const {return m_PlayersById.getCount();}
int Team::getTopScorerId() const {return m_topScorer->getPlayerId();}
void Team::setTeamId(int id){ m_TeamId=id;}
void Team::setGamePlayed(int gamePlayed){m_gamesPlayed=gamePlayed;}
void Team::setTeamPoints(int points){m_TeamPoints=points;}
void Team::setTeamGoals(int goals){m_TeamGoals=goals;}
void Team::setTeamCards(int Cards){ m_TeamCards=Cards;}

void Team::insertPlayer(int playerid, std::shared_ptr<Player> player) {
    m_PlayersById.insert(playerid,player);
    PlayerKey* playerKey = player->getThePlayerKey();
    m_PlayersByStats.insert(*playerKey,player);
    m_TeamCards+= player->getCards();
    m_TeamGoals+=player->getGoals();
    if(player->getGoalKeeper())
        m_goaKeeperCount++;
    updateTopScorer();

    player->setGamesHasNotPlayed(m_gamesPlayed);
}

void Team::removePlayer(int playerId) {
    std::shared_ptr<Player> player = m_PlayersById.findValue(playerId);

    PlayerKey *playerKey = player->getThePlayerKey();
    m_PlayersById.remove(playerId);
    m_PlayersByStats.remove(*playerKey);
    m_TeamCards-= player->getCards();
    m_TeamGoals-=player->getGoals();
    if (player->getGoalKeeper())
        m_goaKeeperCount--;
    updateTopScorer();
}

void Team::playGame() {
    this->setGamePlayed(this->getGamePlayed()+1);
}
void Team::winGame(){
    m_TeamPoints+=WIN_POINTS;
}
void Team::drawGame(){
    m_TeamPoints+=DRAW_POINTS;
}


//
void uniteTeams(std::shared_ptr<Team>& newTeam, Team& team1, Team& team2,int newTeamId){
    newTeam = std::make_shared<Team>(newTeamId,
                                     (team1.m_gamesPlayed+team2.m_gamesPlayed),
                                     (team1.m_TeamPoints+team2.m_TeamPoints),
                                     (team1.m_TeamGoals+team2.m_TeamGoals),
                                     (team1.m_TeamCards+team2.m_TeamCards),
                                     (team1.m_goaKeeperCount+team2.m_goaKeeperCount));

    newTeam->m_PlayersById.mergeTrees(team1.m_PlayersById,team2.m_PlayersById);
    newTeam->m_PlayersByStats.mergeTrees(team1.m_PlayersByStats,team2.m_PlayersByStats);
    newTeam->updateTopScorer();
}

bool Team::isTeamKosher() const
{
    return (getNumOfPlayers() >= 11 && m_goaKeeperCount > 0);
}

void Team::updateTopScorer()
{
    if(m_PlayersByStats.isEmpty()){
        m_topScorer= nullptr;
        return;
    }
    m_topScorer=m_PlayersByStats.findMax();
}

int Team::getScore() const {
    return m_TeamPoints + m_TeamGoals - m_TeamCards;
}

bool Team::isEmpty() const {
    return m_PlayersById.isEmpty();
}

void Team::getArrayByPlayerKey(PlayerKey* ptr){
    m_PlayersByStats.getArray(ptr);
}

bool Team::playerExists(int playerId) const{
    return m_PlayersById.keyExists(playerId);
}

std::shared_ptr<Player> Team::findPlayer(int playerId){
    return m_PlayersById.findValue(playerId);
}

void Team::setAllPlayers(){

    node<int,std::shared_ptr<Player>>* root = m_PlayersById.getRoot();
    inorderFixPlayer(root);

}

void Team::inorderFixPlayer(node<int,std::shared_ptr<Player>>* root){

    if( root == nullptr)
        return;
    inorderFixPlayer( root->getLeftSon());
    std::shared_ptr<Player> player = root->getValue();
    player->setTeam(this);
    inorderFixPlayer( root->getRightSon());
}