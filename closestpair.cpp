//Fausto Tommasi
#include "closestpair.h"
#include <algorithm>
#include <cstdlib>
#include <sys/time.h>  // used to seed srand for extra credit
#include <math.h>

using namespace std;

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

Outcome recursive_search(const vector<Point>& xSorted, const vector<Point>& ySorted){
   if(xSorted.size() <= 90 ){ //constant value found through experimentation
      return brute(xSorted);
   }
   else{
      Point midPoint = xSorted[(xSorted.size())/2];
      auto leftHalf = vector<Point>(xSorted.begin(), xSorted.begin() + (xSorted.size()/2));
      auto rightHalf = vector<Point>(xSorted.begin() + (xSorted.size()/2), xSorted.end());
      
      vector<Point> Yleft;
      vector<Point> Yright;
      for(unsigned int i=0; i< ySorted.size(); i++){
        if(compareByX(ySorted[i] , midPoint)){
	        Yleft.push_back(ySorted[i]);
	      }
	      else{
	        Yright.push_back(ySorted[i]);
	      }
      }
    
          
     auto leftdelta = recursive_search(leftHalf,Yleft);
     auto rightdelta = recursive_search(rightHalf,Yright);
     Outcome delta = ((leftdelta.dsq < rightdelta.dsq) ? leftdelta : rightdelta);  
              
     vector<Point> Ystrip;
      for(unsigned int i=0; i < ySorted.size(); i++){
        if(pow(abs(ySorted[i].x - midPoint.x),2.0) <= delta.dsq){
	        Ystrip.push_back(ySorted[i]);
	      }
      }
     
      for(unsigned int i =0; i< Ystrip.size(); i++){
        for(unsigned int j = 1; j <  6 ; j++){ //Look only at next five points as shown by algorithm proof
          
          if( (i+j) > Ystrip.size() -1 ) break; //do not go out of bounds 
          
          if(distSquared(Ystrip[i],Ystrip[i+j]) < delta.dsq){
            delta = Outcome(Ystrip[i],Ystrip[i+j],distSquared(Ystrip[i],Ystrip[i+j])) ;
          }
        }
      }

      return delta;
    }
}

Outcome efficient(const vector<Point>& data) {
   
   //sortByX
   auto xSorted (data);
   sort(xSorted.begin(),xSorted.end(),compareByX);
   
   //sortbyY
   auto ySorted (data);
   sort(ySorted.begin(),ySorted.end(),compareByY);
   
   Outcome best = recursive_search(xSorted,ySorted);
   return best;
}

Outcome extra(const vector<Point>& data) {
    return Outcome();
}
