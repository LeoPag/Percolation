#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>

using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef pair<int,int> PI;
typedef queue<PI> QPI;

VVI generate_vvi(int m, int n) {
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

VVI generate_vvi_null(int m, int n) {
    VVI vvi(m, VI(n));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            vvi[i][j] = 0;
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


//Run a BFS search starting from cell (i,j)
bool bfs(const VVI& vvi, int i,int j, VVI &explored) {

    QPI q; //Initialize empty queue
    q.push(make_pair(i,j)); //Insert starting node in the queue

    while (q.empty() == false){
      PI curr_pair = q.front();
      q.pop();
      int curr_i = curr_pair.first;
      int curr_j = curr_pair.second;
      explored[curr_i][curr_j] = 1;

      if(vvi[curr_i][curr_j] == 0){ //Ignore current cell if it is blocked
        continue;
      }
      if(curr_i == vvi.size()-1){
        return true;
      }
      else{
        if((curr_j > 0) && (explored[curr_i][curr_j-1] == 0)){
          q.push(make_pair(curr_i,curr_j-1));
        }
        if((curr_j < vvi[0].size()-1) && (explored[curr_i][curr_j+1] == 0)){
          q.push(make_pair(curr_i,curr_j+1));
        }
        if(explored[curr_i+1][curr_j] == 0){
          q.push(make_pair(curr_i+1,curr_j));
        }
      }
    }

    return false;
}

bool check_percolation(const VVI& vvi){
    for(int j=0; j<vvi[0].size();j++) {
        VVI explored = generate_vvi_null(vvi.size(), vvi[0].size()); //Initialize explored matrix
        if (bfs(vvi,0,j,explored)){
            return true;
        }
    }
    return false;
}

int main(){
    int T = 5; //Choose the number of testcases here

    int M = 5; //Choose the size of the matrices here
    int N = 3;
    
    bool res;
    for(int i=0;i<T;i++){
        cout << "_____________________" << endl;
        cout << "TESTCASE: " << i + 1  << endl;
        VVI mat = generate_vvi(M,N);
        print_vvi(mat);
        res = check_percolation(mat);
        if (res == true){
            cout<<"PERCOLATION is POSSIBLE"<<endl;
        }
        else{
            cout<<"PERCOLATION is NOT POSSIBLE"<<endl;
        }
        cout <<endl;
    }

    return 0;
}
