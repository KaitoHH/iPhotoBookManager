#include"iPhotoBook.h"
#include<list>
#include<iostream>
#include<windows.h>
using namespace std;

iPhotoBook myalbum;
int main()
{
	myalbum.intialize();
	/*int n;
	list<int>l;
	cout << "grass..." << endl;
	myalbum.findByTittle("grass", n, l);
	int t = l.front();
	for (int i = 0; i < n; i++){
		cout << myalbum.record(l.front());
		l.pop_front();
	}

	
	cout << "数学馆..." << endl;
	myalbum.findByPosition("数学馆", n, l);
	for (int i = 0; i < n; i++){
		cout << myalbum.record(l.front());
		l.pop_front();
	}


	cout << "删除结点..." << endl;
	cout << myalbum.record(t);
	myalbum.del(myalbum.record(t));
	cout << "删除后..." << endl;

	myalbum.findByTittle("grass", n, l);
	for (int i = 0; i < n; i++){
		cout << myalbum.record(l.front());
		l.pop_front();
	}
	cout << "数学馆..." << endl;
	myalbum.findByPosition("数学馆", n, l);
	for (int i = 0; i < n; i++){
		cout << myalbum.record(l.front());
		l.pop_front();
	}*/

	/*int d = -1;
	for (int i = 0; i < myalbum.size(); i++){
		d = myalbum.next(d);
		cout << d << " : " << myalbum.record(d);
	}
	myalbum.del(myalbum.record(1807));
	d = -1;
	for (int i = 0; i < myalbum.size(); i++){
		d = myalbum.next(d);
		cout << d << " : " << myalbum.record(d);
	}*/
	
	int n;
	list<int>l;
	myalbum.set_fuzzy(true);
	myalbum.findByTittle("T", n, l);
	cout << "找到" << " " << n << "个" << endl;
	cin.get();
	for (int i = 0; i < n; i++){
		cout << l.front() << " : " << myalbum.record(l.front());
		l.pop_front();
	}
	cout << "找到" << " " << n << "个" << endl;
	/*cout << "删除1319" << endl;
	myalbum.del(myalbum.record(1319));
	myalbum.findByTittle("river", n, l);
	for (int i = 0; i < n; i++){
		cout << l.front() << " : " << myalbum.record(l.front());
		l.pop_front();
	}*/
	return 0;
}