//----------------------------------------------------------------------
// Author: Michael Calmette
// File:   hash_table_collection.h
// Implement a hash table 
//
//----------------------------------------------------------------------

 
#ifndef HASH_TABLE_COLLECTION_H
#define HASH_TABLE_COLLECTION_H

#include <vector>
#include <algorithm>
#include <functional>
#include "collection.h"


template<typename K, typename V>
class HashTableCollection : public Collection<K,V>
{
public:

  // create an empty hash table with default number of buckets
  HashTableCollection();

  // hash table copy constructor
  HashTableCollection (const HashTableCollection <K,V>& rhs);

  // hash table assignment operator
  HashTableCollection <K,V>& operator=(const HashTableCollection <K ,V >& rhs);

  // delete a linked list
  ~HashTableCollection();
  
  // add a new key-value pair into the collection 
  void add(const K& a_key, const V& a_val);

  // remove a key-value pair from the collectiona
  void remove(const K& a_key);

  // find and return the value associated with the key
  bool find(const K& search_key, V& the_val) const;

  // find and return the values with keys >= to k1 and <= to k2 
  void find(const K& k1, const K& k2, std::vector<V>& vals) const;
  
  // return all of the keys in the collection 
  void keys(std::vector<K>& all_keys) const;

  // return all of the keys in ascending (sorted) order
  void sort(std::vector<K>& all_keys_sorted) const;

  // return the number of key-value pairs in the collection
  int size() const;

private:

  // helper to empty entire hash table
  void make_empty();
  
  // helper to resize and rehash the hash table
  void resize_and_rehash();
  
  // linked list node structure
  struct Node {
    K key;
    V value;
    Node* next;
  };
  
  // number of k-v pairs in the collection
  int collection_size;

  // number of hash table buckets (default is 16)
  int table_capacity;

  // hash table array load factor (set at 75% for resizing)
  double load_factor_threshold;

  // hash table array
  Node** hash_table;
   
};


// TODO: implement the above functions here ...

template<typename K, typename V>
HashTableCollection<K,V>::HashTableCollection() //constructor
{
    table_capacity = 16;
    collection_size = 0;
    load_factor_threshold = 0.75;
    Node **newTable = new Node*[table_capacity];
    hash_table = newTable;

    for(int i = 0; i < table_capacity; i++)
      hash_table[i] = nullptr;
}

//copy constructor
template<typename K, typename V>
HashTableCollection<K,V>::HashTableCollection(const HashTableCollection <K,V>& rhs)
{
  *this = rhs;
}

//assignment operator
template<typename K, typename V>
HashTableCollection<K,V>& HashTableCollection<K,V>::operator=(const HashTableCollection <K ,V >& rhs)
{
  if(*this == rhs)
    return * this;

  //empty everything and then add everything from the hash table
  make_empty();

  Node* tmp;
  for(int i = 0; i < rhs.table_capacity; i++)
  {
    tmp = rhs.hash_table[i];
    while(tmp != nullptr)
    {
      add(tmp->key,tmp->value);
      tmp = tmp -> next;
    }
  }
  return *this;
}

template<typename K, typename V>  //destructor
HashTableCollection<K,V>::~HashTableCollection()
{
  make_empty();
}

template<typename K, typename V>
void HashTableCollection<K,V>::add(const K& a_key, const V& a_val)
{
   std::hash<K> hash_fun; //K based hash function object
   size_t value = hash_fun(a_key); //get unsigned int based value for key
   size_t index = value % table_capacity; //calculate the index

   //if needs to resize, rehash
   double load_factor = collection_size / table_capacity;
   if(load_factor > load_factor_threshold)
      resize_and_rehash();

   //create a tmp node to hold the key and val
   Node* tmp = new Node;
   tmp -> key = a_key;
   tmp -> value = a_val;

   //add to hash_table
   //either index is empty or has nodes in it
  if(hash_table[index] == nullptr)
  {  
    hash_table[index] = tmp;
    tmp -> next = nullptr;
  } 
  else  //insert from the front
  {
    tmp -> next = hash_table[index];
    hash_table[index] = tmp;
  }
  collection_size++;
}

template<typename K, typename V>
void HashTableCollection<K,V>::remove(const K& a_key)
{
  std::hash<K> hash_fun; //K based hash function object
  size_t value = hash_fun(a_key); //get unsigned int based value for key
  size_t index = value % table_capacity; //calculate the index

  //create a tmp node to hold the key and val
  Node* firstPtr = hash_table[index]; //points to first

  if(hash_table[index] == nullptr)
    return;
  //if node is first in bucket
    if(firstPtr -> key == a_key)
    {
      if(firstPtr -> next = nullptr) //if it is alone
      {
          delete firstPtr;
          hash_table[index] = nullptr;
      }
      else //if there is more nodes in it
      {
          hash_table[index] = firstPtr -> next;
          delete firstPtr;
      }
      collection_size--;
    }
    else //if it isn't the first one
    {
      Node* tmp = hash_table[index] -> next;
      while(tmp != nullptr)
      {
        //if its at the end of the list
        if(tmp -> key == a_key && tmp -> next == nullptr)
        {
          firstPtr -> next = nullptr;
          delete tmp;
          collection_size--;
        }
        //if its somewhere in the middle
        else if(tmp -> key == a_key) 
        {
          firstPtr -> next = tmp -> next;
          delete tmp;
          collection_size--;
        }
        tmp = tmp -> next;
        firstPtr = firstPtr -> next;
      }
    }
 
}

template<typename K, typename V>
bool HashTableCollection<K,V>::find(const K& search_key, V& the_val) const
{
  std::hash<K> hash_fun; //K based hash function object
  size_t value = hash_fun(search_key); //get unsigned int based value for key
  size_t index = value % table_capacity; //calculate the index

  if(hash_table[index] == nullptr) 
      return false;
  else 
  {
    //iterate through index position
    Node* tmp = hash_table[index]; 
    while(tmp != nullptr)
    {
      if(tmp -> key == search_key)
      {
        the_val = tmp -> value;
        return true;
      }
      else
        tmp = tmp -> next;
    }
  }
  return false;
}

template<typename K, typename V>
void HashTableCollection<K,V>::find(const K& k1, const K& k2, std::vector<V>& vals) const
{
  Node* tmp;
  //iterate through table with nested loop
  for(int i = 0; i < table_capacity; i++)
  {
    tmp = hash_table[i];
    while(tmp != nullptr)
    {
      if((tmp->key) >= k1 && (tmp->key) <= k2){
        vals.push_back(tmp->value); //add to vector
      }
      tmp = tmp -> next;
    }
  } 

}

template<typename K, typename V>
void HashTableCollection<K,V>::keys(std::vector<K>& all_keys) const
{
  Node* tmp;
  //iterate through with nested loop
  for(int i = 0; i < table_capacity; i++)
  {
    tmp = hash_table[i];
    while(tmp != nullptr)
    {
      all_keys.push_back(tmp -> key);
      tmp = tmp -> next;
    }
  }
  
}

template<typename K, typename V>
void HashTableCollection<K,V>::sort(std::vector<K>& all_keys_sorted) const
{
  keys(all_keys_sorted);
  std::sort(all_keys_sorted.begin(), all_keys_sorted.end()); 
}

template<typename K, typename V>
int HashTableCollection<K,V>::size() const
{
  return collection_size;
}

template<typename K, typename V>
void HashTableCollection<K,V>::make_empty()
{
  //go through and delete everything
  Node* next;
  for(int i = 0; i < collection_size; i++)
  {
    Node* tmp = hash_table[i];
    while (hash_table[i] != nullptr)
    {
         next = tmp -> next;
         delete tmp;
         tmp = next;
         hash_table[i] = tmp;
    }
  } 
  delete hash_table;
}

template<typename K, typename V>
void HashTableCollection<K,V>::resize_and_rehash()
{
  int new_capacity;
  new_capacity = table_capacity * 2;
  Node** new_table = new Node*[new_capacity];

  for(int i = 0; i < new_capacity; i++)
    new_table[i] = nullptr;

  std::vector <K> c;
  size_t index; 
  keys(c);
  V theVal;

  for(K key:c){
    std::hash<K> hash_fun;
    size_t value = hash_fun(key);
    size_t index = value % table_capacity;

    Node* newNode = new Node;
    bool tmp;
    tmp = find(key, theVal);
    newNode-> key = key;
    newNode -> value = theVal;
    if(new_table[index] == nullptr)
    {
      hash_table[index] = newNode;
      newNode -> next = nullptr;
    }
    else
    {
      newNode -> next = new_table[index];
      new_table[index] = newNode;
    }
  } 
  make_empty();
  table_capacity = new_capacity;
  hash_table = new_table;
}


#endif
