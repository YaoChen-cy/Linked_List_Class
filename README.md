# Linked_List_Class
This object implements a Linked List Class to manage a doubly linked list.\
A linked list data structure is a collection of elements called nodes. Each element can hold data along with a pointer to the next element. Doubly linked list structures hold two pointers in each element instead of one. The first pointer points to the next element, and the second one points to the previous element in the list.\
The class "Node" having the following data members and methods:
- Int data member to hold the data in each element
- A pointer to Node to hold the pointer to the next element
- A pointer to Node to hold the pointer to the previous element
- A default constructor Node() that initializes the data members appropriately
- A destructor ~Node() that makes sure all dynamically allocated memory was
appropriately deleted (if any)
- A personalized constructor that will create a node and assign its data and pointers
to the given values passed as arguments Node( int data, Node* next, Node* previous )
The class DLLStructure (for Doubly Linked List Structure) having the following data members and methods:
- A pointer to the first element of the list
- A pointer to the last element of the list
- A default constructor that initializes an empty list
- A destructor that makes sure all elements in the list are being destroyed (calling delete operator for each element in the list)
- A personalized constructor that will create a list from an array passed as argument, meaning that the list will have the same number of elements as the array and each element will have its data assigned to the value from the corresponding array element (you may need to pass the array’s size as an argument as well). Make sure to call the new operator to dynamically create a new Node element for each value in the array.
