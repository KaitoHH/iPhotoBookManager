//Graphlist.h
#pragma once
#include"GraphInfo.h"
#include"ImageInfo.h"
#include<string>
#include<vector>
#include"state.h"
using namespace std;

class Graphlist
{
public:
	Graphlist(string mapname = "undefined");
	err_code intialize(string);
	int size();
	GraphInfo at(int);
private:
	string mapname;			//��ͼ����
	int n;					//������
	vector<GraphInfo>map;	//��ǰ��ͼ�µ����е�ͼ��Ϣ
};
