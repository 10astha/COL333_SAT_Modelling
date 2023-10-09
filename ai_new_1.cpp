
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
    int numVariables=2*n+3*n*n ;
    int numClauses=2*n+n*(n-1)-2*E+4*n*n+2*n-4 ; // need to verify
    // Print the header
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
                } 
            }
        }
  
         for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                edge temp;temp.first=i;temp.second=j;
                if(mapping[temp]==0){
                 meow << "-" << i+n << " -" << j+n << " 0" << endl;
                } 
            }
        }
// constraint3:
//G1
    //atmost k1
        int offset = 2*n ;
        // Clause 1: ¬x1 ∨ s11
        meow << "-1 " << 1*k1+1+offset << " 0" << endl;
        // Clause 2: ¬xn ∨ ¬s(n-1)k
        meow << "-" << n << " -" << (n - 1) * k1 + k1+offset << " 0" << endl;
        // Clauses for ¬s1j for j in 1 to k
        for (int j = 2; j <= k1; ++j) {
            meow << "-" << 1*k1+j +offset<< " 0"<<endl;
        }
        // Clauses for ¬xi ∨ si1, ¬si-11 ∨ si1, ¬xi ∨ ¬si-1k
        for (int i = 2; i < n; i++) {
            meow << "-" << i << " " << i * k1 + 1 + offset << " 0" << std::endl;
            meow << "-" << (i - 1) * k1 + 1 + offset << " " << i * k1 + 1 + offset << " 0" << std::endl;
            meow << "-" << i << " -" << (i - 1) * k1 + k1 + offset << " 0" << std::endl;
        // Clauses for ¬xi ∨ sij ∨ ¬si-1(j-1), ¬si-1j ∨ sij
            for (int j = 2; j <= k1; j++) {
                meow << "-" << i << " " << i * k1 + j + offset << " -" << (i - 1) * k1 + j - 1 + offset << " 0" << std::endl;
                meow << "-" << (i - 1) * k1 + j + offset << " " << i * k1 + j + offset << " 0" << std::endl;
            }
        }

    // atleast k1 True=atmost n-k1 False,negated in both rhs and lhs and it converts to not xis have atmost n-k1 true
        int currentOffset = (n-1 ) * (k1) + k1 + offset;
    // Clause 1: ¬x1 ∨ s11
        int k11=n-k1;
        meow << "1 " << 1*k11+currentOffset+1 << " 0" << endl;
        // Clause 2: ¬xn ∨ ¬s(n-1)k
        meow <<   n << " -" << (n - 1) * k11 +k11+ currentOffset << " 0" << endl;
        // Clauses for ¬s1j for j in 1 to k
        for (int j = 2; j <= k11; ++j) {
            meow << "-" << 1*k11+j +currentOffset<< " 0"<<endl;
        }
        // Clauses for ¬xi ∨ si1, ¬si-11 ∨ si1, ¬xi ∨ ¬si-1k
        for (int i = 2; i < n; ++i) {
            meow  << i << " " << i * k11 + 1 + currentOffset << " 0" << std::endl;
            meow << "-" << (i - 1) * k11 + 1 + currentOffset << " " << i * k11+ 1 + currentOffset << " 0" << std::endl;
            meow  << i << " -" << (i - 1) * k11 + k11 + currentOffset << " 0" << std::endl;
        // Clauses for ¬xi ∨ sij ∨ ¬si-1(j-1), ¬si-1j ∨ sij
            for (int j = 2; j <= k11; ++j) {
                meow <<  i << " " << i * k11 + j + currentOffset << " -" << (i - 1) * k11+ j - 1 + currentOffset << " 0" << std::endl;
                meow << "-" << (i - 1) * k11 + j + currentOffset << " " << i * k11 + j +currentOffset << " 0" << std::endl;
            }
        }

//G2
        // atmost k2 people can be in a group
        //sij=i*k2+j+offsset
        // Offset to ensure variables don't clash
        int offset1 = currentOffset+ (n-1) * (n-k1) + (n-k1);
        // Clause 1: ¬x1 ∨ s11
        meow << "-"<<1+n<<" "<< (1+n)*k2+1+offset1 << " 0" << std::endl;
        // Clause 2: ¬xn ∨ ¬s(n-1)k
        meow << "-" << 2*n << " -" << (2*n - 1) * k2 + k2+offset1 << " 0" << std::endl;
        // Clauses for ¬s1j for j in 1 to k
        for (int j = 2; j <= k2; ++j) {
            meow << "-" << (1+n)*k2+j +offset1<< " 0"<<endl;
        }
            
        // Clauses for ¬xi ∨ si1, ¬si-11 ∨ si1, ¬xi ∨ ¬si-1k
        for (int i = 2; i < n; ++i) {
            meow << "-" << i+n << " " << (i+n) * k2 + 1 + offset1 << " 0" << std::endl;
            meow << "-" << (i+n - 1) * k2 + 1 + offset1 << " " << (i+n) * k2 + 1 + offset1 << " 0" << std::endl;
            meow << "-" << i+n << " -" << (i +n- 1) * k2 + k2 + offset1 << " 0" << std::endl;
        // Clauses for ¬xi ∨ sij ∨ ¬si-1(j-1), ¬si-1j ∨ sij
            for (int j = 2; j <= k2; ++j) {
                meow << "-" << i+n << " " << (i+n) * k2 + j + offset1 << " -" << (i +n- 1) * k2 + j - 1 + offset1 << " 0" << std::endl;
                meow << "-" << (i+n - 1) * k2 + j + offset1 << " " << (i+n) * k2 + j + offset1<< " 0" << std::endl;
            
            }
        }

        int currentOffset1 =offset1+ (2*n-1)*k2+k2;
        int k22=n-k2;
        // Clause 1: ¬x1 ∨ s11
        meow <<1+n<<" "<< (1+n)*k22+1+currentOffset1 << " 0" << std::endl;

        // Clause 2: ¬xn ∨ ¬s(n-1)k
        meow  << 2*n << " -" << (2*n - 1)*k22 +k22+currentOffset1<< " 0" << std::endl;
        // Clauses for ¬s1j for j in 1 to k
        for (int j = 2; j <= k22; ++j) {
            meow << "-" << (1+n)*k22+j +currentOffset1<< " 0"<<endl;
        }
        // Clauses for ¬xi ∨ si1, ¬si-11 ∨ si1, ¬xi ∨ ¬si-1k
        for (int i = 2; i < n; ++i) {
            meow <<  i+n << " " << (i+n) * k22 + 1 + currentOffset1 << " 0" << std::endl;
            meow << "-" << (i+n - 1) * k22 + 1 + currentOffset1 << " " << (i+n) * k22 + 1 +currentOffset1<< " 0" << std::endl;
            meow <<  i+n << " -" << (i +n- 1) * k22 + k22 + currentOffset1 << " 0" << std::endl;
        // Clauses for ¬xi ∨ sij ∨ ¬si-1(j-1), ¬si-1j ∨ sij
            for (int j = 2; j <= k22; ++j) {
                meow <<  i+n << " " << (i+n) * k22 + j + currentOffset1 << " -" << (i - 1+n) * k22 + j - 1 +currentOffset1 << " 0" << std::endl;
                meow << "-" << (i+n - 1) * k22 + j +currentOffset1 << " " << (i+n) * k22 + j + currentOffset1<< " 0" << std::endl;
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


















