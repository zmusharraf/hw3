#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>

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

private:
  /// Add whatever helper functions and data members you need below
  size_t parent(size_t i) const;
  size_t kthChild(size_t i, int k) const;
  void trickleUp(size_t index);
  void heapifyDown(size_t index);

  int m_;
  PComparator comp_;
  std::vector<T> data_;
};

// Add implementation of member functions here
//constructor
template <typename T, typename PComparator>
Heap<T, PComparator>::Heap(int m, PComparator c) : m_(m), comp_(c), data_()
{
  if(m_ < 2){
    throw std::invalid_argument("Heap arity m must be => 2");
  }
}

//destructor
template <typename T, typename PComparator>
Heap<T, PComparator>::~Heap()
{
}

//push
template <typename T, typename PComparator>
void Heap<T, PComparator>::push(const T& item)
{
  data_.push_back(item);
  trickleUp(data_.size() - 1);
}

//empty
template <typename T, typename PComparator>
bool Heap<T, PComparator>::empty() const{
  return data_.empty();
}

//size
template <typename T, typename PComparator>
size_t Heap<T, PComparator>::size() const
{
  return data_.size();
}


template <typename T, typename PComparator>
size_t Heap<T, PComparator>::parent(size_t i) const
{
  if(i == 0){
    return 0;
  }
  return (i-1)/m_;
}

template <typename T, typename PComparator>
size_t Heap<T, PComparator>::kthChild(size_t i, int k) const
{
  return m_ * i + static_cast<size_t>(k);
}

template <typename T, typename PComparator>
void Heap<T, PComparator>::trickleUp(size_t index)
{
  while(index > 0){
    size_t p = parent(index);
    if(comp_(data_[index], data_[p])){
      std::swap(data_[index], data_[p]);
      index = p;
    } else {
      break;
    }
  }
}

template <typename T, typename PComparator>
void Heap<T, PComparator>::heapifyDown(size_t index){
  size_t n = data_.size();
  while(true){
    size_t best = index;

    for(int k = 1; k <= m_; k++){
      size_t c = kthChild(index, k);
      if(c >= n){
        break;
      }
      if(comp_(data_[c], data_[best])){
        best = c;
      }
    }

    if(best != index){
      std::swap(data_[index], data_[best]);
      index = best;
    } else {
      break;
    }
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
    throw std::underflow_error("Heap::top on empty heap");

  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return data_.front();
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
    throw std::underflow_error("Heap::pop on empty heap");
  }
  data_.front() = data_.back();
  data_.pop_back();
  if(!empty()){
    heapifyDown(0);
  }
}



#endif

