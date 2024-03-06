#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>
#include <algorithm>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m=2, PComparator c = PComparator());

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap();

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const;

    /**
   * @brief Returns size of the heap
   * 
   */
  size_t size() const;

  void trickleDown(size_t idx);

  void trickleUp(int idx);

private:
  /// Add whatever helper functions and data members you need below
  size_t m_;
  std::vector<T> elements;
};

// Add implementation of member functions here

template <typename T, typename PComparator>
Heap<T, PComparator>::Heap(int m, PComparator c) : m_(m) {

}

template <typename T, typename PComparator>
Heap<T, PComparator>::~Heap() {


}

template <typename T, typename PComparator>
void Heap<T, PComparator>::push(const T& item) {
  elements.push_back(item);
  if(size() != 1) {
    trickleUp(size()-1);
  }
}

// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("underflow error");
  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return elements.front();
}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("underflow error");
  }
  if(size() == 1) {
    elements.pop_back();
  }
  else {
    std::swap(elements[0], elements[size()-1]);
    elements.pop_back();
    trickleDown(0);
  }
}

template <typename T, typename PComparator>
bool Heap<T,PComparator>::empty() const {
  if(elements.empty()) {{
    return true;
  }}
  return false;
}

template <typename T, typename PComparator>
size_t Heap<T,PComparator>::size() const {
  return elements.size();
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::trickleDown(size_t idx) {
  size_t bestChild = idx;
  if(idx > (size()/m_)) {      // if idx == leaf node 
    return;
  }
  for(size_t i = 1; i < m_; i++) {
    if(i+idx*m_+1 >= size()) {
      break;
    }
    if(PComparator()(elements[i+idx*m_], elements[i+idx*m_+1])) {     // assuming the child row is full
      if(PComparator()(elements[i+idx*m_], elements[bestChild])) {
        bestChild = i+idx*m_;
      }
    }
    else if(PComparator()(elements[i+idx*m_+1], elements[bestChild])) {
      bestChild = i+idx*m_+1;
    }
  }
  if(size() == 2) {
    if(PComparator()(elements[1], elements[0])) {
      std::swap(elements[1], elements[0]);
    }
    return;
  }
  if(bestChild != idx) {
    std::swap(elements[idx], elements[bestChild]);
    trickleDown(bestChild);
  }
}

template <typename T, typename PComparator>
void Heap<T, PComparator>::trickleUp(int idx) {
  int parent = (idx-1)/m_;
  while(parent >= 0 && PComparator()(elements[idx], elements[parent])) {
    std::swap(elements[parent], elements[idx]);
    idx = parent;
    if(idx-1 >= 0) {
      parent = (idx-1)/m_;
    }
    else {
      return;
    }
  }
}

#endif
