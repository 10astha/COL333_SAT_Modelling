#include <bits/stdc++.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

typedef pair<int, int> edge;
map<edge , int> dict;

int main(int argc, char *argv[]){
    std::string filename = argv[1];
    std::string graph_file = filename + ".graph";
    std::string minisat_input = filename + ".satinput";
    std::string minisat_output = filename + ".satoutput";
    std::string mapping = filename + ".mapping";
    std::ifstream graph(graph_file);

    int n,E;
    
    if (!graph) { // no file
        cout << "No such file\n";
        exit(0);
    }

    else { // reads inputs from the file (will read only n,E for 2, and set k1 and k2 according to our needs)
        graph >> n;
        graph >> E;

        for (int i = 1; i<=E; i++) { // takes edges one by one and stores them in a mapping (same for 2)
            int a,b;
            graph >> a;
            graph >> b;
            edge temp;temp.first=a;temp.second=b;
            if(temp.first > temp.second) swap(temp.first , temp.second);
            dict[temp] = 1;
        }

        graph.close();

    }

    int start = 1;
    int end = n;
    while (start != end) {

        std::ofstream meow{minisat_input};
       
        
        int mid = floor((start+end+1)/2);
        int k1 = mid;
        int k2 = n - k1;

       int numVariables=n+(n-2)*(n-k1)+n-k1;
    int numClauses=(n*(n-1))/2-E+2*n*(n-k1)+n-3*(n-k1)-1 ; // need to verify
    meow << "p cnf " << numVariables << " " << numClauses << endl;
  
//constrain 2 : 
  
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                edge temp;temp.first=i;temp.second=j;
                if(dict[temp]==0){
                 meow << "-" << i << " -" << j << " 0" << endl;
           
                } 
            }
        }

      int offset = 2*n ; int k11=n-k1;
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

        meow.close();

        std::string minisat_command = "minisat " + minisat_input + " " + minisat_output;
        system(minisat_command.c_str()); //._c_str to convert into const char* type that system() requires
        
        std::ifstream minisat_output_file(minisat_output);
        std::string sat_line;

        // Read first line of result file
        if (minisat_output_file.is_open() ) { 
            minisat_output_file >> sat_line; 
        }

        // If first line is SAT then we have obtained our required max clique

        if (sat_line.compare("SAT")==0){ // CHECK HIGHER
            start = mid;
            end = end;
        }

        else {
            start = start;
            end = mid - 1;

        }

        if (start == end){
            break;
        }

        minisat_output_file.close();
    }

    // Now write onto mapping

    std::ifstream minisat_output_file(minisat_output);
    std::ofstream mapping_file(mapping); 

    std::string sat_line;
    minisat_output_file >> sat_line; 

    mapping_file << "#1" << endl;
    
    int k=0;
    for (int count=0;count<=n;count++){
        int literal;
        minisat_output_file >> literal;
       
        k += 1;
        if (k != 1){
            mapping_file << " ";
        }
        if (literal > 0){
        
        mapping_file << literal<< " ";}
    }

    mapping_file << endl;
    minisat_output_file.close();
    mapping_file.close();

}
