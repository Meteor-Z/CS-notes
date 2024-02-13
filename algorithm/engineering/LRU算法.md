# LRU算法

- 不直接使用unordered_map存入数据，是因为要将东西放到前面
- 数据实现还是非常简单的
- [leetcode题目](https://leetcode.cn/problems/lru-cache/description/)

```c++
/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
struct Node {
    int key { 0 };
    int value { 0 };
    Node* pre { nullptr };
    Node* next { nullptr };
    Node() = default;
    Node(int key, int value) : key(key), value(value), pre(nullptr), next(nullptr) {}
};

class LRUCache {
public:
    LRUCache(int capacity)
        : m_capacity(capacity), m_size(0), m_head(nullptr), m_tail(nullptr) {
        m_head = new Node();
        m_tail = new Node();
        m_head->next = m_tail;
        m_tail->pre = m_head;
    }

    int get(int key) {
        if (!m_cache.count(key)) {
            return -1;
        }

        Node* node = m_cache[key];
        move_to_head(node);
        return node->value;
    }

    void put(int key, int value) {
        if (!m_cache.count(key)) {
            Node* node = new Node(key, value);

            m_cache[key] = node;

            add_to_head(node);

            m_size++;

            if (m_size > m_capacity) {
                Node* remove_node = remove_tail();
                m_cache.erase(remove_node->key);
                delete remove_node;
                m_size--;
            }
        } else {
            Node* node = m_cache[key];
            node->value = value;
            move_to_head(node);
        }
    }

private:
    void add_to_head(Node* value) {
        value->pre = m_head;
        value->next = m_head->next;

        m_head->next->pre = value;
        m_head->next = value;
    }

    void move_to_head(Node* value) {
        value->pre->next = value->next;
        value->next->pre = value->pre;

        value->pre = m_head;
        value->next = m_head->next;

        m_head->next->pre = value;
        m_head->next = value;
    }

    Node* remove_tail() {
        Node* value = m_tail->pre;

        value->pre->next = value->next;
        value->next->pre = value->pre;

        return value;
    }

private:
    std::unordered_map<int, Node*> m_cache {};
    Node* m_head { nullptr };
    Node* m_tail { nullptr };
    int m_size { 0 };
    int m_capacity { 0 };
};

```