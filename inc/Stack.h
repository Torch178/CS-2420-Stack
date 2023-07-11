#ifndef ORDEREDLINKEDLIST_H
#define ORDEREDLINKEDLIST_H
#include <iostream>
#include <sstream>

template <class Type>
struct Node
{
	Type data;
	Node *next {nullptr};
};

template <class Type>
class Stack;

template <class Type>
std::ostream& operator<<(std::ostream&, const Stack<Type>& stack);


template <class Type>
class Stack
{
public:
	Stack();
	Stack(const Stack<Type>& other);
	Stack<Type>& operator=(const Stack<Type>& other);
	~Stack();
    Node<Type>* recursivePush(std::string indentAmt, Node<Type>* node);

        int size() const;
        bool empty() const;
	Type top() const;
	void push(const Type&);
	void pop();
        void pop(int);
        Type topPop();
        void clear();
        
        std::string recursiveOutput(std::string indentAmt, Node<Type>* node, std::string strOut);
        friend std::ostream& operator<< <>(std::ostream&, const Stack<Type>& stack);

protected:
    Node<Type>* head{ nullptr };
    Node<Type>* tail{ nullptr };
    int nodeCount = 0;
};

template <class Type>
Stack<Type>::Stack()
{
    head = nullptr;
    tail = nullptr;
    nodeCount = 0;
}

template <class Type>
Stack<Type>::Stack(const Stack<Type>& other)
{

    if (other.head == nullptr) {
        head = nullptr;
        tail = nullptr;
        nodeCount = 0;
    }
    else {
        this->head = nullptr;
        this->tail = nullptr;
        Node<Type>* currNode = other.head;
        Node<Type>* prevNode = nullptr;
        Node<Type>* newNode = nullptr;
        if (currNode != nullptr) {
            newNode = new Node<Type>;
            newNode->data = currNode->data;
            currNode = currNode->next;
            prevNode = newNode;
            this->head = newNode;

        }
        while (currNode != nullptr) {
            newNode = new Node<Type>;
            newNode->data = currNode->data;
            newNode->next = nullptr;
            currNode = currNode->next;
            prevNode->next = newNode;
            prevNode = newNode;

        }
        this->tail = newNode;
        this->nodeCount = other.nodeCount;
    }
    

}

template <class Type>
Stack<Type>& Stack<Type>::operator=(const Stack& other)
{   
    
    if (this != &other) {
        Node<Type>* currNode = this->head;
        while (currNode != nullptr) {
            auto nodeToDelete = currNode;
            currNode = currNode->next;
            delete nodeToDelete;
        }
        //initialize head, tail, and pointers
        this->head = nullptr;
        this->tail = nullptr;
        currNode = other.head;
        Node<Type>* prevNode = nullptr;
        Node<Type>* newNode = nullptr;
        //first node check
        if (currNode != nullptr) {
            newNode = new Node<Type>;
            newNode->data = currNode->data;
            currNode = currNode->next;
            prevNode = newNode;
            this->head = newNode;

        }
        //remaining node cases
        while (currNode != nullptr) {
            newNode = new Node<Type>;
            newNode->data = currNode->data;
            newNode->next = nullptr;
            currNode = currNode->next;
            prevNode->next = newNode;
            prevNode = newNode;
            
        }
        this->tail = newNode;
        this->nodeCount = other.nodeCount;
    }
    return *this;
}

template <class Type>
Stack<Type>::~Stack()
{
    auto currNode = this->head;
    auto nodeToDelete = this->head;
    while (currNode != nullptr) {
        nodeToDelete = currNode;
        currNode = currNode->next;
        delete nodeToDelete;
        nodeCount--;
    }
}


template <class Type>
int Stack<Type>::size() const
{
    return nodeCount;
}

template <class Type>
bool Stack<Type>::empty() const
{
    if (nodeCount == 0) { return true; }
    else { return false; }
}

template <class Type>
Type Stack<Type>::top() const
{
    if (empty()) {
        throw std::logic_error("Stack is empty, invalid command");
    }
    else {
        return (head->data);
    }
}

template <class Type>
void Stack<Type>::push(const Type& item)
{
    auto newNode = new Node<Type>;
    newNode->data = item;
    newNode->next = nullptr;
    if (head == nullptr) {
        head = newNode;
        tail = newNode;
    }
    else {
        newNode->next = head;
        head = newNode;
    }
    nodeCount++;
}

template <class Type>
void Stack<Type>::pop()
{
    if (!empty()) {
        auto currNode = head;
        head = currNode->next;
        delete currNode;
        nodeCount--;
    }
}

template <class Type>
void Stack<Type>::pop(int count)
{
    while (!empty() && count > 0) {
        auto nodeToDelete = head;
        head = head->next;
        delete nodeToDelete;
        nodeCount--;
        count--;
    }
}

template <class Type>
Type Stack<Type>::topPop()
{
    if (empty()) {
        throw std::logic_error("Stack is empty, invalid command");
    }
    else {
        Type data = head->data;
        pop();
        return data;
    }
}

template <class Type>
void Stack<Type>::clear()
{
    //use currNode to point to node, nodeToDelete to free up memory to clear the stack
    auto currNode = this->head;
    auto nodeToDelete = this->head;
    while (currNode != nullptr) {
        nodeToDelete = currNode;
        currNode = currNode->next;
        delete nodeToDelete;
        nodeCount--;
    }
    head = nullptr;
    tail = nullptr;
    nodeCount = 0;
}

template <class Type>
std::string  Stack<Type>::recursiveOutput(std::string indentAmt, Node<Type>* node, std::string strOut) {
    //base case
    if (node->next == nullptr) {
        strOut += std::to_string(node->data);
        strOut += "->";
    }
    //recursive case, iterates through the list in reverse, printing bottom to top of the stack
    else {
        
        
        strOut = recursiveOutput(indentAmt + "   ", node->next, strOut);
        strOut += std::to_string(node->data);
        strOut += "->";
        
    }
    return strOut;
}

template <class Type>
std::ostream& operator<<(std::ostream& out, const Stack<Type>& stack)
{
    auto currNode = stack.head;
    Stack<Type> q = stack;
    //empty list case
    if (stack.empty()) {
        out << "";
    }
    //single item case
    else if (q.nodeCount == 1) {
        auto currNode = stack.head;
        out << currNode->data;
    }
    //More than one item, use recursive function to iterate through stack in reverse
    else {
        
        out << q.recursiveOutput("", currNode->next, "");
        out << std::to_string(currNode->data);
    }
    
    return out;
}
#endif
