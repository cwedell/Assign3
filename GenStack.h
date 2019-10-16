#include <iostream>

using namespace std;

template <class T>
class GenStack {
public:
  GenStack();
  GenStack(int maxSize);
  ~GenStack();

  void push(T d);
  T& pop() throw(runtime_error);
  T& peek() throw(runtime_error);

  bool isFull();
  bool isEmpty();
  int getSize(); // return max size
  int getTop(); // return top location
  void reverse(); // reverse order of stack

private:
  int size;
  int top;

  T *myArray;
};

template <class T>
GenStack<T>::GenStack() {
  myArray = new T[128];
  size = 128;
  top = -1;
}

template <class T>
GenStack<T>::GenStack(int maxSize) {
  myArray = new T[maxSize];
  size = maxSize;
  top = -1;
}

template <class T>
GenStack<T>::~GenStack() {
  delete []myArray;
}

template <class T>
void GenStack<T>::push(T d) {
  if(isFull()) { // double the array size
    T *tempArray;
    tempArray = new T[size * 2];
    for(int i = size - 1; i >= 0; --i) {
      tempArray[i] = myArray[i];
    }
    delete []myArray;
    myArray = tempArray;
    size *= 2;
  }
  myArray[++top] = d;
}

template <class T>
T& GenStack<T>::pop() throw(runtime_error) {
  if(isEmpty()) {
    throw runtime_error("Stack empty");
  } else {
    return myArray[top--];
  }
}

template <class T>
T& GenStack<T>::peek() throw(runtime_error){
  if(isEmpty()) {
    throw runtime_error("Stack empty");
  } else {
    return myArray[top];
  }
}

template <class T>
bool GenStack<T>::isFull() {
  return(top == size - 1);
}

template <class T>
bool GenStack<T>::isEmpty() {
  return(top == -1);
}

template <class T>
int GenStack<T>::getSize() {
  return size;
}

template <class T>
int GenStack<T>::getTop() {
  return top;
}

template <class T>
void GenStack<T>::reverse() {
  if(top > 0) {
    T *tempArray;
    tempArray = new T[size];
    for(int i = 0; i <= top; ++i) {
      tempArray[i] = myArray[top - i];
    }
    delete []myArray;
    myArray = tempArray;
  }
}
