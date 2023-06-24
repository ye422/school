#include <iostream>
#include <fstream>

using std::cout;
using std::cin;

const int MAX = 100;

typedef struct node* treePointer;
struct node {
    int key;
    treePointer parent;
    treePointer leftChild, rightChild;
    int n;
};
int node_num = 1;
int stack_top= -1;
int stack[50];
bool push(int dir);
int pop();
node * insertNode(node* root, int item);
bool findNode(node *& root, int item);
int deleteNode( node *&top, node *& root);
void sort(node *&top);
void cleannode(node *& top);



int main() {
    int n1, n2;
    int deleted;
    int temp;
    char input;
    treePointer root = nullptr;
    treePointer top = nullptr;
    bool exit_flag = true;
    bool newtop  = true;
    while( exit_flag) {
        if(node_num > MAX) {
            cout << "Too many numbers.\n";
            exit(1);
        }
        cin >> input;
        if(input == 'i') {
            cin >> temp;
            if ( !findNode(top, temp )) 
            {    
                root = insertNode(root, temp);
                cout << "Insert " << temp <<'\n';
                if ( newtop ) {
                    top = root;
                    newtop = false;
                }
            }
            else cout << "Exist Number\n";
        }

        else if (input == 'q') exit_flag = false; 
        else if (input == 'd') {
            deleted = deleteNode(top, root);
            if (deleted == -1) {
                cout << "Heap Empty.\n";
                newtop = true;
            }
            else cout << "Delete " <<deleted << '\n'; 
        }
    }
    cleannode(top);
    return 0;
}

// 다음에 삽입할 root 리턴
node* insertNode(node* root, int item) {
    int temp,mv_cnt;
   
    treePointer newnode = new node;
    treePointer nextpos = nullptr;

    newnode->key = item;
    newnode->leftChild = nullptr;
    newnode->rightChild = nullptr;
    newnode->n = node_num;

    if (node_num == 1) {
        
        newnode->parent = nullptr;
        root = newnode;
        nextpos = root;
        node_num++;
        return nextpos;
    }
    else newnode->parent = root;
    
    if (node_num%2 == 0) {
        
        root->leftChild = newnode;
        nextpos = root;
    }
    else {
        root -> rightChild = newnode;
    }
    node * current1 = newnode;
   
    node * temptop = root;
    while(temptop -> n != 1)
    {
        temptop = temptop->parent;
    } 
    sort(temptop);

// node_num이 홀수일때 다음 노드 설정
    mv_cnt = 0;
    stack_top = -1;

    if (node_num%2 == 1) {
        bool left_check = false;
        node* current2 = newnode;
        int i = current2-> n;
        while ( i%2 != 0 ) {
            if (current2->n == 1) break;
            current2 = current2->parent;
            if ( i%2 == 0 ) left_check = true;
            i = i/2;
            mv_cnt++;
        }
        if( !left_check &&  current2 -> n == 1) {
            for(int i=0; i<mv_cnt; i++) current2 = current2 -> leftChild;
        }
        else {
            current2 = current2 -> parent -> rightChild;
            for(int i=0; i<mv_cnt-1;i++) current2 = current2 -> leftChild;
        }
    
        nextpos = current2;
    }
    node_num++;
    return nextpos;
}

bool findNode(node *&top, int item) {

    node * current = top;
    bool result;
    if (current == nullptr) result = false;
    else if (current-> key == item) result = true;
    else if (current -> key < item) result = false;
    else if (current -> key != item && current -> leftChild == nullptr && current -> rightChild == nullptr) return false;
    else if (current -> leftChild != nullptr && current -> key  > item && current -> leftChild -> key < item) result = false;
    else if ( current ->  leftChild != nullptr && current -> leftChild -> key == item) result = true;
    else if ( current -> leftChild != nullptr && current -> rightChild != nullptr) {
        if (current -> leftChild -> key >= item && current -> rightChild -> key < item) result = findNode(current->leftChild, item);
        else if (current -> rightChild -> key == item) result = true;
        else result = (findNode(current->leftChild, item ) || findNode(current->rightChild, item));
    }
    return result;
}

int deleteNode(node *& top, node *& root) {
    
    int result, mv, tempval, last_mv;
    if ( top == nullptr ) return -1;
   
    int delete_num  = node_num - 1;
    int i = delete_num;
    stack_top = -1;

    if (delete_num == 1) {
        node * temp = top;
        result = temp -> key;
        top = nullptr;
        node_num = delete_num;
        return result;
    }
    
    else {
        node * temp2 = top;
        node * deleter;
        result = top -> key;
        while(delete_num != 1) {
            i = delete_num%2;
            if( !push(i) ) exit(1);
            delete_num = delete_num / 2;
        } 
        mv = pop();
        while( mv != -1) {
            if (!mv) temp2 = temp2 -> leftChild;
            else temp2 = temp2 -> rightChild;
            last_mv = mv;
            mv = pop();
            
        }
        deleter = temp2;
        root = temp2->parent;
        tempval = deleter -> key;
        deleter -> key = top -> key;
        top -> key = tempval;

        if (last_mv == 1 )
            deleter -> parent -> rightChild = nullptr;
        else deleter -> parent -> leftChild = nullptr;
        
        node_num--;
        sort(top);
        delete deleter;
        }
    return result;
}

bool push(int dir) {
    if (stack_top == 49) return false;
    else {
        stack_top++;
        stack[stack_top] = dir;
        return true;
    }

}

int pop() {
    if (stack_top == -1) return -1;
    else {
        int result = stack[stack_top];
        stack_top--;
        return result; 
    }
}
void sort(node *& root) {

    int temp;
    if (root == nullptr) return;
    if ( root->leftChild != nullptr && root -> rightChild != nullptr ) {
        sort(root->leftChild);
        sort(root->rightChild);
    }
    else if (root -> rightChild == nullptr && root->leftChild != nullptr) {
        sort(root -> leftChild);
    }
    else if (root -> rightChild != nullptr && root->leftChild == nullptr) {
        sort(root -> rightChild);
    }
    else if (root -> rightChild == nullptr && root -> leftChild == nullptr) {
        if (root -> parent == nullptr) return;
    }
    if (root -> parent != nullptr ) {

        if ( root -> parent -> key < root -> key) {
            temp = root -> key;
            root -> key = root -> parent ->key;
            root -> parent -> key = temp;
            sort(root);
        }
        if(root -> n % 2 == 1 && root -> parent -> leftChild != nullptr) {
            if (root -> key > root -> parent -> leftChild -> key )
            {
                temp = root -> key;
                root -> key = root ->parent->leftChild->key;
                root ->parent->leftChild->key = temp;
                sort(root);
                sort(root->parent -> leftChild);
            }
        }
        else if (root -> n % 2 == 0 && root -> parent -> rightChild != nullptr) {
            if (root -> key < root -> parent -> rightChild -> key )
            {
                temp = root -> key;
                root-> key = root ->parent->rightChild->key;
                root->parent->rightChild->key = temp;
                sort(root);
                sort(root->parent->rightChild);
            }
        }
    }
    return;
}


void cleannode(node *& top) {
    node * current = top;
    if (current == nullptr) return;
    if(current-> leftChild != nullptr) cleannode(current -> leftChild);
    if (current -> rightChild != nullptr) cleannode(current -> rightChild);
    delete current;
}