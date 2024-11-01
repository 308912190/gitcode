#include <iostream>
using namespace std;
//创建立方体类，设计属性，设计行为，获取立方体体积，判断两个立方体是否相等。（全局函数/成员函数）
class Cube
{
public:
	void set(int l,int w,int h)
	{
		m_l = l;
		m_w = w;
		m_h = h;
	}
	int get()
	{
		return m_l;
		return m_w;
		return m_h;

	}
	int caculate()
	{
		return m_l * m_w * m_h;
	}
	bool issame0(Cube& c)//成员函数
	{
		if (m_l == c.m_l && m_h == c.m_h && m_w == c.m_w)
		{
			return true;
		}
		return false;
	}

private:
	int m_l;
	int m_w;
	int m_h;
};
bool issame(Cube& c1, Cube& c2)//全局函数
{
	if (c1.get() == c2.get())
	{
		return true;
	}
	return false;
}
int main()
{
	Cube c1, c2;
	c1.set(10, 10, 10);
	c2.set(10, 10, 10);

	cout << "体积为" << c1.caculate() << endl;
	bool ret = issame(c1, c2);
	if (ret)
	{
		cout << "c1=c2" << endl;
	}
	else
	{
		cout << "c1!=c2" << endl;
	}
	bool ret0 = c1.issame0(c2);
	if(ret0)
	{
		cout << "c1=c2" << endl;
	}
	else
	{
		cout << "c1!=c2" << endl;
	}
}
