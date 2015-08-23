//GraphInfo.h
#pragma once
#include<string>
using namespace std;

class GraphInfo
{
public:
	int getNumber();
	int getX();
	int getY();
	string getName();
	string getDetail();

	void setNumber(int number);
	void setX(int x);
	void setY(int y);
	void setName(string name);
	void setDetail(string detail);
private:
	int number;			//�����
	int x;				//������
	int y;				//������
	string name;		//�������
	string detail;		//��ϸ��Ϣ
};

ostream& operator << (ostream &out, const GraphInfo);