//ImageInfo.h
#pragma once
#include<string>
using namespace std;

class ImageInfo
{
public:
	//构造函数
	ImageInfo();
	ImageInfo(string, int, int, int, int, string, string, 
			  string, string, string, string, string);
	
	//int no();			//图片编号
	bool used();
	void set_used(bool);
	string filename();	//图片文件名
	void set_filename(string);
	int width();		//宽度
	void set_width(int);
	int height();		//高度
	void set_height(int);
	int size();			//大小(Kib)
	void set_size(int);
	int time();			//创建日期(自1970-1-1的ms数)
	void set_time(int);
	string textcn();	//中文描述
	void set_textcn(string);
	string texten();	//英文描述
	void set_texten(string);
	string map();		//所属地图
	void set_map(string);
	string postion();	//拍摄地点
	void set_postion(string);
	string posl();		//上一级拍摄地点(null or 中国)
	void set_posl(string);
	string lname();		//上一级地图的地点名称(null or 上海)
	void set_lname(string);
	string uper();		//上传者
	void set_uper(string);

private:
	//int number;	//图片编号
	bool vaild;
	string key;		//图片文件名
	int w;			//宽度
	int h;			//高度
	int s;			//大小(Kib)
	int t;			//修改日期
	string cn;		//中文描述
	string en;		//英文描述
	string m;		//所属地图
	string p;		//拍摄地点
	string pl;		//上一级拍摄地图(null or 中国)
	string ln;		//上一级地图中的地点名称(null or 上海)
	string up;		//上传者
};

ostream& operator << (ostream &out, const ImageInfo);