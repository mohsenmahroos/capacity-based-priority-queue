# capacity-based-priority-queue

This project introduces priority_que, a capacity-based implementation of the standard template library (STL) container priority_queue.

The c++ class priority_que constructor has a mandatory parameter that specifies that maximum number of values that can be stored in the container at any given instant.

The standared public methods push, pop, top, size and empty of priority_queue are implement in the priority_que class to behave exactly the same as their equivalent methods in priority_queue. 

Internally, priority_que uses a dynamic array of value_type to implement the required functions, with time-complexity O(1) for top() method and O(log N) for push() and pop() methods.

The performance improvement is gained mainly from replacing the std::vector/std::deque container with dynamic array which does not require push_back/pop_back to add/remove item to/from the binary-tree representation of the priority-queue.
