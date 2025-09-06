// holds only the declarations of the HyperLogLog class and its methods.
// .h files -> menu .cpp files -> kitchen

#pragma once // include this header file only once

// #ifndef HYPERLOGLOG_H
// #define HYPERLOGLOG_H
// #endif

#include<string>
#include<vector>
#include<cstdint> // for including fixed - width integers like uint8_t , uint32_t 
 

class HyperLogLog {

public : 
  
  // constructor
  explicit HyperLogLog(uint8_t b);
  //          without explicit          |  with explicit 
  //       HyperLogLog hll = 10 --- ✅  |  HyperLogLog hll = 10 --- ❌
  //       HyperLogLog hll(10)  --- ✅  |  HyperLogLog hll(10)  --- ✅ 
  
  void addElement(const string &s); // add element to HyperLogLog
  // const meaning the function is not allowed to change the string

  double getCardinality(); // returns the estimated number of unique elements , floored to the nearest integer 

private : 

  uint8_t b_ ; // the number of bits used for register index , b .
  // the first b bits of the hash for the index in the buckets_

  uint32_t m_ ; // the number of registers , m = 2^b .
  // number of buckets_

  vector<uint8_t>registers_; // these are the buckets 

  double Compute_Cardinality(); // calculates and returns the final estimate in double  

}



