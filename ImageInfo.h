//ImageInfo.h
#pragma once
#include<string>
using namespace std;

class ImageInfo
{
public:
	//���캯��
	ImageInfo();
	ImageInfo(string, int, int, int, int, string, string, 
			  string, string, string, string, string);
	
	//int no();			//ͼƬ���
	bool used();
	void set_used(bool);
	string filename();	//ͼƬ�ļ���
	void set_filename(string);
	int width();		//���
	void set_width(int);
	int height();		//�߶�
	void set_height(int);
	int size();			//��С(Kib)
	void set_size(int);
	int time();			//��������(��1970-1-1��ms��)
	void set_time(int);
	string textcn();	//��������
	void set_textcn(string);
	string texten();	//Ӣ������
	void set_texten(string);
	string map();		//������ͼ
	void set_map(string);
	string postion();	//����ص�
	void set_postion(string);
	string posl();		//��һ������ص�(null or �й�)
	void set_posl(string);
	string lname();		//��һ����ͼ�ĵص�����(null or �Ϻ�)
	void set_lname(string);
	string uper();		//�ϴ���
	void set_uper(string);

private:
	//int number;	//ͼƬ���
	bool vaild;
	string key;		//ͼƬ�ļ���
	int w;			//���
	int h;			//�߶�
	int s;			//��С(Kib)
	int t;			//�޸�����
	string cn;		//��������
	string en;		//Ӣ������
	string m;		//������ͼ
	string p;		//����ص�
	string pl;		//��һ�������ͼ(null or �й�)
	string ln;		//��һ����ͼ�еĵص�����(null or �Ϻ�)
	string up;		//�ϴ���
};

ostream& operator << (ostream &out, const ImageInfo);