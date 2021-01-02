//EE19MTECH01008:- Question1

#include <iostream>
using namespace std;

double power(double x, int y){   
  double temp; 
  if(y == 0) 
    return 1; 
  temp = power(x, y / 2); 
  if (y % 2 == 0) 
    return temp * temp; 
  else{ 
    if(y > 0) 
      return x * temp * temp; 
    else
      return (temp * temp) / x; 
  } 
} 

double nth_root(double num, double k) {
    double x;
    double c;
    double acc(10e-6);
    x = num/2;
    c = (num/power(x,k-1)-x)/k;
    while(c >= acc || c <= -acc){
        x = x + c;
        c = (num/power(x,k-1)-x)/k;
    }
   return x;
}

unsigned long int floor(double j){
 unsigned long int t; 
 t=(int)j; 
 return t; 
} 

int main(){
    int test;
    unsigned long long int n,k,result;
    cin>>test;
    while(test--){ 
      cin>>n;
      cin>>k;
      double v = nth_root(n,k);
      result = floor(v);
      cout << result << "\n";
    }    

    return 0;
}

