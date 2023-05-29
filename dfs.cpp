#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;


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
    if (j < vvi[i].size() - 1 && explored[i][j + 1] == 0) {
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

bool check_percolation(const VVI& vvi){
    for(int j=0; j<vvi[0].size();j++) {
        VVI explored = generate_vvi_null(vvi.size(), vvi[0].size());
        if(dfs(vvi,0,j,explored)){
            return true;
        }
    }
    return false;
}

int main() {
    int T = 5;
    int M = 5;
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
