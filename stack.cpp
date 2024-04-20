#include <iostream>
using namespace std;
template <class T> class stacktype {
private:
  T *list;
  int stacktop;
  int maxstacksize;

public:
  void initializeStack() { stacktop = 0; }

  stacktype(int stacksize) {
    if (stacksize <= 0) {
      cout << "not true";
      maxstacksize = 100;
    } else
      maxstacksize = stacksize;
    list = new T[maxstacksize];
  }

  bool isFullstack() {
    if (stacktop == maxstacksize)
      return true;
    else
      return false;
  }
  void push(T item) {
    if (isFullstack())
      cout << "stack is full on puch";
    else {
      list[stacktop] = item;
      stacktop++;
    }
  }
  bool isEmptystack() {
    if (stacktop == 0)
      return true;
    else
      return false;
  }
  void pop() {
    if (isEmptystack())
      cout << "stack is empty on pop";
    else
      stacktop--;
  }
  int Stacktop() {
    if (isEmptystack())
      return 0;
    else
      return list[stacktop - 1];
  }
  void traverse() {
    for (int i = stacktop - 1; i >= 0; i--) {
      cout << list[i] ;
    }
    cout << endl;
  }
  int stacksize() {
    int count = 0;
    if (isEmptystack())
      cout << "empty";
    else {
      for (int i = stacktop - 1; i >= 0; i--)
        count++;
    }
    return count;
  }
  void clearstack() {
    if (isEmptystack())
      cout << "empty";
    else {
      for (int i = stacktop - 1; i >= 0; i--)
        stacktop--;
    }
    cout << "empty stack";
  }
};

int main() {
 /* stacktype<int> s(90);
  s.initializeStack();
  s.push(5);
  s.push(10);
  s.push(20);
  s.push(30);
  s.traverse();
cout << "stack top" << s.Stacktop()<<endl;
  s.Stacktop();
  s.stacksize();
  cout << "stacksize=" << s.stacksize() << endl;
  s.clearstack();
  cout << "after delete all element in stack" << endl;
  */
char character;
  stacktype<char>s(90);
  cout<<"enter the word: ";
  
  while((character=getchar())!='\n')
  {
      
      s.push(character);
  }
  s.traverse();
  

  return 0;
}





