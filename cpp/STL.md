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
vector<int>v2(v1.begin(), v1.end()); //把v1.begin()-v1.end()区间内数给v2   
vector<int>v3(10, 100); //这是10个100，不是100个10  
vector<int>v4(v3);  
### 2.1.2 赋值  
v3.assign(v1.begin(), v1.end());  //提供两个迭代器，两个迭代器区间中的元素都赋值给vector容器，区间为前闭后开   
v4.assign(10, 100);  
### 2.1.3 容量和大小   
v1.resize(15);  //如果重新指定的比原来长了，默认用0填充新的位置  
v1.resize(20,100);  //利用重载版本，参数2可以指定默认填充值  
v1.resize(5);  //如果重新指定的比原来短了，超出的部分会删除掉  
v1.empty()    v1.capacity()  v1.size()  
### 2.1.4插入删除  
v1.push_back(10);//尾插   v1.pop_back();//尾删   v1.insert(v1.begin(), 100);//插入参数是迭代器     
v1.erase()删除操作参数也是迭代器（it=v.erase(it)     返回值是一个新的迭代器，指向删除的元素之后的下一个有效元素。如果删除的是最后一个元素，返回值将是 end()（表示容器末尾的迭代器）  
//清空 v1.clear();  
### 2.1.5 数据存取  
v.front(); //返回容器中第一个数据元素   
v.back(); //返回容器中最后一个数据元素   
除了用迭代器获取vector容器中元素，[]和at(v.at(i)也可以。  
v1.swap(v2);//交换容器  
## 2.2 string容器  
### 2.2.1 构造函数  
string str;  
const char* str = "hello world"; string s2(str)    
string s3(s2);  
string s4(10, 'a');  
### 2.2.2 赋值操作 
string str1 = "hello world";  //第一种等号方式  string str2 = str1;   //第二种等号方式     string str3 = 'a';    //第三种等号方式  
str4.assign("hello C++");  
str5.assign("hello C++",5);   //第二种assign方式，取字符串"hello C++"中的前五个字符赋值给str5   
str6.assign(str5);   
str7.assign(10,'w');  
### 2.2.3 字符串拼接  
str1 += "爱玩游戏";  
str1 += ':';   //追加一个字符  
str1 += str2;    //追加字符串  
str3.append(" love ");  
str3.append("game abcde ",4);  //只把字符串的前4个拼接过去    
str3.append(str2);   
str3.append(str2,0,4);  //只截取到LoL，参数2表示从哪个位置开始截取，参数3表示截取字符个数  
### 2.2.4 字符串查找和替换  
string str1 = "abcdefgde";   
int pos = str1.find("de");  //从零开始索引，返回值为d出现的位置"3"，若找不到子字符串，就返回-1  
pos = str1.rfind("de");  //rfind是从右往左查找，find是从左往右查找  
string str1 = "abcdefg";  
str1.replace(1, 3, "1111");  // 从 "1" 号位置起，"1111"有四个字符，所以变为4个字符替换成 "1111"，而不是出现3个字符替换成"111"  
### 2.26 字符串比较   
//compar常用于比较两个字符串相等或不相等，判断谁大谁小的意义并不是很大
str1.compare(str2)  
### 2.2.7字符串存取  
str.at(i) 和 str[i]  效果一样
### 2.2.8字符串插入删除  
str.insert(1, "111");  
str.erase(1, 3); //从第“1”个位置起，删3个  
### 2.2.9 子串获取  
string email = "zhangsan@sina.com";  //从邮件地址中获取 用户名称  
int pos = email.find("@");   //pos=8
string usrName = email.substr(0, pos);  
