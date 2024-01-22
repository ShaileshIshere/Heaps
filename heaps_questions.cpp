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

/*get biggest three rhombus sums in a grid*/
// this is the functions that tells whether the given coordinated of rhombus lies in the matrix or not
bool checkBounds(vector<vector<int>> &grid, vector<pair<int, int>> &v) {
    for (auto pt : v) {
        if (pt.first < 0 || pt.first >= grid.size() || pt.second < 0 || pt.second >= grid[0].size())
            return false;
    }
    return true;
}
// this is the function where we assign the points of a rhombus and check whether the rhombus lies in the given matrix
bool getAllVertices(vector<vector<int>> &grid, vector<pair<int, int>> &v, pair<int, int> c, int &delta) {
    // here we're assigning the points of rhombus
    pair<int, int> A(c.first - delta, c.second);
    pair<int, int> B(c.first, c.second + delta);
    pair<int, int> C(c.first + delta, c.second);
    pair<int, int> D(c.first, c.second - delta);
    v[0] = A;
    v[1] = B;
    v[2] = C;
    v[3] = D;
    // here we're checking if the rhombus lies in the matrix
    if (checkBounds(grid, v))
        return true;
    return false;
}
/*this is the main fuction, all working is being held here, so here we're pushing the elements from
matrix to heap and also performing the sum of a rhombus and pushing it to the heap*/
void getAllSum(vector<vector<int>> &grid, priority_queue<int> &pq, int &cx, int &cy) {
    // push every element of matrix
    pq.push(grid[cx][cy]);
    // it's the variable that controls the length of the rhombus
    int delta = 1;
    // this pair shows each side of rhombus that have been made
    vector<pair<int, int>> v(4);
    // here we're calculating the sum of rhombus and pushing it into the max-heap
    while (getAllVertices(grid, v, {cx, cy}, delta)) {
        pair<int, int> &A = v[0];
        pair<int, int> &B = v[1];
        pair<int, int> &C = v[2];
        pair<int, int> &D = v[3];
        int csum = grid[A.first][A.second] + grid[B.first][B.second] + grid[C.first][C.second] +
                   grid[D.first][D.second];
        // calculating all cell between A-B
        for (int i = 1; i < (B.first - A.first); ++i)
            csum += grid[A.first + i][A.second + i];
        // calculating all cell between B-C
        for (int i = 1; i < (C.first - B.first); ++i)
            csum += grid[B.first + i][B.second - i];
        // calculating all cell between C-D
        for (int i = 1; i < (C.first - D.first); ++i)
            csum += grid[C.first - i][C.second - i];
        // calculating all cell between D-A
        for (int i = 1; i < (D.first - A.first); ++i)
            csum += grid[D.first - i][D.second + i];
        pq.push(csum);
        // increase the length of rhombus after claculating the sum of smaller one
        delta++;
    }
}
// here we're checking if any element in heap would occurs twice
bool canPush(vector<int> &ans, int &top) {
    for (auto val : ans) {
        if (val == top)
            return false;
    }
    return true;
}
/*here we're sending indexes of the upcoming elements to above mentioned fuctions
and we also pushing the biggest [3] rhombus in the given matrix*/
vector<int> getBiggestThree(vector<vector<int>> &grid) {
    vector<int> ans;
    priority_queue<int> pq;
    // here we're inserting indexes to above function
    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[i].size(); ++j)
            getAllSum(grid, pq, i, j);
    }
    // here we're inserting top [3] rhombuses into a array
    while (!pq.empty() && ans.size() < 3) {
        int top = pq.top();
        pq.pop();
        // here we're checking if any element had occured twice in the heap
        if (canPush(ans, top))
            ans.push_back(top);
    }
    return ans;
}

// minimum difference in sums after removal of elements
long long minimum_difference(vector<int> &nums) {
    int n = nums.size() / 3;
    vector<long long> prefix(nums.size(), -1), suffix(nums.size(), -1);
    long long sum = 0;
    priority_queue<long long> maxHeap;
    // inserting in maxHeap
    for (int i = 0; i < nums.size() - 1; ++i) {
        sum += nums[i];
        maxHeap.push(nums[i]);
        // pop out max elements
        if (maxHeap.size() > n) {
            sum -= maxHeap.top();
            maxHeap.pop();
        }
        if (maxHeap.size() == n)
            prefix[i] = sum;
    }
    sum = 0;
    priority_queue<long long, vector<long long>, greater<long long>> minHeap;
    // inserting in minHeap
    for (int i = nums.size() - 1; i > 0; --i) {
        sum += nums[i];
        minHeap.push(nums[i]);
        // pop out max elements
        if (minHeap.size() > n) {
            sum -= minHeap.top();
            minHeap.pop();
        }
        if (minHeap.size() == n)
            suffix[i] = sum;
    }
    long long ans = LONG_LONG_MAX;
    for (int i = n - 1; i < 2 * n; ++i)
        ans = min(ans, prefix[i] - suffix[i + 1]);
    return ans;
}

// minimum number of refueling stops
int min_refueling_stops(int target, int startFuel, vector<vector<int>> &stations) {
    int stops = 0, distance = 0, i = 0;
    priority_queue<pair<int, int>> maxHeap; //{fuel, pos}
    while (true) {
        while (i < stations.size()) {
            if (stations[i][0] <= distance + startFuel)
                maxHeap.push({stations[i][1], stations[i][0]});
            else
                break;
            ++i;
        }
        distance += startFuel;
        startFuel = 0;
        if (distance >= target)
            break;
        if (maxHeap.empty()) {
            stops = -1;
            break;
        }
        auto &top = maxHeap.top();
        startFuel = (distance - top.second) + top.first;
        distance = top.second;
        maxHeap.pop();
        ++stops;
    }
    return stops;
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

    // int rows, cols;
    // cout << "enter rows and columns : ";
    // cin >> rows >> cols;
    // vector<vector<int>> grid(rows, vector<int>(cols));
    // for(int i=0; i<rows; ++i) {
    //     for(int j=0; j<cols; ++j)
    //         cin >> grid[i][j];
    // }
    // cout << "here is your given vector : " << endl;
    // for(const auto &row:grid) {
    //     cout << "[ ";
    //     for(int x:row)
    //         cout << x << " ";
    //     cout << " ]" << endl;
    // }
    // vector<int> result = getBiggestThree(grid);
    // cout << "here are the top [3] biggest values that forms a rhombus : " << "[ ";
    // for(int r:result)
    //     cout << r << " ";
    // cout << " ]" << endl;

    // int n;
    // cout << "enter the size of vector : ";
    // cin >> n;
    // vector<int> nums(n);
    // for(int i=0; i<n; ++i)
    //     cin >> nums[i];
    // cout << "the minimum difference between the sums : " << minimum_difference(nums) << endl;

    // int target, startFuel, rows;
    // cout << "enter your target and your starting fuel : ";
    // cin >> target >> startFuel;
    // cout << "enter the number of gas stations : ";
    // cin >> rows;
    // vector<vector<int>> stations(rows, vector<int>(2));
    // cout << "enter the position of all gas stations as well as their fueling capacity : ";
    // for(int i=0; i<rows; ++i) {
    //     for(int j=0; j<2; ++j)
    //         cin >> stations[i][j];
    // }
    // cout << "minimum number of stations you've to stop and refuel are : " << min_refueling_stops(target, startFuel, stations);

    return 0 ;
}