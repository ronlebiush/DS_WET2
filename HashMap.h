template <typename K, typename V>
class HashMap {
public:
    HashMap(int capacity) : capacity_(capacity), size_(0) {
        data_ = new Node *[capacity];
        for (int i = 0; i < capacity; i++) {
            data_[i] = nullptr;
        }
    }

    ~HashMap() {
        for (int i = 0; i < capacity_; i++) {
            Node *cur = data_[i];
            while (cur != nullptr) {
                Node *next = cur->next;
                delete cur;
                cur = next;
            }
        }
        delete[] data_;
    }

    void Put(K key, V value) {
        // Increase the size of the hash map if the load factor exceeds 0.75.
        if (static_cast<double>(size_) / capacity_ > 0.75) {
            Resize(capacity_ * 2);
        }
        int hash = Hash(key);
        Node *cur = data_[hash];
        while (cur != nullptr) {
            if (cur->key == key) {
                cur->value = value;
                return;
            }
            cur = cur->next;
        }
        // Key not found, add a new node.
        Node *new_node = new Node{key, value, data_[hash]};
        data_[hash] = new_node;
        size_++;
    }

    V Get(K key) {
        int hash = Hash(key);
        Node *cur = data_[hash];
        while (cur != nullptr) {
            if (cur->key == key) {
                return cur->value;
            }
            cur = cur->next;
        }
        // Key not found, throw an exception.
        throw std::out_of_range("Key not found in hash map");
    }

    bool Contains(K key) {
        int hash = Hash(key);
        Node *cur = data_[hash];
        while (cur != nullptr) {
            if (cur->key == key) {
                return true;
            }
            cur = cur->next;
        }
        return false;
    }

    int Size() {
        return size_;
    }

private:
    struct Node {
        K key;
        V value;
        Node* next;
    };

    int Hash(K key) {
        // Implement a hash function here.
        // You can use the std::hash function if it is available.
        // Otherwise, you can implement your own hash function.

        // For example, you can use the Jenkins hash function:
        // https://en.wikipedia.org/wiki/Jenkins_hash_function
        size_t hash = 0;
        for (unsigned char c : key) {
            hash += c;
            hash += (hash << 10);
            hash ^= (hash >> 6);
        }
        hash += (hash << 3);
        hash ^= (hash >> 11);
        hash += (hash << 15);
        return hash % capacity_;
    }

    Node** data_;
    int capacity_;
    int size_;
};


