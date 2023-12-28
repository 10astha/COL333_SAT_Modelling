
#include <bits/stdc++.h>
using namespace std;
int main(int argc, char *argv[]) {
    // Specify the value of n

    int n,E,k1,k2;
    string filename = argv[1];
    string inputfilename = filename+".graph";
    // string inputfilename ("test.graph");
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
    string inputfilename1 = filename+".satoutput";
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
            // cout << "k1: " << k1 << " k2: " << k2 << endl;
            int kk1=1;
            for(int i = 1; i <= n; i++){
                opfile >> var;
                
                if (var > 0 and kk1<k1) {
                    // cout << "Var: " << var << endl;
                    G1 << var << " ";
                    kk1++;
                } else if (var > 0 and kk1==k1) {
                    G1 << var;
                    kk1++;
                }
                
            }
            int kk2=1;
            for(int i=n+1;i<=2*n;i++){
                opfile >> var;
                
                if (var > 0 and kk2<k2) {
                    // cout << "Var: " << var << endl;
                    G2 << var-n << " ";
                    kk2++;
                } else if (var > 0 and kk2==k2) {
                    G2 << var-n;
                    kk2++;
                }
            }
        } else {
            cout << 0;
        }

       

    }
    string outputfilename = filename+".mapping";
    ofstream outputFile(outputfilename);

    // Check if the file is opened successfully
    if (!outputFile.is_open()) {
        cerr << "Failed to open the file for writing." << std::endl;
        exit(0);
    }

    outputFile << G1.str()<<endl;
    outputFile << G2.str()<< endl;
}
