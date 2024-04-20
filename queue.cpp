#include <iostream>
#include <cstring>
#include <cassert>
using namespace std;

template <class type>
class queuetype
{
    int maxqueuesize;
    int front;
    int rear;
    int count;
    type *list;

public:
    void initializequeue()
    {
        front = 0;
        rear = maxqueuesize - 1;
        count = 0;
    }

    bool isempty()
    {
        return count == 0;
    }

    bool isfull()
    {
        return count == maxqueuesize;
    }

    void addqueue(const type &newelement)
    {
        if (!isfull())
        {
            rear = (rear + 1) % maxqueuesize;
            count++;
            list[rear] = newelement;
        }
        else
            cout << "queue is full\n";
    }

    void deletequeue()
    {
        if (!isempty())
        {
            count--;
            front = (front + 1) % maxqueuesize;
        }
        else
            cout << "queue is empty \n";
    }

    type getfront()
    {
        assert(!isempty());
        return list[front];
    }

    type getback()
    {
        assert(!isempty());
        return list[rear];
    }

    void traversequeue()
    {
        for (int i = front; i != rear; i = (i + 1) % maxqueuesize)
        {
            cout << list[i] << " ";
        }
        cout << list[rear];
    }

    void reverse_traversequeue()
    {
        for (int i = rear; i != front; i = (i - 1 + maxqueuesize) % maxqueuesize)
        {
            cout << list[i] << " ";
        }
        cout << list[front];
    }

    // void traversequeue(){
    //     if (!isempty())
    //     {
    //         int i = front -1;
    //         while(i!=rear){
    //             i = (i+1) % maxqueuesize;
    //             cout << list[i] << " ";
    //         }
    //     }
    // }

    void copyqueue(const queuetype<type> &otherqueue)
    {
        maxqueuesize = otherqueue.maxqueuesize;
        front = otherqueue.front;
        rear = otherqueue.rear;
        count = otherqueue.count;
        list = new type[maxqueuesize];
        for (int i = 0; i < count; i++)
        {
            list[i] = otherqueue.list[i];
        }
    }

    queuetype(int queuesize)
    {
        if (queuesize <= 0)
        {
            cout << "size of the array to hold the queue must be positive.\n";
            cout << "creating array of size 100...\n";
            maxqueuesize = 100;
        }
        else
            maxqueuesize = queuesize;

        front = 0;
        rear = maxqueuesize - 1;
        count = 0;
        list = new type[maxqueuesize];
    }

    ~queuetype()
    {
        delete[] list;
    }

    queuetype(const queuetype<type> &otherqueue)
    {
        copyqueue(otherqueue);
    }

    queuetype &operator=(const queuetype<type> &otherqueue)
    {
        if (this != &otherqueue)
            copyqueue(otherqueue);
        return *this;
    }

    friend bool operator==(const queuetype<type> &q1, const queuetype<type> &q2)
    {
        if (q1.count != q2.count)
        {
            return false;
        }
        else
        {
            int i = 0;
            bool equal = true;
            while (i < q1.count && equal)
            {
                int index = (q1.front + i) % q1.maxqueuesize;
                int otherIndex = (q2.front + i) % q2.maxqueuesize;
                if (q1.list[index] != q2.list[otherIndex])
                {
                    equal = false;
                }
                i++;
            }
            return equal;
        }
    }

    friend ostream &operator<<(ostream &os, queuetype<type> &q)
    {
        os << "Queue elements: ";
        if (!q.isempty())
        {
            for (int i = q.front; i != q.rear; i = (i + 1) % q.maxqueuesize)
            {
                os << q.list[i] << " ";
            }
            os << q.list[q.rear];
        }
        else
        {
            os << "Queue is empty.";
        }
        return os;
    }

    friend queuetype<type> operator+(const queuetype<type> &q1, const queuetype<type> &q2)
    {
        queuetype<type> result(q1.maxqueuesize + q2.maxqueuesize);

        int i = q1.front;
        while (i != q1.rear)
        {
            result.addqueue(q1.list[i]);
            i = (i + 1) % q1.maxqueuesize;
        }
        result.addqueue(q1.list[i]);

        i = q2.front;
        while (i != q2.rear)
        {
            result.addqueue(q2.list[i]);
            i = (i + 1) % q2.maxqueuesize;
        }
        result.addqueue(q2.list[i]);

        return result;
    }
};

int main()
{
    queuetype<int> queue1(10);
    int x, y;
    queue1.initializequeue();
    x = 4;
    y = 5;
    queue1.addqueue(x);
    queue1.addqueue(y);
    queue1.deletequeue();
    queue1.addqueue(x + 5);
    queue1.addqueue(15);
    queue1.addqueue(x);
    queue1.addqueue(y + 6);
    queue1.addqueue(y - 3);

    cout << "Normal traversal: ";
    queue1.traversequeue();
    cout << endl;

    cout << "Reverse traversal: ";
    queue1.reverse_traversequeue();
    cout << endl;

    cout << "-------------------------------" << endl;
    queuetype<int> q1(5);
    q1.addqueue(1);
    q1.addqueue(2);
    q1.addqueue(3);

    queuetype<int> q2(5);
    q2.addqueue(4);
    q2.addqueue(5);

    cout << "Queue 1: " << q1 << endl;
    cout << "Queue 2: " << q2 << endl;

    queuetype<int> q3 = q1 + q2;
    cout << "Queue 3 (result of addition): " << q3 << endl;

    return 0;
}

