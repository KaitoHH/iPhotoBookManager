//ImageInfo.cpp
#include "ImageInfo.h"
ImageInfo::ImageInfo()
{

}

ImageInfo::ImageInfo(string key,int w,int h,int s,int t,string cn,string en,
					string m,string p,string pl,string ln,string up){
	//this->number = number;
	this->key = key;
	this->w = w;
	this->h = h;
	this->s = s;
	this->t = t;
	this->cn = cn;
	this->en = en;
	this->m = m;
	this->p = p;
	this->pl = pl;
	this->ln = ln;
	this->up = up;
	this->vaild = true;
}

/*int ImageInfo::no(){
	return number;
}*/

string ImageInfo::filename(){
	return key;
}

void ImageInfo::set_filename(string s){
	key = s;
}

int ImageInfo::width(){
	return w;
}

void ImageInfo::set_width(int d){
	w = d;
}

int ImageInfo::height(){
	return h;
}

void ImageInfo::set_height(int d){
	h = d;
}

int ImageInfo::size(){
	return s;
}

void ImageInfo::set_size(int d){
	s = d;
}

int ImageInfo::time(){
	return t;
}

void ImageInfo::set_time(int d){
	t = d;
}

string ImageInfo::textcn(){
	return cn;
}

void ImageInfo::set_textcn(string s){
	cn = s;
}

string ImageInfo::texten(){
	return en;
}

void ImageInfo::set_texten(string s){
	en = s;
}

string ImageInfo::map(){
	return m;
}

void ImageInfo::set_map(string s){
	m = s;
}

string ImageInfo::postion(){
	return p;
}

void ImageInfo::set_postion(string s){
	p = s;
}

string ImageInfo::posl(){
	return pl;
}

void ImageInfo::set_posl(string s){
	pl = s;
}

string ImageInfo::lname(){
	return ln;
}

void ImageInfo::set_lname(string s){
	ln = s;
}

string ImageInfo::uper(){
	return up;
}

void ImageInfo::set_uper(string s){
	up = s;
}

bool ImageInfo::used(){
	return vaild;
}

void ImageInfo::set_used(bool f){
	vaild = f;
}
ostream& operator << (ostream &out, ImageInfo item){
	out << item.filename() << "," << item.width() << ","
		<< item.height() << "," << item.size() << ","
		<< item.time() << "," << item.textcn() << ","
		<< item.texten() << "," << item.map() << ","
		<< item.postion() << "," << item.posl() << ","
		<< item.lname() << "," << item.uper();
	out << endl;
	return out;
}