
#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> edge;
map<edge , int> mapping;
int main() {
    // Specify the value of n
    int n,E,k1,k2;
    string inputfilename ("test.graph");
    fstream ipfile;
    ipfile.open(inputfilename, ios::in);
    if (!ipfile) {
        cout << "No such file\n";
        exit( 0 );
    }
    else {
        ipfile>> n;
        ipfile >> E;
        ipfile >> k1;
        ipfile >> k2;

        for (int i = 1; i<=E; i++) {
            int a,b;
            ipfile >> a;
            ipfile >> b;
            edge temp;temp.first=a;temp.second=b;
            if(temp.first > temp.second) swap(temp.first , temp.second);
            mapping[temp] = 1;
        }

    }
    // int n,E,k1,k2;
    // cin>>n>>E>>k1>>k2;
    // edge curr;
    // for(int i = 1 ; i <= E ; i++){
    //     cin >> curr.first >> curr.second;

    //     if(curr.first > curr.second) swap(curr.first , curr.second);
    //     mapping[curr] = 1;
	// }
    stringstream meow;
    int numVariables=2*n+(n-2)*(n-k1)+n-k1+(n-2)*(n-k2)+n-k2;
    int numClauses=n+n*(n-1)-2*E+2*n*(n-k1)+n-3*(n-k1)-1+2*n*(n-k2)+n-3*(n-k2)-1 ; // need to verify
    
       meow << "p cnf " << numVariables << " " << numClauses << endl;

//constraint 1 : a person can belong to only one graph  (not xi and not yi)       
    //Clause 1: (x_i or y_i) for 1 < i < n
            for (int i = 1; i <= n; i++) {
                meow<< "-"<<i << " -" << (i + n) << " 0" << endl;
            }
//constrain 2 : 
  
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                edge temp;temp.first=i;temp.second=j;
                if(mapping[temp]==0){
                 meow << "-" << i << " -" << j << " 0" << endl;
           
                 meow << "-" << i+n << " -" << j+n << " 0" << endl;
                } 
            }
        }
        // meow<<"hehe"<<endl;
// // // constraint3:
// // //G1        i*k1+j
// //     //atmost k1
      int offset = 2*n ;
       int k22=n-k2;
         int k11=n-k1;
       int currentOffset= (n-2) * (k11) + (k11)+offset;
       
       
// //         // Clause 1: ¬x1 ∨ s11
// meow<<"f"<<endl;
    // atleast k1 True=atmost n-k1 False,negated in both rhs and lhs and it converts to not xis have atmost n-k1 true
       
    // Clause 1: ¬x1 ∨ s11
       
        meow << "1 " << 0*k11+offset+1 << " 0" << endl;
        // Clause 2: ¬xn ∨ ¬s(n-1)k
        meow <<   n << " -" << (n - 2) * k11 +k11+ offset << " 0" << endl;
        // Clauses for ¬s1j for j in 1 to k
        for (int j = 2; j <= k11; ++j) {
            meow << "-" << 0*k11+j +offset<< " 0"<<endl;
        }
        // Clauses for ¬xi ∨ si1, ¬si-11 ∨ si1, ¬xi ∨ ¬si-1k
        for (int i = 2; i < n; ++i) {
            meow  << i << " " << (i-1) * k11 + 1 + offset << " 0" << std::endl;
            meow << "-" << (i - 2) * k11 + 1 + offset << " " << (i-1) * k11+ 1 + offset << " 0" << std::endl;
            meow  << i << " -" << (i - 2) * k11 + k11 + offset << " 0" << std::endl;
        // Clauses for ¬xi ∨ sij ∨ ¬si-1(j-1), ¬si-1j ∨ sij
            for (int j = 2; j <= k11; ++j) {
                meow <<  i << " " << (i-1) * k11 + j + offset<< " -" << (i - 2) * k11+ j - 1 + offset << " 0" << std::endl;
                meow << "-" << (i - 2) * k11 + j + offset << " " << (i-1) * k11 + j +offset << " 0" << std::endl;
            }
        }

// meow<<"f3"<<endl;
       
        // Clause 1: ¬x1 ∨ s11
        meow <<1+n<<" "<< (0)*k22+1+currentOffset << " 0" << std::endl;

        // Clause 2: ¬xn ∨ ¬s(n-1)k
        meow  << 2*n << " -" << (n - 2)*k22 +k22+currentOffset<< " 0" << std::endl;
        // Clauses for ¬s1j for j in 1 to k
        for (int j = 2; j <= k22; ++j) {
            meow << "-" << (0)*k22+j +currentOffset<< " 0"<<endl;
        }
        // Clauses for ¬xi ∨ si1, ¬si-11 ∨ si1, ¬xi ∨ ¬si-1k
        for (int i = 2; i < n; ++i) {
            meow <<  i+n << " " << (i-1) * k22 + 1 + currentOffset << " 0" << std::endl;
            meow << "-" << (i - 2) * k22 + 1 + currentOffset << " " << (i-1) * k22 + 1 +currentOffset<< " 0" << std::endl;
            meow <<  i+n << " -" << (i - 2) * k22 + k22 + currentOffset<< " 0" << std::endl;
        // Clauses for ¬xi ∨ sij ∨ ¬si-1(j-1), ¬si-1j ∨ sij
            for (int j = 2; j <= k22; ++j) {
                meow <<  i+n << " " << (i-1) * k22 + j + currentOffset << " -" << (i - 2) * k22 + j - 1 +currentOffset<< " 0" << std::endl;
                meow << "-" << (i-2) * k22 + j +currentOffset << " " << (i-1) * k22 + j + currentOffset<< " 0" << std::endl;
            }
        }

    string outputfilename ("test.satinput");
    ofstream outputFile(outputfilename);

    // Check if the file is opened successfully
    if (!outputFile.is_open()) {
        cerr << "Failed to open the file for writing." << std::endl;
        exit(0);
    }

    outputFile << meow.str();
    
}

























