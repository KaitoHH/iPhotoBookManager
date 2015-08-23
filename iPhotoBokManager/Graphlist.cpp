//Graphlist.cpp
#include "Graphlist.h"
#include <fstream>
#include <string>
extern enum err_code;

Graphlist::Graphlist(string mapname)
{
	this->mapname = mapname;
	n = 0;
}

err_code Graphlist::intialize(string path){
	string prefix = /*path + "\\" +*/ mapname + "_";
	string file1 = prefix + "introduction.txt";
	string file2 = prefix + "graphVertex.txt";
	fstream fin1(file1);
	fstream fin2(file2);
	if (!fin2||!fin2)		return open_graph_file_error;
	int t,x, y;
	while (fin2 >> t >> x >> y){
		if (t == 58){
			t++;
			t--;
		}
		n++;
		GraphInfo item;
		item.setNumber(n);
		item.setX(x);
		item.setY(y);
		
		string name, detail;
		fin1 >> t >> name >> detail;
		if (!fin1)		return open_graph_file_error;
		item.setName(name);
		item.setDetail(detail);
		map.push_back(item);
	}
	fin1.close();
	fin2.close();
	return success;
}

int Graphlist::size(){
	return n;
}

GraphInfo Graphlist::at(int index){
	return map[index];
}