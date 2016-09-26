//Fausto Tommasi
#include "closestpair.h"
#include <algorithm>
#include <cstdlib>
#include <sys/time.h>  // used to seed srand for extra credit
#include <math.h>
#include <iostream>
using namespace std;

//comparitor functions
bool CompX(const Point& a,const Point& b){
  return compareByX(a,b);
}

bool CompY(const Point& a,const  Point& b){
  return compareByY(a,b);
}

void dump(const vector<Point>& vec){
  for(unsigned int i=0; i<vec.size(); i++){
    cout << "(" << vec[i].x << ", " << vec[i].y << ")" << ", ";
  }
  cout << endl;
}

Outcome CompMin(Outcome a, Outcome b){
  if( a.dsq < b.dsq){
  
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
  for(unsigned int i =0; i < ySorted.size(); i++){
    for(unsigned int j = i+1; 
      j< ySorted.size() && j < i+7; //(pow((ySorted[j].y - ySorted[i].y),2.0) < best.dsq);
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

Outcome proc(const vector<Point>& xSorted, const vector<Point>& ySorted){
   if(xSorted.size() <= 3 ){
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
    
      /* 
     
     cout << "Midpoint (" << midPoint.x << ", " << midPoint.y << ")" << endl;
     cout << "Dumping left" << endl;
     dump(leftHalf);
     cout << "Done Dumping Left" << endl;
     
     cout << "Dumping right" << endl;
     dump(rightHalf);
     cout << "Done Dumping Right" << endl;

     cout << "Dumping left" << endl;
     dump(Yleft);
     cout << "Done Dumping Left" << endl;
     
     cout << "Dumping right" << endl;
     dump(Yright);
     cout << "Done Dumping Right" << endl;
     
     */
     
     auto leftdelta = proc(leftHalf,Yleft);
     auto rightdelta = proc(rightHalf,Yright);
     //auto delta = CompMin(proc(leftHalf,Yleft),proc(rightHalf,Yright));
     Outcome delta = leftdelta;

     if(min(leftdelta.dsq,rightdelta.dsq)==rightdelta.dsq){
       delta = rightdelta;
     }
     else{
       delta = leftdelta;
     }
      
     vector<Point> Ystrip;
      for(unsigned int i=0; i < ySorted.size(); i++){
              //verify this - what is delta
        if(pow(abs(ySorted[i].x - midPoint.x),2.0) <= delta.dsq){
	        Ystrip.push_back(ySorted[i]);
	      }
      }
/*
    cout << "Midpoint (" << midPoint.x << ", " << midPoint.y << ")" << endl;
    cout << "delta.dsq = " << delta.dsq << endl; 
    cout << "Dumping strip" << endl;
    dump(Ystrip);
    cout << "Done Dumping strip" << endl;
  */   
      for(unsigned int i =0; i< Ystrip.size(); i++){
        for(unsigned int j = 1; j <  9 ; j++){ //next seven points
          if( (i+j) > Ystrip.size()-1) break;
          if(distSquared(Ystrip[i],Ystrip[i+j]) < delta.dsq){
            delta = Outcome(Ystrip[i],Ystrip[i+j],distSquared(Ystrip[i],Ystrip[i+j])) ;
          }
        }
      }

//----------------------------------------------------------------
/*
      for(unsigned int i =0; i < Ystrip.size(); i++){
      for(unsigned int j = i+1; 
        j< Ystrip.size() && (pow((Ystrip[j].y - Ystrip[i].y),2.0) < delta.dsq);
        j++){
          if(distSquared(Ystrip[i],Ystrip[j]) < delta.dsq) {
            delta= 
              Outcome(Ystrip[i],Ystrip[j],
              distSquared(Ystrip[i],Ystrip[j])
              );//update best
          }
       }
      }
*/
      return delta;
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
