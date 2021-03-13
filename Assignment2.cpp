#include <iostream>
using namespace std;

//Question1
class Node
{
public:
    int data;
    Node *next;
    Node *previous;
    Node();
    ~Node();
    Node(int data, Node *next, Node *previous);
};

Node::Node()
{
    //Set the default data as zero
    this->data = 0;
    this->next = NULL;
    this->previous = NULL;
}

Node::~Node()
{
    //Nothing need to do in the destructor
    //If we destruct the next and previous here, it will cause segmentation fault11 in destructor of DLL
}

Node::Node(int data, Node *next, Node *previous)
{
    this->data = data;
    this->next = next;
    this->previous = previous;
}

//Question2
class DLLStructure
{
public:
    DLLStructure();
    ~DLLStructure();
    DLLStructure(int array[], int size);
    void PrintDLL();
    void InsertAfter(int valueToInsertAfter, int valueToBeInserted);
    void InsertBefore(int valueToInsertBefore, int valueToBeInserted);
    void Delete(int value);
    void Sort();
    bool IsEmpty();
    int GetHead();
    int GetTail();
    int GetSize();
    int GetMax();
    int GetMin();
    DLLStructure(DLLStructure &dlls);

private:
    Node *first;
    Node *last;
};

//Question2
DLLStructure::DLLStructure()
{
    this->first = NULL;
    this->last = NULL;
}

DLLStructure::~DLLStructure()
{
    //Iterate the whole list and delete each node
    Node *cur = this->first;
    while (cur != NULL)
    {
        Node *next = cur->next;
        delete cur;
        cur = next;
    }
}

DLLStructure::DLLStructure(int array[], int size)
{
    //Iterate the whole array and create a node for each number, then set the next and previous correctly
    if (size > 0)
    {
        this->first = new Node(array[0], NULL, NULL);
        Node *cur = this->first;
        for (int i = 1; i < size; i++)
        {
            cur->next = new Node(array[i], NULL, cur);
            cur = cur->next;
        }
        this->last = cur;
    }
    else
    {
        this->first = NULL;
        this->last = NULL;
    }
}

//Question3
void DLLStructure::PrintDLL()
{
    Node *cur = this->first;
    while (cur != NULL)
    {
        cout << cur->data << " ";
        cur = cur->next;
    }
    //Go to the next line in the end
    cout << endl;
}

//Question4
void DLLStructure::InsertAfter(int valueToInsertAfter, int valueToBeInserted)
{
    //Iterate the whole list to find the first node of the valueToInsertAfter
    Node *target = NULL;
    Node *cur = this->first;
    while (cur != NULL)
    {
        if (cur->data == valueToInsertAfter)
        {
            target = cur;
            break;
        }
        cur = cur->next;
    }
    //If not found, add the valueToBeInserted in the end of the list
    if (target == NULL)
    {
        Node *toadd = new Node(valueToBeInserted, NULL, this->last);
        this->last->next = toadd;
        this->last = toadd;
    }
    //If found, add the valueToBeInserted after the target node
    else
    {
        Node *toadd = new Node(valueToBeInserted, NULL, NULL);
        target->next->previous = toadd;
        toadd->next = target->next;
        target->next = toadd;
        toadd->previous = target;
        if (target == this->last)
        {
            this->last = toadd;
        }
    }
}

//Question5
void DLLStructure::InsertBefore(int valueToInsertBefore, int valueToBeInserted)
{
    //Iterate the whole list to find the first node of valueToInsertBefore, and set the target value as the value of previous node
    Node *cur = this->first;
    int target;
    bool condition = false;
    while (cur != NULL)
    {
        if (cur->data == valueToInsertBefore)
        {
            condition = true;
            target = cur->previous->data;
            break;
        }
        cur = cur->next;
    }
    //If find the target, call the InsertAfter method
    if (condition)
    {
        this->InsertAfter(target, valueToBeInserted);
    }
    //If not, add the valueToBeInserted in the head of the list
    else
    {
        Node *toAdd = new Node(valueToBeInserted, this->first, NULL);
        this->first->previous = toAdd;
        this->first = toAdd;
    }
}

//Question6
void DLLStructure::Delete(int value)
{
    Node *target = NULL;
    Node *cur = this->first;
    //Iterate the whole list to find the node we want to delete
    while (cur != NULL)
    {
        if (cur->data == value)
        {
            target = cur;
            break;
        }
        cur = cur->next;
    }
    //If found, set the next and previous point to the correct reference
    if (target != NULL)
    {
        target->previous->next = target->next;
        target->next->previous = target->previous;
        target->next = NULL;
        target->previous = NULL;
        delete target;
    }
}

//Question7
void DLLStructure ::Sort()
{
    //Check if the list is empty
    if (this->first != NULL)
    {
        //Use the bubble sort, start from the head of the list
        Node *cur = this->first;
        while (cur->next != NULL)
        {
            //If the data of next node smaller than the current one, swap them
            Node *next = cur->next;
            while (next != NULL)
            {
                if (cur->data > next->data)
                {
                    //Only need to swap the data, which is much simpler than swapping the reference of next and previous
                    int tmp = cur->data;
                    cur->data = next->data;
                    next->data = tmp;
                }
                next = next->next;
            }
            cur = cur->next;
        }
    }
}

//Question8
bool DLLStructure ::IsEmpty()
{
    //We can simply check if the head and tail of the list is NULL or not
    if (this->first != NULL && this->last != NULL)
    {
        return false;
    }
    else
    {
        return true;
    }
}

//Question9
int DLLStructure ::GetHead()
{
    //If the list is not empty, then there will be a head node
    if (!this->IsEmpty())
    {
        return this->first->data;
    }
    else
    {
        cout << "The List is empty" << endl;
        return -1;
    }
}
int DLLStructure ::GetTail()
{
    //Similar to GetHead. If the list is not empty, then there will be a tail node
    if (!this->IsEmpty())
    {
        return this->last->data;
    }
    else
    {
        cout << "The List is empty" << endl;
        return -1;
    }
}

//Question10
int DLLStructure ::GetSize()
{
    //Iterate the whole list and count the number of node
    Node *cur = this->first;
    int count = 0;
    while (cur != NULL)
    {
        count++;
        cur = cur->next;
    }
    return count;
}

//Question11
int DLLStructure ::GetMax()
{
    //Check if the list is empty
    if (this->IsEmpty())
    {
        cout << "The List is empty" << endl;
        return -1;
    }
    else
    {
        //Iterate the whole list, set the initial max as the first data, and update the max when iterating
        int max = this->first->data;
        Node *cur = this->first;
        while (cur != NULL)
        {
            if (cur->data > max)
            {
                max = cur->data;
            }
            cur = cur->next;
        }
        return max;
    }
}
int DLLStructure ::GetMin()
{
    //Check if the list is empty
    if (this->IsEmpty())
    {
        cout << "The List is empty" << endl;
        return -1;
    }
    else
    {
        //Similar idea as the GetMax()
        int min = this->first->data;
        Node *cur = this->first;
        while (cur != NULL)
        {
            if (cur->data < min)
            {
                min = cur->data;
            }
            cur = cur->next;
        }
        return min;
    }
}

//Question12
DLLStructure::DLLStructure(DLLStructure &dlls)
{
    int size = dlls.GetSize();
    //Check if the input dlls is empty
    if (size > 0)
    {
        //Similar to the constructor of inputting an array, but iterating the input list instead
        this->first = new Node(dlls.first->data, NULL, NULL);
        Node *cur = this->first;
        Node *pointer = dlls.first->next;
        for (int i = 1; i < size; i++)
        {
            cur->next = new Node(pointer->data, NULL, cur);
            cur = cur->next;
            pointer = pointer->next;
        }
        this->last = cur;
    }
    else
    {
        this->first = NULL;
        this->last = NULL;
    }
}

int main()
{
    // Q 1, 2, 3 should obviously be implemented successfully
    // in order to run the following code
    int array[5] = {11, 2, 7, 22, 4};
    DLLStructure dll(array, 5); // note that 5 is the size of the array
    dll.PrintDLL();             // the output should be: 11, 2, 7, 22, 4
    // Q 4
    dll.InsertAfter(7, 13); // To insert 13 after the first occurence of 7
    dll.PrintDLL();         // the output should be: 11, 2, 7, 13, 22, 4
    dll.InsertAfter(25, 7); // To insert 7 after the first occurence of 25
    dll.PrintDLL();         // the output should be: 11, 2, 7, 13, 22, 4, 7
    // Q 5
    dll.InsertBefore(7, 26);  // To insert 26 before the first occurence of 7
    dll.PrintDLL();           // the output should be: 11, 2, 26, 7, 13, 22, 4, 7
    dll.InsertBefore(19, 12); // To insert 12 before the first occurence of 19
    dll.PrintDLL();           // the output should be: 12, 11, 2, 26, 7, 13, 22, 4, 7
    // Q 6
    dll.Delete(22);
    dll.PrintDLL(); // the output should be: 12, 11, 2, 26, 7, 13, 4, 7
    // Q 7
    dll.Sort();
    dll.PrintDLL(); // the output should be: 2, 4, 7, 7, 11, 12, 13, 26
    // Q 8
    if (dll.IsEmpty())
    {
        cout << "The list is empty" << endl;
    }
    // Q 9
    cout << "Head element is: " << dll.GetHead() << endl;
    cout << "Tail element is: " << dll.GetTail() << endl;
    // Q 10
    cout << "Number of elements in the list is: " << dll.GetSize() << endl;
    // Q 10 theory question
    // print to the screen the written answer for the theory question
    cout << "The Best implementation for GetSize is to add a field in the class to remember the size of the list" << endl;
    cout << "And update the field when add or remove a node from the list" << endl;
    cout << "In the GetSize method, we can return the value stored in the size field directly" << endl;
    // Q 11
    cout << "Max element is: " << dll.GetMax() << endl;
    cout << "Min element is: " << dll.GetMin() << endl;
    // Q 11 theory question
    // print to the screen the written answer for the theory question
    cout << "Question11. We can add two fields, min and max, which are initialized by the data of first node." << endl;
    cout << "When we add a new node to the list, we should compare the input data with these two fields and update them if necessary." << endl;
    cout << "As a consequence, we can return the value stored in these two field directly in getMin andgetMax method." << endl;
    // Q 12 theory question
    // print to the screen the written answer for the theory question
    cout << "Question12. The default copy constructor is not reliable since it only does the shallow copy." << endl;
    cout << "However, we have two fields which are pointers in the linked list. We have to deeply copy them." << endl;
    cout << "Otherwise, the dll2 is the shallow copy of dll, and if we free the memory of dll, there will be part of memory for dll2 is freed as well" << endl;
    cout << "Which will cause error. As a consequence, we have to write our own copy constructor." << endl;
    // Q 12
    DLLStructure dll2(dll);
    dll2.PrintDLL(); // the output should be: 2, 4, 7, 7, 11, 12, 13, 26
    return 0;
}