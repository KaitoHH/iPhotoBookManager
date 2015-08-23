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
	int number;			//结点编号
	int x;				//横坐标
	int y;				//纵坐标
	string name;		//结点名称
	string detail;		//详细信息
};

ostream& operator << (ostream &out, const GraphInfo);