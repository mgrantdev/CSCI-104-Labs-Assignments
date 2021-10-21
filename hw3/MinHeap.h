#include <exception>
#include <iostream>
#include <stdexcept>
#include <vector>

template<class T>
class MinHeap {
public:
    MinHeap(int d);
    /* Constructor that builds a d-ary Min Heap
    This should work for any d >= 2,
    but doesn't have to do anything for smaller d.*/

    ~MinHeap();

    void add(T item, int priority);
    /* adds the item to the heap, with the given priority. */

    const T& peek() const;
    /* returns the element with smallest priority.
    Break ties however you wish.
    Throws an exception if the heap is empty. */

    void remove();
    /* removes the element with smallest priority.
    Break ties however you wish.
    Throws an exception if the heap is empty. */

    bool isEmpty() const;
    /* returns true iff there are no elements on the heap. */

private:
    // whatever you need to naturally store things.
    // You may also add helper functions here.
    std::vector<int> a;    // This vector stores all priorities
    std::vector<T> items;  // This vector stores all items
    int d;
    void swap(int pos1, int pos2);  // Swap two elements of a vector
    void bubbleUp(int pos);
    void trickleDown(int pos);
    int findSmallestChildPos(int parentPos);  // Swap the smallest child since MinHeap, so need a helper function to
                                              // find the smallest child
};

template<class T>
MinHeap<T>::MinHeap(int d) {
    this->d = d;
}

template<class T>
MinHeap<T>::~MinHeap() {}  // No destructor needed since no there is no pointer

template<class T>
const T& MinHeap<T>::peek() const {
    if (isEmpty())
        throw std::logic_error(
                "The heap is empty!");  // If the heap is empty, there's nothing on the top, throw an exception
    return items[0];
}

template<class T>
bool MinHeap<T>::isEmpty() const {
    return a.size() == 0;
}

template<class T>
void MinHeap<T>::swap(int pos1, int pos2) {
    // Swap both the priorities vector and the items vector to maintain MinHeap property
    // So that when removing, both use pop_back() = O(1)
    int temp1 = a[pos1];
    a[pos1] = a[pos2];
    a[pos2] = temp1;
    T temp2 = items[pos1];
    items[pos1] = items[pos2];
    items[pos2] = temp2;
}

template<class T>
void MinHeap<T>::bubbleUp(int pos) {
    if (pos > 0 && a[pos] <= a[(pos - 1) / d]) {
        // This is for doublet A*
        // If the priority is the same, we break ties by the smaller item value. So for string it is the smaller
        // alphabetical string If the priority of a node and its parent is the same but actually the parent has lower
        // alphabetical value, there's no need to swap
        if (a[pos] == a[(pos - 1) / d] && !(items[pos] < items[(pos - 1) / d]))
            return;
        swap(pos, (pos - 1) / d);
        bubbleUp((pos - 1) / d);
    }
}

template<class T>
void MinHeap<T>::add(T item, int priority) {
    items.push_back(item);
    a.push_back(priority);
    bubbleUp(a.size() - 1);
}

template<class T>
int MinHeap<T>::findSmallestChildPos(int parentPos) {
    int smallestChildPos = parentPos;
    int smallestPriority = a[smallestChildPos];
    for (int i = 1; i <= d; i++) {
        int childPos = parentPos * d + i;
        if (childPos < a.size() && a[childPos] <= smallestPriority) {
            // If the priority of the current smallest child and another child is the same but the current one has lower
            // alphabetical value Then simply go to the next child to see if it has lower alphabetical value than the
            // current smallest child
            if (a[childPos] == smallestPriority && !(items[childPos] < items[smallestChildPos]))
                continue;
            smallestChildPos = childPos;
            smallestPriority = a[childPos];
        }
    }
    return smallestChildPos;
}

template<class T>
void MinHeap<T>::trickleDown(int pos) {
    int smallestChildPos = findSmallestChildPos(pos);
    if (a[smallestChildPos] <= a[pos]) {
        // If priority of the current position and the smallest child is the same and current position's item has lower
        // alphabetical value
        if (a[smallestChildPos] == a[pos] && !(items[smallestChildPos] < items[pos]))
            return;  // Then there's no need to swap
        swap(smallestChildPos, pos);
        trickleDown(smallestChildPos);
    }
}

template<class T>
void MinHeap<T>::remove() {
    if (isEmpty())
        throw std::logic_error(
                "The heap is empty!");  // If the heap is empty, there's nothing to be removed, throw an exception
    swap(0, a.size() - 1);
    // pop_back() is O(1)
    items.pop_back();
    a.pop_back();
    trickleDown(0);
}