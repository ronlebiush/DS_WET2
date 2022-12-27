//
// Created by ronl on 12/24/2022.
//

#ifndef WET2_PLAYERSHASHTABLE_H
#define WET2_PLAYERSHASHTABLE_H
#include "Player.h"

class PlayersHashTable {
private:
    const static int INIT_SIZE = 31;

    struct Node {
        int m_playerId;
        std::shared_ptr<Player> m_player;
        Node *next;
    };

    Node **table_;
    int m_size;
    int m_capacity;

    int Hash(int playerId);
    int r_Hash(int playerId);
    void resize();

public:
    PlayersHashTable();
    ~PlayersHashTable();
    void Put(int playerId, std::shared_ptr<Player> player);
    std::shared_ptr<Player> Get(int playerId) ;
    bool Contains(int playerId) ;
    void Remove(const int playerId);

};


#endif //WET2_PLAYERSHASHTABLE_H
