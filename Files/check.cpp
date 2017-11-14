#include <bits/stdc++.h>

using namespace std;


vector<string> methods;

vector<string> problems;

map<string, pair<string, double>> fes;


void read ()
{
    ifstream in("in.txt");

    string str;

    getline(in, str);
    stringstream ss(str);

    while(ss >> str)
        methods.push_back(str);
    
    for(int i = 0; i < 1; ++i)
    {
        in >> str;
        problems.push_back(str);

        double aux;

        getline(in, str);
        stringstream lol(str);

        int j = 0;

        //cout << str << "\n";

        while(lol >> aux)
            fes[methods[j++]] = make_pair(problems.back(), aux);
    }
}


void check ()
{
    ifstream in("in2.txt");

    string str;
    int j = 0;    

    while(getline(in, str) && str.size())
    {
        double aux;

        for(int i = 0; i < 5; ++i)
            in >> aux;

        
        cout << str << "      " << aux << "    " << fes[str].second << "\n\n";

        assert(abs(aux - fes[str].second) < 1e-4);
        

        in.ignore();
        
        ++j;
    }
}



int main ()
{
    read();

    check();



    return 0;
}