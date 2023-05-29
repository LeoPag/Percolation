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

int find(int x, VI& parents){
    if (parents[x]!=x){
        return find(parents[x],parents);
    }
    return x;
}

void merge(int x,int y,VI& parents){
    parents[find(x,parents)] = find(y,parents);
}

bool check_percolation(const VVI& vvi){
    VI parents;
    const int M = vvi.size();
    const int N = vvi[0].size();
    const int SOURCE = N*M;
    const int TARGET = N*M+1;

    for(int i=0;i<N*M+2;i++){
        parents.push_back(i);
    }

    for(int i=0;i<M;i++){
        for(int j=0; j < N-1;j++){
            if (vvi[i][j]  == 1 && vvi[i][j+1] ==1){
                merge(i*N+j,i*N+j+1,parents);
            }
        }
    }

    for(int i=0;i<M-1;i++){
        for(int j=0; j < N;j++){
            if (vvi[i][j]  == 1 && vvi[i+1][j] ==1){
                merge(i*N+j,(i+1)*N+j,parents);
            }
        }
    }

    for(int i=0;i<vvi.size();i++){
        merge(SOURCE,i,parents);
        merge(TARGET,N*M-1-i,parents);
    }

    return find(SOURCE,parents)==find(TARGET,parents);
}

int main() {
    int T = 100000;
    int N = 2;
    int M = 2;
    float counter = 0;
    bool res;
    for(int i=0;i<T;i++){
        cout << "_____________________" << endl;
        cout << "TESTCASE: " << i + 1  << endl;
        VVI mat = generate_vvi(M,N);
        print_vvi(mat);
        res = check_percolation(mat);
        counter +=res;
        if (res == true){
            cout<<"PERCOLATION is POSSIBLE"<<endl;
        }
        else{
            cout<<"PERCOLATION is NOT POSSIBLE"<<endl;
        }
        cout <<endl;
    }
    cout<<counter/T;

    return 0;
}
