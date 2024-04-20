# include <iostream>
using namespace std;
template < class T > class Stack
{
  struct node
  {
	T info;
	node *link;
  };
  node *stacktop;

public:
  Stack ()
  {
	stacktop = nullptr;
  }

  void initialize ()
  {
	node *temp;
	while (stacktop != NULL)
	  {
		temp = stacktop;
		stacktop = stacktop->link;
		delete temp;
	  }
  }
  bool isempty ()
  {
	return (stacktop == nullptr);
  }

  bool isfull ()
  {
	return false;
  }
  void push (T newelement)
  {
	node *newNode = new node;
	newNode->info = newelement;
	newNode->link = stacktop;
	stacktop = newNode;
  }
  void pop ()
  {
	if (stacktop != nullptr)
	  {
		node *temp = stacktop;
		stacktop = stacktop->link;
		delete temp;
	  }
	else
	  {
		cout << "stack is empty";
	  }
  }
  T top ()
  {
	if (stacktop != nullptr)
	  return stacktop->info;
	else
	  {
		cerr << "Error: Stack is empty" << endl;
	  }
  }

  
  void traverse ()
  {
	node *temp = stacktop;
	while (temp != NULL)
	  {
		cout << temp->info << " ";
		temp = temp->link;
	  }
	cout << endl;
  }
  int stacksize ()
  {
	int count = 0;
	node *temp = stacktop;
	while (temp != NULL)
	  {
		temp = temp->link;
		count++;
	  }
	return count;
  }

  void clearstack ()
  {
	stacktop = NULL;
  }
bool operator==(Stack& otherStack) {
        node* node1 = stacktop;
        node* node2 = otherStack.stacktop;
        while (node1 && node2) {
            if (node1->info != node2->info) {
                return false;
            }
            node1 = node1->link;
            node2 = node2->link;
        }
        return node1 == nullptr && node2 == nullptr;
    }
    
/*Stack operator+(const Stack& otherStack) {
        Stack resultStack;
        node* temp = stacktop;
        while (temp != nullptr) {
            resultStack.push(temp->info);
            temp = temp->link;
        }
        temp = otherStack.stacktop;
        while (temp != nullptr) {
            resultStack.push(temp->info);
            temp = temp->link;
        }
        return resultStack;
}*/


Stack operator+(const Stack& otherStack) {
    Stack resultStack;
    node* node1 = stacktop;
    node* node2 = otherStack.stacktop;
    int carry = 0;

    while (node1 != nullptr || node2 != nullptr || carry != 0) {
        int sum = carry;
        if (node1 != nullptr) {
            sum += node1->info;
            node1 = node1->link;
        }
        if (node2 != nullptr) {
            sum += node2->info;
            node2 = node2->link;
        }
        carry = sum / 10;
        sum %= 10;
        resultStack.push(sum);
    }

    return resultStack;
}



};
int main ()
{
 /*Stack < int >s;
  s.push (100);
  s.push (200);
  s.push (300);
  s.traverse ();
  cout << "stacksize: " << s.stacksize () << endl;
  s.clearstack ();
  cout << "stack after clear: ";*/

 /* char character;
  Stack < char >s_char;
  cout << "Enter the word: ";
  while ((character = getchar ()) != '\n')
	{
	  s_char.push (character);
	}
  s_char.traverse ();*/

/*Stack<int> stack1;
    stack1.push(1);
    stack1.push(2);
    stack1.push(3);

    Stack<int> stack2;
    stack2.push(1);
    stack2.push(2);
    stack2.push(3);

    if (stack1 == stack2) {
        cout << "are equal ";
    } else {
        cout << "not equal";
    }*/
 
/*Stack<int> s1, s2;
    s1.push(12);
    s1.push(11);
    s1.push(10);
    s2.push(6);
    s2.push(5);
    
    Stack<int> result = s1 + s2;
    cout << "after addition: ";
    result.traverse();*/
    
 
Stack<int> stack1;
    Stack<int> stack2;

    stack1.push(3);
    stack1.push(8);
    stack1.push(1);
    stack1.push(3);
    stack1.push(5);
    stack2.push(6);
    stack2.push(2);
    stack2.push(4);
    stack2.push(3);
    stack2.push(5);

    Stack<int> binarySum = stack1 + stack2;
    
    while (!binarySum.isempty()) {
        cout << binarySum.top() << " ";
        binarySum.pop();
    }

  return 0;
}

        


    
