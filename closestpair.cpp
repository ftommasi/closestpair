#include "closestpair.h"
#include <algorithm>
#include <cstdlib>
#include <sys/time.h>  // used to seed srand for extra credit
#include <iostream>
using namespace std;

//comparitor functions
bool CompX(const Point& a,const Point& b){
  return compareByX(a,b);
}

bool CompY(const Point& a,const  Point& b){
  return compareByY(a,b);
}

Outcome CompOut(Outcome a, Outcome b){
  if( a.dsq< b.dsq){
  
    return a;
  }
  else{
    return b;
  }
}

Outcome CompMin(Outcome a, Outcome b){
  if( a.dsq< b.dsq){
  
    return a;
  }
  else{
    return b;
  }
}

Outcome brute(const vector<Point>& data) {
    Outcome best(data[0], data[1], distSquared(data[0],data[1]));
    for (unsigned int j=1; j < data.size(); j++) {
        for (unsigned int k=0; k < j; k++) {
            long long temp = distSquared(data[j], data[k]);
            if (temp < best.dsq) {
                best = Outcome(data[j], data[k], temp);
            }
        }
    }
    return best;
}

Outcome strip(const vector<Point>& ySorted,const Outcome& toBeat){
  //strip logic
  Outcome best = toBeat;
  for(int i =0; i < ySorted.size(); i++){
    for(int j =i+1; 
        j< ySorted.size() &&  ((ySorted[j].y - ySorted[i].y) < best.dsq);
	j++){
      
      if(distSquared(ySorted[i],ySorted[j]) < best.dsq) {
        best = 
	  Outcome(ySorted[i],ySorted[j],
	    distSquared(ySorted[i],ySorted[j])
	    );//update best
	  }
	}
      }
  return best;
}	

void dump(const vector<Point>& vec){
  for(int i=0; i<vec.size(); i++){
    cout << "(" << vec[i].x << ", " << vec[i].y << ")" << endl;
  }
}

Outcome proc(const vector<Point>& xSorted, const vector<Point>& ySorted){
   //pick a line and divide and conquer - Find closest pair within a smaller block i.e. divide by half

   Outcome best(xSorted[0],xSorted[1],distSquared(xSorted[0],xSorted[1])); // default initialization 
   
   if(xSorted.size() > 2){
      //return the closest so far - compare current best with best of next recursion and get closest/min
      Point midPoint = xSorted[xSorted.size()/2];
      auto firstHalf = vector<Point>(xSorted.begin(), xSorted.begin() + (xSorted.size()/2));
      auto secondHalf = vector<Point>(xSorted.begin() + (xSorted.size()/2), xSorted.end());
      
      cout << "Midpoint (" << midPoint.x << ", " << midPoint.y << endl;
      vector<Point> Yleft;
      vector<Point> Yright;
      for(int i=0; i< ySorted.size(); i++){
        if(ySorted[i].x <= midPoint.x){
	  Yleft.push_back(ySorted[i]);
	}
	else{
	  Yright.push_back(ySorted[i]);
	}

      }
     
     cout << "Dumping left" << endl;
     dump(Yleft);
     cout << "Done Dumping Left" << endl;
     cout << "Dumping right" << endl;
     dump(Yright);
     cout << "Done Dumping Right" << endl;
     
     auto halvesMin = CompMin(proc(firstHalf,Yleft),proc(secondHalf,Yright));
      best = halvesMin; 
       
      vector<Point> Ystrip;
      for(int i=0; i < ySorted.size(); i++){
        if(abs(ySorted[i].x - midPoint.x) < best.dsq){
	  Ystrip.push_back(ySorted[i]);
	}
      }

     cout << "Midpoint (" << midPoint.x << ", " << midPoint.y << endl;
     cout << "Dumping strip" << endl;
     dump(Ystrip);
     cout << "Done Dumping strip" << endl;

      return CompMin(best,strip(Ystrip,best));
    }
    else{
      return brute(xSorted);
    }


}

Outcome efficient(const vector<Point>& data) {
   vector<Point> delta;
   Outcome best(data[0],data[1],distSquared(data[0],data[1]));
   //sortByX
   auto xSorted (data);
   sort(xSorted.begin(),xSorted.end(),CompX);
   
   //sortbyY
   auto ySorted (data);
   sort(ySorted.begin(),ySorted.end(),CompY);
   
   best = proc(xSorted,ySorted);
   return best;
}

Outcome extra(const vector<Point>& data) {
    return Outcome();
}
