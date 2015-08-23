//GraphInfo.cpp
#include "GraphInfo.h"


int GraphInfo::getNumber(){
	return number;
}

int GraphInfo::getX(){
	return x;
}

int GraphInfo::getY(){
	return y;
}

string GraphInfo::getName(){
	return name;
}

string GraphInfo::getDetail(){
	return detail;
}

void GraphInfo::setNumber(int number){
	this->number = number;
}

void GraphInfo::setX(int x){
	this->x = x;
}

void GraphInfo::setY(int y){
	this->y = y;
}

void GraphInfo::setName(string name){
	this->name = name;
}

void GraphInfo::setDetail(string detail){
	this->detail = detail;
}

ostream& operator << (ostream &out, GraphInfo item){
	out << item.getName();
	return out;
}