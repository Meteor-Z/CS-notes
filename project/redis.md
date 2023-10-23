# redis

多个客户端和服务端，客户端发送TCP请求，发送给服务端，然后服务端进行请求

## 数据结构

### 哈希表

```c++
struct HNode {
    HNode *next = nullptr;
    uint64_t hcode = 0;
};

// a simple fixed-sized hashtable
struct HTab {
    HNode **tab = nullptr;
    size_t mask = 0;
    size_t size = 0;
};
```

这里面HNode* 是指向指针的指针，其实是相当于一个数组，每一个数组都有一个指针。

```c++
// n must be a power of 2
static void h_init(HTab *htab, size_t n) {
    assert(n > 0 && ((n - 1) & n) == 0); // (n - 1) & n 其实就是判断是否是2的power
    htab->tab = (HNode **)calloc(sizeof(HNode *), n);
    htab->mask = n - 1; // 掩码 2的幂是 100000，掩码就是 11111, ，然后下面的pos 只要& 就会得到 hcode中的位置。
    htab->size = 0;
}

// hashtable insertion
static void h_insert(HTab *htab, HNode *node) {
    size_t pos = node->hcode & htab->mask;
    HNode *next = htab->tab[pos];

    node->next = next;
    htab->tab[pos] = node;
    htab->size++;
/*
相当于 cur -> a ，插入B的话，那么答案就是 cur-> b -> a;
所以插入的时间复杂度是O(1)
*/
}
```

### 侵入时数据结构

平常的数据结构是非侵入式数据结构

```c++
template<typename T>
struct ListNode {
    ListNode* prev;
    ListNode* next;
    T value;
}
```

侵入时的数据结构是这样的，`对象的内部状态由外部对象管理`

```c++
struct ListNode {
    ListNode* prev;
    ListNode* next;
}

template<typename T>
struct Data {
    ListNode list;
    T value;
}
```

每一个节点都包含指向下一节点的指针，并且连接关系由节点本身来决定，在访问链表的时候，客户端必须要入侵到数据结构内部的对象里面才能管理对象。
