C++

Table of Contents
=================

* [Constructors &amp; Destructors](#constructors--destructors)
  * [Constructor &amp; Default constructors](#constructor--default-constructors)
  * [Create objects on stack and heap](#create-objects-on-stack-and-heap)
  * [malloc/free and new/delete](#mallocfree-and-newdelete)
  * [Initializer list](#initializer-list)
  * [this pointer](#this-pointer)
  * [Destructor](#destructor)
  * [Constructors &amp; Destructors](#constructors--destructors-1)
  * [Copying objects](#copying-objects)
  * [Copy Constructor &amp; Move Constructor](#copy-constructor--move-constructor)
  * [lvalues &amp; rvalues](#lvalues--rvalues)
* [Overloading operators](#overloading-operators)
  * [Assignment operators](#assignment-operators)
  * [Arithmetic Operators](#arithmetic-operators)
  * [const members](#const-members)
  * [Overloading increment/decrement](#overloading-incrementdecrement)
  * [Overloading comparison operators](#overloading-comparison-operators)
  * [Overloading the subscript operator](#overloading-the-subscript-operator)
  * [friend keyword and overloading operators](#friend-keyword-and-overloading-operators)
  * [Overloading Input &amp; Output operators](#overloading-input--output-operators)

## Constructors & Destructors

### Constructor & Default constructors

A *constructor* is a special member function that is called when an object is created.

A *constructor* must have the same name as the class and has no return type.

If there's no constructor provided for a class, the system will automatically generate a default constructor
which will initialize all data members.

To declare an array of an object, a default constructor is compulsory.

```
class Rational{
public:
	Rational(int n = 0,int d = 1);//this acts as a default constructor
private:
	int numerator_;
	int denominator_;
}
Rational::Rational(int n,int d): numerator_(n), denominator_(d) { }
```

### Create objects on stack and heap

Create objects on stack:
```
List list;
Student student(1234,"John Doe");
```

Create objects on heap:
```
List *list = new List();
Student *student = new Student(2234,"Jane Doe");
```
### `malloc`/`free` and `new`/`delete`

syntax:
```
class Foo{
//anything...
};

int main(){
	Foo foo1("something");
	
	Foo *foo2 = new Foo("bar");
	delete foo;
	
	Foo *foo3 = (Foo*)malloc(sizeof(Foo));
}
```

What are the differences between `malloc`/`free` and `new`/`delete`?
1. `malloc` simply allocates the necessary number of bytes in memory.`New` will allocate memory chunks 
and also call *constructor* for a new object.
2. We have to manually set required size for `malloc` while the compiler will calculate the size for `new`.
3. `new` returns a full typed pointer(type-aware).`malloc` returns a *void pointer which is needed to cast to an appropriate type.
4. `new`/`delete` call the constructors and the destructor of a class while `malloc`/`free` do not.

What are the differences between `delete` and `delete[]`?
1. The `delete` will free up the memory and call the destructor for a single object.
2. The `delete[]` will deallocate the memory and call destructors for an array of objects.

### Initializer list

To initialize the **const** and **reference** members in a constructor, we must use initializer list.

### `this` pointer

Each instance of a class has its own referential pointer `this`.

`this` pointer has the address of the start of the instance in memory.

### Destructor

1. Destructors are important to avoid memory leaks when objects use dynamically allocated memory.
2. Generally,a destructor is only required when a class has pointer members.
3. The destructor is called automatically for objects allocated on stack goes out of scope or when `delete`
is called for dynamically allocated objects.

### Constructors & Destructors

| Object Defined | Constructor called | Destructor called |
| -------------- | ------------------ | ----------------- |
| Global Scope | Before any function | When `main` terminates|
| local Scope | When object enters scope | When object leaves scope |
| Static Local Scope | When scope is entered for first time | When `main` terminates |
| Dynamic | When `new` is called | When `delete` is called |

### Copying objects

Why shallow copy would cause problem?

When an object is passed by value each member values of that object will be copied directly 
to the new object. In the case the original instance has pointer members or use dynamically allocated memory,the pointers 
in the original one and the copied object point to the same memory chunks.This will cause double delete when
destructors are called when one of the object goes out of the related scope.

How can we solve this problem?

1. Use a reference or a pointer as the parameter to avoid copying the object all together.

2. Create a deep copy constructor and assignment operator overloading in the class.

### Copy Constructor & Move Constructor
 
We can ensure a deep copy operation by defining a copy constructor. It will be called automatically whenever one object
is passed by value.

syntax:
```
class List{
public:
	List();
	//Copy constructor to ensure a deep copy.
	List(const List &list);
	//Move constructor
	List(List &&list);
	void AddtoFront(int number);
	~List();
private:
	struct Node{
		int data;
		Node *next;
	};
	Node *front_ptr_;
};
List::List(): front_ptr_(nullptr){ }
List::~List(){
	Node *prev_node = nullptr;
	while(front_ptr_ != nullptr){
		prev_node = front_ptr_;
		front_ptr_ = front_ptr_ -> next;
		delete prev_node;
		prev_node = nullptr;
	}
}
/**
 * This copy constructor can create new nodes and copy 
 * each element to the new list from the original list.
 */
List::List(const List &list):{
	Node *to_be_add = list.front_ptr_;
	while(to_be_add != nullptr){
			AddtoFront(to_be_add->data); // implemented allocating new memory for a new node.
			to_be_add = to_be_add -> next;
	}
}
/**
 * Move constructor.Deliver the member values to "this" object 
 * and clear original member values. 
 */
List::List(List &&list){
	front_ptr_ = list.front_ptr_;
	list.front_ptr_ = nullptr;
}
void List::AddtoFront(int number){
	Node *new_node = new Node;
	new_node->data = number;
	new_node->next = front_ptr_;
	front_ptr_ = new_node;
}
```
Why must the parameter for a copy constructor be a reference to pointer?

1. If it's not passed by reference,  the copy constructor will be called in infinite recursion as it needs to copy the object to 
the constructor's parameter by value.
2. Since copy constructors don't change the values of the original object, we use const to ensure this feature.
 
 ### lvalues & rvalues
 
1. In general, lvalues can sit on the left side of an assignment while rvalues can not.
2. An lvalue is an expression that refers to a memory location and allows us to get the address of that memory location 
using the `&` operator.An rvalue is an expression that is not an lvalue.
3. A copy constructor can be used to take a copy of either an lvalue or an rvalue while move constructor can only be used to copy an rvalue.
4. If there's no move constructor available, the compiler will use the copy constructor.
5. We can call `std::move()` explicitly to move the object to an lvalue.

## Overloading operators

### Assignment operators

Assignment operator must implement deep copies.

When an object is initialized with another object, the copy constructor is called.The assignment operator is called when one object is 
assigned to another exist object.

sample syntax continuing with the previous List context:
```
class List{
public:
	...
	//Overloading assignment operator
	List& operator=(const List &rhs);
	//move assignment operator
	List& operator=(List &&rhs);
	...
private:
	...
};
List& List::operator=(const List &rhs){
	if(this != &rhs){   // avoid self assignment
		this->~List();   // Manually call the destructor to free up memory the current object occupied
		Node *to_be_add = rhs.front_ptr_;
		while(to_be_add != nullptr){
			AddtoFront(to_be_add->data);
			to_be_add = to_be_add->next;
		}
	}
	return *this;
}
List& List::operator=(List &&rhs){
	if(this != &rhs){
		this-> ~List();
		front_ptr_ = rhs.front_ptr_;
		rhs.front_ptr_ = nullptr;
	}
	return *this;
}
```

### Arithmetic Operators

General implementation:

```
class Rational{
public:
	Rational(int n =0,int d = 1);
	~Rational();
	Rational(const Rational &rational);
    Rational(Rational &&rational);
	Rational& operator=(const Rational & rhs);
	Rational& operator=(Rational &&rhs);
	//Overloading operator addition
	Rational operator+(const Rational &rhs) const;
	Rational& operator+=(const Rational &rhs);
private:
	int *element_;
}
Rational::Rational(int n, int d){
	element_ = new int[2];
	element_[0] = n;
	element_[1] = d;
 }
 Rational::~Rational(){
	delete[] element_;
 }
 Rational::Rational(const Rational &rational) {
    element_ = new int[2];
    element_[0] = rational.element_[0];
    element_[1] = rational.element_[1];
}
Rational::Rational(Rational &&rational) {
    element_ = rational.element_;
    rational.element_ = nullptr;
}
Rational& Rational::operator=(const Rational &rhs){
	if(this!=&rhs){
		delete[] element_;
		element_ = new int[2];
		element_[0] = rhs.element_[0];
		element_[1] = rhs.element_[1];
	}
	return *this;
}
Rational& Rational::operator=(Rational &&rhs){
	if(this != &rhs){
		delete[] element_;
		element_ = rhs.element_;
		rhs.element_ = nullptr;
	}
	return *this;
}
Rational Rational::operator+(const Rational &rhs) const{
	int result_n = element_[0] * rhs.element_[1] + rhs.element_[0]*element_[1];
	int result_d = element_[1]*rhs.element_[1];
	return Rational(result_n,result_d);
}
Rational& Rational::operator+=(const Rational &rhs){
	element_[0] = element_[0] * rhs.element_[1] + rhs.element_[0] * element_[1];
	element_[1] *= rhs.element_[1];
	return *this;
}
```
If we have implemented overloading operator "+=" then, "+" can be implemented as follow:
```
Rational Rational::operator+(const Rational& rhs){
	Rational result(*this);
	result += rhs;
	return result;
}
``` 

### `const` members

`const` should be added on both in the class declaration and the associate function definition outside the class
if the member guarantees it will not revise the object.

Overloading can be done on `const` members.

For `const` object, it only can invoke `const` member functions.

*Make any member function `const` if it does not modify the state of the instance.*

### Overloading increment/decrement

General implementations continuing with the previous Rational class:
```
class Rational{
	...
	//prefix
	Rational& operator++();
	//postfix
	Rational operator++(int);
}
Rational& Rational::operator++(){
	*this+=1;
	return *this;
}
Rational Rational::operator++(int){
	Rational result(*this);
	*this+=1;
	return result;
}
```

The prefix increment/decrement function returns a reference since it change the changed object will be used immediately.

The postfix increment/decrement function returns an new object which is copied from the current object. And the changed object
will be used in the next steps. 

### Overloading comparison operators

Sample implementations continuing with the previous Rational class:
```
bool Rational::operator==(const Rational& rational) const{
	if(element_[0] == rational.element_[0] && element_[1] == rational.element_[1]){
		return true;
	}
	return false;
}
```

### Overloading the subscript operator

Sample implementations continuing with the previous Rational class:
```
int& Rational::operator[](int i){
	if(i>=0 && i<2) return element_[i];
	return element_[0]; //if the index exceeds the object defined return the first element.
}
```

Why return a reference?
Returning a reference allows assignment.

An overloading declaration for const object use:
```
const int& Rational::operator[](int i) const;	
```

### `friend` keyword and overloading operators

When we define an overloading operator function in global scope and it needs access to private members,
the `friend` keyword could be used.

```
class Rational{
	...
	friend Rational operator+(const Rational &lhs,const Rational &rhs);
};
Rational operator+(const Rational &lhs,const Rational &rhs){
	int n = lhs.element_[0] * rhs.element_[1] + rhs.element_[0] * lhs.element_[1];
    int d = lhs.element_[1] * rhs.element_[1];
    return Rational(n, d);
}	
```

Be aware of ambiguous definitions for overloading the same operator. The above sample duplicates the overloading "+" 
as there's already a member with the same functionality. So the compiler will complain.

### Overloading Input & Output operators

`<<` & `>>` must be non-member functions. Since they are members of the class ostream and  