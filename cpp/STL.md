## 1.1 STL基本概念  
① STL(Standard Template Library，标准模板库)  
② STL 从广义上分为：容器(container)、算法(algorithm)、迭代器(iterator)  
③ 容器和算法之间通过迭代器进行无缝连接。  
④ STL 几乎所有的代码都采用了模板类或者模板函数  
## 1.2 STL六大部件  
![image](https://github.com/user-attachments/assets/e67a650e-e57c-430c-b3c2-65bc23a93736)  
![image](https://github.com/user-attachments/assets/33e36ac7-c00c-46f8-a022-4f5dc4a8536e)  
1.一个容器vector  
2.使用vector时，使用分配器分配内存  
3.使用vi.begin(),vi.end()即迭代器，作为算法的参数  
4.使用count_if算法  
5.使用仿函数less()  
6.使用函数适配器来对我们算法的结果进行进一步筛选（not1, bind2nd） 
## 2.0 容器  
![1733399944720](https://github.com/user-attachments/assets/28d279ce-2eb2-4fec-a584-fb16615db614)  
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
![1733400718299](https://github.com/user-attachments/assets/42f8625e-24ec-4056-ac16-8b7a4d501811)  
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
## 2.3 set容器  
### 2.3.1 简介  
① set容器中所有元素在插入时自动被排序。  
② set容器和multiset容器属于关联式容器，底层结构用二叉树实现。 
③ set容器与multiset容器区别： 
set容器不允许容器中有重复的元素。 
multiset容器允许容器中有重复的元素  
### 2.3.2 构造赋值  
set<int>s1;  
//插入数据  只有insert方式s1.insert(10);    
//拷贝构造  set<int>s2(s1);  
//赋值  set<int>s3;  s3 = s2;  
### 2.3.3 大小和交换  
s1.swap(s2);  s1.empty()  s1.size()  
### 2.3.4 插入和删除  
clear(); //清除所有元素。  
erase(pos); //删除pos迭代器所指的元素，返回下一个元素的迭代器。  
erase(beg,end); //删除区间[beg,end)的所有元素，返回下一个元素的迭代器。  
erase(elem); //删除容器中值为elem的元素。   
### 2.3.5 查找和统计  
find(key); //查找key是否存在，若存在，返回该键的元素的迭代器，若不存在，返回set.end();  
cout(key); //统计key的元素个数。  
## 2.4 map容器  
### 2.4.1 简介  
① map容器中的所有元素都是pair。  
② pair中第一个元素为key(键值)，起到索引作用，第二个元素为value(实值)。  
③ 所有元素都会根据元素的键值自动排序。  
④ map容器和multimap容器属于关联式容器，底层结构是用二叉树实现。  
⑤ map容器可以根据key值快速找到value值。  
⑥ map和multimap区别：  
map不允许容器中有重复key值元素。  
mutimap运行容器中有重复的key值元素。  
## 2.4.2 构造赋值  
1.pair对组的创建  
① 功能描述：成对出现的数据，利用对组可以返回两个数据。  
② 两种创建方式：  
pair<type,type> p (value1, value2);   
pair<type,type> p = make_pair(value1,value2);   

map<int, int>m;    m.insert(pair<int, int>(1, 10));   //1为key；10为value  
//拷贝构造 map<int, int>m2(m);  
//赋值  map<int, int>m3; m3 = m2;  
## 2.4.3 大小交换  
size(); //返回容器中元素的数目  
empty(); //判断容器是否为空。  
swap(st); //交换两个集合容器。  
## 2.4.4 插入删除  
插值：
//第一种：m.insert(pair<int, int>(1, 10));   
//第二种：m.insert(make_pair(2, 10));  
//第三种：m.insert(map<int, int>::value_type(3, 30));  //map容器下为"值"为(3,30)  
//第四种：m[4] = 40;   
clear(); //清除所有元素。  
erase(pos); //删除pos迭代器所指的元素，返回下一个元素的迭代器。  
erase(beg,end); //删除区间[beg,end)的所有元素，返回下一个元素的迭代器。  
erase(key); //删除容器中值为key的元素。  
### 2.4.5 查找统计    
find(key); //查找key是否存在，若存在，返回该键的元素的迭代器；若不存在，返回set.end();  
cout(key); //统计key的元素个数。  
### 2.4.6 排序  
① map容器默认排序规则为按照key值进行从小到大排序，利用仿函数，可以改变排序规则。  
② 利用仿函数可以指定map容器的排序规则。  
③ 对于自定义数据类型，map必须要指定排序规则，同set容器。  
