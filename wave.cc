#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

class Wave{
public:
  double start;
  double stop;
  double amplitude;
  double frequency;
  
  
  Wave(double start, double stop, double amplitude, double frequency)
  : start(start), stop(stop), amplitude(amplitude), frequency(frequency){}
  
  double sample(double time){
    double omega = frequency * 2 * M_PI;
    
    if(time < start || time > stop){
      return 0;
    }else{
      return amplitude * sin(omega * time);
    }
    
  }
};


class ConectionWave{
public:
  int sampling;
  int duration;
 const int size;
   ConectionWave(int sampling, int duration)
  :sampling(sampling), duration(duration),size(sampling * duration), waves(size,0.0){}
  
  void synthesis(Wave &wave){
    cout<< "********************************************" << endl;
    double time;
    for(int i = 0; i < size; ++i){
      time = i / static_cast<double> (sampling);
      waves[i]+= wave.sample(time);
    cout<<"(" << waves[i] << "  " << time << ")" ;
    }
}
private:
    vector <double> waves;


 
};


void load(Wave &a, string &data, int &i){
  string start;
  string stop;
  string amplitude;
  string frequency;
  
  for(int j = i + 1 ;j < data.length() && data[j] != '\n';++j){
    if(data[j] == 's'){
      j += 1;
      while(data[j] != ' '){
	start += data[j];
	++j;
      }
      a.start = stod(start);
      cout<< a.start << endl;
    }
    if(data[j] == 'e'){
      j += 1;
      while(data[j] != ' '){
	stop += data[j];
	++j;
      }
      a.stop = stod(stop);
      cout<< a.stop << endl;
    }
    if(data[j] == 'a'){
      j += 1;
      while(data[j] != ' '){
	amplitude += data[j];
	++j;
      }
      a.amplitude = stod(amplitude);
      cout<< a.amplitude << endl;
    }
    if(data[j] == 'f'){
      j += 1;
      while(data[j] != ' '){
	frequency += data[j];
	++j;
      }
      a.frequency = stod(frequency);
      cout<< a.frequency << endl;
    }
    i = j;
  }
  
};


void run(){
  Wave a(0.0,0.0,0.0,0.0);
  ConectionWave b(10,30);
  fstream file;
  string data;
  int itr = 0;
  char c;
  
  FILE *pfile;
  pfile = fopen("waves.txt","r");
  
  while(c != EOF){
    c = fgetc(pfile);
    data += c;
  }
  
  for(int i = 0; i < data.length();++i){
    if(data[i] == 'x'){
      load(a,data,i);
      b.synthesis(a);
    }
  }
 fclose(pfile);
 
};


int main(){
  run();

}