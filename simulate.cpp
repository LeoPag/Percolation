//This code runs a complete simulation to find the probabilities of percolation given the size of the matrix.
//It uses a DFS O(N^2) exploration to check for percolation starting from each element on the top row. Therefore
//complexity for checking for percolation is O(N^3).


//For given dimensions of the matrix M*N, we can compute the probability of percolation. If the matrices are of size
//M*N, there exists 2^(M*N) possible binary matrices, which all ocuur with the same odd if p = 0.5.

//It is worth noting, that our simulation works for M*N smal (<= 16).
#include <iostream>
#include <vector>

using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<VVI> VVVI; //Define list of matrices as 3D tensor

VVVI all_mat;

//These bounds define the maximum M and maximum N sizes of the binary matrices.
//Since computing the matrices is expoenential in M*N, we ae forced to keep M*N small.
int max_m = 4;
int max_n = 4;

//Generate a random binary matrix
VVI generate_vvi(int m,int n) {
    int c;
    VVI vvi(m, VI(n));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            c= rand() %2;
            if(c==0) {
                vvi[i][j] = 0;
            }
            else{
                vvi[i][j] = 1;
            }
        }
    }
    return vvi;
}


//Generate a null matrix
VVI generate_vvi_null(int m, int n) {
    VVI vvi(m, VI(n));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            vvi[i][j] = 0;
        }
    }
    return vvi;
}

//Display a matrix
void print_vvi(const VVI& vvi){
    for (int i = 0; i < vvi.size(); i++) {
        for (int j = 0; j < vvi[i].size(); j++) {
            cout << vvi[i][j] << " ";
        }
        cout << endl;
    }
    cout <<endl;
}


//Display a tensor of matrices
void display_tensor(){
  int c = 1;
  for (auto it = all_mat.begin(); it != all_mat.end(); it++){
    cout << "MATRIX " << c << endl;
    print_vvi(*it);
    c += 1;
  }
}

//Backtracking function to compute all possible binary matrices of a given size.
void backtrack(VVI& curr_mat, int i, int j){

  if (j < curr_mat[i].size() - 1){
    curr_mat[i][j] = 0;
    backtrack(curr_mat, i, j+1);
    curr_mat[i][j] = 1;
    backtrack(curr_mat, i, j+1);
  }

  else if(i < curr_mat.size() - 1){
    curr_mat[i][j] = 0;
    backtrack(curr_mat, i+1, 0);
    curr_mat[i][j] = 1;
    backtrack(curr_mat, i+1, 0);
  }

  else if((i == curr_mat.size() - 1) && (j == curr_mat[i].size() - 1)){
    curr_mat[i][j] = 0;
    all_mat.push_back(curr_mat);
    curr_mat[i][j] = 1;
    all_mat.push_back(curr_mat);
  }
}



//Run a DFS exploration to check if percolation is possible. Recursive calls.
bool dfs(const VVI& vvi, int i,int j, VVI &explored) {
    if (i == vvi.size() - 1 && vvi[i][j] == 1) {
        return true;
    }
    if (vvi[i][j] == 0) {
        return false;
    }
    explored[i][j] = 1;

    if (j > 0 && explored[i][j - 1] == 0) {
        if (dfs(vvi, i, j - 1, explored)) {
            return true;
        }
    }
    if (j < vvi[0].size() - 1 && explored[i][j + 1] == 0) {
        if (dfs(vvi, i, j + 1, explored)) {
            return true;
        }
    }

    if (explored[i + 1][j] == 0) {
        if (dfs(vvi, i + 1, j, explored)) {
            return true;
        }
    }
    return false;
}


//Returns True if percolation is possible, else rerturn False
bool check_percolation(const VVI& vvi){
    for(int j=0; j<vvi[0].size();j++) {
        VVI explored = generate_vvi_null(vvi.size(), vvi[0].size());
        if(dfs(vvi,0,j,explored)){
            return true;
        }
    }
    return false;
}


//Given the size of the matrix (M*N), function comput the exact probability of percolation for a random binary matrix.
float compute_probability(int m, int n){
  VVI start_mat = generate_vvi(m,n);
  all_mat = VVVI();
  backtrack(start_mat, 0,0);
  float success = 0;
  for(auto it = all_mat.begin(); it != all_mat.end(); it++){
    success += check_percolation(*it);
  }

  return success / all_mat.size();
}

//By plotting the table we notice that the table is a peculiar sorted matrix where:
// table[i][j] < table[i][j+1] for every i,j
// table[i][j] > table[i+1][j] for every i,j
// This confirms our intuition: by increasing the rows, the chances of percolation decrease, whereas
// by increasing the columns the chances of percolation increase.

// You are free to experiment more by trying out different values of M and N. Just remember about the exponential
// complexity of the experiment.


void simulate(){

  cout << endl;
  cout << "THIS TABLE SHOWS THE PROBABILITY OF PERCOLATION FOR A BINARY MATRIX OF SIZE M*N" << endl << endl;
  cout << " N";
  for(int j = 1; j <= max_n; j++){
    cout << "    " << j;
  }
  cout << endl;
  cout << "M" << endl;
  for (int i = 1; i <= max_m; i++){
    cout << i << "  ";
    for(int j = 1; j <= max_n; j++){
      cout << "  " << compute_probability(i,j);
    }
    cout << endl;
  }
  cout << endl;
}


int main(){
  simulate();
  return 0;
}
