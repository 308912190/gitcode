#include<iostream>
using namespace std;
#include<string>;
class Student
{
public:
	//属性
	string str_name;
	int m_id;
	//行为 成员函数
	void showStudent()
	{
		cout << "姓名" << str_name << endl << "学号" << m_id << endl;
	}
	void setname(string name)
	{
		str_name = name;
	}
	void setid(int id)
	{
		m_id = id;
	}
};
int main()
{
	Student s1;
	s1.setname("abc");
	s1.setid(2024);
	s1.showStudent();
}