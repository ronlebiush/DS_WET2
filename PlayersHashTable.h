//
// Created by ronl on 12/24/2022.
//

#ifndef WET2_PLAYERSHASHTABLE_H
#define WET2_PLAYERSHASHTABLE_H
#include <utility>

#include "Player.h"
#include "PlayerNode.h"

class PlayersHashTable {
private:
    const static int INIT_SIZE = 31;

    PlayerNode **m_table;
    int m_size;
    int m_capacity;

    int Hash(int playerId) const;
    //nt r_Hash(int playerId);
    void resize(int newCapacity);

public:
    PlayersHashTable();
    ~PlayersHashTable();
    void insert(int playerId, std::shared_ptr<Player> player);
    std::shared_ptr<Player> getPlayer(int playerId) ;
    PlayerNode* getNode(int playerId);
    bool Contains(int playerId)const ;
    //void Remove(const int playerId);
};

#endif //WET2_PLAYERSHASHTABLE_H