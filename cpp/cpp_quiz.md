# CPP quiz

## 1

```c++

```

## 2

```c++
#include <iostream>
#include <string>

void f(const std::string &) { std::cout << 1; } // one

void f(const void *) { std::cout << 2; } // two

int main() {
  f("foo");
  const char *bar = "bar";
  f(bar);
}
```

答案 22
字符串常量注定不是std::string，因为要进行转换，但是const void* 不需要进行转换，所以这里优先选择第二个，两个都是优先选择第二个

## 3

```c++

```

## 4

```c++

```

## 5

```c++

```

## 6

```c++

```

## 7

```c++

```

## 8

```c++

```

## 9

```c++

```

## 10

```c++

```

## 11

```c++

```

## 12

```c++

```

## 13

```c++

```

## 14

```c++

```

## 15

```c++

```

## 16

```c++

```

## 17

```c++

```

## 18

```c++

```

## 19

```c++

```

## 20

```c++

```

## 21

```c++

```

## 22

```c++

```

## 23

```c++

```

## 24

```c++

```

## 25

```c++

```

## 26

```c++

```

## 27

```c++

```

## 28

```c++

```

## 29

```c++

```

## 30

```c++

```

## 31

```c++
#include <iostream>

struct X {
  X() { std::cout << "X"; }
};

struct Y {
  Y(const X &x) { std::cout << "Y"; }
  void f() { std::cout << "f"; }
};

int main() {
  Y y(X()); // one
  y.f();
}
```

答案 CE
因为one这里其实是声明一个函数。。。而不是一个一个变量。。所以还是优先使用花括号初始化吧，但是

## 32

```c++

```

## 33

```c++

```

## 34

```c++

```

## 35

```c++
#include <iostream>
#include <vector>

int main() {
  std::vector<int> v1(1, 2);
  std::vector<int> v2{ 1, 2 };
  std::cout << v1.size() << v2.size();
}
```

答案 输出：12
很简单，列表初始化的知识，如果出现`{}`,优先使用`{}`.

## 36

```c++

```

## 37

```c++

```

## 38

```c++

```

## 39

```c++

```

## 40

```c++

```

## 41

```c++

```

## 42

```c++

```

## 43

```c++

```

## 44

```c++

```

## 45

```c++

```

## 46

```c++

```

## 47

```c++

```

## 48

```c++

```

## 49

```c++

```

## 50

```c++

```

## 51

```c++

```

## 52

```c++

```

## 53

```c++

```

## 54

```c++

```

## 55

```c++

```

## 56

```c++

```

## 57

```c++

```

## 58

```c++

```

## 59

```c++

```

## 60

```c++

```

## 61

```c++

```

## 62

```c++

```

## 63

```c++

```

## 64

```c++

```

## 65

```c++

```

## 66

```c++

```

## 67

```c++

```

## 68

```c++

```

## 69

```c++

```

## 70

```c++

```

## 71

```c++

```

## 72

```c++

```

## 73

```c++

```

## 74

```c++

```

## 75

```c++

```

## 76

```c++

```

## 77

```c++

```

## 78

```c++

```

## 79

```c++

```

## 80

```c++

```

## 81

```c++

```

## 82

```c++

```

## 83

```c++

```

## 84

```c++

```

## 85

```c++

```

## 86

```c++

```

## 87

```c++

```

## 88

```c++

```

## 89

```c++

```

## 90

```c++

```

## 91

```c++

```

## 92

```c++

```

## 93

```c++

```

## 94

```c++

```

## 95

```c++

```

## 96

```c++

```

## 97

```c++

```

## 98

```c++

```

## 99

```c++

```

## 100

```c++

```

## 101

```c++

```

## 102

```c++

```

## 103

```c++

```

## 104

```c++

```

## 105

```c++

```

## 106

```c++
#include <iostream>

extern "C" int x; // one
extern "C" { int y; } // two

int main() {

  std::cout << x << y;

  return 0;
}
```

答案 UB(更像CE)
这里 one 只是一个声明，也就是说没有链接，two这里是一个定义，所以这里没有这个x的链接，虽然答案是UB，但是我觉得答案就是CE

## 107

```c++

```

## 108

```c++
#include <algorithm>
#include <iostream>

int main() {
    int x = 10;
    int y = 10;

    const int &max = std::max(x, y);
    const int &min = std::min(x, y);

    x = 11;
    y = 9;

    std::cout << max << min;
}
```c++

```

## 109

```c++

```

## 110

```c++

```

## 111

```c++

```

## 112

```c++

```

## 113

```c++

```

## 114

```c++

```

## 115

```c++

```

## 116

```c++
#include <iostream>
#include <utility>

int y(int &) { return 1; }
int y(int &&) { return 2; }

template <class T> int f(T &&x) { return y(x); }
template <class T> int g(T &&x) { return y(std::move(x)); }
template <class T> int h(T &&x) { return y(std::forward<T>(x)); }

int main() {
  int i = 10;
  std::cout << f(i) << f(20);
  std::cout << g(i) << g(20);
  std::cout << h(i) << h(20);
  return 0;
}
```

答案 112212
太简单了，了解一下相关的知识点就知道了

## 117

```c++

```

## 118

```c++
#include <iostream>

void print(char const *str) { std::cout << str; }
void print(short num) { std::cout << num; }

int main() {
  print("abc");
  print(0); // one
  print('A');
}
```

答案 CE
one 这里的 0 都可以调用，但是根据重载决议，这里都可以进行传唤，但是没有一个更好，导致摸棱两可，所以这里直接CE

## 119

```c++

```

## 120

```c++

```

## 121

```c++

```

## 122

```c++

```

## 123

```c++

```

## 124

```c++

```

## 125

```c++

```

## 126

```c++

```

## 127

```c++

```

## 128

```c++
#include <iostream>

volatile int a;

int main() {
  std::cout << (a + a);
}
```

答案 UB
没看懂

## 129

```c++
#include <vector>
#include <iostream>

using namespace std;

int main() {
  vector<char> delimiters = { ",", ";" };  
  cout << delimiters[0];
}
```

答案 UB
没看懂，我的电脑直接报错了，不清楚这里咋了，但是显示的是`fist last`。。。

## 130

```c++

```

## 131

```c++

```

## 132

```c++

```

## 133

```c++
#include <iostream>
using namespace std;

class A
{
public:
    A() { cout << "A"; }
    A(const A &) { cout << "a"; }
};

class B: public virtual A
{
public:
    B() { cout << "B"; }
    B(const B &) { cout<< "b"; }
};

class C: public virtual A
{
public:
    C() { cout<< "C"; }
    C(const C &) { cout << "c"; }
};

class D:B,C
{
public:
    D() { cout<< "D"; }
    D(const D &) { cout << "d"; }
};

int main()
{
    D d1;
    D d2(d1);
}
```

答案 输出：ABCDABCDd
构造函数的时候，如果不是显示的调用父类的构造函数，那么就默认的使用普通的构造函数

## 134

```c++

```

## 135

```c++

```

## 136

```c++

```

## 137

```c++

```

## 138

```c++

```

## 139

```c++

```

## 140

```c++

```

## 141

```c++

```

## 142

```c++

```

## 143

```c++

```

## 144

```c++

```

## 145

```c++

```

## 146

```c++

```

## 147

```c++

```

## 148

```c++

```

## 149

```c++

```

## 150

```c++

```

## 151

```c++

```

## 152

```c++

```

## 153

```c++

```

## 154

```c++

```

## 155

```c++

```

## 156

```c++

```

## 157

```c++
#include <iostream>
#include <typeinfo>

struct A {};

int main() 
{
    std::cout<< (&typeid(A) == &typeid(A));
}
```

答案： UB(未指定行为)
typeid()是一个运算符
在cppreference上查到，typeid返回的是一个type_info，但是不保证同一类型上的 typeid 表达式的所有求值都指代同一个 std::type_info 实例，不过这些 type_info 对象的 std::type_info::hash_code 相同，它们的 std::type_index 也相同。
当应用于多态类型的表达式时，typeid 表达式的求值可能涉及运行时开销（虚表查找），其他情况下 typeid 表达式都在编译时解决，可能在运行期求值，也有可能在编译期求值。

```c++
const std::type_info& ti1 = typeid(A);
const std::type_info& ti2 = typeid(A);
 
assert(&ti1 == &ti2); // 不保证
assert(ti1.hash_code() == ti2.hash_code()); // 保证
assert(std::type_index(ti1) == std::type_index(ti2)); // 保证
```

## 158

```c++

```

## 159

```c++
#include <iostream>

int i;

void f(int x) {
    std::cout << x << i;
}

int main() {
    i = 3;
    f(i++);
}
```

答案 34
i++和++i的区别，先将3传入，然后i就会变成4了，答案就是34

## 160

```c++
#include <iostream>

struct A {
    virtual void foo (int a = 1) {
        std::cout << "A" << a;
    }
};

struct B : A {
    virtual void foo (int a = 2) {
        std::cout << "B" << a;
    }
};

int main () {
    A *b = new B;
    b->foo();
}
```

答案 B2
根据标准，默认实现并不会进行使用，使用父类的，如果传入了，那么肯定用传入的参数。

## 161

```c++

```

## 162

```c++

```

## 163

```c++

```

## 164

```c++

```

## 165

```c++

```

## 166

```c++

```

## 167

```c++

```

## 168

```c++

```

## 169

```c++

```

## 170

```c++

```

## 171

```c++

```

## 172

```c++

```

## 173

```c++

```

## 174

```c++

```

## 175

```c++

```

## 176

```c++

```

## 177

```c++

```

## 178

```c++

```

## 179

```c++

```

## 180

```c++

```

## 181

```c++

```

## 182

```c++

```

## 183

```c++

```

## 184

```c++

```

## 185

```c++
#include <iostream>

template <typename T> void f() {
  static int stat = 0;
  std::cout << stat++;
}

int main() {
  f<int>();
  f<int>();
  f<const int>();
}
```

答案 010
根据模板`f(const int )`和`f(int)`是不一样的函数，所以这里其实会生成两个两个函数，那么static相当于在这个两个函数中都有一份，所以是010

## 186

```c++

```

## 187

```c++
#include <iostream>

struct C {
  C() { std::cout << "1"; }
  C(const C& other) { std::cout << "2"; }
  C& operator=(const C& other) { std::cout << "3"; return *this;}
};

int main() {
  C c1;
  C c2 = c1;
}
```

答案： 12
很简单，初始化的问题，`C c2 = c1`与`C c2(c1)`其实是等价的，两者都是赋值初始化。

## 188

```c++

```

## 189

```c++

```

## 190

```c++

```

## 191

```c++

```

## 192

```c++

```

## 193

```c++

```

## 194

```c++

```

## 195

```c++
#include <iostream>
#include <cstddef>
#include <type_traits>

int main() {
  std::cout << std::is_pointer_v<decltype(nullptr)>;
}
```

答案 0
std::nullptr_t 是空指针字面量 nullptr 的类型。 它是既非指针类型亦非指向成员指针类型的独立类型，啥也不是

## 196

```c++
#include <iostream>

namespace x {
  class C {};
  void f(const C& i) {
    std::cout << "1";
  }
}

namespace y {
  void f(const x::C& i) {
    std::cout << "2";
  }
}

int main() {
  f(x::C());
}
```

答案 输出1
虽然f函数没有指定命名空间，但是根据传参查找，这里调用的是`namespace x`里面的函数
[ADL](https://zh.wikipedia.org/wiki/%E4%BE%9D%E8%B5%96%E4%BA%8E%E5%AE%9E%E5%8F%82%E7%9A%84%E5%90%8D%E5%AD%97%E6%9F%A5%E6%89%BE)

## 197

```c++
#include <iostream>

int j = 1;

int main() {
  int& i = j, j;
  j = 2;
  std::cout << i << j;
}
```

答案 12
这里其实是`int& i = j; int j;`。。。 所以答案显然易见。就是12（第二个修改的是局部变量）

## 198

```c++
#include <iostream>

namespace A {
  extern "C" { int x; }
};

namespace B {
  extern "C" { int x; }
};

int A::x = 0;

int main() {
  std::cout << B::x;
  A::x=1;
  std::cout << B::x;
}
```

答案 CE
出现在不同命名空间作用域中的具有相同名称（忽略限定它的命名空间名称）的 C 语言链接变量的两个声明引用同一变量。
这里两个都是定义，定义两个相同的名字是错误的，CE
注意下面的用法

```c++
extern "C" int i;                   // declaration 声明
extern "C" {
  int i;                            // definition // 定义
}
```


## 199

```c++

```

## 200

```c++

```

## 201

```c++

```

## 202

```c++

```

## 203

```c++

```

## 204

```c++

```

## 205

```c++

```

## 206

```c++
#include <iostream>

int main() {
   int n = sizeof(0)["abcdefghij"]; 
   std::cout << n;   
}
```

答案 1
有点像 `std::cout << '\n'[i==n]`这样子，

## 207

```c++
#include <iostream>
#include <map>
using namespace std;

int main() {
    map<int, int> m;
    cout << m[42];
}
```

答案 输出：0
如果没有的话，相当于塞了一个0进入。

## 208

```c++

```

## 209

```c++

```

## 210

```c++

```

## 211

```c++

```

## 212

```c++

```

## 213

```c++

```

## 214

```c++

```

## 215

```c++

```

## 216

```c++

```

## 217

```c++

```

## 218

```c++

```

## 219

```c++

```

## 220

```c++

```

## 221

```c++

```

## 222

```c++

```

## 223

```c++

```

## 224

```c++

```

## 225

```c++

```

## 226

```c++

```

## 227

```c++

```

## 228

```c++

```

## 229

```c++

```

## 230

```c++

```

## 231

```c++

```

## 232

```c++

```

## 233

```c++
#include <type_traits>
#include <iostream>

using namespace std;

struct X {
    int f() const&&{
        return 0;
    }
};

int main() {
    auto ptr = &X::f;
    cout << is_same_v<decltype(ptr), int()>
         << is_same_v<decltype(ptr), int(X::*)()>;
}
```

答案 00
返回类型、参数类型列表、引用限定符、cv 限定符序列和异常规范（但不是默认参数）是函数类型的一部分。

## 234

```c++

```

## 235

```c++

```

## 236

```c++

```

## 237

```c++

```

## 238

```c++

```

## 239

```c++

```

## 240

```c++

```

## 241

```c++

```

## 242

```c++

```

## 243

```c++

```

## 244

```c++

```

## 245

```c++

```

## 246

```c++

```

## 247

```c++

```

## 248

```c++
#include <algorithm>
#include <iostream>

int main() {
    int x = 10;
    int y = 10;

    const int &max = std::max(x, y);
    const int &min = std::min(x, y);

    x = 11;
    y = 9;

    std::cout << max << min;
}
```

答案 1111
`std::max() 和 std::min()`返回的都是一个引用，但是如果都是相同的话，那么返回的是第一个参数，那么答案就是1111

## 249

```c++

```

## 250

```c++

```

## 251

```c++

```

## 252

```c++

```

## 253

```c++

```

## 254

```c++
#include <iostream>
#include <type_traits>

int main() {
    std::cout << std::is_same_v<
        void(int),
        void(const int)>;

    std::cout << std::is_same_v<
        void(int*),
        void(const int*)>;
}
```

答案 10
`参数的常量不是函数类型的一部分`，`const int` 和 `int`是同一种类型，但是`int*` 和 `const int*`并不是一类型，因为这里的const修饰的不是指针，而是指针所指向的东西.
为什么参数的常量不是函数类型的一部分，当参数按值传递的时候，会生成一个副本，并且原始参数永远不会不会修改，参数对于const调用者来说并不重要，它只是对函数内部相关。

```c++
#include <iostream>
#include <type_traits>

int main() 
{ 
    std::cout << std::is_same_v<void(int), void(const int)> << std::endl; // 1
    std::cout << std::is_same_v<int, int> << std::endl; // 1
    std::cout << std::is_same_v<int, const int> << std::endl; // 0
    std::cout << std::is_same_v<int*, const int*> << std::endl; // 0
    std::cout << std::is_same_v<int*, int* const> << std::endl; // 0
    return 0;w
}
```

## 255

```c++

```

## 256

```c++

```

## 257

```c++

```

## 258

```c++

```

## 259

```c++

```

## 260

```c++

```

## 261

```c++

```

## 262

```c++

```

## 263

```c++

```

## 264

```c++

```

## 265

```c++

```

## 266

```c++

```

## 267

```c++

```

## 268

```c++

```

## 269

```c++

```

## 270

```c++

```

## 271

```c++

```

## 272

```c++

```

## 273

```c++

```

## 274

```c++

```

## 275

```c++

```

## 276

```c++

```

## 277

```c++

```

## 278

```c++

```

## 279

```c++

```

## 280

```c++

```

## 281

```c++

```

## 282

```c++

```

## 283

```c++

```

## 284

```c++

```

## 285

```c++

```

## 286

```c++

```

## 287

```c++
#include <string>
#include <iostream>

int main() {
  using namespace std::string_literals;
  std::string s1("hello world",5); 
  std::string s2("hello world"s,5); 

  std::cout << s1 << s2;
}
```

答案 hello world
好坑，这里是表示的是直接使用std::string()来初始化，前面的从0开始，保留前五个，后面的5是

## 288

```c++

```

## 289

```c++

```

## 290

```c++

```

## 291

```c++

```

## 292

```c++

```

## 293

```c++

```

## 294

```c++

```

## 295

```c++

```

## 296

```c++

```

## 297

```c++

```

## 298

```c++

```

## 299

```c++

```

## 300

```c++

```

## 301

```c++

```

## 302

```c++

```

## 303

```c++

```

## 304

```c++

```

## 305

```c++

```

## 306

```c++

```

## 307

```c++

```

## 308

```c++

```

## 309

```c++

```

## 310

```c++

```

## 311

```c++

```

## 312

```c++

```

## 313

```c++

```

## 314

```c++

```

## 315

```c++

```

## 316

```c++

```

## 317

```c++

```

## 318

```c++

```

## 319

```c++

```

## 320

```c++

```

## 321

```c++

```

## 322

```c++

```

## 323

```c++

```

## 324

```c++

```

## 325

```c++

```

## 326

```c++

```

## 327

```c++

```

## 328

```c++

```

## 329

```c++

```

## 330

```c++

```

## 331

```c++

```

## 332

```c++
#include <iostream>

struct S {
    template <typename Callable>
    void operator[](Callable f) {
        f();
    }
};

int main() {
    auto caller = S{};
    caller[ []{ std::cout << "C";} ];
}
```

答案 CE
不允许出现这样的函数调用，`[[]]`。

## 333

```c++

```

## 334

```c++

```

## 335

```c++

```

## 336

```c++

```

## 337

```c++

```

## 338

```c++
#include <type_traits>
#include <iostream>
#include <string>

template<typename T>
int f()
{
    if constexpr (std::is_same_v<T, int>) { return 0; }
    else { return std::string{}; }
}

int main()
{
    std::cout << f<int>();
}
```

答案 UB（我更觉得是编译错误）
如果说你改成auto 就能编译过，其实就是`constexpr if`语法。

## 339

```c++

```

## 340

```c++

```

## 341

```c++

```

## 342

```c++

```

## 343

```c++

```

## 344

```c++

```

## 345

```c++

```

## 346

```c++

```

## 347

```c++
#include <iostream>
#include <type_traits>
#include <boost/type_index.hpp>

template <typename T>
void foo(T& x)
{
    std::cout << std::is_same_v<const int, T> << ' ';
    std::cout << boost::typeindex::type_id_with_cvr<T>().pretty_name() << std::endl;
}

template <typename T>
void bar(const T& x)
{
    std::cout << std::is_same_v<const int, T> << ' ';
    std::cout << boost::typeindex::type_id_with_cvr<T>().pretty_name() << std::endl;
}

int main()
{
    const int i{};
    int j{};

    foo(i); // const int
    foo(j); // int 
    bar(i); // int
    bar(j); // int

}
```

答案 1000
boost库是我加入的，这里得看一下C++类型的类型推导，`typename T` 和 `T& const T&` 这里推导出来的东西可能是不一样的。

## 348

```c++

```

## 349

```c++

```

## 350

```c++

```

## 351

```c++

```

## 352

```c++

```

## 353

```c++

```

## 354

```c++
#include <cstdlib>
#include <iostream>

struct S {
    char s;
    S(char s): s{s} {}
    ~S() { std::cout << s; }
};

S a('a');

int main() {
    S b('b');
    std::exit(0);
}
```

答案 a
调用的时候，只会执行静态局部变量的函数，其他不执行，无意义，没啥用

## 355

```c++

```

## 356

```c++

```

## 357

```c++

```

## 358

```c++

```

## 359

```c++

```

## 360

```c++

```

## 361

```c++

```

## 362

```c++

```

## 363

```c++

```

## 364

```c++

```

## 365

```c++

```

## 366

```c++

```

## 367

```c++

```

## 368

```c++

```

## 369

```c++

```

## 370

```c++

```

## 371

```c++

```

## 372

```c++

```

## 373

```c++

```

## 374

```c++

```

## 375

```c++

```

## 376

```c++

```

## 377

```c++

```

## 378

```c++

```

## 379

```c++

```

## 380

```c++

```

## 381

```c++

```

## 382

```c++

```

## 383

```c++

```

## 384

```c++

```

## 385

```c++

```

## 386

```c++

```

## 387

```c++

```

## 388

```c++

```

## 389

```c++

```

## 390

```c++

```

## 391

```c++

```

## 392

```c++

```

## 393

```c++

```

## 394

```c++

```

## 395

```c++

```

## 396

```c++

```

## 397

```c++

```

## 398

```c++

```

## 399

```c++

```

## 400

```c++

```

## 401

```c++

```

## 402

```c++

```

## 403

```c++

```

## 404

```c++

```

## 405

```c++

```

## 406

```c++

```

## 407

```c++

```

## 408

```c++

```

## 409

```c++

```

## 410

```c++

```

## 411

```c++

```

## 412

```c++

```

## 413

```c++

```

## 414

```c++

```

## 415

```c++

```

## 416

```c++

```

## 417

```c++

```

## 418

```c++

```

## 419

```c++

```

## 420

```c++

```

## 421

```c++

```

## 422

```c++

```

## 423

```c++

```

## 424

```c++

```

## 425

```c++

```

## 426

```c++

```

## 427

```c++

```

## 428

```c++

```

## 429

```c++

```

## 430

```c++

```

## 431

```c++

```

## 432

```c++

```

## 433

```c++

```

## 434

```c++

```

## 435

```c++

```

## 436

```c++

```

## 437

```c++

```

## 438

```c++

```

## 439

```c++

```

## 440

```c++

```

## 441

```c++

```

## 442

```c++

```

## 443

```c++

```

## 444

```c++

```

## 445

```c++

```

## 446

```c++

```

## 447

```c++

```

## 448

```c++

```

## 449

```c++

```

## 450

```c++

```

## 451

```c++

```

## 452

```c++

```

## 453

```c++

```

## 454

```c++

```

## 455

```c++

```

## 456

```c++

```

## 457

```c++

```

## 458

```c++

```

## 459

```c++

```

## 460

```c++

```

## 461

```c++

```

## 462

```c++

```

## 463

```c++

```

## 464

```c++

```

## 465

```c++

```

## 466

```c++

```

## 467

```c++

```

## 468

```c++

```

## 469

```c++

```

## 470

```c++

```

## 471

```c++

```

## 472

```c++

```

## 473

```c++

```

## 474

```c++

```

## 475

```c++

```

## 476

```c++

```

## 477

```c++

```

## 478

```c++

```

## 479

```c++

```

## 480

```c++

```

## 481

```c++

```

## 482

```c++

```

## 483

```c++

```

## 484

```c++

```

## 485

```c++

```

## 486

```c++

```

## 487

```c++

```

## 488

```c++

```

## 489

```c++

```

## 490

```c++

```

## 491

```c++

```

## 492

```c++

```

## 493

```c++

```

## 494

```c++

```

## 495

```c++

```

## 496

```c++

```

## 497

```c++

```

## 498

```c++

```

## 499

```c++

```

## 500

```c++

```
