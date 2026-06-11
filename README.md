# Data Structures and Algorithms

This repository contains C++ implementations of various algorithms and data structures. The primary purpose of this repository is to keep track of my DSA code while solving the **NeetCode 150** questions list.

## Intervals

The `Intervals` folder contains solutions to interval-based problems from the NeetCode 150 list:

*   **Merge Intervals** (`merge_intervals.cpp`): Merging all overlapping intervals.
*   **Non-overlapping Intervals** (`non_overlapping_intervals.cpp`): Finding the minimum number of intervals to remove to make the rest non-overlapping.
*   **Minimum Interval to Include Each Query** (`min_interval_to_include_each_query.cpp`): Finding the smallest interval that contains each query.

## Dynamic Programming

The `Dynamic Programming` folder contains solutions to classic DP problems:

*   **0/1 Knapsack Problem** (`knapsack.cpp`): Maximizing value in a knapsack with weight capacity.
*   **Subset Sum** (`subsetSum.cpp`): Determining if a subset exists with a specific sum.
*   **Equal Sum Partition** (`equalSumPartition.cpp`): Checking if an array can be split into two equal sum subsets.
*   **Count of Subsets** (`CountOfSubset.cpp`): Counting subsets that sum to a target.
*   **Minimum Subset Sum Difference** (`minSubsetDiff.cpp`): Minimizing the difference between two subset sums.
*   **Count of Subsets with Difference** (`CountOfMinSubsetDiff.cpp`): Counting subsets with a specific difference.

### Unbounded Knapsack

*   **Coin Change** (`coinChange2.cpp`): Finding the minimum number of coins required to make a target sum.

Each file includes a `Solution` class with recursive and memoized approaches.