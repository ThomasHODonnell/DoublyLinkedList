/*
This program was created by Thomas O'Donnell
CSC 1254 - Project 2
*/

//inline after invalid case
#include <iostream>
#include <string>
using namespace std;


// Do not edit the structure of the Node class
template<class Type>
class Node
{
public:
    Node(Type value) { data = value; }
    Node* nextNode;
    Node* previousNode;
    Type data;
};


template <class Type>
class LinkedList
{
public:
    // Constructor
    // Do not edit this function.
    LinkedList()
    {
        head = nullptr;
        tail = nullptr;
    }

    // 5 Points
    // This function returns a pointer to the head. 
    // If head is null, return it anyway.
    Node<Type>* first()
    {
        return head;  
        //may need to overload opp. for empty case
        // I am not sure how this line of code works. (see 2 other places where it is used as the function output.)
    }

    // 5 Points
    // This function returns a pointer to the tail. 
    // If tail is null, return it anyway.
    Node<Type>* last()
    {
        return tail; 
    }

    // 5 Points
    // This function returns true if there are no Nodes in the LinkedList.
    // It returns false if there are any number of Nodes in the LinkedList.
    bool isEmpty() { return head == nullptr; }

    // 15 Points
    // This function takes an argument of the template type Type.
    // It creates a Node with this value as the field data and places this new Node in the last position of the LinkedList.
    void addNode(Type value)
    {
        // Case 1: List is Empty
        if (head == nullptr)
        {
            head = new Node<Type>(value);
            tail = head; 
            head->nextNode = nullptr;
            head->previousNode = nullptr;
            return;
        }
        // Case 2: List not Empty
        Node<Type>* current = head;
        while (current->nextNode != nullptr)
            current = current->nextNode;
       
        current->nextNode = new Node<Type>(value);
        Node<Type>* previous = current;
        current = current->nextNode;
        current->previousNode = previous;
        current->nextNode = nullptr;
        tail = current; 
        return;
    }
    
    // 10 Points
    // This function returns how many Nodes are currently in the LinkedList.
    int size()
    {
        Node<Type>* current = head;
        int i = 0;
        for (; current != nullptr; i++) 
            current = current -> nextNode;
        return i;
    }

    // 20 Points
    // The integer argument given to this function is in 0-indexed format.
    // Meaning: getNodeAtPosition(0) indicates that the first item should be returned.
    // The returned data is a pointer to the Node in that current position in the LinkedList.
    Node<Type>* getNodeAtPosition(int position)
    {
        if (position >= 0 &&  position < size()) {
        Node<Type>* current = head;
        for (int i = 0; i < position; i++)
            current = current -> nextNode;
        return current;
        }
        return nullptr;
    }

    // 45 Points
    // The first argument to this function is the value for data of a Node to be added.
    // The second argument is the position to add it at.
    // The function will create and add the Node to the LinkedList at the requested 0-indexed position.
    void addNodeAtPosition(Type value, int position)
    {
        if (position < 0 || position > size()) { cout << "Invalid Position\n"; return; }
        Node<Type>* newNode = new Node<Type>(value);
        Node<Type>* current = head;
            //case 1 - addnode at begining
            //need empty case and non-empty case
        if (position == 0){
            if (isEmpty()) {head = tail = newNode; return;}
            else {
            newNode -> nextNode = head; 
            head -> previousNode = newNode;
            head = newNode;
            head -> previousNode = nullptr;
            return; 
            }
        }
            //case 2 - addnode in mid
        else if (position > 0 && position < size()) {
            for (int i = 0; i < position; i++) current = current -> nextNode;
            newNode -> nextNode = current;
            newNode -> previousNode = current -> previousNode; 
            current -> previousNode = newNode; 
            newNode -> previousNode -> nextNode = newNode; 
            return; 
        }
            //case 3 - add node at end
        else {
            current = tail; 
            current -> nextNode = newNode; 
            newNode -> previousNode = current; 
            tail = newNode;  
            tail -> nextNode = nullptr; 
            return; 
        }
    }

    // 20 Points
    // This function removes the Node at the provided 0-indexed position from the LinkedList. 
    // This function should also explicitly delete the Node at this position to make sure it does not get lost in memory.
    // Node pointers for other items in the list should be updated appropriately to account for this deletion.
    void deleteNodeAtPosition(int position)
    {
        Node<Type>* current = head;
        Node<Type>* tempNode = new Node<Type>(0);
        if (position == 0) {
            if (current -> nextNode == nullptr) {head = tail = nullptr; delete current; delete tempNode; return;}
            else {
            head = current -> nextNode;
            head -> previousNode = nullptr; 
            delete current;
            delete tempNode;
            return; 
            }
        }
        else if (position > 0 && position < size() - 1) {
            for (int i = 0; i < position; i++) current = current -> nextNode;
            tempNode -> nextNode = current -> nextNode; 
            tempNode -> previousNode = current -> previousNode; 
            delete current;
            tempNode -> previousNode -> nextNode = tempNode -> nextNode; 
            tempNode -> nextNode -> previousNode = tempNode -> previousNode; 
            delete tempNode;
            return; 
        }
        else {
            current = tail;
            tail = current -> previousNode; 
            tail -> nextNode = nullptr; 
            delete current; 
            return; 
        }
    }

    // 15 Points
    // This function finds the first Node with the specified value of Type in the LinkedList.
    // The 0-indexed position of that Node is then returned.
    // If there is no Node with this value, it returns -1.
    int findNodeWithValue(Type value)
    {
        Node<Type>* current = head; 
        int i = 0; 
        while (current != nullptr) {
            if (current -> data == value) return i; 
            else current = current -> nextNode; 
            i++; 
        }
        return -1;

    }

    // 20 Points
    // This function reverses the LinkedList.
    // Update all pointers accordingly.
    void reverseLinkedList()
    {
        Node<Type>* temp = nullptr; 
        Node<Type>* current = head; 
        Node<Type>* previous = nullptr; 
        tail = head; 
        while (current != nullptr) { 
            temp = current -> nextNode; 
            current -> nextNode = previous;
            previous = current; 
            current = temp;
            }
        head = previous; 
        head -> previousNode = nullptr; 
        tail -> nextNode = nullptr; 
 
        return;
    }

    // Printer
	// Do not edit this function
    void printListValues()
    {
        Node<Type>* current = head;
        if (isEmpty()) { cout << "Empty List"; }
        while (current != nullptr)
        {
            cout << current->data << " -> ";
            current = current->nextNode;
        }
        cout << endl;
    }

    // Destructor
	// Do not edit this function
    ~LinkedList()
    {
        Node<Type>* current = head;
        cout << "Deleting LinkedList" << endl;
        while(current != nullptr)
        {
            Node<Type>* nodeBeingDeleted = current;
            current = current->nextNode;
            delete nodeBeingDeleted;
        }
        cout << "LinkedList Deleted" << endl;
    }

protected:
    // First node in the Linked List - do not edit
    Node<Type>* head;
    // Last node in the Linked List - do not edit
    Node<Type>* tail;
};


// Do not edit any of the functions below this
void first(LinkedList<int>* ll) { cout << ll->first()->data << endl; }
void last(LinkedList<int>* ll) { cout << ll->last()->data << endl; }
void size(LinkedList<int>* ll) { cout << ll->size() << endl; }
void isEmpty(LinkedList<int>* ll) {cout << ll->isEmpty() << endl; }
void addNode(LinkedList<int>* ll, int value) { ll->addNode(value); }
void getNodeAtPosition(LinkedList<int>* ll, int position) 
{if(ll->getNodeAtPosition(position) != nullptr){ cout << ll->getNodeAtPosition(position)->data << endl; }
 else { cout << "Invalid Position" << endl; }}
void addNodeAtPosition(LinkedList<int>* ll, int value, int position) { ll->addNodeAtPosition(value, position); }
void deleteNodeAtPosition(LinkedList<int>* ll, int position) { ll->deleteNodeAtPosition(position); }
void findNodeWithValue(LinkedList<int>* ll, int value) {cout << ll->findNodeWithValue(value) << endl; }
void reverseLinkedList(LinkedList<int>* ll) { ll->reverseLinkedList(); }
void printListValues(LinkedList<int>* ll) { ll->printListValues(); }
void deleteLinkedList(LinkedList<int>* ll) { delete ll; }

void process(LinkedList<int>* ll, string line)
{
    string input1;
    string input2;
    if(line == "first") { first(ll); }
    else if (line == "last") { last(ll); }
    else if (line == "size") { size(ll); }
    else if (line == "isEmpty") { isEmpty(ll); }
    else if (line == "addNode") { getline(cin, input1); addNode(ll, stoi(input1)); }
    else if (line == "getNodeAtPosition") { getline(cin, input1); getNodeAtPosition(ll, stoi(input1)); }
    else if (line == "addNodeAtPosition") { getline(cin, input1); getline(cin, input2); addNodeAtPosition(ll, stoi(input1), stoi(input2)); }
    else if (line == "deleteNodeAtPosition") { getline(cin, input1); deleteNodeAtPosition(ll, stoi(input1)); }
    else if (line == "findNodeWithValue") { getline(cin, input1); findNodeWithValue(ll, stoi(input1)); }
    else if (line == "reverseLinkedList") { reverseLinkedList(ll); }
    else if (line == "printListValues") { printListValues(ll); }
    else if (line == "deleteLinkedList") { deleteLinkedList(ll); }
}

int main()
{
    LinkedList<int>* ll = new LinkedList<int>();
    string line;
    while (getline(cin, line)) { if(line == "eof") break; process(ll, line); }
    cout << "Run finished." << endl;
}