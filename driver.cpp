#include <iostream>
#include <cstdlib>
#include <random>
#include <vector>
#include <chrono>
#include "point.h"
#include "closestpair.h"
using namespace std;

#define GRIDSIZE 40000001

void usage() {
    cout << "Usage: driver A N [S]" << endl;
    cout << "  A=0 brute, A=1 divide/conquer, A=2 extra" << endl;
    cout << "  N=number of points (N >= 2)" << endl;
    cout << "  S=integer random seed (optional)" << endl;
    exit(-1);
}
bool PointEqual(Point a,Point b){
  if(a.x == b.x && a.y == b.y){
    return true;
  }
  return false;
}
bool OutEqual(Outcome a,Outcome b){
  if(PointEqual(a.p,b.p) && PointEqual(a.q,b.q) && a.dsq == b.dsq){
    return true;
  }
  return false;
}

bool EffBruteValid(const vector<Point>& eff,const vector<Point>& brute ){
  for(int i=0; i < eff.size(); i++){ 
    //if()
  }
  return true;
}

void validate(const vector<Point>& data, const Point& p) {
    bool found = false;
    for (unsigned int j=0; j < data.size(); j++) {
        if (data[j].x == p.x && data[j].y == p.y) {
            found = true;
            break;
        }
    }

    if (!found)
        cout << "ERROR: reported point " << p.x << "," << p.y << " not in original data set" << endl;
}

int main(int argc, char* argv[]) {
    if (argc < 3)
        usage();
    int A = atoi(argv[1]);
    if (A < 0 || A > 2)
        usage();
    int N = atoi(argv[2]);
    if (N < 2)
        usage();
    long S;
    if (argc > 3) 
        S = atol(argv[3]);
    else {
        S = time(NULL);
        cout << "Seed = " << S << endl;
    }

    mt19937 mt_rand(S);

    vector<Point> data(N);
    for (int j=0; j < N; j++) {
        data[j].x = mt_rand() % GRIDSIZE;
    }
    for (int j=0; j < N; j++) {
        data[j].y = mt_rand() % GRIDSIZE;
    }

    Outcome ans,check;
    auto begin = chrono::steady_clock::now();
    switch (A) {
    case 0:
        ans = brute(data);
        break;
    case 1:
        //check = brute(data);
	//begin = chrono::steady_clock::now();
        ans = efficient(data);
        break;
    case 2:
        ans = extra(data);
        break;
    }
    auto end = chrono::steady_clock::now();

    cout << "minimum distance squared reported as " << ans.dsq << endl;
    cout << "achieved by points " << ans.p.x << "," << ans.p.y << " and " << ans.q.x << "," << ans.q.y << endl;
    cout << "elapsed time: " << chrono::duration<double, milli> (end-begin).count() << " ms" << endl;
   /*
   if(!OutEqual(ans,check)){
     cout << "wrong ans" << endl; 
     cout << "should have been " << check.dsq << endl;
     cout << "Points " << check.p.x << ", " << check.p.y << " and " << check.q.x << ", " << check.q.y << endl;
   }
   */
    validate(data, ans.p);
    validate(data, ans.q);
}


