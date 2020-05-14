#include <fstream>
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
#include <sstream>
#include <map>
#include <queue>
#include <deque>
#include <cstdlib>
#include <cassert>
#include <stack>
#include <list>
#include <ctime>
#include <cmath>

const int maxd = 20;

using namespace std;

class Bintree;
class treenode{
    friend Bintree;

public:
    int num=-1;
    int min_n = -1;
    treenode *left=nullptr;
    treenode *right=nullptr;
    treenode(){}
    treenode(int n):num(n){}
    ~treenode(){
    }
    void insert_l(treenode *l){
        left = l;
    }
    void insert(treenode *r){
        right = r;
    }
    bool isl(){
        return (left != nullptr) ? true : false;
    }
    bool isr(){
        return (right != nullptr) ? true : false;
    }
};

class Bintree{
public:
    int size = 1;
    treenode *root=nullptr;
    Bintree(){
        root = new treenode;
    };
    void remove(treenode* a){
        if(a->left==nullptr&&a->right==nullptr){
            delete a;
            return;
        }
        if(a->left!=nullptr)
            remove(a->left);
        if(a->right!=nullptr)
            remove(a->right);
    }
    ~Bintree(){
        remove(root);
    }
    void leve_prase(ostream &out){
        queue<treenode*> t;
        t.push(root);
        treenode *v = nullptr;
        while(!t.empty()){
            v = t.front();
            
            t.pop();
            if(v->left!=nullptr)
                t.push(v->left);
            if(v->right!=nullptr)
                t.push(v->right);
            if(!t.empty()){
                out << v->num<<" ";
            }
            else{
                out << v->num;
            }
        }
        out << endl;
    }
};

int mbtree(vector<int>& m,vector<int>& b,treenode* root){
    vector<int>::iterator itm = find(m.begin(), m.end(), *(b.end() - 1));
    if((itm==m.end()-1)&&(itm==m.begin())){
        root->num = *itm;
        root->min_n = root->num;
        return *itm;
    }
    int left = 0, right = 0;
    if(itm!=m.end()-1){
        
        root->right = new treenode;
        root->num = *itm;

        vector<int> rb(b.end() - (m.end() - itm), b.end() - 1);
        vector<int> rm(itm+1, m.end());
        right=mbtree(rm, rb, root->right);
    }
    if(itm!=m.begin()){
        
        
        root->left = new treenode;
        root->num = *itm;
        vector<int> lb(b.begin(), b.begin()+(itm-m.begin()));
        vector<int> lm(m.begin(),itm);
        left=mbtree(lm, lb, root->left);
    }
    if(left*right==0){
        root->min_n = (left == 0) ? root->right->min_n : root->left->min_n;
        int ln = (left == 0) ? right : left;
        return (root->num)+ln;
    }
    if(left==right){
        root->min_n = (root->left->min_n > root->right->min_n) ?root->right->min_n : root->left->min_n;
    }
    else{
        root->min_n=(left>right)?root->right->min_n : root->left->min_n;
    }
    int ln = (left >right) ? right : left;
    return root->num + ln;
}





int main(){
    ifstream fcin(".\\input.txt",ifstream::in);
    ofstream fcout(".\\output.txt",ofstream::out);

    vector<int> middle;
    vector<int> back;

    
    string s;
    while(getline(fcin, s)){
        middle.clear();
        back.clear();
        stringstream ss(s);
        string es;
        while(ss>>es){
            middle.push_back(stoi(es));
        }
        getline(fcin, s);
        stringstream sb(s);
        while(sb>>es){
            back.push_back(stoi(es));
        }
        int res = 0;
        Bintree H;
        res = mbtree(middle, back, H.root);
        fcout << H.root->min_n<<endl;
    }
    

    fcin.close();
    fcout.close();

    return 0;

}

