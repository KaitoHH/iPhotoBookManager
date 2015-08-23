//state.h
#pragma once
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
enum err_code{
	success,
	overflow = 1001,
	already_exist, 
	not_exist, 
	not_present, 
	open_info_file_error, 
	open_graph_file_error,
	no_map
};