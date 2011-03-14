#ifndef ANALYSE_H
#define ANAlYSE_H

#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/flyweight.hpp>

struct entry
{/*
  boost::flyweight<double> lambda;
  boost::flyweight<double> db;*/
  double lambda;
  double db;
};

class analyser
{
 public:
  std::vector<entry> data;
  void start_find_range(const double startwl, const double max);
  void start_find_peak();
  void start_find_peak_distance();
  double get_ub();
  double get_lb();
  void print_peaks(std::ostream &mystream);
  void start_find_inten();
  void print_inten(std::ostream &mystream);
  void print_distance(std::ostream &mystream);
 private:
  std::vector<double>  peaks;
  std::vector<double>  peak_dis;
  double intensity;
  void find_biggest();
  double upper_border;
  double lower_border;
  void findup(const double startwl,const double max, double &myret);
  void finddown(const double startwl,const double max,double &ret);
  bool check_radius_up(int max_depth, int start, int currdepth);
  bool check_radius_down(int maxdepth, int startm ,int currdepth);
  double get_db(double wl);
  double get_wl(double db);
  void find_inten(double &area);
  void find_peak_distance(std::vector<double> &vec);
};

#endif //ANALYSE_H
