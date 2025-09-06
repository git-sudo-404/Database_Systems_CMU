
#include "hyperloglog.h"
#include "../murmurhash/MurmurHash3.h"

#include<algorithm> // for max 
#include<bitset> // for handling 64 - bit hash as a sequence of bits 
#include<cmath> // for std::pow and std::floor


// Constructor Implementation of hyperloglog 

HyperLogLog::HyperLogLog(uint8_t b){
  
  this->b_ = b ;

  this->m_ = 1 << b_ ;

  this->registers_.resize(m_,0) ;

}


// Add Element 

void HyperLogLog::addElement(const std::string &s){

  // Step - 1 : Calculate the 64 - bit hash of the input string 
  
  uint64_t hash_val ;
  MurmurHash3_x64_128(s.c_str(),s.length(),0,&hash_val) ; 
  
  // .c_str() --> returns a pointer to the null terminated character array ( a classic c - style string ) , which is the format the hash function requires

  
  // Step - 2 : Get the registers_ index (or) the Bucket index ( the first b bits )
  
  uint32_t register_ind = hash_val >> (64 - b_) ;


  // Step - 3 : Find the position of the leftmost 1 in the remaining mask 

  // 3 - i ) Create a bitmask leaving the top b bits , having the reamaining (64 - b) bits 
  uint64_t rem_bits_mask = (1ULL << (64 - b_)) - 1 ;
  uint64_t rem_bits = rem_bits_mask & hash_val ;

  uint8_t p = 0 ;

  // __builtin_clzll() -- count leading 0's in a long long 

  if(rem_bits == 0){

    p = (64 - b_) + 1 ;  // the whole rem_bits has 0's --> has a run of (64 - b) + 1 .

  } else {

    p = __builtin_clzll(rem_bits) - b_ + 1 ;   // we are subracting b_ , since the first b_ bits are bucket indices are not to be considered for the runs 

  }

  registers_[register_ind] = std::max(registers_[register_ind] , p) ;    // update with the maximum runs in the bucket
 
  // 01010000000011011...0
  // 0101 0000  000011011....0 
  //|--------| |____| 
  //  8-bits   4-runs 


}

double HyperLogLog::getCardinality(){

  return std::floor(Compute_Cardinality());

}


double HyperLogLog::Compute_Cardinality(){


  // Step - 1 : Calculate the sum part of the formula: Σ(2^(-R[j])).

  double sum = 0.0 ;    // sum = 1 / 2^-m[j] ; j = 1,2,...,n 
  
  for(uint8_t register_val : registers_){

    sum += std::pow(2.0, -static_cast<double>(register_val)) ;

  }

  // Step - 2 : Calculate the alpha constant for bias correction (standard for HLL).

  double alpha;
  if (m_ == 16) {
      alpha = 0.673;
  } else if (m_ == 32) {
      alpha = 0.697;
  } else if (m_ == 64) {
      alpha = 0.709;
  } else {
      alpha = 0.7213 / (1.0 + 1.079 / m_);
  }

  // Step - 3 : Calc the raw estimate use HLL formulae
  double estimate = alpha * m_ * m_ / sum ; 
  
  return estimate ;

}


