#include "worldcup23a2.h"

world_cup_t::world_cup_t()=default;

world_cup_t::~world_cup_t()=default;

StatusType world_cup_t::add_team(int teamId)// O(log(k))

{
    if(teamId<=0)
        return StatusType::INVALID_INPUT;


    try {
        std::shared_ptr<Team> team = std::make_shared<Team>(teamId,0);
        if(m_teamsAndPlayers.insertTeam(teamId,team)==StatusType::FAILURE)
            return StatusType::FAILURE;
        m_teamsByAbility.insert(team->getTeamKey(), team);
        return StatusType::SUCCESS;
    }
    catch (std::bad_alloc& ba)
    {
        std::cerr << "bad_alloc caught: " << ba.what() << '\n';
        return StatusType::ALLOCATION_ERROR;
    }
    catch (keyAlreadyTaken& id)
    {
        std::cerr << "keyAlreadyTaken caught: " << id.what() << '\n';
        return StatusType::FAILURE;
    }
}

StatusType world_cup_t::remove_team(int teamId)// O(log(k))
{
    if(teamId <=0)
        return StatusType::INVALID_INPUT;
    try {
        output_t<std::shared_ptr<Team>> teamToRemove = m_teamsAndPlayers.getTeam(teamId);
        if(teamToRemove.status() == StatusType::FAILURE )
            return StatusType::FAILURE;
        TeamKey keyToRemove = teamToRemove.ans()->getTeamKey();
        m_teamsByAbility.remove(keyToRemove);
        StatusType status = m_teamsAndPlayers.removeTeam(teamId);
        if(status!= StatusType::SUCCESS)
            return status;
    }
    catch (std::bad_alloc& ba)
    {
        std::cerr << "bad_alloc caught: " << ba.what() << '\n';
        return StatusType::ALLOCATION_ERROR;
    }
    catch (keyDoesntExist& id)
    {
        std::cerr << "keyDoesntExist caught: " << id.what() << '\n';
        return StatusType::FAILURE;
    }
    return StatusType::SUCCESS;
}

StatusType world_cup_t::add_player(int playerId, int teamId,
                                   const permutation_t &spirit, int gamesPlayed,
                                   int ability, int cards, bool goalKeeper) // O(log(k)) Average
{
    if(playerId <=0 || teamId <= 0 || gamesPlayed < 0 ||cards < 0 || !spirit.isvalid())
        return StatusType::INVALID_INPUT;
    output_t<std::shared_ptr<Team>> output_tTeam = m_teamsAndPlayers.getTeam(teamId);
    if(output_tTeam.status() == StatusType::FAILURE )
        return StatusType::FAILURE;
    m_teamsByAbility.remove(output_tTeam.ans()->getTeamKey());

    std::shared_ptr<Player> player = std::make_shared<Player>(playerId,spirit,gamesPlayed,ability,cards,goalKeeper);
    if(m_teamsAndPlayers.insertPlayer(teamId,playerId,player)!=StatusType::SUCCESS) {
        return StatusType::FAILURE;
    }

    m_teamsByAbility.insert(output_tTeam.ans()->getTeamKey(),output_tTeam.ans());
    std::shared_ptr<Team> teamOfPlayer= m_teamsAndPlayers.findPlayersTeam(playerId);
    return StatusType::SUCCESS;
}

//enum struct MatchStatus {
//    DRAW                = 0,
//    TEAM_1_ABILITY_WIN  = 1,
//    TEAM_1_SPIRIT_WIN   = 2,
//    TEAM_2_ABILITY_WIN  = 3,
//    TEAM_2_SPIRIT_WIN   = 4,
//};
enum MatchStatus { DRAW ,TEAM_1_ABILITY_WIN ,TEAM_1_SPIRIT_WIN ,TEAM_2_ABILITY_WIN ,TEAM_2_SPIRIT_WIN };

MatchStatus getMatchStatus(std::shared_ptr<Team> team1,std::shared_ptr<Team> team2){
    int team1SumPointsAndAbility = team1->getScore();
    int team2SumPointsAndAbility = team2->getScore();
    int team1SpiritStrength = team1->getSpirit().strength();
    int team2SpiritStrength = team2->getSpirit().strength();

    if(team1SumPointsAndAbility==team2SumPointsAndAbility){
        if(team1SpiritStrength==team2SpiritStrength)
            return MatchStatus::DRAW;

        else if (team1SpiritStrength >team2SpiritStrength)
            return MatchStatus::TEAM_1_SPIRIT_WIN;

        else
            return MatchStatus::TEAM_2_SPIRIT_WIN;
    }
    else{
        if(team1SumPointsAndAbility>team2SumPointsAndAbility)
            return MatchStatus::TEAM_1_ABILITY_WIN;
        return MatchStatus::TEAM_2_ABILITY_WIN;
    }
}

output_t<int> world_cup_t::play_match(int teamId1, int teamId2) //  O(log(k)) worst case
{
    if (teamId1 <= 0 || teamId2 <= 0 || teamId1 == teamId2)
    {
        return StatusType::INVALID_INPUT;
    }
    output_t<std::shared_ptr<Team>> output_t_team1 = m_teamsAndPlayers.getTeam(teamId1);
    if(output_t_team1.status() == StatusType::FAILURE )
        return StatusType::FAILURE;
    output_t<std::shared_ptr<Team>> output_t_team2 = m_teamsAndPlayers.getTeam(teamId2);
    if(output_t_team2.status() == StatusType::FAILURE )
        return StatusType::FAILURE;
    if ((!output_t_team1.ans()->isTeamKosher()) || (!output_t_team1.ans()->isTeamKosher()))
    {
        return StatusType::FAILURE;
    }
    output_t_team1.ans()->playGame();
    output_t_team2.ans()->playGame();
    MatchStatus matchStatus = getMatchStatus(output_t_team1.ans(),output_t_team2.ans());
    switch(matchStatus)
    {
        case(DRAW) :
            output_t_team1.ans()->drawGame();
            output_t_team2.ans()->drawGame();
            break;
        case(TEAM_1_ABILITY_WIN) :
        case(TEAM_1_SPIRIT_WIN) :
            output_t_team1.ans()->winGame();
            break;
        default:
            output_t_team2.ans()->winGame();
    }
    return  (int)matchStatus;
}

output_t<int> world_cup_t::num_played_games_for_player(int playerId) // O(log*(n)) Average
{
    if (playerId <= 0)
        return StatusType::INVALID_INPUT;
    return m_teamsAndPlayers.num_played_games_for_player(playerId);
}

StatusType world_cup_t::add_player_cards(int playerId, int cards)
{
    if(playerId <= 0 || cards < 0)
        return StatusType::INVALID_INPUT;
    output_t<std::shared_ptr<Player>> output_t_Player = m_teamsAndPlayers.getPlayer(playerId);
    if(output_t_Player.status() == StatusType::FAILURE )
        return StatusType::FAILURE;
    output_t_Player.ans()->setCards(output_t_Player.ans()->getCards()+cards);
    m_teamsAndPlayers.findPlayersTeam(playerId);//for log*n
    return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_player_cards(int playerId) // O(1) Average
{
    if(playerId <= 0)
        return StatusType::INVALID_INPUT;
    output_t<std::shared_ptr<Player>> output_t_Player = m_teamsAndPlayers.getPlayer(playerId);
    if(output_t_Player.status() == StatusType::FAILURE )
        return StatusType::FAILURE;
    return output_t_Player.ans()->getCards();

}

output_t<int> world_cup_t::get_team_points(int teamId) //  O(log(k)) worst case
{
    output_t<std::shared_ptr<Team>> output_tTeam = m_teamsAndPlayers.getTeam(teamId);
    if(output_tTeam.status() == StatusType::FAILURE )
        return StatusType::FAILURE;
    return output_tTeam.ans()->getTeamPoints();
}

output_t<int> world_cup_t::get_ith_pointless_ability(int i)
{
    try{
        std::shared_ptr<Team> team = m_teamsByAbility.findByRank(i+1);
        return team->getTeamId();
    }
    catch ( RankIsNotInRange&)
    {
        return StatusType::FAILURE;
    }

}

output_t<permutation_t> world_cup_t::get_partial_spirit(int playerId)
{
    return m_teamsAndPlayers.get_partial_spirit(playerId);
}

StatusType world_cup_t::buy_team(int teamId1, int teamId2) //(int buyerTeamId, int boughtTeamId)
{
    output_t<std::shared_ptr<Team>> output_t_buyerTeam = m_teamsAndPlayers.getTeam(teamId1);
    if(output_t_buyerTeam.status() == StatusType::FAILURE )
        return StatusType::FAILURE;
    output_t<std::shared_ptr<Team>> output_t_boughtTeam = m_teamsAndPlayers.getTeam(teamId2);
    if(output_t_boughtTeam.status() == StatusType::FAILURE )
        return StatusType::FAILURE;
    m_teamsByAbility.remove(output_t_buyerTeam.ans()->getTeamKey());
    m_teamsByAbility.remove(output_t_boughtTeam.ans()->getTeamKey());

    m_teamsAndPlayers.unionTeams(teamId1,teamId2);

    m_teamsByAbility.insert(output_t_buyerTeam.ans()->getTeamKey(),output_t_buyerTeam.ans());
    m_teamsByAbility.insert(output_t_boughtTeam.ans()->getTeamKey(),output_t_buyerTeam.ans());



    return StatusType::SUCCESS;
}