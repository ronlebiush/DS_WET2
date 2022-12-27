//
// Created by ronl on 12/24/2022.
//

#include "PlayersHashTable.h"


int PlayersHashTable::Hash(int playerId) {
    return playerId % m_capacity;
}
int r_Hash(int playerId) {
    return 1+ (playerId%capacity)
}

void resize();

PlayersHashTable();
~PlayersHashTable();
void Put(int playerId, std::shared_ptr<Player> player);
std::shared_ptr<Player> Get(int playerId) ;
bool Contains(int playerId) ;
void Remove(const int playerId);


int NextMersennePrime(int n) {
    // Implement a function that returns the next Mersenne prime number greater than or equal to n
}

void Resize() {
    int new_capacity = NextMersennePrime(m_capacity * 2);
    Node **new_table = new Node *[new_capacity]();

    for (int i = 0; i < m_capacity; i++) {
        Node *entry = table_[i];
        while (entry != nullptr) {
            Node *next = entry->next;
            int index = Hash(entry->key, new_capacity, kMersennePrime);
            int step = r_Hash(entry->key, new_capacity, kMersennePrime);
            while (new_table[index] != nullptr) {
                index = (index + step) % new_capacity;
            }
            new_table[index] = entry;
            entry->next = nullptr;
            entry = next;
        }
    }

    delete[] table_;
    table_ = new_table;
    m_capacity = new_capacity;
}

public:

HashTable(int capacity) : m_size(0), m_capacity(capacity) {
    table_ = new Node *[m_capacity]();
}

~HashTable() {
    for (int i = 0; i < m_capacity; i++) {
        Node *entry = table_[i];
        while (entry != nullptr) {
            Node *prev = entry;
            entry = entry->next;
            delete prev;
        }
        table_[i] = nullptr;
    }
    delete[] table_;
}

void Put(const K &key, const V &value) {
    int index = Hash(key, m_capacity, kMersennePrime);
    int step = r_Hash(key, m_capacity, kMersennePrime);
    Node *entry = table_[index];
    while (entry != nullptr) {
        if (entry->key == key) {
            entry->value = value;
            return;
        }
        index = (index + step) % m_capacity;
        entry = table_[index];
    }

    entry = new Node{key, value, table_[index]};
    table_[index] = entry;
    m_size++;

    if (m_size > kLoadFactor * m_capacity) {
        Resize();
    }
}

V Get(const K &key) {
    int index = Hash(key, m_capacity, kMersennePrime);
    int step = r_Hash(key, m_capacity, kMersennePrime);
    Node *entry = table_[index];
    while (entry != nullptr) {
        if (entry->key == key) {
            return entry->value;
        }
        index = (index + step) % m_capacity;
        entry = table_[index];
    }
    throw std::out_of_range("Key not found in hash table");
}

bool Contains(const K &key) {
    int index = Hash(key, m_capacity, kMersennePrime);
    int step = r_Hash(key, m_capacity, kMersennePrime);
    Node *entry = table_[index];
    while (entry != nullptr) {
        if (entry->key == key) {
            return true;
        }
        index = (index + step) % m_capacity;
        entry = table_[index];
    }
    return false;
}

void Remove(const K &key) {
    int index = Hash(key, m_capacity, kMersennePrime);
    int step = r_Hash(key, m_capacity, kMersennePrime);
    Node *entry = table_[index];
    if (entry == nullptr) {
        return;
    }
    if (entry->key == key) {
        table_[index] = entry->next;
        delete entry;
        m_size--;
        return;
    }
    while (entry->next != nullptr) {
        if (entry->next->key == key) {
            Node *temp = entry->next;
            entry->next = entry->next->next;
            delete temp;
            m_size--;
            return;
        }
        index = (index + step) % m_capacity;
        entry = entry->next;
    }
}

};
