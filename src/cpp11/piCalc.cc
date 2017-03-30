#include <thread>
#include <iostream>
#include <random>
#include <vector>
#include <future>

using std::cout;
using std::endl;

double doPiEstimate(int nToys) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<double> dis(0.0,1.0);
  double sum=0.0;
  for(int i=0; i<nToys; ++i) {
    double x = dis(gen);
    double y = dis(gen);
    if( (x*x + y*y)<1.0 ) sum+=1.0;
  }
  return 4.0 * sum / ((double)nToys);
}

int main() {

  int nth=10;
  int npoints=20000000;
  std::vector<std::future<double> > results;
  for(int it=0; it<nth; ++it) {
    results.push_back( std::async(std::launch::async, doPiEstimate, npoints/nth) );
  }
    
  
  double piEst=0.0;
  for(int it=0; it<nth; ++it) {
    piEst += results[it].get();
  }
  piEst = piEst / ((double)nth);
    
  cout << "Pi multi-thread = " << piEst << endl;
  cout << "Pi serial = " << doPiEstimate(100000) << endl;
  
  return 0;
}
