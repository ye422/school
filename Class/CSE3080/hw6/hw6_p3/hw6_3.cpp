#include <iostream>
#include <fstream>
using std::cout;
using std::cin;
const int MAX_VAL = 50;

struct Node {
    int key;
    Node* left;
    Node* right;
};

Node *insert(Node *root, int key);
Node* remove(Node *root, int key);
Node* findMaxNode(Node* node);
void inorderTraversal(Node* root);
void preorderTraversal(Node * root);
void memorydelete(Node*root);

int main() {
    int n, tempval, d;

    Node* root = nullptr;
    std::ifstream infile("input.txt");
    if(infile.fail()) {
        cout << "File open Error!\n";
        exit(1);
    }
    
    std::ifstream deletefile("delete.txt");
    if(deletefile.fail()) {
        cout << "Delete File open Error!\n";
        exit(1);
    }

    infile >> n;

    // 이진 검색 트리에 노드 삽입
    for (int i=0; i<n;i++) {
        infile >> tempval;
        if(tempval < MAX_VAL + 1 && tempval > 0)
            root = insert(root, tempval);
    }
    
    while(deletefile) {
        deletefile >> d;
        root = remove(root, d);
    }
    cout << "inorder : ";
    inorderTraversal(root);
    cout <<'\n';
    cout << "preorder : ";
    preorderTraversal(root);
    cout << '\n';
    infile.close();
    deletefile.close();
    memorydelete(root);
    return 0;
}


Node* insert(Node* root, int key) {
    // 빈 트리일 경우, 새로운 노드 생성 후 반환
    if (root == nullptr) {
        Node* newNode = new Node;
        newNode->key = key;
        newNode->left = nullptr;
        newNode->right = nullptr;
        return newNode;
    }

    // 중복된 키를 가진 노드는 삽입되지 않음
    if (key == root->key) {
        return root;
    }

    // 삽입할 키가 현재 노드의 키보다 작은 경우 왼쪽 서브트리로 이동
    if (key < root->key) {
        root->left = insert(root->left, key);
    }
    // 삽입할 키가 현재 노드의 키보다 큰 경우 오른쪽 서브트리로 이동
    else {
        root->right = insert(root->right, key);
    }

    return root;
}


Node* remove(Node* root, int key) {
    // 빈 트리일 경우, 삭제할 노드가 없으므로 그대로 반환
    if (root == nullptr) {
        return root;
    }

    // 삭제할 노드를 찾음
    if (key < root->key) {
        root->left = remove(root->left, key);
    } 
    else if (key > root->key) {
        root->right = remove(root->right, key);
    } 
    else {
        // 삭제할 노드를 찾은 경우

        // 자식이 없거나 하나만 있는 경우
        if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        // 두 개의 자식이 있는 경우 더 작은 노드 중 최대와 값 바꾸고 바꾼 자리 삭제
        Node* maxNode = findMaxNode(root->left);
        root->key = maxNode->key;
        root->left = remove(root->left, maxNode->key);
    }

    // 변경된 트리 반환
    return root;
}


Node* findMaxNode(Node* node) {
    Node* current = node;
    while (current && current->right != nullptr) {
        current = current->right;
    }
    return current;
}


void inorderTraversal(Node* root) {
    if (root == nullptr) {
        return;
    }
    inorderTraversal(root->left);
    cout << root->key << " ";
    inorderTraversal(root->right);
}

void preorderTraversal(Node * root) {
    if (root == nullptr)
        return;
    cout << root-> key << " ";
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

void memorydelete(Node *root) {
    Node * temp = root;
    if (root == nullptr) return;
    if (root->left != nullptr) memorydelete(root->left);
    if (root->right != nullptr) memorydelete(root->right);
    delete temp;
}
