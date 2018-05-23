/**
* @file a2p2.h
*
* @brief 159234 assignment 2 part 2
*		 Implements a simple template container acting as a vector.Supports access, pushback, insert, remove etc operations on this container.
*
* @details 1. The template class MyVector uses an array as a underlying container and implements dynamic storage allocation.
*          2. When specializing the type T in MyVector, the type T should at least have a copy constructor and support assignment operation.
*          3. This container ensures deep copy.
*          4. Bounds checking is performed. Exception "invalid_argument" will be thrown when invalid operations occur.
*          5. References:
*             a. http://en.cppreference.com/w/cpp/container/vector
*             b. http://www.cplusplus.com/reference/vector/vector/
*
* @author Wan Qian ID:17326163
*/

#ifndef A2P2_H
#define A2P2_H
#include<stdexcept>
#include<iostream>
#include<string>

using namespace std;

const unsigned FIRST_BLOCK_SIZE = 1;///< the value when capacity expands from 0 to 1;
const unsigned INCREMENT_FACTOR = 2;///< the factor when capacity expands.

/**
 * Forward declaration of MyVector class
 */
template<typename T>
class MyVector;

/**
 * output each element to a stream
 * @param[out] out the stream where the output is printed to
 * @param[in] vector a MyVector instance.
 * @return an output stream object
 */
template<typename T>
ostream& operator<<(ostream &out, MyVector<T> &vector);

/**
 * Print the student information
 */
void printStudentInfo();

/**
* The template class MyVector acts as a vector.It's implemented with an array as the underlying container.
*/
template<typename T>
class MyVector {
public:
    /**
     * Default constructor, constructs an empty container with specified capacity.The capacity will be 0 by default.
     * @param[in] initialCapacity the initial capacity
     * @throw invalid_argument if initialCapacity<0
     */
    MyVector<T>(int initialCapacity = 0);

    /**
     * Destructor,will release space an instance allocates on the memory.
     */
    ~MyVector<T>();

    /**
     * Copy constructor, constructs the container with the copy of the contents of other.Ensures deep copy
     * @param[in] other another MyVector instance to be copied from.It ensures deep copy.
     */
    MyVector<T>(const MyVector<T> &other);

    /**
     * Move constructor, constructs the container with the contents of other using move semantics.
     * @param[in] other another MyVector to be copied from. After move, it will become an empty vector.
     */
    MyVector<T>(MyVector<T> &&other);

    /**
     * Copy assignment operator, replaces the contents with a copy of the contents of other.Ensures deep copy
     * @param[in] other another MyVector to be copied from.It ensures deep copy.
     */
    MyVector<T>& operator=(const MyVector<T> &other);

    /**
    * Move assignment operator, replaces the contents with a copy of the contents of other using move semantics
    * @param[in] other another MyVector to be copied from. After assigning, it will become an empty vector.
    */
    MyVector<T>& operator=(MyVector<T> &&other);

    /**
    * Returns a reference to the element at specified location index. Bounds checking is performed.
    * @param[in] index the subscript of the requested element in the MyVector
    * @return reference to the requested element.
    * @throw invalid_argument if index<0 or index>=vector's size
    */
    T& operator[](int index);

    /**
     * Gets the current capacity of the MyVector
     * @return the capacity of the currently allocated storage
     */
    int getCapacity() const;

    /**
     * Gets the actual number of elements in the MyVector object
     * @return the size of the vector
     */
    int getSize() const;

    /**
     * Resets a MyVector instance to the initial condition
     */
    void clear();

    /**
     * Appends the given element value to the end of the MyVector
     * @param[in] item the value of the element to append
     */
    void pushBack(const T& item);

    /**
     * Inserts elements at the specified location in the MyVector. Bounds checking is performed.
     * @param[in] item element value to insert
     * @param[in] position the subscript value with which the element to insert.
     * @throw invalid_argument if position < 0 or position > vector's size
     */
    void insert(const T& item, int position);

    /**
     * Removes an item at the given index and return it to the caller. Bounds checking is performed.
     * @param[in] index the subscript of the requested item.
     * @return the requested item to be removed.
     * @throw invalid_argument index<0 or index>=vector's size.If the vector is empty, this exception will also be thrown.
     */
    T remove(int index);

    /**
     * Checks if the MyVector has no element.
     * @return true if the MyVector is empty otherwise false
     */
    bool isEmpty() const;
private:
    int mSize; ///< actual number of elements currently stored in the vector.
    int mCapacity; ///< space of the currently allocated storage
    T * mData; ///< point to a dynamic array

    /**
     * Increase the capacity by a new specified volume for the MyVector.
     * If the newCapacity is greater than current then new storage will be allocated and all current elements will be reserved
     * otherwise the method does nothing.
     * @param[in] newCapacity the requested new space to allocate for MyVector.
     */
    void reserve(int newCapacity);

    /**
     * Checks if a given index is out of access bounds
     * @return true if index < 0 or index >= MyVector's size otherwise false
     */
    bool isOutOfAccessBound(int index);

};

template<typename T>
void MyVector<T>::reserve(int newCapacity) {
    if (newCapacity > mCapacity) {
        T* newArray = new T[newCapacity];
        if (mSize != 0) {
            for (int i = 0; i != mSize; ++i) {
                newArray[i] = mData[i];
            }
        }
        delete[] mData;
        mData = newArray;
        mCapacity = newCapacity;
    }
}

template<typename T>
bool MyVector<T>::isOutOfAccessBound(int index) {
    return index < 0 || index >= mSize;
}

template<typename T>
MyVector<T>::MyVector(int initialCapacity) :mSize(0),mCapacity(0),mData(nullptr) {
    if (initialCapacity < 0) {
        throw invalid_argument("initialCapacity is negative.");
    }
    reserve(initialCapacity);
}

template<typename T>
MyVector<T>::~MyVector() {
    mSize = 0;
    mCapacity = 0;
    delete[] mData;
    mData = nullptr;
}

template<typename T>
MyVector<T>::MyVector(const MyVector<T> &other) :mSize(other.mSize), mCapacity(other.mCapacity) {
    mData = new T[mCapacity];
    for (int i = 0; i != mSize; ++i) {
        mData[i] = other.mData[i];
    }
}

template<typename T>
MyVector<T>::MyVector(MyVector<T> &&other) :mSize(other.mSize), mCapacity(other.mCapacity), mData(other.mData) {
    other.mSize = 0;
    other.mCapacity = 0;
    other.mData = nullptr;
}

template<typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector<T> &other) {
    if (this != &other) {
        mSize = other.mSize;
        mCapacity = other.mCapacity;
        delete[] mData;
        mData = new T[mCapacity];
        for (int i = 0; i != mSize; ++i) {
            mData[i] = other.mData[i];
        }
    }
    return *this;
}

template<typename T>
MyVector<T>& MyVector<T>::operator=(MyVector<T> &&other) {
    if (this != &other) {
        mSize = other.mSize;
        mCapacity = other.mCapacity;
        mData = other.mData;
        other.mSize = 0;
        other.mCapacity = 0;
        other.mData = nullptr;
    }
    return *this;
}

template<typename T>
T& MyVector<T>::operator[](int index) {
    if (isOutOfAccessBound(index)) {
        throw invalid_argument("Index out of bound");
    }
    return mData[index];
}

template<typename T>
int MyVector<T>::getCapacity() const {
    return mCapacity;
}

template<typename T>
int MyVector<T>::getSize() const {
    return mSize;
}

template<typename T>
void MyVector<T>::clear() {
    mSize = 0;
    mCapacity = 0;
    delete[] mData;
    mData = nullptr;
}

template<typename T>
void MyVector<T>::pushBack(const T& item) {
    if (mSize == mCapacity) {
        if (mCapacity == 0) {
            reserve(FIRST_BLOCK_SIZE);
        }
        else {
            reserve(mCapacity*INCREMENT_FACTOR);
        }
    }
    mData[mSize] = item;
    ++mSize;
}

template<typename T>
void MyVector<T>::insert(const T& item, int position) {
    if (position < 0 || position > mSize) {
        throw invalid_argument("Index out of bound");
    }
    pushBack(item);
    int last = mSize - 1;
    for (int i = position; i != last; ++i) {
        T toBeSwap = mData[i];
        mData[i] = mData[last];
        mData[last] = toBeSwap;
    }
}

template<typename T>
T MyVector<T>::remove(int index) {
    if (isOutOfAccessBound(index)) {
        throw invalid_argument("Index out of bound");
    }
    T result = mData[index];
    --mSize;
    for (int i = index; i != mSize; ++i) {
        mData[i] = mData[i + 1];
    }
    return result;
}

template<typename T>
bool MyVector<T>::isEmpty() const {
    return mSize == 0;
}

template<typename T>
ostream& operator<<(ostream& out, MyVector<T> &vector) {
    int size = vector.getSize();
    for (int i = 0; i != size; ++i) {
        out << vector[i] << " ";
    }
    return out;
}

void printStudentInfo() {
    cout << "**************************************************\n* 159.234 Assignment 2 Part 2\n"
        "* Name: Wan Qian\n* ID: 17326163\n**************************************************" << endl;
}
#endif // A2P2_H
