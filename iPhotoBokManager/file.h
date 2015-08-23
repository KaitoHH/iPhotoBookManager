//file.h
#pragma once
#include<string>
bool readfile();
void defaultfile();
void creatfile();

struct mysetting{
	std::string libname;
	std::string libpath;
	std::string avatorpath;
	int browse;
	int ssearch;
};