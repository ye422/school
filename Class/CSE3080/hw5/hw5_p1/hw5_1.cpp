#include <iostream>
#include <fstream>
using std::cin;
using std::cout;

// Node structure for the linked list
struct Node {
    int value;
    Node* next;
};

Node * head = nullptr;
// Function to insert a new node at the beginning of the linked list
void insertNode(int value) {
    Node* newNode = new Node;
    newNode->value = value;
    newNode->next = nullptr;

    Node* finder = head;
    Node * prev = nullptr;

    if (head == nullptr) {
        head = newNode;
        return;
    }

    if (newNode -> value <= finder -> value) {
        newNode -> next = finder; 
        head = newNode;
    }

    else {
        while ( (newNode -> value > finder->value) && finder->next != nullptr )
        {
            prev = finder;
            finder = finder->next;
        }
        if (finder->next == nullptr && (newNode -> value > finder->value) )
        {
            finder -> next = newNode;
            newNode->next = nullptr; 
        }
        else {
        
            newNode->next = finder;
            prev -> next = newNode;
        }
    }
}

// Function to print the linked list
void printList() {
    std::ofstream outfile("output.txt");
    if(outfile.fail()){
        std::cerr << "Can't make file!\n";
        exit(2);
    }
    Node* current = head;
    while (current != nullptr) {
        outfile << current->value << " ";
        current = current->next;
    }
    outfile << std::endl;
    outfile.close();
}

void deleteList() {
    Node* current = head;
    while (current != nullptr) {
        Node* deleter = current;
        current = current->next;
        delete deleter;
    }
    head = nullptr; 
}

int main() {
    int n;
    std::ifstream infile("input.txt");
    if(infile.fail()) {
        std::cerr << "Can't open file!\n";
        exit(1);
    }
    // Insert nodes into the linked list
    infile >> n;
    int * temp_arr = new int[n];
    for(int i=0; i < n; i++)
    {   
        infile >> temp_arr[i];
        insertNode(temp_arr[i]);
    }    
    
    printList();
    infile.close();
    return 0;
}
