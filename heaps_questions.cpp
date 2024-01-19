#include<bits/stdc++.h>

using namespace std;

// check if the given binary tree is a heap or not
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
    cout << "enter left Node : " << endl;
    root->left = create_binary_tree();
    cout << "enter right Node : " << endl;
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

// merge two binary max heaps
void heapify(vector<int> &merged, int size, int index) {
    while(true) {
        // here we'er doing [0] based indexing
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int swapIndex = index;
        if(left < size && merged[left] > merged[swapIndex])
            swapIndex = left;
        if(right < size && merged[right] > merged[swapIndex])
            swapIndex = right;
        if(index != swapIndex) {
            swap(merged[index], merged[swapIndex]);
            index = swapIndex;
        }
        else 
            break;
    }
}
vector<int> merge_heaps(vector<int> &a, vector<int> &b) {
    // here we're copying/inserting elements from [a] vector to [merged] vector
    vector<int> merged(a.begin(), a.end());
    // here we're adding up all the elements of [b] vector to [merged] vector
    merged.insert(merged.end(), b.begin(), b.end());
    for(int i=(merged.size() >> 1)-1; i>=0; --i)
        heapify(merged, merged.size(), i);
    return merged;
}

// [k] closest points to origin
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

    // Node* root = create_binary_tree();
    // int node_count = nodeCount(root);
    // if(isCBT(root, node_count, 1) && isMaxOrder(root))
    //     cout << "the given tree follows the property of max heap" << endl;
    // else 
    //     cout << "the given tree doesn't follows the property of max heap" << endl;

    // int n, m;
    // cout << "enter the size of 1st or 2nd vector : ";
    // cin >> n >> m;
    // cout << "enter the elements of 1st vector : ";
    // vector<int> a(n);
    // for(int i=0; i<n; ++i)
    //     cin >> a[i];
    // cout << "enter the elements of 2nd vector : ";
    // vector<int> b(m);
    // for(int i=0; i<m; ++i)
    //     cin >> b[i];
    // vector<int> ans = merge_heaps(a, b);
    // cout << "here is your merged heap : " << endl << "[ ";
    // for(int a:ans)
    //     cout << a << " ";
    // cout << "]" << endl;

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