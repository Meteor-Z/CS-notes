#include <iostream>
#include <unordered_map>
class Node
{
public:
    Node() = default;
    Node(int key, int val) : key(key),  val(val) { }
    ~Node() {
        int* a = new int(1);
        if (next) delete next;
        if (pre) delete pre;
    }
    int key { 0 };
    int val { 0 };
    Node* next { nullptr };
    Node* pre { nullptr };

};
class LRUCache {
public:
    LRUCache(int capacity) : capacity(capacity) 
    {
        head = new Node();
        tail = new Node();
        head->next = tail;
        tail->pre = head;
    } 
    
    int get(int key) 
    {
        if (!cache.count(key))
        {
            return -1;
        }
        Node* ptr = cache[key];
        move_to_head(ptr);
        return ptr->val;   
    }
    void move_to_head(Node* ptr) 
    {
        // 先将这个指针的左右链接起来
        ptr->pre->next = ptr->next; 
        ptr->next->pre = ptr->pre;
        
        ptr->pre = head;
        ptr->next = head->next;

        head->next->pre = ptr;
        head->next = ptr;
        
    }
    void add_to_head(Node* ptr) 
    {
        ptr->pre = head;
        ptr->next = head->next;

        head->next->pre = ptr;
        head->next = ptr;
    }
    void put(int key, int value) 
    {
        if (!cache.count(key)) 
        {
            Node* ptr = new Node(key, value);
            cache.emplace(key, ptr);
            add_to_head(ptr);
            size++;
            if (size > capacity)
            {
                Node* ptr = remove_tail();
                cache.erase(ptr->key);
                delete ptr;
                --size;
            }
        } else 
        {
            Node* ptr = cache[key];
            ptr->val = value;
            move_to_head(ptr);
        }
    }
    Node* remove_tail() 
    {
        Node* cur_ptr = tail->pre;
        cur_ptr->pre->next = tail;
        tail->pre = cur_ptr->pre;
        return cur_ptr;
    }
    ~LRUCache() 
    {
        if (head) delete head;
        if (tail) delete tail;
        for (auto& item: cache)
        {
            delete item.second;
        }
        cache.clear();
    }
private:
    int capacity;
    std::unordered_map<int, Node*> cache;
    Node* head { nullptr };
    Node* tail { nullptr };
    int size { 0 };
};
