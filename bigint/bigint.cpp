#include "bigint.h"
#include <iostream>
#include <vector>

using namespace std;

BigInt::BigInt(string s){
  for ( int i = s.size() - 1; i >=0 ; i--){
    data_vec.push_back((int)s[i] - 48) ; // read s into data_vec 
  }
}
   // the convert s into an int 
  //for ( int i = 0; i < data_vec.size(); i++){
    //data_vec[i] = (int)(data_vec.push_back[i]) - 48; 
  //}

string BigInt::to_string(){
  string temp; 
  for ( int i = data_vec.size() -1; i >= 0; i--){ 
   temp.push_back((char)(data_vec[i] + 48));
  }
  return temp;
}

void BigInt::add(BigInt b){
  if (data_vec.size() > b.data_vec.size()){
    int sizeA = data_vec.size();
    int sizeB = b.data_vec.size();
    int sizeDiff = sizeA - sizeB; 
    for (int i = 0; i < sizeDiff; i++){
      b.data_vec.push_back(0); 
    }
  }
  else{
    int sizeA = data_vec.size();
    int sizeB = b.data_vec.size();
    int sizeDiff = sizeB - sizeA; 
    for (int i = 0; i < sizeDiff; i++){
      data_vec.push_back(0); 
    }
  }
  
  int carry = 0; 
  for ( int i = 0; i < data_vec.size(); i++){    
    if (data_vec[i] + b.data_vec[i] + carry < 10){
      data_vec[i]= data_vec[i] + b.data_vec[i] + carry;
      carry = 0; 
    }
    else if ((data_vec[i] + b.data_vec[i] + carry) >= 10){
          data_vec[i]= (data_vec[i] + b.data_vec[i] + carry)%10;
      //data_vec.push_back((data_vec[i] + b.data_vec[i])%10); 
          carry = 1; 
      //data_vec.insert(data_vec.begin() + i, 0);
          //data_vec.push_back(data_vec[i+1] + b.data_vec[i+1] + 1);
    }   
  }
  if (carry == 1){
  data_vec.push_back(1);
  }
  
}
  

