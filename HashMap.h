

template <typename K, typename V>
class HashMap {
public:
    HashMap(int capacity) : m_capacity(capacity), m_size(0) {
        m_data = new Node *[capacity];
        for (int i = 0; i < capacity; i++) {
            m_data[i] = nullptr;
        }
    }

    ~HashMap() {
        for (int i = 0; i < m_capacity; i++) {
            Node *cur = m_data[i];
            while (cur != nullptr) {
                Node *next = cur->next;
                delete cur;
                cur = next;
            }
        }
        delete[] m_data;
    }

    void Put(K key, V value) {
        // Increase the size of the hash map if the load factor exceeds 0.75.
        if (static_cast<double>(m_size) / m_capacity > 0.75) {
            Resize(m_capacity * 2 + 1);
        }
        int hash = Hash(key);
        Node * prev = m_data[hash];
        Node *new_node = new Node{key, value, m_data[hash]};
        m_data[hash] = new_node;
        new_node->next = prev;
        m_size++;
    }

    V Get(K key) {
        int hash = Hash(key);
        Node *cur = m_data[hash];
        while (cur != nullptr) {
            if (cur->key == key) {
                return cur->value;
            }
            cur = cur->next;
        }
        // Key not found, throw an exception.
        // throw std::out_of_range("Key not found in hash map");
    }

    bool Contains(K key) {
        int hash = Hash(key);
        Node *cur = m_data[hash];
        while (cur != nullptr) {
            if (cur->key == key) {
                return true;
            }
            cur = cur->next;
        }
        return false;
    }

    int Size() {
        return m_size;
    }
    void Resize(int new_capacity) {
        Node** new_data = new Node*[new_capacity];
        for (int i = 0; i < new_capacity; i++) {
            new_data[i] = nullptr;
        }
        // Rehash all the key-value pairs into the new data array.
        for (int i = 0; i < m_capacity; i++) {
            Node* cur = m_data[i];
            while (cur != nullptr) {
                Node* next = cur->next;
                int hash = Hash(cur->key);
                cur->next = new_data[hash];
                new_data[hash] = cur;
                cur = next;
            }
        }
        delete[] m_data;
        m_data = new_data;
        m_capacity = new_capacity;
    }


private:
    struct Node {
        K key;
        V value;
        Node* next;
    };

    int Hash(K key) {
        return key % m_capacity;
    }

    Node** m_data;
    int m_capacity;
    int m_size;
};


