# C++

### Constructor

A *constructor* is a special member function that is called when an object is created.

A *constructor* must have the same name as the class and has no return type.

### Default constructors

If there's no constructor provided for a class, the system will automatically generate a default constructor
which will initialize all data members.

To declare an array of a object, a default constructor is compulsory.

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
2. `malloc` is a function whereas `new` is an operator.
3. We have to manually set required size for `malloc` while the compiler will calculate the size for `new`.
4. `new` returns a full typed pointer(type-aware).`malloc` returns a *void pointer which is needed to cast to an appropriate type.
5. `new`/`delete` call the constructors and the destructor of a class while `malloc`/`free` do not.

What is the difference between `delete` and `delete[]`?
1. The `delete` will free up the memory and call the destructor for a single object.
2. The `delete[]` will deallocate the memory and call destructors for an array of objects.

### Initializer list

To initialize the const and reference members in a constructor, we must use initializer list.

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
to the new object.When the original instance has pointer members or use dynamically allocated memory,the pointers 
in the original one and the copied object point to the same memory chunks.This will cause double delete when
destructors are called when one of the object goes out of the related scope.

How can we solve this problem?

1. Use a reference or a pointer as parameters to avoid copying the object all together.

2. Create a deep copy constructor and assignment operator overloading in the class.

### Copy Constructor & Move Constructor
 
We can ensure a deep copy operation by defining a copy constructor.It will be called automatically whenever one object
is passed by value.

syntax:
```
class Array{
public:
	Array(int size);
	//Copy constructor to ensure a deep copy.
	Array(const Array &array);
	//Move constructor
	Array(Array &&array);
	~Array();
private:
	int size_;
	int *element_;
};

Array::Array(int size):size_(size){
	element_ = new int[size];
}
Array::~Array(){
	delete[] element_;
}

/**
 * This copy constructor can allocate new memory and copy each element to the new array from the original array.
 */
Array::Array(const Array &array){
	size_ = array.size_;
	element_ = new int[size_];
	for(int i =0; i != size_; ++i){
		element_[i] = array.element_[i];
	}
}
/**
 * Move constructor.Deliver the member values to `this` object and clear original member values. 
 */
Array::Array(Array &&array){
	size_ = array.size_;
	element_ = array_.element_;
	array.size_ = 0;
	array.element_ = nullptr;
}
```
 Why must the parameter for a copy constructor be a reference to pointer?
 1. If it's not passed by reference,  the copy constructor will be called in infinite recursion as it needs to copy the object to 
 the constructor's parameter by value.
 2. Since copy constructors don't change the values of the original object, we use const to ensure this feature.
 
 ### lvalues & rvalues
 1. In general, lvalues can sit on the left side of an assignment while rvalues can not.
 2. An lvalue is an expression that refers to a memory location and allows us to get the address of that memory location using the `&` operator.