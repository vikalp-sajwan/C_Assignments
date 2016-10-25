#include <stdio.h>
#include <stdlib.h>

int main() {

	int n, num, i;
	int current_sum, //to save the sum of current sequence
	max_sum; //to save the maximum continuous sum that we have calculated so far
	
	printf("enter the size of array:");
	scanf("%d", &n);
	
	printf("enter array elements:");
	
	//set first element as the max sum so far as well as current sum
	scanf("%d", &num);
	current_sum = max_sum = num;
	
	// to process rest n-1 elements 
	for(i=0; i<n-1; i++){
		scanf("%d", &num);
		
		// if max continuous sum till now is -ve --- means that we have seen only -ve numbers so far
		// and as adding -ve numbers only decreases the sum
		// therefore max_sum will be only one number i.e. -ve number of highest value 
		if(max_sum < 0){
			// if a +ve value comes or a greater -ve number (as -3 is greater than -5)
			// then do following operation
			// else ignore the smaller -ve numbers
			if(num > max_sum)
			max_sum = current_sum = num;
		}
		// if max_sum is greater that or equal to zero -- means that we have seen atleast a 0 or +ve number till now
		else{
			current_sum += num;
			if(max_sum < current_sum)
			max_sum = current_sum;
			
			// if the current_sum goes down to -ve at any point
			// set current_sum to 0 -- means that we start looking for a fresh continuos sequence
			// as we know that we have already seen atlest a 0 and largest sum of continuous elements cannot be -ve
			if(current_sum < 0)
			current_sum = 0;
		}
	}
	
	printf("%d", max_sum);
	return 0;
}
