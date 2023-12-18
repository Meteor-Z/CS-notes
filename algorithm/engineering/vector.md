# vector

- `operator new` 和 `placement new` 要搞清楚
- `const` 和 `noexpect` 加入的合适地方
- 移动构造函数一定要加入`noexpect`


```c++
#include <bits/stdc++.h>

namespace my_code {
template <typename T>
class vector {
public:
    friend void swap(T& a, T& b) { a.swap(b); }

public:
    explicit vector() noexcept = default;
    vector(std::size_t n) : m_cap(n), m_ptr(alloc(n)) {
        for (; m_len < m_cap; m_len++) {
            construct(m_ptr + m_len);
        }
    }

    vector(std::size_t n, const T& val) {
        for (; m_len < m_cap; m_len++) {
            construct(m_ptr, m_ptr + m_len);
        }
    }

    vector(const vector& other) : m_cap(other.m_cap), m_ptr(other.m_cap) {
        for (; m_len < m_cap; m_len++) {
            construct(m_ptr + m_len, other.m_cap + m_cap);
        }
    }

    vector(vector&& rhs) noexcept {
        // 将 obj 的数值返回，并将 new_val 赋值给 obj
        m_cap = std::exchange(rhs.m_cap, 0);
        m_len = std::exchange(m_len, 0);
        m_ptr = std::exchange(rhs.m_ptr, nullptr);
    }

    vector(std::initializer_list<T> list) : m_cap(list.size()), m_ptr(alloc(list.size())) {
        for (const auto& item : list) {
            construct(m_ptr + m_len, item);
            m_len++;
        }
    }

    void swap(vector& other) noexcept {
        // 这里不能直接使用 std::swap(),如果没有自己实现的话，那么才会调用标准库里面的
        using std::swap;
        swap(m_cap, other.m_cap);
        swap(m_len, other.m_len);
        swap(m_ptr, other.m_ptr);
    }

    void clear() {
        for (; m_len > 0; m_len--) {
            destroy(m_ptr + m_len - 1);
        }
    }

    ~vector() noexcept {
        clear();
        dealloc(m_ptr);
    }

    vector& operator=(const vector& rhs) {
        if (&this != rhs) {
            vector { rhs }.swap(*this);
        }
    }
    vector& operator=(vector&& rhs) noexcept {
        if (*this != rhs) {
            vector { std::move(rhs) }.swap(*this);
        }
        return *this;
    }

    vector& operator=(std::initializer_list<T> list) {
        vector { list }.swap(*this);
        return *this;
    }

    void push_back(const T& val) { emplace_back(val); }
    void push_back(T&& rhs) { emplace_back(std::move(rhs)); }

    template <typename... Args>
    void emplace_back(Args&&... args) {
        if (m_len == m_cap) {
            auto new_cap = m_cap ? m_cap * 2 : 1;
            auto new_ptr = alloc(new_cap);
            for (size_t new_len = 0; new_len < m_len; new_len++) {
                construct(new_ptr + new_len, std::move_if_noexcept(m_ptr[new_len]));
            }
            m_cap = new_cap;
            std::swap(m_ptr, new_ptr);
            dealloc(new_ptr);
        }
        construct(m_ptr + m_len, std::forward<Args>(args)...);
        m_len++;
    }

    void pop_back() noexcept {
        destroy(m_ptr + m_len - 1);
        m_len--;
    }
    size_t size() const noexcept { return m_len; }
    size_t capacity() const noexcept { return m_cap; }
    bool empty() const noexcept { return m_len == 0; }

    // 取地址
    T& operator[](size_t index) { return m_ptr[index]; }
    // const my::vector 进行调用的
    const T& operator[](size_t index) const { return m_ptr[index]; }

    T* begin() { return m_ptr; }
    T* end() { return m_ptr + m_len; }

    const T* begin() const noexcept { return m_ptr; }
    const T* end() const noexcept { return m_ptr + m_len; }

private:
    // 得到一堆的内存
    T* alloc(size_t num) { return static_cast<T*>(::operator new(sizeof(T) * num)); }

    void dealloc(T* ptr) noexcept { ::operator delete(ptr); }

    // 在当前一小块内存上进行构造
    template <typename... Args>
    void construct(T* ptr, Args&&... args) {
        ::new (ptr) T(std::forward<Args>(args)...);
    }

    // 里面区域的每一个元素的析构
    void destroy(T* ptr) noexcept { ptr->~T(); }

private:
    size_t m_cap { 0 }; // 容量
    size_t m_len { 0 }; // 大小
    T* m_ptr { nullptr };
};
} // namespace my_code

```