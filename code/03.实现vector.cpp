#include <cstddef>
#include <initializer_list>
#include <new>
#include <type_traits>
#include <utility>

namespace my_stl 
{
    template <typename T>
    class vector {
    public:
        vector() noexcept = default;
        explicit vector(size_t n): m_cap(n), m_ptr(alloc(m_cap))
        {
            for (; m_len < n; ++m_len) {
                construct(m_ptr + m_len);
            }
        }
        vector(size_t n, const T& rhs): m_cap {m_ptr}, m_ptr{alloc(m_cap)} 
        {
            for(; m_len < n; ++m_len) {
                construct(m_ptr + m_len, rhs);
            }
        }
        vector(const vector& rhs): m_cap {rhs.m_cap}, m_ptr {alloc(m_cap)} 
        {
            for (; m_len < m_cap; ++m_len)
            {
                construct(m_ptr + m_len, rhs[m_len]);
            }
        }
        vector(vector&& rhs) 
        {
            m_cap = std::exchange(rhs.m_cap, 0);
            m_len = std::exchange(rhs.m_len, 0);
            m_ptr = std::exchange(rhs.m_ptr, nullptr);
        }
        vector(std::initializer_list<T> list): m_cap {list.size()}, m_ptr {alloc(m_cap)} 
        {
            for (const auto& item: list)
            {
                construct(m_ptr + m_len, item);
                ++m_len;
            }
        }
        ~vector() noexcept 
        {
            clear();
            dealloc(m_ptr);
        }

        vector& operator =(const vector& rhs) 
        {
            if (this != &rhs) 
            {
                vector {rhs}.swap(*this);
            }
            return *this;
        }
        vector& operator =(vector&& rhs) noexcept 
        {
            if (this != &rhs)
            {
                vector {std::move(rhs)}.swap(*this);
            }
            return *this;
        }
        vector& operator =(std::initializer_list<T> list) 
        {
            vector {list}.swap(*this);
            return *this;
        }
        
        void push_back(const T& val) 
        {
            emplace_back(val);
        }
        void push_back(T&& val) 
        {
            // 参数永远是左值，所以这里还要进行转换
            emplace_back(std::move(val));
        }

        template<typename... Args>
        void emplace_back(Args&&... args) {
            if (m_len == m_cap) 
            {
                size_t new_cap = m_cap ? m_cap * 2: 1;
                T* new_ptr = alloc(new_cap);
                for (size_t new_len = 0; new_len < m_len; ++new_len)
                {
                    construct(new_ptr + new_len, std::move_if_noexcept(m_ptr[new_len]));
                }
                m_cap = new_cap;
                m_ptr = new_ptr;
            }
            construct(m_ptr + m_len,std::forward<Args>(args)...);
            ++m_len;
        }
        
        void pop_back();


        size_t size() const noexcept { return m_len; }

        size_t capacity() const noexcept { return m_cap; }

        bool empty() const noexcept { return m_len == 0; }

        T& operator[](size_t idx) { return m_ptr[idx]; }

        const T& operator[](size_t idx) const { return m_ptr[idx]; }     

        T* begin() { return m_ptr; }

        T* end() { return m_ptr + m_len;}
        
        const T* begin() const noexcept { return m_ptr; }

        const T* end() const noexcept { return m_ptr + m_len;}

        void swap(vector& rhs) noexcept 
        {
            using std::swap; // 如果已经实现了重载函数，那么优先使用已经实现的。
            //与std::swap()这样有本质的区别！
            swap(m_cap, rhs.m_cap);
            swap(m_len, rhs.m_len);
            swap(m_ptr, rhs.m_ptr);

        }
        void clear() noexcept 
        {
            for (; m_len > 0; m_len --) 
            {
                destory(m_ptr + m_len - 1);
            }
        }

        
    private:
        T* alloc(size_t n) {
            return static_cast<T*>(::operator new(n * sizeof(T)));
        }
        void dealloc(T* ptr) {
            ::operator delete(ptr);
        }
        
        // placement new 用法，在当前内存上构建一个对象。
        template <typename... Args>
        void construct(T* ptr, Args&& ... args) {
            ::new(ptr) T {std::forward<Args>(args)...}; 
        }

        void destory(T* ptr) noexcept {
            ptr->~T();
        }

        size_t m_cap {0};
        size_t m_len {0};
        T* m_ptr {nullptr};
    };    
}
