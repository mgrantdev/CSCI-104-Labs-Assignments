## D-ary MinHeap
Suppose we are on index n, the parent's index is (n-1)/d, the children's indeices are dn+1, dn+2, ..., dn+d.
To maintain the heap property, not only swap the priority vector but also the item vector.
In comparisons, even if priority is the same, when alphabetical value is different, still need to swap.

## Node
To do A* Search, I customized a class Node, which has "word" representing the node's word and "curSteps" representing the node's g-value.

## A* Search
Since there is no update and only expand when the distance (g-value) to the current node is the smallest, if a node is popped but its g-value is not the smallest, pop again. To store the smallest g-values, use a map named minG.
The priority is still caculated by (g+h)*(n+1)+h.