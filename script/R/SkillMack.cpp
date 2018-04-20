#include <bits/stdc++.h>

using namespace std;


int M = 0, N = 0;
double mat[10][50];
int sum[100] = {0};
int n;

int main ()
{
    cin >> n;

    ifstream in("table.txt");
    ofstream out("out.txt");

    string str;

    while(getline(in, str))
    {
        stringstream ss(str);

        int c = 0;

        while(ss >> mat[M][c]) ++c;

        if(N == 0) N = c;

        ++M;
    }

    
    for(int j = 0; j < N; ++j)
        for(int i = 0; i < M; ++i)
            sum[j] += mat[i][j] > 0;


    for(int i = 0; i < M; ++i)
    {
        int yup = 0;
        
        for(int j = 0; j < N; ++j) if(sum[j] >= n)
        {
            if(mat[i][j] > 0) out << mat[i][j] << ", ";
            else              out << "NA, ";

            yup =1;
        }

        if(yup) out << "\n";
    }



    // for(int i = 0; i < M; ++i)
    // {
    //     for(int j = 0; j < N; ++j)
    //         cout << mat[i][j] << " ";
    //     cout << "\n";
    // }


    return 0;
}