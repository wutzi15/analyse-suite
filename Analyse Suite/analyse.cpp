#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <numeric>
#include "analyse.h"
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/foreach.hpp>

//hello world
int _analyse(const char *argv){
	std::cout << "analysing ------" << std::endl;
	std::string names = argv;
	std::string _of = "_my_ana_" + names;
	std::string _only = "_only_" + names;
	std::string _peaks = "_peak_" + names;
	std::string _dist = "_dist_"+names;
	
	std::ofstream of("tmp.txt");
	of << argv << std::endl;
	std::string _name, _line;
	std::ifstream _in("tmp.txt");
	while (getline(_in,_line)){
		std::cout << _line << std::endl;
		analyser analysator; 
		//get file to read
		std::string name = _line;
		std::ifstream in(name.c_str());
		std::string line;
		
		double max = -10000;
		double maxwl = 0;
		
		
		//parse data file
		while(std::getline(in,line)){
			
			
			std::stringstream sstr(line);
			double a,b;
			sstr >> a >> b;
			if(b > max){
				max = b;
				maxwl = a;
			}
			entry e;
			e.lambda = a;
			e.db = b;
			analysator.data.push_back(e);
			std::cout << a << b;
		}
		
		std::cout << name << std::endl;
		
		//prepare outputfiles
		std::string of = _of;
		std::string only = _only;
		std::string peaks = _peaks;
		std::string distan = _dist;
		std::ofstream d(distan.c_str());
		std::ofstream pf(peaks.c_str());
		std::ofstream f(of.c_str());
		std::ofstream onl(only.c_str());
		
		//analyse datafile
		analysator.start_find_range(maxwl,max);
		analysator.start_find_peak();
		analysator.start_find_inten();
		analysator.start_find_peak_distance();
		
		
#ifdef DEBUG
		analysator.print_peaks(boost::ref(std::cout));
		analysator.print_distance(boost::ref(std::cout));
#endif
		
		
		//write to outputfiles
		f << name.c_str()<< std::endl; 
		f << "Maximum WL and dB " << maxwl <<"nm"<< '\t' << max <<"dB"<< std::endl;
		if(analysator.get_ub() != 0  && analysator.get_lb()  != 0){
			f << "Upper Border: " << analysator.get_ub() << std::endl;
			f << "Lower Border: " << analysator.get_lb() << std::endl;
			f << "Width in nm:" << std::endl << (analysator.get_ub() - analysator.get_lb()) << std::endl;
			analysator.print_peaks(boost::ref(f));
			analysator.print_inten(boost::ref(f));
			analysator.print_peaks(boost::ref(pf));
			analysator.print_distance(boost::ref(f));
			analysator.print_distance(boost::ref(d));
			onl <<(analysator.get_ub() - analysator.get_lb())  << std::endl;
		}else{
			f << "Could not determine values!" << std::endl;
			onl << -42 << std::endl;
		}
	}
	return 0;
}

