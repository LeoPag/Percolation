//This code generates all the possible binary matrices with size M,N

#include <iostream>
#include <vector>

using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<VVI> VVVI; //Define list of matrices as 3D tensor

VVVI all_mat;

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

void print_vvi(const VVI& vvi){
    for (int i = 0; i < vvi.size(); i++) {
        for (int j = 0; j < vvi[i].size(); j++) {
            cout << vvi[i][j] << " ";
        }
        cout << endl;
    }
    cout <<endl;
}

void display_tensor(){
  int c = 1;
  for (auto it = all_mat.begin(); it != all_mat.end(); it++){
    cout << "MATRIX " << c << endl;
    print_vvi(*it);
    c += 1;
  }
}


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

int main(){
  int M = 2;
  int N = 3;
  VVI start_mat = generate_vvi(M,N);
  backtrack(start_mat, 0,0);
  display_tensor();
  return 0;
}
