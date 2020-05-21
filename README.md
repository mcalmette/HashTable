# HashTable


## Class Setup
```
cmake CMakeLists.txt
make
```
To use the test file:
```
./hashTest
```

To use the performance test:
```
./hashPerf rand-50k.txt
```

## About this project
Modular hash table using separate chaining with a 75% load factor - once the table reaches the threshold, the hash table will resize and rehash. The seperate chaining uses a linked list, and each new object is inserted to the front. The hash table class also uses these functions:
- add
- remove
- find
- range find
- keys (returns all keys by reference)
- sort (ascending order)
- size


The test file is used as a way to ensure that each function works with different test cases.  The performance file is used to find the speed and number of calls for each function. This can be used with a randomly generated key-value pairs that ranges from 10k pairs to 50k pairs.

Note: Need to have Cmake installed

# 50k items Performance - Test Results
=============

  Add Calls...: 50000
  
  Add Time....: 8842 microseconds
  
  Add Average.: 0.17684 microseconds


  Remove Calls...: 2000
  
  Remove Time....: 48 microseconds
  
  Remove Average.: 0.024 microseconds


  Find Calls...: 2000
  
  Find Time....: 50 microseconds
  
  Find Average.: 0.025 microseconds


  Range Calls...: 1
  
  Range Time....: 850 microseconds
  
  Range Average.: 850 microseconds

  Sort Calls...: 1
  
  Sort Time....: 5235 microseconds
  
  Sort Average.: 5235 microseconds
