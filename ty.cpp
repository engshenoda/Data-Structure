#include<iostream>
using namespace std;
template<class type> 
class queue{
    private:
    struct node 
    {
        type item ;
        node *next ;
        node *before;
    };
    node *front , *curr_front;
    node *rear , *curr_rear;
    int count;
    public:
    queue();
    type add_Element(type element);
    bool isEmpty();
    void del_Element();
    void clearQueue();
    void get_Rear();
    void get_Front();
    void get_lenght();
    void traveres();
    void reverse();
};
template<class type> queue<type>::queue(){
    front =NULL;
    rear =NULL;
    count =0;
}
template<class type>
bool queue<type>::isEmpty(){return count==0;}

template<class type>
type queue<type>::add_Element(type new_Element){
    node *oldbox ;
    node *newbox ;
    if(isEmpty()){
    oldbox =new node ;
    oldbox->item=new_Element;
    oldbox->next=NULL;
    oldbox->before=NULL;
    front = oldbox;
    rear = front;
    count++;
    }
    else{newbox=new node;
    newbox->item=new_Element;
    newbox->next=NULL;
    newbox->before=oldbox;
    oldbox->next=newbox;
    oldbox=newbox;
    rear=oldbox;
    count++;
   }
   return 0;
}

template<class type>
void queue <type> ::del_Element(){
    node *temp ;
    temp=front;
    front = front->next;
    temp->next=NULL;
    temp->before=NULL;
    delete temp;
    count--;
    //cout<<count;
}
template<class type>
void queue <type> :: clearQueue(){
      node *temp ;
      while (front!=NULL)
      {
        
    temp=front;
    front = front->next;
    temp->next=NULL;
    temp->before=NULL;
    delete temp;
    count--;
  
      }
      count =0;
      rear=NULL;
      front=NULL;
}

template<class type>
void queue <type> :: get_Rear(){cout<<"the element in the rear is : "<<rear->item<<endl;}
template<class type>
void queue <type> :: get_Front(){cout<<"the element in the front is : "<<front->item<<endl;}
template<class type>
void queue <type> :: get_lenght(){cout<<"the number of element in queue : "<<count<<endl;}
template<class type>
void queue <type> ::  traveres(){
    curr_front=front;
    cout<<" [ ";
    while (curr_front!=NULL)
    {
        cout<<curr_front->item<<"  ";
        curr_front=curr_front->next;
    }
    cout<<"] ";
}
template<class type>
void queue <type> :: reverse(){
    curr_rear=rear;
    cout<<" [ ";
     while (curr_rear!=NULL)
    {
        cout<<curr_rear->item<<"  ";
        curr_rear=curr_rear->before;
    }
    cout<<" ] ";
}
int main (){
    queue <int> q;
q.add_Element(9898);

q.add_Element(2);
q.add_Element(3);
q.add_Element(4);
q.add_Element(5);

q.add_Element(243);
q.add_Element(993);
q.get_Rear();
q.get_lenght();
q.get_Front();
q.del_Element();
q.del_Element();
q.traveres();
q.clearQueue();
q.reverse();
q.get_Front();

}