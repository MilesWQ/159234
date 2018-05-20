C++

----

This material is only for personal use.

The contents are sorted and referenced from course slides as well as notes in lectures and tutorials. 

This note will not record every detail which could be referred from public resources,  **it mainly covers the key emphases of the course**.

Use Visual Studio 2017 as a learning environment. Sample code can be compiled with vc++, c++11 standard.

----

Table of Contents
=================

* [C review &amp; C\+\+ basic](#c-review--c-basic)
  * [Static(Stack) memory in C](#staticstack-memory-in-c)
  * [Dynamic(Heap) memory in C](#dynamicheap-memory-in-c)
  * [Enumeration](#enumeration)
  * [Range\-based loop](#range-based-loop)
  * [Input and Output](#input-and-output)
  * [File streams](#file-streams)
* [Strings](#strings)
  * [C style strings vs C\+\+ strings](#c-style-strings-vs-c-strings)
  * [Initialize and assign to strings](#initialize-and-assign-to-strings)
  * [Accessing Strings](#accessing-strings)
  * [String functions](#string-functions)
* [Functions](#functions)
  * [Prototypes and definitions](#prototypes-and-definitions)
  * [inline function](#inline-function)
  * [Function overloading](#function-overloading)
  * [Default parameters](#default-parameters)
  * [References](#references)
* [Memory Management](#memory-management)
  * [Static memory and dynamic memory](#static-memory-and-dynamic-memory)
  * [Scope](#scope)
  * [Namespaces](#namespaces)
  * [Static variables](#static-variables)
* [Introduction to Class](#introduction-to-class)
  * [Structures](#structures)
  * [Class concept](#class-concept)
  * [Encapsulation](#encapsulation)
  * [Static members](#static-members)
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
  * [Arithmetic operators](#arithmetic-operators)
  * [const members](#const-members)
  * [Overloading increment/decrement](#overloading-incrementdecrement)
  * [Overloading comparison operators](#overloading-comparison-operators)
  * [Overloading the subscript operator](#overloading-the-subscript-operator)
  * [friend keyword and overloading operators](#friend-keyword-and-overloading-operators)
  * [Overloading Input &amp; Output operators](#overloading-input--output-operators)
* [Inheritance](#inheritance)
  * [Inheritance vs Composition](#inheritance-vs-composition)
  * [Sample code](#sample-code)
  * [Inherited visibility](#inherited-visibility)
  * [Member overriding](#member-overriding)
  * [Designing with inheritance](#designing-with-inheritance)
  * [Inheritance and Constructors](#inheritance-and-constructors)

----
  
## C review & C++ basic

### Static(Stack) memory in C

Each function can set up its own variables on the stack. Variables set up on the stack typically last only for the duration
of the function that declares them.

### Dynamic(Heap) memory in C

`malloc` allocates bytes of memory and returns a void pointer (void*).

```
int *p = (int*)malloc(10*sizeof(int));
free(p);
```

The memory chunks allocated by `malloc` must be deallocated by `free` after they are no longer use.

### Enumeration

```
enum day{mon, tue, wed, thur, fri, sat, sun};
int main(){
    day today = mon;
}
```

### Range-based loop

Range-based for loops in C++ can be used to iterate through all the elements in an array.

C++11 and onwards support this feature.

```
for(auto i: {0,1,2,3,4}){
    cout<<i<<endl;
}
```

### Input and Output

`cerr` can't write to files.

The extraction operator `>>` discards all whitespace and reads the next data item.

The way data is read is determined by the variable on the right hand side of the operator.

example:

```
int main(){
    int i;
    float f;
    char c;
    cin>>c;  // After input xy, c stores 'x', y is held.
    cin>>i>>f // After input 10.66 99, i stores 10 , f stores 0.66, 99 is held.
}
```

### File streams

ifstream: read data from a file stream to program variables.

ofstream: write data from program variables to a file stream.

```
#include<fstream>
using namespace std;
int main(){
    int i1,i2;
    ifstream fin;
    fin.open("file");
    if(!fin){
        cerr<<"error at opening file"<<endl;
    }
    fin>>i1>>i2;
    fin.close(); // remember to close the stream.
    
    ofstream fout("file2");
    if(!fout){
        cerr<<"error at opening file"<<endl;
    }
    fout<<i1<<i2;
    fout.close();
}
```

check files:
```
ifstream fin("file");
if(!fin.is_open()){
    cerr<<"error at opening file"<<endl;
}
//or
if(!fin){
    cerr<<"error at opening file"<<endl;
}
```

Conclusions on streams:

| #include<iostream> | #include <fstream> | |
| ---- | ---- | ---- |
| cin>>ch | file >> ch | skip whitespace ifstream file |
| cin.get(ch) | file.get(ch) | read  a character ifstream file |
| cin.get(str,40) | file.get(str.40) | read  c-string appends '\0' ifstream file |
| cin.getline(str,40) | file.getline(str,40) | read line into c-string.appends '\0' ifstream file |
| cout<<value | file<<value | write value to output stream. ofstream file |
| cout.put(ch) | file.put(ch) | write out a char. ofstream file |

formatting output uses `<iomanip>`.

----

## Strings

### C style strings vs C++ strings

C style strings: An array of characters terminated by the null character '\0'.

C++ strings: Defined as a type with associated functions in the library.`<string>`

Compare c type strings and C++ String:
1. C++ string is implemented with an ADT in library which is more intuitive to use.
2. C++ string avoid dynamical memory allocation.
3. There are many useful functions and operators.
4. C type strings have pointers behind.It might have a risk at memory leaks or dangling memory.

### Initialize and assign to strings

Initialize sample:

```
int main(){
    string s1("hello");
    string s2(10, 's');
    string name = "John Doe";
}
```

Strings can be assigned to each other directly or using `assign()`. `assign()` can copy the whole string or just a section of it.

Assignment sample:

```
int main() {
    string s1, s2, s3;
    s1 = "hello";
    s2.assign(s1);
    s3.assign(s2, 0, 2); // assign two characters beginning at the subscript 0;
    cout << s1 << " " << s2 << " " << s3 << endl;
}
```

### Accessing Strings 

Accessing individual characters of the string using `[]` or `at()`.

```
int main() {
    string s1 = "foo";
    string s2 = "bar";
    s1[0] = s2.at(2);
}
```

Difference between `[]` and `at()`

1. The `at()` function performs range checking, while `[]` does not.
2. If the parameter index is out of bounds by calling `at()` function, an out_of_range exception will be thrown.

### String functions

refer to library [information](http://www.cplusplus.com/reference/string/string/).

----

## Functions

### Prototypes and definitions

Every function should have its prototype declared before the `main` function and its definition after `main`.

Functions should at least have their prototypes(declarations) set up before they are used.

### `inline` function

A `inline` function requires the compiler to perform substitution rather than a full function call.

A `inline` function is more efficient but need to be simple enough, avoiding loops or recursions.

```
inline int cube(int i){
    return i * i * i;
}
```

### Function overloading

C doesn't support function overloading.

In C++, overloaded functions should have different numbers or types of parameters.

The compiler just determines the matched function by parameter signatures. **The difference only in return type is not function overloading**.

The complier can determine which of the functions should be called based on the type of arguments.

Matching rules of function calling:
1. Exact match.
2. Match by promoting float to double, short to long etc.
3. Match by converting float to int.

### Default parameters

Default parameters can only be set on the tail of the parameter list.

If we want to pass an argument to one of  default parameters, we must provide arguments for all preceding default values.

### References

References can only be initialized.Once a reference has been set to refer to a variable it can not be changed to refer to something else.

## Memory Management

### Static memory and dynamic memory

Statically allocated memory is performed by the system and is determined at compile-time, using declarations and definitions.

Dynamically allocated memory is set at run-time, using predefined operators.

C run-time memory allocation uses `malloc`, it allocates specified bytes of memory and returns a void* pointer.

C dynamic memory management sample:

```
int main(){
    int *p1 = (int*)malloc(sizeof(int));
    int *p2 = (int*)malloc(10*sizeof(int));
    *p1 = 1;
    p2[0] = *p1;
    free(p1); free(p2);
    p1 = NULL; p2 = NULL;
}
```

C++ dynamic memory management sample:

```
int main(){
    int *p1 = new int;
    int *p2 = new int[10];
    
    *p1 = 1;
    p2[0] = *p1;
    delete(p1); delete[](p2);
    p1 = nullptr; p2 = nullptr;
}
```

What are the differences between `malloc`/`free` and `new`/`delete`?
1. `malloc` simply allocates the necessary number of bytes in memory.`New` will allocate memory chunks 
and also call *constructor* for a new object.
2. We have to manually set required size for `malloc` while the compiler will calculate the size for `new`.
3. `new` returns a full typed pointer(type-aware). `malloc` returns a *void pointer which is needed to cast to an appropriate type.
4. `new`/`delete` call the constructors and the destructor of a class while `malloc`/`free` do not.

It's important to ensure to call `new`/`delete` and 'new[]'/`delete[]` in  a matching manner.

What are the differences between `delete` and `delete[]`?
1. The `delete` will free up the memory and call the destructor for a single object.
2. The `delete[]` will deallocate the memory and call destructors for an array of objects.

`delete` is type aware it knows how much memory to be free.

`nullptr` only represents a pointer which can not be implicitly converted  to an integral type.

`nullptr` is a pointer of type `nullptr_t`. If there are two or more overloaded functions that accept a pointer type,an overloaded for `nullptr_t`
should be provided to handle the `nullptr`.

sample:
```
void print(int *p) {cout<<"int* "<<endl;}
void print(nullptr_t nullp) {cout<<"nullptr"<<endl;}
int main(){
    print(nullptr);
}
```

### Scope

The scope resolution operater `::` allows us to access something in the external scope.

The `::` in the below sample just accesses the global scope:

```
int i =0;
int main(){
    int i =1;
    for (int i =2; i<3; ++i){
        cout<<i<<" "<<(::i)<<endl;  //output: 2 0
    }
}
```

### Namespaces

3 manners to import namespaces

```
using namespace std;
//or
using std::cout;
using std::endl;
//or
std::cout<<"foo"<<std::endl;
```

### Static variables

A static local variable is created when the program encounters it and will not be destroyed until the finish of `main` function.

----

## Introduction to Class

### Structures

A `struct` is a definition not a declaration.

Structure variables can be assigned to each other.

Comparison or input/output must be operated with each member individually.

All members in a structure are public. 

operations on struct:
```
struct Room {
	string room_name;
	string purpose;
	int time_limit;
};
int main(){
    Room[10] rooms;
    rooms[0].room_name = "lab1";
    rooms[0].purpose = "teaching";
    rooms[0].time_limit = 120;
    rooms[1] = rooms[0];    //struct assignment
    Room room2 = rooms[1];    //another struct assignment
    if(room[0].room_name == room2.room_name){
        cout<<"identical"<<endl;
    }
}
```

### Class concept

A class is a collection of a fixed number of components -- variable declarations and/or function definitions.

Variables declarations are usually referred to data members.

function definitions are usually called methods.

Information hiding is the basic of encapsulation which is implemented by visibility modifiers -- `public`, `protected`, 'private'.

### Encapsulation

Encapsulation is a mechanism of wrapping the data(variables) and functions acting on these data(methods) together as a single unit.

Encapsulation = Group the data and functionalities + data hiding.

The advantage of  encapsulation is the interior workings of an object are not known to the outside that 
avoid setting the variable to a wrong value accidentally.

The public methods are referred as interfaces of the class. 

Methods should be public if they are part of the interface of the class and private if they are only used as part of the inner workings of the class.

public interface get and set methods are accessors and mutators.

Accessors and mutators have two similarities:
1. In generally ,they're public members.
2. They both have direct access to private members.
 
 Two differences:
 1. Accessors return types of related private members. Mutators have parameters to modify private members.
 2. In most cases, accessors are const methods.The advantage of this setting is that they can work with const object of this defined type.
 Mutators can never be const methods.

Class can contain other classes. This is called composition.

### Static members

Static variables and methods are associated to the class rather than instances.

Static methods can be implemented inline or outside the class declaration.

static member sample
```
class Account{
public:
    Account(float balance);
    float getBalance()const { return balance_;}
    void setBalance(float balance){ balance_ = balance; }
    static float getInterestRate(){ return interest_rate_; }
private:
    static float interest_rate_;
    float balance_;
};
Account::Account(float balance): balance_(balance) {}
float Account::interest_rate_ = 0.05f;      // initialize static member outside the class.
int main(){
    cout<<Account::getInterestRate()<<endl;
}
```

----

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

### Initializer list

To initialize the **const** and **reference** members in a constructor, we must use initializer list.

### `this` pointer

Each instance of a class has its own referential pointer `this`.

`this` pointer has the address of the start of the instance in memory.

### Destructor

Destructors are important to avoid memory leaks when objects use dynamically allocated memory.

Generally,a destructor is only required when a class has pointer members.

The destructor is called automatically for objects allocated on stack goes out of scope or when `delete`
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
to the new object. In the case the original instance has pointer members or use dynamically allocated memory,both the pointers 
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

1. If it's not passed by reference,  the copy constructor will be called in infinite recursion when it needs to copy the object to 
the constructor's parameter.
2. Since copy constructors don't change the values of the original object, we use const to ensure this feature.
 
 ### lvalues & rvalues
 
In general, lvalues can sit on the left side of an assignment while rvalues can not.

An lvalue is an expression that refers to a memory location and allows us to get the address of that memory location 
using the `&` operator.An rvalue is an expression that is not an lvalue.

A copy constructor can be used to take a copy of either an lvalue or an rvalue while move constructor can only be used to copy an rvalue.

If there's no move constructor available, the compiler will use the copy constructor.

We can call `std::move()` explicitly to move the object to an lvalue.

----

## Overloading operators

### Assignment operators

Assignment operator must implement deep copies.

When an object is initialized with another object, the copy constructor is called.

The assignment operator is called when one object is assigned to another exist object.

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

### Arithmetic operators

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

The prefix increment/decrement function returns a reference since the changed object will be used immediately.

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
Returning a reference allows assignment to modify the member of the object.

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

Be aware ambiguous definitions for overloading the same operator. The above sample duplicates the overloading "+" 
as there's already a member overloading "+" with the same functionality. So the compiler will complain.

Also be careful using friend functions as they essentially allow the data hiding and encapsulation of a class to be bypassed.

### Overloading Input & Output operators

`<<` & `>>` must be non-member functions. Since they are members of the class ostream & istream.We can't overload a member of the other class.

Overloading `<<` &`>>` operator sample:
```
class Rational{
    ...
    friend ostream& operator<<(ostream& out, const Rational &rational);
    friend istream& operator>>(istream& in, Rational &rational);
};
ostream& operator<<(ostream& out, const Rational &rational){
    out<<element_[0]<<"/"<<element_[1];
    return out;
}
istream& operator>>(istream& in, Rational &rational){
    in>>rational.element_[0]>>rational.element_[1];
    return in;
}
```

Why return a reference to an ostream?

By returning a reference, the result output can be used as an output stream for another object which has the functionality to 
receive multiple output values.

sample:
```
int main(){
    Rational a(3,4);
    Rational b(4,3);
    cout<<a<<b<<endl;
}
```

The operator `[]`, `()`, `=` and `->` can only be declared as non-static member functions.

pros and cons of overloading operators
+ advantages:
  + Code which uses a class with overloaded operaters can be more compact and intuitive. 
  + The semantics can be both simple and natural.

- disadvantage:
  - It's easy to misunderstand the real meaning of an overloaded operator if the programmer doesn't implement it in natural semantics.
  
## Inheritance
  
### Inheritance vs Composition
Inheritance is used to implement a "is-a" relationship where a class is a kind of the existing classes.
Composition is used to implement a "has-a" relationship where a class has or contains one or more of the existing classes.
  
### Sample code
  
 ```
class Shape {
public:
    Shape(float x = 0.0, float y = 0.0);
    void print();
protected:
    float x_;
    float y_;
};

Shape::Shape(float x, float y) :x_(x), y_(y) {}
void Shape::print() {
    cout << "(" << x_ << "," << y_ << ")" << endl;
}

/**
 * Inherited from base class Shape
 */
class Circle :public Shape {
public:
    Circle(float x = 0.0, float y = 0.0, float r = 0.0);
private:
    float radius_;
};
//Since member visibility of Shape are "protected", derived class can access them directly.
Circle::Circle(float x, float y, float r) :x_(x), y_(y), radius_(r) {}
```

In princple, a publicly derived class inherits access to every member of a base class except:

1. its contructor and its destructor
2. its assignment operator members
3. its frends
4. its private members

### Inherited visibility

The exact rules of visibility are dependent on both the visibility of the member of the class and the type of inheritance used.

*class* derived_class_name :  *type of inheritance* base_class_name
```
class Circle : public Shape{...};
class Circle : protected Shape(...);
class Circle : private Shape{...};
```

If a derived class inherited from a base class:
| Type of Inheritance | Members in base class | In derived class |
| --- | --- | --- |
| public | public / protected / private | public / protected / private |
| protected | public / protected / private | protected / protected / private |
| private | public / protected / private | private / private / private |

### Member overriding

```
class Circle:public Shape{
public:
    void print();
private:
    float radius_;
};

void Circle::print(){
    cout << "(" << x_ << "," << y_ <<"," <<radius_<<")" << endl;
}
```

In the case of inheritance, when the compiler looks for a function, it will initially look in the derived class.
If there's no definition, it will search the base class and so on up to the hierarchy
unitl a definition is found or the end of the hierarchy is reached.

Overriding vs Overloading
Overloading functions have different parameters, overriden functions have exactly the same parameters but are defined in sub-classes.

*You should only override a function if the behaviour actually needs to change.*

### Designing with inheritance

In most cases with object-oriented design, keeping a sensible concept and staying true to the system is more important than a minor performance optimization.

Sometimes we should consider a reasonable relationship between classes.Are they "is-a"(inheritance) or "has-a"(composition) relation?

### Inheritance and Constructors
