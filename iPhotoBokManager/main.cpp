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

	
	cout << "��ѧ��..." << endl;
	myalbum.findByPosition("��ѧ��", n, l);
	for (int i = 0; i < n; i++){
		cout << myalbum.record(l.front());
		l.pop_front();
	}


	cout << "ɾ�����..." << endl;
	cout << myalbum.record(t);
	myalbum.del(myalbum.record(t));
	cout << "ɾ����..." << endl;

	myalbum.findByTittle("grass", n, l);
	for (int i = 0; i < n; i++){
		cout << myalbum.record(l.front());
		l.pop_front();
	}
	cout << "��ѧ��..." << endl;
	myalbum.findByPosition("��ѧ��", n, l);
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
	cout << "�ҵ�" << " " << n << "��" << endl;
	cin.get();
	for (int i = 0; i < n; i++){
		cout << l.front() << " : " << myalbum.record(l.front());
		l.pop_front();
	}
	cout << "�ҵ�" << " " << n << "��" << endl;
	/*cout << "ɾ��1319" << endl;
	myalbum.del(myalbum.record(1319));
	myalbum.findByTittle("river", n, l);
	for (int i = 0; i < n; i++){
		cout << l.front() << " : " << myalbum.record(l.front());
		l.pop_front();
	}*/
	return 0;
}