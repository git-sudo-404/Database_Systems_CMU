#pragma once


#include<string>
#include<vector>
#include<cstdint>
#include<map>

using std::string ;
using std::map ;
using std::vector ;

class HyperLogLog_Presto{

public : 

  explicit HyperLogLog_Presto(uint8_t b) ;

  void addElem(const string &s) ;

  double GetCardinality() ;

  vector<uint8_t> GetDenseBucket() ;  // Returns the dense bucket array

  uint8_t GetOverflowBucketOfIdx(uint32_t idx) ;    // Returns the overflow set of bits for the given index

private : 

  uint8_t b_ ;
  
  uint32_t m_ ;

  double alpha_ ;

  vector<uint8_t> registers_ ;    // Conceptually this is uint4_t

  double ComputeCardinality() ;

  double get_alpha() ;    //  Calculates the HLL Correction constant

  map<uint32_t,uint8_t> overflow_registers_ ;   //  Conceptually it is a map<uint32_t,uint3_t> 
  
  // the value of p can go upto 65 
  //  2^6 = 64 , hence atleast 7-bits are needed to represent 65
  //  
  //  010     1010 
  // |--|    |---| --> registers_
  //  ^
  //  |
  // overflow_registers_

};

