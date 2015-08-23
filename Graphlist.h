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
	string mapname;			//地图名称
	int n;					//结点个数
	vector<GraphInfo>map;	//当前地图下的所有地图信息
};
