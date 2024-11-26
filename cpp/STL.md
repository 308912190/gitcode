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
## 2.2 string容器  
### 2.2.1 构造函数  
1. string();   //  创建一个空的字符串 例：string str;  
2. string(const char* s);    // 使用字符串s初始化   例：const char* str = "hello world"; string s2(str)    
4. string(const string & str);  // 使用一个string对象初始化另一个string对象   string s3(s2);  
5. string(int n, char c);  //使用n个字符c初始化 string s4(10, 'a');  
### 2.2.2 赋值操作 
string str1 = "hello world";  //第一种等号方式  string str2 = str1;   //第二种等号方式     string str3 = 'a';    //第三种等号方式  
str4.assign("hello C++");   //第一种assign方式  
str5.assign("hello C++",5);   //第二种assign方式，取字符串"hello C++"中的前五个字符赋值给str5   
str6.assign(str5);   //第三种assign方式   
str7.assign(10,'w');   //第四种assign方式  
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
string str1 = "hello";   
string str2 = "hello";   
//compar常用于比较两个字符串相等或不相等，判断谁大谁小的意义并不是很大  
if (str1.compare(str2) == 0)  
{  
    cout << "str1 等于 str2" << endl;  
}  
else if (str1.compare(str2) > 0)  
{  
    cout << "str1 大于 str2" << endl;  
}  
### 2.2.7字符串存取  
str.at(i) =  str[i]  
### 2.2.8字符串插入删除  
str.insert(1, "111");  
str.erase(1, 3); //从第“1”个位置起，删3个  
### 2.2.9 子串获取  
string email = "zhangsan@sina.com";  //从邮件地址中获取 用户名称  
int pos = email.find("@");   //pos=8
string usrName = email.substr(0, pos);  
