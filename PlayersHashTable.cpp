//
// Created by ronl on 12/24/2022.
//

#include "PlayersHashTable.h"


PlayersHashTable::PlayersHashTable():m_size(0),m_capacity(7) {
    m_table = new PlayerNode *[m_capacity];
    for (int i = 0; i < m_capacity; i++) {
        m_table[i] = nullptr;
    }
}

PlayersHashTable::~PlayersHashTable() {
    for (int i = 0; i < m_capacity; i++) {
        PlayerNode *cur = m_table[i];
        while (cur != nullptr) {
            PlayerNode *next = cur->m_next;
            delete cur;
            cur = next;
        }
    }
    delete[] m_table;
}


void PlayersHashTable::insert(int playerId, std::shared_ptr<Player> player) {
    if (m_size*2 > m_capacity) {
        resize(m_capacity * 2 + 1);
    }
    int hash = Hash(playerId);
    PlayerNode* new_node = new PlayerNode(playerId, std::move(player), m_table[hash]);
    m_table[hash] = new_node;
    m_size++;
}
std::shared_ptr<Player> PlayersHashTable::getPlayer(int playerId) {
    int hash = Hash(playerId);
    PlayerNode *cur = m_table[hash];
    while (cur != nullptr) {
        if (cur->m_playerId == playerId) {
            return cur->m_player;
        }
        cur = cur->m_next;
    }
    // Key not found, throw an exception.
    //throw std::out_of_range("Key not found in hash map");
    return nullptr;
}

PlayerNode* PlayersHashTable::getNode(int playerId){
    int hash = Hash(playerId);
    PlayerNode *cur = m_table[hash];
    while (cur != nullptr) {
        if (cur->m_playerId == playerId) {
            return cur;
        }
        cur = cur->m_next;
    }
    // Key not found, throw an exception.
    //throw std::out_of_range("Key not found in hash map");
    return nullptr;
}

bool PlayersHashTable::Contains(int playerId)const {
    int hash = Hash(playerId);
    PlayerNode *cur = m_table[hash];
    while (cur != nullptr) {
        if (cur->m_playerId == playerId) {
            return true;
        }
        cur = cur->m_next;
    }
    return false;
}


void PlayersHashTable::resize(int newCapacity) {
    PlayerNode** new_data = new PlayerNode*[newCapacity];
    int oldCapacity = m_capacity;
    m_capacity = newCapacity;
    for (int i = 0; i < newCapacity; i++) {
        new_data[i] = nullptr;
    }
    // Rehash all the key-value pairs into the new data array.
    for (int i = 0; i < oldCapacity; i++) {
        PlayerNode* cur = m_table[i];
        while (cur != nullptr) {
            PlayerNode* next = cur->m_next;
            int hash = Hash(cur->m_playerId);
            cur->m_next = new_data[hash];
            new_data[hash] = cur;
            cur = next;
        }
    }
    delete[] m_table;
    m_table = new_data;
    m_capacity = newCapacity;
}

int PlayersHashTable::Hash(int teamId) const{
    return teamId % m_capacity;
}