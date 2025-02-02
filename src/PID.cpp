#include "PID.h"
#include<iostream>
#include<limits>

using namespace std;


/**
 * TODO: Complete the PID class. You may add any additional desired functions.
 */

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
  /**
   * TODO: Initialize PID coefficients (and errors, if needed)
   */
  parameter.push_back(Kp);
  parameter.push_back(Ki);
  parameter.push_back(Kd);  
  p_error = i_error = d_error = 0;
  
  //twiddle parameters
  need_twiddle = false;
  
  step = 1;
  //let the car run at first 100 steps,then in the next 2000 steps add the cte^2 to the total_error
  val_step = 100;
  test_step = 2000;
  
  for(int i= 0; i<3;++i){
    //init the change rate with the value of 0.1*parameter
    changes.push_back(0.1*parameter[i]);
  }
  index_param = 0;
  best_error = std::numeric_limits<double>::max();
  total_error = 0;
  
  //fail to make the total_error better times
  fail_counter = 0;
 
}

void PID::UpdateError(double cte) {
  /**
   * TODO: Update PID errors based on cte.
   */
  if(step ==1){
  p_error = cte;
 
  }
  
  d_error =cte - p_error;
  p_error = cte;
  i_error +=cte;
  
  if(need_twiddle){
    if(step % (val_step + test_step) > val_step){
      total_error +=(cte*cte);
    }
    
    if(step % (val_step + test_step)== 0){
    
      if(step == (val_step + test_step)){
        if(total_error < best_error){
        best_error = total_error;
        }
        parameter[index_param] += changes[index_param];
      }
      else{
        if(total_error < best_error){
          best_error = total_error;
          changes[index_param] *=1.1;
          IndexMove();
          parameter[index_param] += changes[index_param];
          fail_counter = 0;
        }
        else if(fail_counter == 0){
          parameter[index_param] -= (2*changes[index_param]);
          fail_counter++;
        }
        else{
          parameter[index_param] += changes[index_param];
          changes[index_param] *=0.9;
          IndexMove();
          parameter[index_param] += changes[index_param];
          fail_counter = 0;
        }
      }
      total_error = 0;
    }
  }
  step++;
}


double PID::TotalError() {
  /**
   * TODO: Calculate and return the total error
   */
  
  total_error =  - parameter[0] * p_error - parameter[1] * i_error - parameter[2] * d_error;
  return total_error;  // TODO: Add your total error calc here!
}

void PID::IndexMove(){
  index_param ++;
  if(index_param >=3){
    index_param =0;
  }
}