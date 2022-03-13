/*
 * Q5670 - Trie
 * Date: 2021.8.19
 */

#include<iostream>
#include<iomanip>
#include<string>
using namespace std;
constexpr char EOS = '/';

struct Node {
    char data;
    Node* sibl, * chld;
    Node(char c = 0) {
        data = c; sibl = chld = nullptr;
    }
    ~Node()	{
        if (sibl) delete sibl;
        if (chld) delete chld;
    }
    int countBranch(int base) {
        Node* cur = this->chld, * temp;
        int totBr = 0, br = base;
        while (cur) {
            if (cur->data == EOS)
                totBr += br;
            temp = cur->sibl;
            if (temp) br++;
            while (temp) {
                if (temp->data == EOS)
                    totBr += br - 1;
                else totBr += temp->countBranch(br);
                temp = temp->sibl;
            }
            cur = cur->chld;
        }
        return totBr;
    }
};
struct Trie {
    Node root;
    void insert(string& s) {
        Node* cur = &root;
        for (auto it = s.begin(); it != s.end(); ++it) {
            char c = *it;
            if (cur->chld) {
                cur = cur->chld;
                while (cur->data != c && cur->sibl)
                    cur = cur->sibl;
                if (cur->data != c) {
                    cur->sibl = new Node(c);
                    cur = cur->sibl;
                }
            } else {
                cur->chld = new Node(c);
                cur = cur->chld;
            }
        }
    }
    int countBranch() {
        int totBr = 0;
        Node* temp = root.chld;
        while (temp) {
            totBr += temp->countBranch(1);
            temp = temp->sibl;
        }
        return totBr;
    }
};
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cout << fixed << setprecision(2);
    int N;
    string s;

    while (cin >> N) {
        Trie T;
        for (int n = 0; n < N; ++n) {
            cin >> s;
            s.push_back(EOS);
            T.insert(s);
        }
        cout << ((float)T.countBranch()) / N << '\n';
    }

    return 0;
}
