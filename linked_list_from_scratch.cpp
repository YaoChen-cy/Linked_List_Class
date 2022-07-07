# include <iostream>

using namespace std;

//Question 1
//defines a node structor
class Node {
    public:
    //default constructor that initialize the data members
    Node(){
        this->data=0;
        this->next=NULL;
        this->previous=NULL;
    }
    //destructor to make sure that all dynamicakky allocated memory delete
    ~Node(){}
    //personalized constructor that create a node with input data abd pointers
    Node(int data, Node* next, Node* previous){
        this->data=data;
        this->next=next;
        this->previous=previous;
    }
    //data members
    int data; //hold data in each element
    Node* next; //A pointer to N​ode ​to hold the pointer to the ​next e​lement
    Node* previous; //A pointer to N​ode ​to hold the pointer to the ​prev e​lement
};

//Question2
//define the doubly linked structure and behavior
//class declaration
class DLLStructure{
    public:
    DLLStructure();
    DLLStructure(int array[],int size);
    ~DLLStructure();
    void PrintDLL();
    void InsertAfter(int valueToInsertAfter, int valueToBeInserted);
    void InsertBefore( int valueToInsertBefore, int valueToBeInserted);
    void Delete(int value);
    void Sort();
    bool IsEmpty();
    int GetHead();
    int GetTail();
    int GetSize();
    int GetMax();
    int GetMin();
    DLLStructure(DLLStructure& dll);

    private:
    Node* first; //A pointer to the first element of the list
    Node* last; //A pointer to the last element of the list
};

//A default constructor that initializes an empty list
DLLStructure::DLLStructure(){
    this->first=NULL;
    this->last=this->first;
}

//A destructor that delete all elements in the list
DLLStructure::~DLLStructure(){
    Node* current = this->first;
    Node* next = NULL;
    //iterate all element in the list
    while (current!=NULL){
        next = current->next;
        //delete the current element in the list
        delete current;
        //get to the next element
        current = next;
    }
    first = NULL;
    last = NULL;
}

//A personalized constructor that will create a list from input array
DLLStructure::DLLStructure(int array[],int size){
    //initialized two pointers to node to null
    //one for the current node and one for the temporary node
    Node*cur,*temp=NULL;

    //for each element in the list
    for(int i=0;i<size;i++){
        //create a new node
        cur=new Node;
        //assign its data from the corresponding array element
        cur->data=array[i];
        //if this is the first element in the list
        if(i==0){
            // this node is the onlt element in the list for now
            //it's both the first and the last elememnt in the lisdt
            this->first=cur;
            this->last=cur;
            cur->previous=NULL;
            cur->next=NULL;
            temp=cur;
        }
        else{
            //set this node to be the last node of the list
            this->last=cur;
            cur->previous=temp;
            temp->next=cur;
            temp=cur;
        }
        //if this is the last element in the list
        if(i==size-1){
            cur->next=NULL;
        } 
    } 
}

//Question 3
//A method that loop over elements in the list and print their value
void DLLStructure::PrintDLL(){
    Node* current=this->first;
    Node* next = NULL;
    //iterate over the list(from the first node to the second last node)
    while(current!=NULL){
        //print the data of the element to the screen
        if(current->next==NULL){
            break;
        }
        cout<< current->data <<", ";
        next=current->next;
        current=next;
    }
    //print the data of the last node to the screen
    cout<< current->data <<endl;
}
//Question 4
//A method that insert a new element to the list after the first
//occurenece of the value(first input) and having value(second input)
//If valueToInsertAfter was not found in the list,
//add the new value at the end of the list.
void DLLStructure::InsertAfter(int valueToInsertAfter,int valueToBeInserted){
    Node* current=this->first;
    Node* nextNode = NULL;
    Node* temp=NULL;
    //create the node that will insert to the lsit
    Node* newNode=new Node;
    newNode->data=valueToBeInserted;
    //iterate the list
    while(current!=NULL){
        //if the occurenece of the value(first input) was found
        if(current->data==valueToInsertAfter){
            //insert the newnode to the list
            newNode->previous=current;
            newNode->next=current->next;
            current->next= newNode;
            //get out of the loop
            break;
        }
        //get to the next node in the list
        temp=current;
        nextNode=current->next;
        current=nextNode;
    }
    // If valueToInsertAfter was not found in the list
    if(current==NULL){
        //add the new value at the end of the list.
        newNode->previous=temp;
        temp->next=newNode;
        this->last=newNode;
        newNode->next=NULL;
    }
}
//Question 5
//use the mothod InsertAfter to insert a new element tot he list before
//the first occurence of the value(first input) and having value(second input)
//If valueToInsertBefore was not found in the list,
//add the new value at the beginning of the list.
void DLLStructure ::InsertBefore( int valueToInsertBefore, int valueToBeInserted){
    Node* current=this->first;
    Node* nextNode = NULL;
    Node* temp=NULL;
    //create the node that will insert to the lsit
    Node* newNode=new Node;
    newNode->data=valueToBeInserted;
    //iterate the list
    while(current!=NULL){
        //if the valueToInsertBefore was found in the list and 
        // it is not the first element in the list
        if((current->data==valueToInsertBefore)&&(temp!=NULL)){
            // call the method InsertAfter to insert the node
            // with valueToInsertAfter(the value of previous node)
            InsertAfter(temp->data,valueToBeInserted);
            //the node is successfully inserted, get out of the loop
            break;
        }
        //get to the next node in the list
        temp=current;
        nextNode=current->next;
        current=nextNode;
    }
    //if valueToInsertBefore is the value of the first node or
    //it is not found in the list
    if(current==NULL){
        // insert the node to the beginning of the list
        newNode->previous=NULL;
        newNode->next=this->first;
        this->first->previous=newNode;
        this->first=newNode;
    }
}
//Question 6
//delete the first occurence of the value (input)
//if the input value does not in the list,do nothing
void DLLStructure ::Delete(int value){
    Node* current=this->first;
    Node* nextNode = NULL;
    Node* temp=NULL;
    //loop over the list
    while(current!=NULL){
        //if the value was found in the list
        if(current->data==value){
            //delete the node which has the first occurence of the input value
            delete current;
            //if the only node in the list
            if((current->next==NULL)&&(temp==NULL)){
                this->first=NULL;
                this->last=this->first;
            }
            //if the node at the end of the list
            else if(current->next==NULL){
                temp->next=NULL;
                this->last=temp;
            }
            //if the node at the beginning of the list
            else if(temp==NULL){
                current->next->previous=NULL;
                this->first=current->next;
            }
            //if node is neither at the end nor the biginning of the list
            else{
                temp->next=current->next;
                current->next->previous=temp;
            }

            //get out of the list
            break;
        }
        //get to the next node
        temp=current;
        nextNode=current->next;
        current=nextNode;
    }
}
//Question 7
void DLLStructure ::Sort(){
    Node* current=this->first;
    Node* temp=NULL;
    Node* nextNode = NULL;
    //initialize a int which will use to define whether all the element in 
    // the list in increasing order
    int sort=0;
    do{
        sort=0;
        //loop over the list
        while(current->next!=temp){
            //if the value of the current node and the next node not in
            //ascending order
            if(current->data>current->next->data){
                //swap the data of these two node 
                //iterate one more times to check whether all elements in increasing order
                swap(current->data,current->next->data);
                sort=1;
            }
            //get to the next node
            nextNode=current->next;
            current=nextNode;
        }
        //iterate from the begining of the list to one more node away from the last node
        temp=current;
        current=this->first;
        // if all element in ascending order,get out of the loop
    }while(sort);
}
//Question 8
//check whether the list is empty
bool DLLStructure ::IsEmpty(){
    Node* current=this->first;
    //if there is no node in the list, the list is empty,return true
    if(current==NULL){
        return true;
    }
    //there is node in the list, false is returned 
    return false;
}
//Question 9
//return value of the first node
int DLLStructure ::GetHead(){
    return this->first->data;
}
//return value of the last node
int DLLStructure ::GetTail(){
    return this->last->data;
}
//Question 10
//return the number of elements present in the list
int DLLStructure ::GetSize(){
    Node* current=this->first;
    //initialize an int vatiable to store the size of the list
    int size=0;
    //loop over the list
    while(current!=NULL){
        //increase the size by one
        size++;
        //get to the next node
        current=current->next;
    }
    //return the size(the number of elements present in the list)
    return size;
}
//Question 11
int DLLStructure ::GetMax(){
    //initialized a pointer to node indicate the current node
    Node* current=this->first;
    //if the list is empty,send message
    if(current==NULL){
        cout<<"The list is empty"<<endl;
    }
    //set the data value current node as the max of the list 
    int max=current->data;
    //get to the next node in the list
    current=current->next;
    //loop over the list
    while(current!=NULL){
        //if the data value of the current node larger than max
        if(current->data>max){
             //date value of currrent node becomes max
            max=current->data;
        }
        //get to the next node in the list
        current=current->next;
    }
    //return the maximum data value present in the list
    return max;
}
int DLLStructure ::GetMin(){
    //initialized a pointer to node indicate the current node
    Node* current=this->first;
    //if the list is empty,send message
    if(current==NULL){
        cout<<"The list is empty"<<endl;
    }
    //set the data value of current node as the min of the list 
    int min=current->data;
    //get to the next node in the list
    current=current->next;
    //loop over the list
    while(current!=NULL){
        //if the data value of the current node smaller than min
        if(current->data<min){
            //date value of currrent node becomes min
            min=current->data;
        }
        //get to the next node in the list
        current=current->next;
    }
    //return the minimum data value present in the list
    return min;
}
//Question 12
DLLStructure::DLLStructure(DLLStructure& dll){
    //initialized two pointers to node to null
    //one for the current node and one for the temporary node
    Node* current=dll.first;
    Node*cur,*temp=NULL;

    //for each element in the list
    for(int i=0;i<dll.GetSize();i++){
        //create a new node
        cur=new Node;
        //assign its data from the corresponding array element
        cur->data=current->data;
        //if this is the first element in the list
        if(i==0){
            // this node is the only element in the list for now
            //it's both the first and the last elememnt in the list
            this->first=cur;
            this->last=cur;
            cur->previous=NULL;
            cur->next=NULL;
            //update current node as temporary node
            temp=cur;
        }
        //otherwise
        else{
            //set this node to be the last node of the list
            this->last=cur;
            cur->previous=temp;
            temp->next=cur;
            //update current node as temporary node
            temp=cur;
        }
        //if this is the last element in the list
        if(i==dll.GetSize()-1){
            //the next node of current node point to null
            cur->next=NULL;
        } 
        //get to the next node of the list
        current=current->next;
    } 
}

int main(){
    //Q 1,2,3
    int array[5]={11,2,7,22,4};
    DLLStructure dll(array,5);
    dll.PrintDLL();

    //Q 4
    dll.InsertAfter(7,13);
    dll.PrintDLL();
    dll.InsertAfter(25,7);
    dll.PrintDLL();

    //Q 5
    dll.InsertBefore(7,26);
    dll.PrintDLL();
    dll.InsertBefore(19,12);
    dll.PrintDLL();

    //Q 6
    dll.Delete(22);
    dll.PrintDLL();

    //Q 7
    dll.Sort();
    dll.PrintDLL();

    //Q 8
    if (dll.IsEmpty()){cout<<"The list is empty"<<endl;}

    //Q 9
    cout<<"Head element is: "<<dll.GetHead()<<endl;
    cout<<"Tail element is: "<<dll.GetTail()<<endl;

    //Q 10
    cout<<"Number of elements in the list is: "<<dll.GetSize()<<endl;
    //Q 10 theory question
    cout<<"The best implementation of GetSize is creating a int data member for "
    "the size of the list.\nWithin the class DLLStructure, write code like: int size;. "
    "Initialize the size to be 0\nat the default constructor. And modify the size when "
    "add/delete nodes of the list.In this way,\nwe can directly return the size of "
    "of the list, by write code like: this->size; ,\navoid looping over the "
    "elements of the list each time the GetSize method gets called."<<endl;

    //Q 11
    cout<<"Max element is: "<<dll.GetMax()<<endl;
    cout<<"Min element is: "<<dll.GetMin()<<endl;
    //Q 11 theory question
    cout<<"The best implementation of GetMax and GetMin is creating two int data "
    "member for the maximum\nand minimum data values present in the list. Within "
    "the class DLLStructure, write\ncode like: int max; and int min;. Initialize "
    "the size to be 0 at the default constructor.\nAnd modify the max and min when "
    "add/delete nodes of the list. In this way, we can\ndirectly return the max or "
    "min data value in the list, by write code like: this->max;,\navoid looping over "
    "the elements of the list each time the GetMax or\nGetMin method gets called."<<endl;
    
    //Q 12 theory question
    cout<<"The default compy constructor that is provide by the compiler will copy the "
    "elements of a list with\naddress of dynamically allocated memory as we initialize "
    "the list dynamically at run time.\nIt won't make a real copy of that memory. "
    "Becuase the list and the copied list currently points\nto the same memory. If the "
    "data value of an element of one of the list get change, another list will\nbe change at "
    "the same time. And if an element of a list is deleted, it may cause memory\nleak as "
    "the pointer of thta element of another list will still point to that memory.\n"
    "Therefore, the default copy constructor is not reliable."<<endl;
    //Q 12
    DLLStructure dll2(dll);
    dll2.PrintDLL();
    return 0;
}
