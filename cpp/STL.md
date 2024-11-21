# C++的STL
## 1.1 STL基本概念  
① STL(Standard Template Library，标准模板库)  
② STL 从广义上分为：容器(container)、算法(algorithm)、迭代器(iterator)  
③ 容器和算法之间通过迭代器进行无缝连接。  
④ STL 几乎所有的代码都采用了模板类或者模板函数  
## 1.2 STL六大部件  
容器：各种数据结构，如vector、list、deque、set、map等，用来存放数据。
算法：各种常用的算法，如sort、find、copy、for_each等。
迭代器：扮演了容器与算法之间的胶合剂。（类似于指针）
仿函数：行为类似函数，可作为算法的某种策略。
适配器：一种用来修饰容器或者仿函数或迭代器接口的东西。
空间配置器：负责空间的配置与管理。
## 2.1 vector容器  
① vector数据结构和数组非常相似，也称为单端数组。  
② vector与普通数组区别：不同之处在于数组是静态空间，而vector可以动态扩展。  
③ 动态扩展并不是在原空间之后续接新空间，而是找更大的内存空间，然后将原数据拷贝新空间，释放原空间。  
④ vector容器的迭代器是支持随机访问的迭代器。 
### 2.1.1 vector构造函数  
    vector<int> v1; //默认构造  无参构造  
    //通过区间方式进行构造  
    vector<int>v2(v1.begin(), v1.end()); //把v1.begin()-v1.end()区间内数给v2  
    //n个elem方式构造  
    vector<int>v3(10, 100); //这是10个100，不是100个10  
    //拷贝构造  
    vector<int>v4(v3);  
