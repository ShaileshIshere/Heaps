#include<bits/stdc++.h>

using namespace std;

struct Node {
    int data;
    Node *next;
    Node(int val) : data(val), next(nullptr) {}
};

void insert_at_head(Node* &head, Node* &tail, int data) {
    Node* new_node = new Node(data);
    if(!head)
        head = tail = new_node;
    else {
        tail->next = new_node;
        tail = new_node;
    }
}
// here we're inserting all [k] no. of linked lists in 1D vector
void LinkedList_to_vector(Node* head, vector<Node*> &lists) {
    Node* temp = head;
    while(temp) {
        Node* new_node = new Node(temp->data);
        lists.push_back(new_node);
        temp = temp->next;
    }
}

int main() {
    Node *head, *tail;
    head = tail = nullptr;
    int test_case;
    cin >> test_case;
    vector<Node*> lists;
    while(test_case--) {
        int n;
        cin >> n;
        for(int i=0; i<n; ++i) {
            int value;
            cin >> value;
            insert_at_head(head, tail, value);
        }
        LinkedList_to_vector(head, lists);
        head = tail = nullptr;
    }
    for(int i=0; i<lists.size(); ++i)
        cout << lists[i] << " ";

    return 0;
}