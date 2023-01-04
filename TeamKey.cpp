//
// Created by Pasha on 31/12/2022.
//

#include "TeamKey.h"


TeamKey::TeamKey(int ability, int teamID):
m_ability(ability),
m_teamID(teamID)
{}


int TeamKey::getAbility() const {
    return m_ability;
}

int TeamKey::getTeamID() const {
    return m_teamID;
}

bool TeamKey::operator < (const TeamKey &other) const {
    if(m_ability < other.getAbility())
    {return true;}
    else if(m_ability == other.getAbility())
    {
        if(m_teamID < other.getTeamID())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool TeamKey::operator > (const TeamKey &other) const {
    if(m_ability > other.getAbility())
    {return true;}
    else if(m_ability == other.getAbility())
    {
        if(m_teamID > other.getTeamID())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}


bool TeamKey::operator==(const TeamKey &other) const {
    if(m_teamID == other.m_teamID)
    {
        return true;
    }
    else
    {
        return false;
    }
}