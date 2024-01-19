#include<bits/stdc++.h>

using namespace std;

struct Node {
    int data;
    Node *left, *right;
    Node(int val) : data(val), left(0), right(0) {} 
};
Node* create_binary_tree() {
    int data;
    cout << "enter data : ";
    cin >> data;
    if(data == 0)
        return nullptr;
    Node* root = new Node(data);
    cout << "enter left Node : ";
    root->left = create_binary_tree();
    cout << "enter right Node : ";
    root->right = create_binary_tree();
    return root;
}
int nodeCount(struct Node *root) {
    if (!root)
        return 0;
    int l = nodeCount(root->left);
    int r = nodeCount(root->right);
    return 1 + l + r;
}
bool isCBT(struct Node *root, int n, int i) {
    if (!root)
        return true;
    if (i > n)
        return false;
    return isCBT(root->left, n, 2 * i) && isCBT(root->right, n, 2 * i + 1);
}
bool isMaxOrder(struct Node *root) {
    if (!root)
        return true;
    bool l = isMaxOrder(root->left);
    bool r = isMaxOrder(root->right);
    bool ans = false;
    if (!root->left && !root->right)
        ans = true;
    else if (root->left && !root->right)
        ans = root->data > root->left->data;
    else
        ans = root->data > root->left->data && root->data > root->right->data;
    return ans && l && r;
}

struct myComp {
    bool operator() (pair<int, int> &x, pair<int, int> &y) {
        int distX = (x.first*x.first) + (x.second*x.second);
        int distY = (y.first*y.first) + (y.second*y.second);
        return distX > distY;
    }
};
vector<vector<int>> k_closest_point(vector<vector<int>> &points, int k) {
    vector<vector<int>> ans;
    priority_queue<pair<int, int>, vector<pair<int, int>>, myComp> minPoint;
    // here we're inserting all points in heap
    for(auto p:points)
        minPoint.push({p[0], p[1]});
    // here we're fetching the closest k point from the origin 
    while(!minPoint.empty() && k--) {
        pair<int, int> top = minPoint.top(); 
        minPoint.pop();
        ans.push_back({top.first, top.second});
    }
    return ans;
}

int main() {

    Node* root = create_binary_tree();
    int node_count = nodeCount(root);
    cout << endl;
    if(isCBT(root, node_count, 1) && isMaxOrder(root))
        cout << "the given tree follows the property of max heap" << endl;
    else 
        cout << "the given tree doesn't follows the property of max heap" << endl;

    // int rows, cols=2, k;
    // cout << "enter the no. of points and [k] : ";
    // cin >> rows >> k;
    // vector<vector<int>> points(rows, vector<int>(cols));
    // cout << "enter your desired points here : ";
    // for(int i=0; i<rows; ++i) {
    //     for(int j=0; j<cols; ++j) 
    //         cin >> points[i][j];
    // }
    // vector<vector<int>> ans = k_closest_point(points, k);
    // cout << "here is your [k] closest point from origin : " << endl << "[ ";
    // for(auto x:ans) {
    //     cout << "[ ";
    //     for(auto y:x)
    //         cout << y << " ";
    //     cout << "]";
    // }
    // cout << " ]" << endl;

    return 0 ;
}