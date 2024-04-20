#include <iostream>
#include <cassert>
using namespace std;

template <class Type>
class linkedQueueType
{
private:
    struct nodeType
    {
        Type info;
        nodeType *link;
    };
    nodeType *queueFront;
    nodeType *queueRear;

public:
    bool isEmptyQueue() const
    {
        return (queueFront == NULL);
    }

    bool isFullQueue() const
    {
        return false;
    }

    void initializeQueue()
    {
        nodeType *temp;
        while (queueFront != NULL)
        {
            temp = queueFront;
            queueFront = queueFront->link;
            delete temp;
        }
        queueRear = NULL;
    }

    Type front() const
    {
        assert(queueFront != NULL);
        return queueFront->info;
    }

    Type back() const
    {
        assert(queueRear != NULL);
        return queueRear->info;
    }

    void addQueue(const Type &newElement)
    {
        nodeType *newNode;
        newNode = new nodeType;
        newNode->info = newElement;
        newNode->link = NULL;
        if (queueFront == NULL)
        {
            queueFront = newNode;
            queueRear = newNode;
        }
        else
        {
            queueRear->link = newNode;
            queueRear = queueRear->link;
        }
    }

    void deleteQueue()
    {
        nodeType *temp;
        if (!isEmptyQueue())
        {
            temp = queueFront;
            queueFront = queueFront->link;
            delete temp;
            if (queueFront == nullptr)
                queueRear = nullptr;
        }
        else
            cout << "Cannot remove from an empty queue" << endl;
    }

    linkedQueueType()
    {
        queueFront = NULL;
        queueRear = NULL;
    }

    linkedQueueType(const linkedQueueType<Type> &otherQueue)
    {
        queueFront = NULL;
        queueRear = NULL;
        *this = otherQueue;
    }

    ~linkedQueueType()
    {
        initializeQueue();
    }

    linkedQueueType<Type> &operator=(const linkedQueueType<Type> &otherQueue)
    {
        if (this != &otherQueue)
        {
            initializeQueue();
            nodeType *temp = otherQueue.queueFront;
            while (temp != nullptr)
            {
                addQueue(temp->info);
                temp = temp->link;
            }
        }
        return *this;
    }

    friend bool operator==(const linkedQueueType<Type> &q1, const linkedQueueType<Type> &q2)
    {
         nodeType *temp1 = q1.queueFront;
         nodeType *temp2 = q2.queueFront;

        while (temp1 != nullptr && temp2 != nullptr)
        {
            if (temp1->info != temp2->info)
                return false;
            temp1 = temp1->link;
            temp2 = temp2->link;
        }
        return true;
    }

    void traverseQueue() const
    {
        nodeType *current = queueFront;
        while (current != NULL)
        {
            cout << current->info << " ";
            current = current->link;
        }
        cout << endl;
    }

    void reverseTraverse() const
    {
        nodeType *prev = nullptr;
        nodeType *current = queueFront;
        nodeType *next = nullptr;
        while (current != nullptr)
        {
            next = current->link;
            current->link = prev;
            prev = current;
            current = next;
        }
        current = prev;

        while (current != nullptr)
        {
            cout << current->info << " ";
            current = current->link;
        }
        cout << endl;
    }

    friend ostream &operator<<(ostream &os, const linkedQueueType<Type> &queue)
    {
        nodeType *current = queue.queueFront;
        while (current != nullptr)
        {
            os << current->info << " ";
            current = current->link;
        }
        return os;
    }

  friend linkedQueueType<Type> operator+(const linkedQueueType<Type> &q1, const linkedQueueType<Type> &q2)
{
    linkedQueueType<Type> resultQueue(q1);

    typename linkedQueueType<Type>::nodeType *current = q2.queueFront;
    while (current != nullptr)
    {
        resultQueue.addQueue(current->info);
        current = current->link;
    }

    return resultQueue;
}

};
int main()
{
    linkedQueueType<int> q1;
    q1.addQueue(1);
    q1.addQueue(2);
    q1.addQueue(3);
    q1.addQueue(4);
    linkedQueueType<int> q2;
    q2.addQueue(1);
    q2.addQueue(2);
    q2.addQueue(3);
    q2.addQueue(3);

    cout << "Normal traversal: " << q1 << endl;
    cout << "revsrse traversal: ";
    q1.reverseTraverse();
    cout << endl;

    cout << "front: " << q1.front() << endl;
    cout << "back: " << q1.back() << endl;
    cout << endl;

    linkedQueueType<int> q3;
    q3.addQueue(1);
    q3.addQueue(2);
    q3.addQueue(3);
    q3.addQueue(4);
    linkedQueueType<int> q4;
    q4.addQueue(1);
    q4.addQueue(2);
    q4.addQueue(3);
    q4.addQueue(4);

    if(q3 == q4) cout << "true";
    else cout << "false";
    cout << endl;

    cout << "Sum queue: " << q3 + q4;

    return 0;
}

