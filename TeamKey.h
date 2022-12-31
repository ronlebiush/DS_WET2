//
// Created by Pasha on 31/12/2022.
//

#ifndef WET2_TEAMKEY_H
#define WET2_TEAMKEY_H

class TeamKey{

private:
    int m_ability;
    int m_teamID;
public:
    TeamKey(int ability , int teamID);
    int getAbility() const;
    int getTeamID() const;
    bool  operator>(const TeamKey& other) const;


};






#endif //WET2_TEAMKEY_H
