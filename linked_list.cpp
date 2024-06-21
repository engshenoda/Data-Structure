#include <iostream>
#include <cassert>
using namespace std;
struct nodeType
{
    int info;
    nodeType *link;
};

template <class Type>
class linkedListIterator
{
private:
    nodeType *current;

public:
    linkedListIterator();

    linkedListIterator(nodeType *ptr);

    Type operator*();

    linkedListIterator<Type> operator++();

    bool operator==(const linkedListIterator<Type> &right) const;

    bool operator!=(const linkedListIterator<Type> &right) const;
};

template <class Type>
linkedListIterator<Type>::linkedListIterator()
{
    current = NULL;
}

template <class Type>
linkedListIterator<Type>::linkedListIterator(nodeType *ptr)
{
    current = ptr;
}

template <class Type>
Type linkedListIterator<Type>::operator*()
{
    return current->info;
}

template <class Type>
linkedListIterator<Type> linkedListIterator<Type>::operator++()
{
    current = current->link;
    return *this;
}

template <class Type>
bool linkedListIterator<Type>::operator==(const linkedListIterator<Type> &right) const
{
    return (current == right.current);
}

template <class Type>
bool linkedListIterator<Type>::operator!=(const linkedListIterator<Type> &right) const
{
    return (current != right.current);
}

template <class Type>
class linkedListType
{
private:
    void copyList(const linkedListType<Type> &otherList);

protected:
    int count;
    nodeType *first;
    nodeType *last;

public:
    const linkedListType<Type> &operator=(const linkedListType<Type> &);

    void initializeList();

    bool isEmptyList() const;

    void print() const;

    int length() const;

    void destroyList();

    Type front() const;

    Type back() const;

    virtual bool search(const Type &searchItem) const = 0;

    virtual void insertFirst(const Type &newItem) = 0;

    virtual void insertLast(const Type &newItem) = 0;

    virtual void deleteNode(const Type &deleteItem) = 0;

    linkedListIterator<Type> begin();

    linkedListIterator<Type> end();

    linkedListType();

    linkedListType(const linkedListType<Type> &otherList);

    ~linkedListType();
};

template <class Type>
const linkedListType<Type> &linkedListType<Type>::operator=(const linkedListType<Type> &otherList)
{
    if (this != &otherList)
    {
        copyList(otherList);
    }
    return *this;
}

// Initialize the list
template <class Type>
void linkedListType<Type>::initializeList()
{
    destroyList();
}

// Check if the list is empty
template <class Type>
bool linkedListType<Type>::isEmptyList() const
{
    return first == NULL;
}

// Print the list
template <class Type>
void linkedListType<Type>::print() const
{
    if (first == NULL)
    {
        cout << "The list is empty." << endl;
        return;
    }
    nodeType *current = first;
    while (current != NULL)
    {
        cout << current->info << " ";
        current = current->link;
    }
    cout << endl;
}

template <class Type>
int linkedListType<Type>::length() const
{
    return count;
}

// Destroy the list
template <class Type>
void linkedListType<Type>::destroyList()
{
    nodeType *current = first;
    while (current != NULL)
    {
        nodeType *temp = current;
        current = current->link;
        delete temp;
    }
    first = NULL;
    last = NULL;
    count = 0;
}

// front
template <class Type>
Type linkedListType<Type>::front() const
{
    assert(first != NULL);
    return first->info;
}

//  back
template <class Type>
Type linkedListType<Type>::back() const
{
    assert(last != NULL);
    return last->info;
}

template <class Type>
linkedListIterator<Type> linkedListType<Type>::begin()
{
    linkedListIterator<Type> temp(first);
    return temp;
}
template <class Type>
linkedListIterator<Type> linkedListType<Type>::end()
{
    linkedListIterator<Type> temp(NULL);
    return temp;
}

// Helper function to copy the list
template <class Type>
void linkedListType<Type>::copyList(const linkedListType<Type> &otherList)
{
    // Clear the existing list
    destroyList();

    if (otherList.first == NULL)
    {
        first = last = NULL;
        count = 0;
    }
    else
    {
        count = otherList.count;
        nodeType *current = otherList.first;

        // Create the first node
        first = new nodeType;
        first->info = current->info;
        first->link = NULL;
        last = first;
        current = current->link;

        // Create the rest of the nodes
        while (current != NULL)
        {
            nodeType *newNode = new nodeType;
            newNode->info = current->info;
            newNode->link = NULL;

            last->link = newNode;
            last = newNode;

            current = current->link;
        }
    }
}

// Default constructor
template <class Type>
linkedListType<Type>::linkedListType()
{
    first = NULL;
    last = NULL;
    count = 0;
}

// copy constructor
template <class Type>
linkedListType<Type>::linkedListType(const linkedListType<Type> &otherList)
{
    first = NULL;
    copyList(otherList);
}

// destructor
template <class Type>
linkedListType<Type>::~linkedListType()
{
    destroyList();
}

template <class Type>
class unorderedLinkedList : public linkedListType<Type>
{
public:
    unorderedLinkedList() {}

    unorderedLinkedList(initializer_list<Type> items)
    {
        for (auto it = items.begin(); it != items.end(); ++it)
        {
            insertLast(*it);
        }
    }

    bool search(const Type &searchItem) const;

    void insertFirst(const Type &newItem);

    void insertLast(const Type &newItem);

    void insertAt(int index, Type element);

    void deleteNode(const Type &deleteItem);

    void deleteAt(int index);

    void TraverseList();

    Type RetrieveItem(int index) const;

    void replaceItem(int index, const Type &newItem);

    bool search(const Type &searchItem);

    void print();

    Type operator[](int index);

    template <class t>
    friend ostream &operator<<(ostream &os, const unorderedLinkedList<t> &list);
};

// Search for an item in the list
template <class Type>
bool unorderedLinkedList<Type>::search(const Type &searchItem) const
{
    nodeType *current;
    bool found = false;
    current = this->first;
    while (current != NULL && !found)
        if (current->info == searchItem)
            return true;
        else
            current = current->link;
    return false;
}

// Insert a new item at the beginning of the list
template <class Type>
void unorderedLinkedList<Type>::insertFirst(const Type &newItem)
{
    nodeType *newNode = new nodeType;
    newNode->info = newItem;
    newNode->link = this->first;
    this->first = newNode;
    if (this->last == NULL)
    {
        this->last = newNode;
    }
    this->count++;
}

// Insert a new item at the end of the list
template <class Type>
void unorderedLinkedList<Type>::insertLast(const Type &newItem)
{
    nodeType *newNode = new nodeType;
    newNode->info = newItem;
    newNode->link = NULL;
    if (this->first == NULL)
    {
        this->first = newNode;
        this->last = newNode;
    }
    else
    {
        this->last->link = newNode;
        this->last = newNode;
    }
    this->count++;
}
// Insert a new item at the index of the list
template <class Type>
void unorderedLinkedList<Type>::insertAt(int index, Type element)
{
    if (index < 0 || index >= this->count)
    {
        cout << "out of range";
        return;
    }
    else
    {
        nodeType *newNode = new nodeType;
        newNode->info = element;
        if (index == 0)
            insertFirst(element);
        else if (index == this->count)
            insertLast(element);
        else
        {
            nodeType *curr = this->first;
            for (size_t i = 1; i < index; i++)
            {
                curr = curr->link;
            }
            newNode->link = curr->link;
            curr->link = newNode;
            this->count++;
        }
    }
}
template <class Type>
void unorderedLinkedList<Type>::deleteAt(int index)
{
    // Special case for deleting the first node
    if (index == 0 || index >= this->count)
    {
        nodeType *nodeToDelete = this->first;
        this->first = this->first->link;
        if (this->first == NULL)
        {
            // If the list becomes empty, update last pointer
            this->last = NULL;
        }
        delete nodeToDelete;
        this->count--;
        return;
    }

    // Traverse the list to find the node at the given index
    nodeType *current = this->first;
    nodeType *previous = NULL;
    for (int i = 0; i < index; i++)
    {
        previous = current;
        current = current->link;
    }

    // Update the pointers to remove the node
    previous->link = current->link;
    if (current == this->last)
    {
        // If the deleted node was the last node, update last pointer
        this->last = previous;
    }

    // Delete the node and decrement the count
    delete current;
    this->count--;
}

// Delete a node with the specified item
template <class Type>
void unorderedLinkedList<Type>::deleteNode(const Type &deleteItem)
{
    nodeType *current = this->first;
    nodeType *previous = NULL;

    // Traverse the list to find the node with the target item
    while (current != NULL && current->info != deleteItem)
    {
        previous = current;
        current = current->link;
    }

    // If the node is not found
    if (current == NULL)
    {
        cout << "Item not found." << endl;
        return;
    }

    // If the node to delete is the first node
    if (previous == NULL)
    {
        this->first = current->link;
    }
    else
    {
        previous->link = current->link;
    }

    // If the node to delete is the last node
    if (current == this->last)
    {
        this->last = previous;
    }

    // Delete the current node and update count
    delete current;
    this->count--;
}

template <class Type>
void unorderedLinkedList<Type>::TraverseList()
{
    nodeType *current = this->first;

    // Check if the list is empty
    if (current == NULL)
    {
        cout << "The list is empty." << endl;
        return;
    }

    // Traverse the list and print the info of each node
    cout << "Traversing the list: ";
    while (current != NULL)
    {
        cout << current->info << " ";
        current = current->link;
    }
    cout << endl; // New line after printing the list
}

template <class Type>
bool unorderedLinkedList<Type>::search(const Type &searchItem)
{
    // Use a for loop with begin() and end() iterators
    linkedListIterator<Type> it(this->begin());
    for (; it != this->end(); ++it)
    {
        if (*it == searchItem)
            return true; // Item found
    }
    return false; // Item not found
}

template <class Type>
void unorderedLinkedList<Type>::print()
{
    // Use a for loop with begin() and end() iterators
    cout << "List: ";
    linkedListIterator<Type> it(this->begin());
    for (; it != this->end(); ++it)
    {
        cout << *it << " "; // Dereference the iterator to get the info of the node
    }
    cout << endl; // New line after printing the list
}

template <class Type>
Type unorderedLinkedList<Type>::RetrieveItem(int index) const
{
    if (index < 0 || index >= this->count)
    {
        cout << "Invalid index. Cannot retrieve item at position " << index << endl;
        return Type();
    }

    nodeType *current = this->first;
    for (int i = 0; i < index; ++i)
    {
        current = current->link;
    }

    return current->info;
}

template <class Type>
void unorderedLinkedList<Type>::replaceItem(int index, const Type &newItem)
{
    if (index < 0 || index >= this->count)
    {
        cout << "Invalid index. Cannot replace item at position " << index << endl;
        return;
    }

    nodeType *current = this->first;
    for (int i = 0; i < index; ++i)
    {
        current = current->link;
    }

    current->info = newItem;
}

template <class Type>
Type unorderedLinkedList<Type>::operator[](int index)
{
    nodeType *newnode;
    newnode = this->first;
    if (index <= this->count)
        for (int i = 0; newnode != NULL; i++)
        {
            if (i == index)
            {
                return newnode->info;
            }
            newnode = newnode->link;
        }
}

template <class Type>
ostream &operator<<(ostream &os, const unorderedLinkedList<Type> &list)
{
    nodeType *current = list.first;
    while (current != nullptr)
    {
        os << current->info << " ";
        current = current->link;
    }
    return os;
}
/*ostream& operator<<(ostream& os, const unorderedLinkedList<Type>& l)
{
    nodeType* temp = l.current;
    if (temp != NULL)
    {
        for (int i = 0; temp != NULL; i++)
        {
            os << "data in index(" << i << "): " << temp->info << endl;
            temp = temp->link;
        }
    }
    return os;
} */

int main()
{
    unorderedLinkedList<int> l1;
    l1.insertFirst(1);
    l1.insertLast(2);
    l1.insertLast(3);

    l1.TraverseList();

    // l1[0] = 10;
    cout << l1;

    /* unorderedLinkedList<int> list1, list2;
     int num;

     cout << " Enter numbers ending " << "with -1" << endl;
     num = 1;

     while (num < 5)
     {
         list1.insertFirst(100 - num++);
         // cin >> num;
     }
     cout << list1;
     cout << "\n";
     // int values[] = {1, 2, 3, 4};
     // int size = sizeof(values) / sizeof(values[0]);
     // unorderedLinkedList<int> list3(values, size);

     unorderedLinkedList<int> list3 = {1,2,3,4};
     list3.print();
     // cout << "\n";
     // for(int i = 0;i<size;i++){
     //     cout << list3[i] << " ";
     // }

     // list1.print();
     // cout << endl;
     // int x;
     // cout << "search for item use itretor: ";
     // cin >> x;
     // if(list1.search(x))
     //     cout << "Item found\n";
     // else cout << "Item not found\n";

     // cout << "print for item use itretor: ";
     // list1.print();

     // list2 = list1;

     // cout << "list2: ";

     // list2.print();
     // cout << endl;

     // cout << "Enter the number to be deleted: ";

     // cin >> num;
     // cout << endl;
     // list2.deleteNode(num);

     // cout << "After deleting " << num << endl
     //      << "list2: ";

     // list2.print();
     // cout << endl;
     // int index;
     // cout << "add position and number: ";
     // cin >> index >> num;
     // list2.insertAt(index, num);
     // cout << endl;
     // list2.print();

     // cout << "delete in position: ";
     // cin >> index;
     // list2.deleteAt(index);
     // cout << "After deleting position num " << num << endl
     //      << "list2: ";
     // list2.print();
     // cout << endl;

     // cout << "Retrieve item: " << list2.RetrieveItem(1) << endl;

     // cout << "enter index you want to  replace and the  new item"<<endl;
     // int x1, x2;
     // cin >> x1 >> x2;
     // list2.replaceItem(x1, x2);
     // list2.print();
     // cout << endl;

     // list2.TraverseList();
     // cout<<list2[1];
     // cout<<"list by operator << "<<list2;

 */

    return 0;
}
