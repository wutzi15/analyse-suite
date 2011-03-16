//#include <boost/thread.hpp>
#include <iostream>

#include <boost/bind.hpp>
#include "analyse.h"
#include <boost/thread.hpp>

//defining minimum peak radius
#define MIN_RADIUS 1
//defining maximum amout of peaks
#define MAX_PEAKS 10

void analyser::print_inten(std::ostream &mystream){
	mystream << "Intensity \n" << intensity <<std::endl;
}

void analyser::print_peaks(std::ostream &mystream){
	mystream << "Found Peaks \n";
	for(unsigned int i = 0; i < peaks.size();i++){
		mystream << peaks[i] << std::endl;
	}
}

void analyser::print_distance(std::ostream &mystream){
	mystream << "Distrance between peaks\n";
	//mystream << peak_dis.size() << std::endl;
	for(size_t i = 0 ; i < peak_dis.size();i++){
		//#ifdef DEBUG
		//    std::cout << i ;
		//#endif
		mystream << peak_dis[i] << std::endl;
	}
}
double analyser::get_ub(){
	return upper_border;
}

double analyser::get_lb(){
	return lower_border;
}

void analyser::start_find_range(const double startwl, const double max){
	//launch multithreaded analysis
	//findup(startwl,max,boost::ref(upper_border));
	//finddown(startwl,max,boost::ref(lower_border));
	
	boost::thread up(&analyser::findup,*this, startwl,max,boost::ref(upper_border));
	boost::thread down(&analyser::finddown, *this, startwl,max,boost::ref(lower_border));
	up.join();
	down.join();
}



void analyser::findup(const double startwl, const double max, double &myret){
	//find the last value bigger than "maximum peak -30 dB"
	try{
		this->data.begin();
		for(int i = (int)data.size() ; i >= 0;i--){
			if(this->data[i].lambda > startwl){
				if(this->data[i].db >= (max-30)) {
					myret = this->data[i+1].lambda;
					return;
				}
			}
		}
	}catch(std::runtime_error &e){
		std::cerr << e.what() << std::endl;
	}
}

void analyser::finddown(const double startwl, const double max,double &ret){
	//find the first value bigger than "maximum peak -30 dB"
	try{
		this->data.begin();
		for(int i = 1; i<(int)data.size();i++){
			if(this->data[i].lambda <= startwl){
				if(this->data[i].db >= (max-30)){
					ret = this->data[i-1].lambda;
					return;
				}
			}
		}
	}catch(std::runtime_error &e){
		std::cerr << e.what() << std::endl;
	}
}

void analyser::start_find_peak(){
	// find single peaks "value bigger than surrounding values"
	try{
		for( unsigned int i = 1; i < data.size();i++){
			/*#ifdef DEBUG
			 std::cout << " ---- \n";
			 #endif*/
			if(this->data[i].db > this->data[i-1].db)
				//check surrounding values in the area of "MIN_RADIUS"
				if(check_radius_up(MIN_RADIUS, i, 1) && check_radius_down(MIN_RADIUS, i ,1)){
					/*#ifdef DEBUG
					 std::cout << "found peak at " << this->data[i].lambda << std::endl;
					 #endif*/
					peaks.push_back(this->data[i].lambda);
				}
		}
		//find the biggest vaules
		find_biggest();
		//sort peaks
		std::sort(peaks.begin(),peaks.end());
	}catch(std::exception err){
		std::cerr << err.what() << std::endl;
    }
}

bool analyser::check_radius_up(int max_depth, int start, int currdepth){
	//recursivly check surrounding area to the right
	if (currdepth > max_depth) return true;
	if (this->data[start].db >= this->data[start +1].db){
		
		//#ifdef DEBUG  
		//    std::cout << "u "<< this->data[start].db << " " << this->data[start+1].db <<" " << currdepth<<std::endl;
		//#endif 
		
		if (check_radius_up(max_depth, start+1, currdepth+1)) return true;
	}else{
		
		//#ifdef DEBUG
		//    std::cout << "u! "<< this->data[start].db << " " << this->data[start+1].db <<" " << currdepth<<std::endl;
		//#endif 
		
		return false;
	}
	return false;
}

bool analyser::check_radius_down(int max_depth, int start, int currdepth){
	//recursivly check surroundung area to the left 
	if (currdepth > max_depth) return true;
	if (this->data[start].db >= this->data[start -1].db){
		//
		//#ifdef DEBUG
		//    std::cout << "d "<< this->data[start].db << " " << this->data[start-1].db <<" " << currdepth<<std::endl;
		//#endif 
		
		if (check_radius_up(max_depth, start-1, currdepth+1)) return true;
	}else{
		
		//#ifdef DEBUG
		//    std::cout << "d! "<< this->data[start].db << " " << this->data[start-1].db <<" " << currdepth<<std::endl;
		//#endif 
		
		return false;
	}
	return false;
}

void analyser::find_biggest(){
	//find biggest n peaks (n=MAX_PEAKS)
	std::vector<double> dbs;
	//get dB's for the peaks
	for(unsigned int k = 0 ; k < peaks.size();k++){
		if(peaks[k]> lower_border && peaks[k]<upper_border)
			dbs.push_back(get_db(peaks[k]));
	}
	peaks.clear();
	//copy the biggest peak back to peaks then look for the next biggest
	for(int j = 0 ; j < MAX_PEAKS ; j++){
		double tmp = *(std::max_element(dbs.begin(),dbs.end()));
		tmp = get_wl(tmp);
		peaks.push_back(tmp);
		for(unsigned int i = 0; i < dbs.size();i++){
			if(dbs[i] == get_db(tmp)){
				dbs.erase(dbs.begin()+ i);
			}
		}
	}
}
double analyser::get_db(double wl){
	//get dB for a certain wavelength
	for(unsigned int i = 0 ; i < data.size() ;i++){
		if(this->data[i].lambda == wl) return this->data[i].db;
	}
	return 42;
}

double analyser::get_wl(double db){
	//get wavelength for a certain dB
	for(unsigned int i = 0 ; i < data.size() ;i++){
		if(this->data[i].db == db) return this->data[i].lambda;
	}
	return 42;
}

void analyser::start_find_inten(){
	//find_inten(boost::ref(intensity));
	
	boost::thread inten(&analyser::find_inten,*this,boost::ref(intensity));
	inten.join();
}

void analyser::find_inten(double &area){
	area = 0;
	for(size_t i = 0; i < this->data.size();i++){
		try{
			double x1,x2,y1,y2;
			x1= this->data[i].lambda;
			x2= this->data[i+1].lambda;
			y1= this->data[i].db;
			y2= this->data[i+1].db;
			double tmp =  (x2-x1)*abs((y2-y1)/2);
			if(tmp > 0)
				area += tmp;
			//#ifdef DEBUG
			//      std::cout << area <<std::endl;
			//#endif
		}catch(std::exception err){
			std::cerr << err.what() <<std::endl;
		}
	}
    area *= area;
	//#ifdef DEBUG
	//    std::cout << "final area " << area << std::endl;
	//#endif
}

void analyser::start_find_peak_distance(){
	//#ifdef DEBUG
	//  std::cout<< "in find distance\n";
	//#endif
	find_peak_distance(boost::ref(peak_dis));
	/*
	 boost::thread dis(&analyser::find_peak_distance, *this,boost::ref(peak_dis));
	 dis.join();*/
}

void analyser::find_peak_distance(std::vector<double> &vec){
	for(size_t i = 0; i < peaks.size()-1;i++){
		double dis = peaks[i+1] - peaks[i];
		//#ifdef DEBUG
		//    std::cout << dis << std::endl;
		//#endif
		vec.push_back(dis);
	}
}
