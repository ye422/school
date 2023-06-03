#include <iostream>
#include <fstream>

using std::cout;
using std::cin;

class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

// 이진 탐색 트리에 노드 삽입
Node* insertNode(Node* root, int data) {
    if (root == nullptr) {
        return new Node(data);
    }

    if (data < root->data) {
        root->left = insertNode(root->left, data);
    } else if (data > root->data) {
        root->right = insertNode(root->right, data);
    }

    return root;
}

// In-order 순회를 수행하여 노드 값들을 배열에 저장
void inorderTraversal(Node* root, int arr[], int& index) {
    if (root == nullptr) {
        return;
    }

    inorderTraversal(root->left, arr, index);
    arr[index++] = root->data;
    inorderTraversal(root->right, arr, index);
}

// 두 이진 탐색 트리가 동일한지 비교
bool isSameBinaryTree(Node* root1, Node* root2) {
    int arr1[50];
    int arr2[50];
    int index1 = 0;
    int index2 = 0;

    inorderTraversal(root1, arr1, index1);
    inorderTraversal(root2, arr2, index2);

    if (index1 != index2) {
        return false;
    }

    for (int i = 0; i < index1; i++) {
        if (arr1[i] != arr2[i]) {
            return false;
        }
    }

    return true;
}

int main() {
    int n1, n2;
    int temp;
    Node* root1 = nullptr;
    Node* root2 = nullptr;
    std::ifstream input1;
    std::ifstream input2;
    input1.open("input1.txt");
    if(input1.fail()) {
        cout << "Can't open file.\n";
        return 1;
    }
    input2.open("input2.txt");
    if(input2.fail()) {
        cout << "Can't open file.\n";
        return 1;
    }
    input1 >> n1;
    input2 >> n2;
    if (( n1 > 50 || n1 < 1 ) || (n2 > 50 || n2 < 1 ))
    {
        cout << "Out of range.\n";    
        return 0; 
    }

    if(n1 != n2) {
        cout << "No\n";
        input1.close();
        input2.close();
        return 0;     
    }
    else {
        
        for(int i=0; i<n1;i++) {
            
            if(i == 0) {
                
                input1 >> temp;
                root1 = insertNode(root1,temp);
            }
            else {
                input1 >> temp;
                insertNode(root1, temp);
            }
        }   
        for(int i=0; i<n2;i++) {
            
            if(i == 0) {
                
                input2 >> temp;
                root2 = insertNode(root2,temp);
            }
            else {
                input2 >> temp;
                insertNode(root2, temp);
            }
        }
    }   

    // 두 트리 비교
    bool sameTree = isSameBinaryTree(root1, root2);

    if (sameTree) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }
    return 0;
}