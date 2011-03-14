#include <iostream>
#include <fstream>
#include <vector>
#include <boost/lexical_cast.hpp>
#include <string>
#include <sstream>

bool check(std::string a){
  try{
    double d = boost::lexical_cast<double>(a);
    return true;
  }catch(boost::bad_lexical_cast){
    return false;
  }
}

int rec(int argc, char *argv){
	
	//new code
	
	std::string _name, _line;
	std::ifstream _in(_name.c_str());
	while (getline(_in,_line)){
		std::cout << _line << std::endl;
	
	//old code
	
    std::string name = _line;
  
    std::ifstream in(name.c_str());
    std::string line;
    std::vector<double> a,b;
    
    while(getline(in,line)){
      std::string first,sec;
      
      std::string TR = line.c_str();
      std::replace(TR.begin(),TR.end(),',','\t');
      std::stringstream sstr(TR);
      sstr >> first >> sec;
      if(check(first) && check(sec)){
	a.push_back(boost::lexical_cast<double>(first));
	b.push_back(boost::lexical_cast<double>(sec));
      }
    }
    //std::replace(name.begin(),name.end(),"CSV","png");
    std::ofstream of(name.c_str());
    for(int j = 0 ; j< a.size();j++){
      of << a[j] << '\t'<< b[j] <<std::endl;
    }
  

	}
  return 0;
}
