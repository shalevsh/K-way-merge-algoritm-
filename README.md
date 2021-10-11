# K-way-merge-algorithm
Implementation of K-way merge algorithm by Heap.

In this project i implemented an additional algorithm for k-way merge sort
This algorithm is a generalization of the merge sort algorithm.

Algorithm description:
Stop conditions: If the given array size is smaller than k, sort the array members using QuickSort.
Other:
1. Divide the members of the array into k sub-arrays.
2. Sort each array (recursive).
3. Merge the sorted arrays into one sorted array.
Note: For 2 = k we get the sort merge algorithm.
In order for the merger process to be as efficient as possible (note that the efficiency of the algorithm also depends on parameter k) i used heap.
