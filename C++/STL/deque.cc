#include<iostream>
#include<deque>
 
using namespace std;
int main()
{
	deque<int> d;
	d.push_back(10);
	d.push_back(20);
	d.push_back(30);
	cout<<"orginial deque："<<endl;
	for (int i = 0; i < d.size(); i++)
	{
		cout<<d.at(i)<<"\t";
	}
	cout<<endl;
	d.push_front(5);
	d.push_front(3);
	d.push_front(1);
 
	cout<<"after push_front(5.3.1):"<<endl;
	for (int i = 0;i < d.size();i++)
	{
		cout<<d.at(i)<<"\t";
	}
	cout<<endl;
	d.pop_front();
	d.pop_front();
	cout<<"after pop_front() two times:"<<endl;
	for (int i = 0;i < d.size();i++)
	{
		cout<<d.at(i)<<"\t";
	}
	cout<<endl;
	d.pop_back();
	cout<<"after pop_back() one time:"<<endl;
	for (int i = 0;i < d.size();i++)
	{
		cout<<d.at(i)<<"\t";
	}
	cout<<endl;
	cout << d.front() 
	     << endl
	     << d.back()
	     << endl;
	return 0;
}
/*
deque可以視為可以在最前面加東西、刪東西的vector，除此之外它就是vector了。
假設變數名是d，想要移除第一項，就用d.pop_front()。
想要在前面加一個東西a，就用d.push_front(a)。
這兩個函式不會使迭代器失效，但會改變deque的下標。

雖說功能比vector強，但代價是時間和空間幾乎翻倍，所以沒事別用deque
*/
