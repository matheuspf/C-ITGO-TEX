#include <bits/stdc++.h>
#include <gnuplot-iostream.h>



#include <cstdlib> // *** Thanks to Leonhard Gruenschloss and Mike Giles   ***
#include <cmath>   // *** for pointing out the change in new g++ compilers ***

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

using namespace std;

// ----- SOBOL POINTS GENERATOR BASED ON GRAYCODE ORDER -----------------
// INPUT: 
//   N         number of points  (cannot be greater than 2^32)
//   D         dimension  (make sure that the data file contains enough data!!)      
//   dir_file  the input file containing direction numbers
//
// OUTPUT:
//   A 2-dimensional array POINTS, where
//     
//     POINTS[i][j] = the jth component of the ith point,
//   
//   with i indexed from 0 to N-1 and j indexed from 0 to D-1
//
// ----------------------------------------------------------------------


char STR[] =  "d       s       a       m_i \n 2       1       0       1 \n 3       2       1       1 3 \n 4       3       1       1 3 1 \n 5       3       2       1 1 1 \n 6       4       1       1 1 3 3 \n 7       4       4       1 3 5 13 \n 8       5       2       1 1 5 5 17 \n 9       5       4       1 1 5 5 5 \n 10      5       7       1 1 7 11 19 \n 11      5       11      1 1 5 1 1 \n 12      5       13      1 1 1 3 11 \n 13      5       14      1 3 5 5 31 \n 14      6       1       1 3 3 9 7 49 \n 15      6       13      1 1 1 15 21 21 \n 16      6       16      1 3 1 13 27 49 \n 17      6       19      1 1 1 15 7 5 \n 18      6       22      1 3 1 15 13 25 \n 19      6       25      1 1 5 5 19 61 \n 20      7       1       1 3 7 11 23 15 103 \n 21      7       4       1 3 7 13 13 15 69 \n 22      7       7       1 1 3 13 7 35 63 \n 23      7       8       1 3 5 9 1 25 53 \n 24      7       14      1 3 1 13 9 35 107 \n 25      7       19      1 3 1 5 27 61 31 \n 26      7       21      1 1 5 11 19 41 61 \n 27      7       28      1 3 5 3 3 13 69 \n 28      7       31      1 1 7 13 1 19 1 \n 29      7       32      1 3 7 5 13 19 59 \n 30      7       37      1 1 3 9 25 29 41 \n 31      7       41      1 3 5 13 23 1 55";







double **sobol_points(unsigned N, unsigned D)
{
  // ifstream infile(dir_file,ios::in);
  // if (!infile) {
  //   cout << "Input file containing direction numbers cannot be found!\n ;
  //   exit(1);
  // }

  
  stringstream infile(STR);

  char buffer[1000];
  infile.getline(buffer,1000,'\n');

  // L = max number of bits needed 
  unsigned L = (unsigned)ceil(log((double)N)/log(2.0)); 

  // C[i] = index from the right of the first zero bit of i
  unsigned *C = new unsigned [N];
  C[0] = 1;
  for (unsigned i=1;i<=N-1;i++) {
    C[i] = 1;
    unsigned value = i;
    while (value & 1) {
      value >>= 1;
      C[i]++;
    }
  }
  
  // POINTS[i][j] = the jth component of the ith point
  //                with i indexed from 0 to N-1 and j indexed from 0 to D-1
  double **POINTS = new double * [N];
  for (unsigned i=0;i<=N-1;i++) POINTS[i] = new double [D];
  for (unsigned j=0;j<=D-1;j++) POINTS[0][j] = 0; 

  // ----- Compute the first dimension -----
  
  // Compute direction numbers V[1] to V[L], scaled by pow(2,32)
  unsigned *V = new unsigned [L+1]; 
  for (unsigned i=1;i<=L;i++) V[i] = 1 << (32-i); // all m's = 1

  // Evalulate X[0] to X[N-1], scaled by pow(2,32)
  unsigned *X = new unsigned [N];
  X[0] = 0;
  for (unsigned i=1;i<=N-1;i++) {
    X[i] = X[i-1] ^ V[C[i-1]];
    POINTS[i][0] = (double)X[i]/pow(2.0,32); // *** the actual points
    //        ^ 0 for first dimension
  }
  
  // Clean up
  delete [] V;
  delete [] X;
  
  
  // ----- Compute the remaining dimensions -----
  for (unsigned j=1;j<=D-1;j++) {
    
    // Read in parameters from file 
    unsigned d, s;
    unsigned a;
    infile >> d >> s >> a;
    unsigned *m = new unsigned [s+1];
    for (unsigned i=1;i<=s;i++) infile >> m[i];
    
    // Compute direction numbers V[1] to V[L], scaled by pow(2,32)
    unsigned *V = new unsigned [L+1];
    if (L <= s) {
      for (unsigned i=1;i<=L;i++) V[i] = m[i] << (32-i); 
    }
    else {
      for (unsigned i=1;i<=s;i++) V[i] = m[i] << (32-i); 
      for (unsigned i=s+1;i<=L;i++) {
	V[i] = V[i-s] ^ (V[i-s] >> s); 
	for (unsigned k=1;k<=s-1;k++) 
	  V[i] ^= (((a >> (s-1-k)) & 1) * V[i-k]); 
      }
    }
    
    // Evalulate X[0] to X[N-1], scaled by pow(2,32)
    unsigned *X = new unsigned [N];
    X[0] = 0;
    for (unsigned i=1;i<=N-1;i++) {
      X[i] = X[i-1] ^ V[C[i-1]];
      POINTS[i][j] = (double)X[i]/pow(2.0,32); // *** the actual points
      //        ^ j for dimension (j+1)
   }
    
    // Clean up
    delete [] m;
    delete [] V;
    delete [] X;
  }
  delete [] C;
  
  return POINTS;
}





#define SOBOL


// int main ()
// {
// 	int N, D = 2;

// 	cin >> N;

// 	vector<pair<double, double>> v(N);


// #ifdef SOBOL

// 	double **P = sobol_points(N,D); 

// 	for(int i = 0; i < N; ++i)
// 		v[i] = make_pair(P[i][0], P[i][1]);

//   string outStr = "set output 'sobol.eps'\n";

// #else

// 	mt19937 gen(0);

// 	uniform_real_distribution<> dist(0.0, 1.0);
	
// 	for(int i = 0; i < N; ++i)
// 		v[i] = make_pair(dist(gen), dist(gen));

//   string outStr = "set output 'twister.eps'\n";

// #endif


//   //random_shuffle(v.begin(), v.end());


// 	Gnuplot gp;

// 	gp << "set terminal postscript eps enhanced color font 'Helvetica,10'\n";
// 	gp << outStr.c_str();

//     gp << "set datafile separator ','\n";
//     gp << "unset key; unset tics; unset border\n";
	
// 	gp << "plot '-' with points pointtype 3, '-' with points pointtype 3, '-' with points pointtype 3\n";

// 	gp.send1d(vector<pair<double, double>>(v.begin(), v.begin() + N / 3));
// 	gp.send1d(vector<pair<double, double>>(v.begin() + N / 3, v.begin() + (2 * N) / 3));
// 	gp.send1d(vector<pair<double, double>>(v.begin() + (2 * N) / 3, v.begin() + N));

// 	cin.get();


// 	return 0;
// }



int main ()
{
    int N, D = 2;

    cin >> N;

    vector<pair<double, double>> v;


    double **P = sobol_points(N / 2, D);

    for(int i = 0; i < N / 2; ++i)
        v.push_back(make_pair(P[i][0], P[i][1]));


    mt19937 gen(0);

    uniform_real_distribution<> dist(0.0, 1.0);
    
    for(int i = 0; i < N / 2; ++i)
        v.push_back(make_pair(dist(gen), dist(gen)));


    Gnuplot gp;

    gp << "set terminal postscript eps enhanced color font 'Helvetica,10'\n";
    gp << "set output 'scatter.eps'\n";

    gp << "set key box opaque height 2\n";
    gp << "set key width 5\n";
    //gp << "set key height 8\n";
    gp << "set key font \",17\"\n";
    gp << "set key spacing 3\n";


    gp << "set datafile separator ','\n";
    gp << "unset tics\n";
    gp << "set style circle radius screen 0.005\n";
    
    gp << "plot '-' with circles linecolor rgb '#0000FF' lw 3 fill solid noborder title 'M. Twister'," 
       << "     '-' with circles linecolor rgb '#FF0000' lw 3 fill solid noborder title 'Sobol'\n";

    gp.send1d(vector<pair<double, double>>(v.begin() + N / 2, v.end()));
    gp.send1d(vector<pair<double, double>>(v.begin(), v.begin() + N / 2));

    cin.get();


    return 0;
}