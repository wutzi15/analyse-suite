//
//  move_files.cpp
//  Analyse Suite
//
//  Created by Wutzi on 16.03.11.
//  Copyright 2011 me. All rights reserved.
//

#include "move_files.h"
#include <vector>
#include <sstream>
#include <string>
#include <boost/filesystem.hpp>

namespace fs= boost::filesystem ;

void copy_file(const char *t_path,fs::path p ){
	try {
		fs::copy_file(p, fs::path(t_path)/p.filename(),fs::copy_option::none);
	}catch(fs::filesystem_error &e){
		std::cerr << e.what() << std::endl;
	}
}

void move_file(const char *t_path,fs::path p ){
	try{
	fs::rename(p, fs::path(t_path)/p.filename());
	}catch(fs::filesystem_error &e){
		std::cerr << e.what() << std::endl;
	}
}

bool move_files(const char *new_path, const char* files){
	std::stringstream sstr(files);
	std::vector<fs::path > f;
	std::string line;
	
	while (std::getline(sstr,line)) {
		f.push_back(fs::path(line));
	}
	
	for (std::vector<fs::path>::iterator i = f.begin(); i != f.end(); i++) {
		fs::path dir = i->parent_path();
		std::string name = i->filename().string();
		move_file(new_path, dir/("_dist_"+name));
		move_file(new_path, dir/("_my_ana_"+name));
		move_file(new_path, dir/("_peak_"+name));
		move_file(new_path, dir/("_only_"+name));
		copy_file(new_path, dir/name);
	}
	
	
	return true;
}
bool copy_files(const char *new_path, const char* files){
	std::stringstream sstr(files);
	std::vector<fs::path > f;
	std::string line;
	
	while (std::getline(sstr,line)) {
		f.push_back(fs::path(line));
	}
	
	for (std::vector<fs::path>::iterator i = f.begin(); i != f.end(); i++) {
		fs::path dir = i->parent_path();
		std::string name = i->filename().string();
		copy_file(new_path, dir/("_dist_"+name));
		copy_file(new_path, dir/("_my_ana_"+name));
		copy_file(new_path, dir/("_peak_"+name));
		copy_file(new_path, dir/("_only_"+name));
		copy_file(new_path, dir/name);
	}
	
	
	return true;
}