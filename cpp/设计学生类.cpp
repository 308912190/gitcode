#include<iostream>
using namespace std;
#include<string>;
class Student
{
public:
	//����
	string str_name;
	int m_id;
	//��Ϊ ��Ա����
	void showStudent()
	{
		cout << "����" << str_name << endl << "ѧ��" << m_id << endl;
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