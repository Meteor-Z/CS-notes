# 现代CPP 要点

这里是关于现代 C/C++ 的一些总结，仅作总结

## 基本六大函数

这里是用vector举例，有以下六种函数 

1. 构造函数 析构函数
2. 拷贝构造 移动构造
3. 拷贝赋值 移动赋值

```cpp
#include <cstddef>
#include <initializer_list>
#include <type_traits>
#include <utility>
#include <new>
#include <iostream>

template <typename T>
class vector 
{
public:
	vector() noexcept
	{
		std::cout << "默认构造" << std::endl;	
	}
	explicit vector(size_t n): m_cap(n), m_ptr(alloc(m_cap)) // 构造函数
	{
		for (; m_len < n; ++m_len)
		{
			construct(m_ptr + m_len);
		}
	}
	vector(size_t n, const T& rhs): m_cap {m_ptr}, m_ptr{alloc(m_cap)}
	{
		for(; m_len < n; ++m_len)
		{
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
		std::cout << "移动构造" << std::endl;
		m_cap = std::exchange(rhs.m_cap, 0);
		m_len = std::exchange(rhs.m_len, 0);
		m_ptr = std::exchange(rhs.m_ptr, nullptr);
	}
	vector(std::initializer_list<T> list): m_cap {list.size()}, m_ptr {alloc(m_cap)}
	{
		std::cout << "列表初始化" << std::endl;
		for (const auto& item: list)
		{
			construct(m_ptr + m_len, item);
			++m_len;
		}
	}
	~vector() noexcept // 析构函数 
	{
		std::cout << "析构函数" << std::endl;
		// do something
	}
	
	vector& operator =(const vector& rhs) // 拷贝赋值
	{
		if (this != &rhs) 
		{
			vector {rhs}.swap(*this);
		}
		return *this;
	}
	vector& operator =(vector&& rhs) noexcept
	{
		std::cout << "移动赋值" << std::endl;
		if (this != &rhs)
		{
			vector {std::move(rhs)}.swap(*this);
		}
		return *this;
	}
	vector& operator =(std::initializer_list<T> list)
	{
		std::cout << "初始化赋值" << std::endl;
		vector {list}.swap(*this);
		return *this;
	}
	void swap(vector& rhs) noexcept
	{
		using std::swap; // 如果已经实现了重载函数，那么优先使用已经实现的。
		//与std::swap()这样有本质的区别！
		swap(m_cap, rhs.m_cap);
		swap(m_len, rhs.m_len);
		swap(m_ptr, rhs.m_ptr);
		
	}		
private:
	T* alloc(size_t n) { return static_cast<T*>(::operator new(n * sizeof(T))); }
	
	void dealloc(T* ptr) { ::operator delete(ptr); }
	
	template <typename... Args>
	void construct(T* ptr, Args&& ... args) { ::new(ptr) T {std::forward<Args>(args)...}; }
	
	void destory(T* ptr) noexcept {	ptr->~T(); }
	
	size_t m_cap {0};
	size_t m_len {0};
	T* m_ptr {nullptr};
	
};    

int main()
{
	// 拷贝赋值 移动赋值
	// 拷贝构造 移动构造
	// 构造函数 析构函数
	vector<std::string> vec_string = {"hello", "nihao"}; // 列表初始化
	vector<int> vec_int = {1, 2, 3, 4}; // 列表初始化
	vector<double> vec_double; // 默认初始化
	vec_double = {1.2, 2.3}; // 拷贝赋值
	vector<int> vec_move_int {std::move(vec_int)}; // 移动构造

	vector<int> test_int = {1, 2, 3, 4, 5}; // 列表初始化
	vec_move_int = std::move(test_int); // 移动复制
	
	// 当离开作用域的时候会出发析构函数
}
```

### consteper-if

可以代替以前通过宏定义的形式来生成配置文件等。其所有的判断其实是编译期的时候就直接完成的。

```cpp
template<typename T>
auto get_val(T t)
{
    if constexpr (std::is_pointer_v<T>) return *t;
    else if constexpr (std::is_same_v<T, int>)
    {
        return std::string("hello");
    } else return t;
}

int main()
{
    std::cout << get_val(1) << std::endl;
    std::cout << get_val(new int(1)) << std::endl;
    return 0;
}
```

std::is_pointer_v<T>，std::is_same_v<T,int>  可以在编译期就可以判断这个数值是否是指针和是否是和int是一个类型，所以说可以得到这个数值，尽管好像是返回多个个数值，但是这其实在编译期就完成了这些操作，所以其实就返回了一个数值。