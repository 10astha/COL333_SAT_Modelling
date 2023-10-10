
#include <bits/stdc++.h>
using namespace std;
int main() {
    // Specify the value of n

    int n,E,k1,k2;
    string inputfilename ("test.graph");
    fstream ipfile;
    ipfile.open(inputfilename, ios::in);
    if (!ipfile) {
        cout << "No such file \n";
        exit( 0 );
    }
    else {
        ipfile>> n;
        ipfile >> E;
        ipfile >> k1;
        ipfile >> k2;

    }

    stringstream G1;
    stringstream G2;
    string inputfilename1 ("test.satoutput");
    fstream opfile;
    opfile.open(inputfilename1, ios::in);
    if (!opfile) {
        cout << "No such file \n";
        exit( 0 );
    }
    else{

        string str;
        opfile >> str;
       
        if (str == "SAT") {
            G1<< "#1"<<endl;
       G2<<"#2"<<endl;
            int var;
            for(int i = 1; i <= n; i++){
                opfile >> var;
                int kk1=0;
                if (var > 0 and kk1<=k1) {
                    G1 << var << " ";
                    kk1++;
                }
                
            }
           
            for(int i=n+1;i<=2*n;i++){
                opfile >> var;
                int kk2=0;
                if (var > 0 and kk2<=k2) {
                    G2 << var-n << " ";
                    kk2++;
                }
            }
        } else {
            cout << 0;
        }

       

    }
    // cout << G1.str() << endl;
    // cout << G2.str() << endl;
    string outputfilename ("test.mapping");
    ofstream outputFile(outputfilename);

    // Check if the file is opened successfully
    if (!outputFile.is_open()) {
        cerr << "Failed to open the file for writing." << std::endl;
        exit(0);
    }

    outputFile << G1.str()<<endl;
    outputFile << G2.str() << endl;
}
