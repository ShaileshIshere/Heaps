#include<bits/stdc++.h>

using namespace std;

// remove stones to minimize the total
int min_stones_sum(vector<int> &piles, int k) {
    priority_queue<int> maxHeap;
    for(int x:piles) 
        maxHeap.push(x);
    while(k--) {
        int max_stones = maxHeap.top();
        maxHeap.pop();
        max_stones -= max_stones >> 1;
        maxHeap.push(max_stones);
    }
    int sum=0;
    while(!maxHeap.empty()) {
        sum += maxHeap.top();
        maxHeap.pop();
    }
    return sum;
}

// reorganize string
// method 1:storing each char and its frequency in [pair] data structure
struct custom_comp {
    bool operator() (pair<char, int> data_1, pair<char, int> data_2) {
        return data_1.second < data_2.second;
    }
};
string reorganize_string(string str) {
    int freq[26] = {0};
    // here we're maintaining the frequecy of each alphabet
    for(int i:str)
        freq[i - 'a']++;
    priority_queue<pair<char, int>, vector<pair<char, int>>, custom_comp> maxHeap;
    // here we're inserting the pairs in heap, it consists of all the char with their frequencies
    for(int i=0; i<26; ++i) {
        if(freq[i] > 0) {
            pair<char, int> inHeap(i + 'a', freq[i]);
            maxHeap.push(inHeap);
        }
    }
    // create a string in which we've to store the reorganize order of string
    string ans = "";
    /*here we're reorganizing the string by taking the maximum pair in heap as the first char to insert or the 
    2nd maximum pair to insert after the first char, we're also storing/capturing the frequency of inserted characters*/
    while(maxHeap.size() > 1) {
        // here we're creating the first maximum pair
        auto top_firstHeap = maxHeap.top(); 
        maxHeap.pop();
        // here we're creating the second maximum pair
        auto top_secondHeap = maxHeap.top();
        maxHeap.pop();
        // here we're inserting both the elements
        ans.push_back(top_firstHeap.first);
        top_firstHeap.second--;
        ans.push_back(top_secondHeap.first);
        top_secondHeap.second--;
        // here we also keep a track of their frequencies
        if(top_firstHeap.second > 0)
            maxHeap.push(top_firstHeap);
        if(top_secondHeap.second > 0)
            maxHeap.push(top_secondHeap);
    }
    /*after reorganizing more than half characters in string there's the last pair 
    remaining in the heap, here we're handling that last case*/
    if(maxHeap.size() == 1) {
        auto lastHeap = maxHeap.top();
        maxHeap.pop();
        ans.push_back(lastHeap.first);
        lastHeap.second--;
        if(lastHeap.second != 0)
            return "";
    }
    return ans;
}
// method 2:creating a class to store each char and it's frequency
struct Info {
    char val;
    int count;
    Info(char ch, int cnt) : val(ch), count(cnt) {}
};
struct compare {
    bool operator() (Info data_1, Info data_2) {
        return data_1.count < data_2.count;
    }
};
// string reorganize_string(string str) {
//     int freq[26] = {0};
//     // here we're maintaining the frequecy of each alphabet
//     for(int i:str)
//         freq[i - 'a']++;
//     priority_queue<Info, vector<Info>, compare> maxHeap;
//     // here we're inserting the pairs in heap, it consists of all the char with their frequencies
//     for(int i=0; i<26; ++i) {
//         if(freq[i] > 0) {
//             Info inHeap(i + 'a', freq[i]);
//             maxHeap.push(inHeap);
//         }
//     }
//     // create a string in which we've to store the reorganize order of string
//     string ans = "";
//     /*here we're reorganizing the string by taking the maximum pair in heap as the first char to insert or the 
//     2nd maximum pair to insert after the first char, we're also storing/capturing the frequency of inserted characters*/
//     while(maxHeap.size() > 1) {
//         // here we're creating the first maximum pair
//         Info top_firstHeap = maxHeap.top(); 
//         maxHeap.pop();
//         // here we're creating the second maximum pair
//         Info top_secondHeap = maxHeap.top();
//         maxHeap.pop();
//         // here we're inserting both the elements
//         ans.push_back(top_firstHeap.val);
//         top_firstHeap.count--;
//         ans.push_back(top_secondHeap.val);
//         top_secondHeap.count--;
//         // here we also keep a track of their frequencies
//         if(top_firstHeap.count > 0)
//             maxHeap.push(top_firstHeap);
//         if(top_secondHeap.count > 0)
//             maxHeap.push(top_secondHeap);
//     }
//     /*after reorganizing more than half characters in string there's the last pair 
//     remaining in the heap, here we're handling that last case*/
//     if(maxHeap.size() == 1) {
//         auto lastHeap = maxHeap.top();
//         maxHeap.pop();
//         ans.push_back(lastHeap.val);
//         lastHeap.count--;
//         if(lastHeap.count != 0)
//             return "";
//     }
//     return ans;
// }

// longest happy string
string longest_happy_string(int a, int b, int c) {
    priority_queue<pair<char, int>, vector<pair<char, int>>, custom_comp> maxHeap;
    // here we're inserting the pair of char and their frequencies in heap
    if (a > 0){
        pair<char, int> temp_a('a', a);
        maxHeap.push(temp_a);
    }
    if (b > 0){
        pair<char, int> temp_b('b', b);
        maxHeap.push(temp_b);
    }
    if (c > 0){
        pair<char, int> temp_c('c', c);
        maxHeap.push(temp_c);
    }
    string ans = "";
    // entire same logic as previous problem
    while (maxHeap.size() > 1){
        auto first_top = maxHeap.top();
        maxHeap.pop();
        auto second_top = maxHeap.top();
        maxHeap.pop();
        /*here we're inserting character 2 times coz it's mentioned in 
        question that we're allowed to insert same character 2 times*/
        if (first_top.second >= 2){
            ans.push_back(first_top.first);
            ans.push_back(first_top.first);
            first_top.second -= 2;
        }
        else{
            ans.push_back(first_top.first);
            first_top.second--;
        }
        if (first_top.second > 0)
            maxHeap.push(first_top);
        /*same as here we're inserting second top most element from heap into string
        but we're checking one condition that we could only insert a char 2 times 
        when the frequency of that character is greater or equal to the 
        frequency of the top most element in heap*/
        if (second_top.second >= 2 && second_top.second >= first_top.second){
            ans.push_back(second_top.first);
            ans.push_back(second_top.first);
            second_top.second -= 2;
        }
        else{
            ans.push_back(second_top.first);
            second_top.second--;
        }
        if (second_top.second > 0)
            maxHeap.push(second_top);
    }
    // here we're handling the last remaining pair in heap
    if (maxHeap.size() == 1){
        auto lastHeap = maxHeap.top();
        maxHeap.pop();
        if (lastHeap.second >= 2){
            ans.push_back(lastHeap.first);
            ans.push_back(lastHeap.first);
            lastHeap.second -= 2;
        }
        else{
            ans.push_back(lastHeap.first);
            lastHeap.second--;
        }
    }
    return ans;
}

// median in a stream
// method 1: done without switch cases
void median_from_stream(double &median, priority_queue<int> &maxHeap, priority_queue<int, vector<int>, greater<int>> &minHeap, int element) {
    if (maxHeap.size() == minHeap.size()) {
        if (element > median) {
            minHeap.push(element);
            median = minHeap.top();
        }
        else {
            maxHeap.push(element);
            median = maxHeap.top();
        }
    }
    else if (maxHeap.size() == minHeap.size() + 1) {
        if (element > median) {
            minHeap.push(element);
        }
        else {
            int maxTop = maxHeap.top();
            maxHeap.pop();
            minHeap.push(maxTop);
            maxHeap.push(element);
        }
        median = (maxHeap.top() + minHeap.top())/2.0;
    }
    else if (minHeap.size() == maxHeap.size() + 1) {
        if (element > median){
            int minTop = minHeap.top();
            minHeap.pop();
            maxHeap.push(minTop);
            minHeap.push(element);
        }
        else
            maxHeap.push(element);
        median = (maxHeap.top() + minHeap.top())/2.0;
    }
}
// method 2: done with switch cases
void find_median_using_switch(double &median, int element, priority_queue<int> &maxHeap, priority_queue<int, vector<int>, greater<int>> &minHeap) {
    int size_difference = maxHeap.size() - minHeap.size();
    switch(size_difference) {
        case -1:
            if (element > median){
                int minTop = minHeap.top();
                minHeap.pop();
                maxHeap.push(minTop);
                minHeap.push(element);
            }
            else
                maxHeap.push(element);
            median = (maxHeap.top() + minHeap.top())/2.0;
            break;
        case 0:
            if (element > median) {
                minHeap.push(element);
                median = minHeap.top();
            }
            else {
                maxHeap.push(element);
                median = maxHeap.top();
            }
            break;
        case 1:
            if (element > median) {
                minHeap.push(element);
            }
            else {
                int maxTop = maxHeap.top();
                maxHeap.pop();
                minHeap.push(maxTop);
                maxHeap.push(element);
            }
            median = (maxHeap.top() + minHeap.top())/2.0;
            break;
    }
}
// method 3: done within class
class MedianFinder {
    priority_queue<int> maxHeap;
    priority_queue<int, vector<int>, greater<int>> minHeap;
public:
    // in this fuction we're inserting the upcomming elements in heaps
    void addNum(int num) {
        if(maxHeap.size() == 0 || num < maxHeap.top()) 
            maxHeap.push(num);
        else 
            minHeap.push(num);
        // we're ensuring here that both the heaps should have same no. of elements
        if(maxHeap.size() < minHeap.size()) {
            maxHeap.push(minHeap.top());
            minHeap.pop();  
        }
        else if(maxHeap.size() > minHeap.size()+1) {
            minHeap.push(maxHeap.top());
            maxHeap.pop();
        }
    }
    // in this fuction we're calculating median from the elements present in both the heaps
    double findMedian() {
        if(maxHeap.size() == minHeap.size())
            return (maxHeap.top() + minHeap.top())/2.0;
        return maxHeap.top();
    }
};

int main() {

    // int n, k;
    // cout << "enter the size of array or value of [k] : ";
    // cin >> n >> k;
    // cout << "enter the array : ";
    // vector<int> piles(n);
    // for(int i=0; i<n; ++i)
    //     cin >> piles[i];
    // cout << "min no. of stones present in piles : " << min_stones_sum(piles, k) << endl;

    // string str;
    // cout << "enter your desired string : ";
    // cin >> str;
    // cout << "string before reorganizing : " << str << endl;
    // if(reorganize_string(str) != "")
    //     cout << "string after reorganizing : " << reorganize_string(str) << endl;
    // else 
    //     cout << "your string has too many duplicate characters, hence it's not able to reorganize" << endl;

    // int a, b, c;
    // cout << "enter the values for [a] [b] or [c] : ";
    // cin >> a >> b >> c;
    // if(longest_happy_string(a, b, c) != "")
    //     cout << "the longest happy string according to your input is :" << endl << longest_happy_string(a, b, c) << endl;
    // else 
    //     cout << "by judging your input it's not possible to generate any kind of happy string" << endl;

    // int n;
    // cout << "enter the size of array : ";
    // cin >> n;
    // vector<int> stream(n);
    // for(int i=0; i<n; ++i) 
    //     cin >> stream[i];
    /* this is for method 1 or 2 */
    // double median = 0;
    // priority_queue<int> maxHeap;
    // priority_queue<int, vector<int>, greater<int>> minHeap;
    // cout << "here is your stream with every possible median :-" << endl << "[ ";
    // for(int s:stream) {
    //     int element = s;
    //     // median_from_stream(median, maxHeap, minHeap, element);
    //     find_median_using_switch(median, element, maxHeap, minHeap);
    //     cout << median << " ";
    // }
    // cout << "]" << endl;
    /* this is for method 3 */
    // vector<int> ans;
    // MedianFinder m;
    // for(int i=0; i<n; ++i) {
    //     m.addNum(stream[i]);
    //     ans.push_back(m.findMedian());
    // }
    // cout << "here is your stream with every possible median :-" << endl << "[ ";
    // for(double m:ans)
    //     cout << m << " ";
    // cout << "]" << endl;

    return 0;
}