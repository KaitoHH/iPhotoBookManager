//file.cpp
//全局变量
#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include "file.h"
#include"iPhotoBook.h"
using namespace std;


iPhotoBook album;
mysetting setting;

bool readfile()
{
	fstream fin("config.ini");
	string s;
	string ans[3];
	int k[2];
	if (!fin)	return false;
	for (int i = 0; i < 3; i++){
		getline(fin, ans[i]);
		if (!fin)	return false;
	}
	for (int i = 0; i < 2; i++){
		fin >> k[i];
		if (!fin)	return false;
	}
	setting.libname = ans[0];
	setting.libpath = ans[1];
	setting.avatorpath = ans[2];
	setting.browse = k[0];
	setting.ssearch = k[1];
	fin.close();
	return true;
}

void defaultfile()
{
	setting.browse = setting.ssearch = 0;
	setting.libname = "picLib";
}

void creatfile()
{
	fstream fout("config.ini", ios::out);
	fout << setting.libname << endl;
	fout << setting.libpath << endl;
	fout << setting.avatorpath << endl;
	fout << setting.browse << endl;
	fout << setting.ssearch << endl;
	fout.close();
}