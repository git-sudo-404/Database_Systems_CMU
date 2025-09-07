#include "hyperloglog_presto.h"
#include "../murmurhash/MurmurHash3.h"

#include<bitset>
#include<cmath>
#include<algorithm>

using std::string ;
using std::map ;
using std::vector ;

const int DENSE_BITS = 4 ;
const int DENSE_MASK = (1 << DENSE_BITS) - 1 ;

HyperLogLog_Presto::HyperLogLog_Presto(uint8_t b){

  this->b_ = b ;

  this->m_ = 1 << b ;

  this->registers_.resize(m_,0) ;

  this->alpha_ = get_alpha() ;

}


void HyperLogLog_Presto::addElem(const string &s){

  uint64_t hash_val ;
  
  MurmurHash3_x64_128(s.c_str(),s.length(),0,&hash_val) ;

  uint32_t bucket_ind = hash_val >> (64 - b_) ;

  uint64_t rem_bits = hash_val & ( (1ULL << (64 - b_)) - 1 );

  uint8_t zeroes;

  if(rem_bits==0)
    zeroes = 64 - b_ ;
  else 
    zeroes = __builtin_ctzll(rem_bits) ;

  uint8_t p = zeroes + 1 ;
  
  // Retrieving the previously stored val
  uint8_t current_dense = registers_[bucket_ind] ;
  uint8_t current_overflow = GetOverflowBucketOfIdx(bucket_ind) ;
  uint8_t current_p = (current_overflow << DENSE_BITS) | current_dense ;

  if(p>current_p){
    
    // Split p into DENSE BITS and Overflow bits 

    uint8_t new_dense = p & DENSE_MASK ;
    uint8_t new_overflow = p >> DENSE_BITS ;

    registers_[bucket_ind] = new_dense ;

    if(new_overflow>0){
      overflow_registers_[bucket_ind] = new_overflow ;
    } else {
      // if there's no overflow then just save space (conceptually!)
      overflow_registers_.erase(bucket_ind) ;
    }


  }

}


double HyperLogLog_Presto::GetCardinality(){
  return ComputeCardinality();
}


double HyperLogLog_Presto::ComputeCardinality(){

  // Step - 1 : Calculate the sum of exponents as per the formula.

  double sum_exp = 0.0 ;
  for(uint8_t j = 0;j<m_;j++){
    // Reconstruct the p from DENSE_BITS and OVERFLOW_BITS 
    uint8_t dense_val = registers_[j];
    uint8_t overflow_val = GetOverflowBucketOfIdx(j);
    uint8_t p_j = (overflow_val << DENSE_BITS) | dense_val ;
    
    sum_exp += std::pow(2.0,-static_cast<double>(p_j)) ;

  }
  
  // Step - 2 : Determine the cardinality using the raw HLL formula 

  double estimate = alpha_ * m_ * m_ / sum_exp ;

  return std::floor(estimate) ;

}


double HyperLogLog_Presto::get_alpha() {
    switch (m_) {
        case 16:
            return 0.673;
        case 32:
            return 0.697;
        case 64:
            return 0.709;
        default:
            return 0.7213 / (1.0 + 1.079 / m_);
    }
}

// --- Implementation of Grading Functions ---

vector<uint8_t> HyperLogLog_Presto::GetDenseBucket() {
    return registers_;
}

uint8_t HyperLogLog_Presto::GetOverflowBucketOfIdx(uint32_t idx) {
    // .count() checks for key existence. If it exists, return the value, otherwise 0.
    if (overflow_registers_.count(idx)) {
        return overflow_registers_.at(idx);
    }
    return 0;
}
