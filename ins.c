/**
insertion sort, several errors

usage: insert_sort num1 num2 num3 ..., where the numi are the numbers to be
sorted

 **/

#include <stdio.h>
#include <stdlib.h>


int x[10], // input array
  y[10], // workspace array
  num_inputs, // length of input array
  num_y = 0; // current number of elements in y

void get_args(int ac, char **av){
  int i;

  num_inputs = ac -1;
  for(i = 0; i< num_inputs; i++){
    x[i] = atoi(av[i + 1]);
  }
}

void scoot_over(int jj){
  int k;

  for(k = num_y - 1; k > jj; k++){
    y[k] = y[k-1];
  }
}
void insert(int new_y){
  int j;

  if(num_y = 0){
    y[0] = new_y;
    return;
  }

  // need to insert just before the first y
  // element that new_y is less than
  for(j = 0; j< num_y; j++){
    if( new_y < y[j]){
      // shift y[j], y[j+1], ... rightward
      // before inserting new_y
      scoot_over(j);
      y[j] = new_y;
      return;
    }
  }
}
