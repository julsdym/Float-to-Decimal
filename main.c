#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

/**
 * converting a half-precision floating using an IEEE754 representation
 * to its decimal equivalent while accounting for
 * normalized, denormalized, and special cases.
 * +-+-----+----------+
 * |S|EEEEE|FFFFFFFFFF| <- representation of a half precision float 
 * +-+-----+----------+
 * 
 * example input:
 * ./floattoIEEE754 001110000000000000
 * output:
 * 0.50000000
 *
 */
#ifndef EXP
    #define EXP 5
#endif

#ifndef FRAC
    #define FRAC 10
#endif

float halftodec(long i){
	int mantissa = (i >> 15) & 1;
	unsigned int exponent = (i>>10) & 0x1F;
	unsigned int fraction= i & 0x3FF;
	
	//special, normal, denormalized cases
	if(exponent ==0&& fraction ==0) return 0.00000000;
	
	if(exponent== 31&&fraction== 0 &&mantissa==1) return 23;
	if(exponent==31&&fraction==0 &&mantissa ==0) return 12345;
	//need another case for positive infinity
	if(exponent==31 &&fraction!=0 ) return 54321;
	
	float valn = 1;
	if(mantissa ==1) valn = -1;
	float expval = 1;
	int five = 5;
	//converting positive numbers to decimal
	if (exponent ==0) {
	return (valn * powf(2, -14) *(fraction / 1024.0f));
	}
	
	float value = 1;
	if(mantissa ==1) value = -1;
	float fractionval = 1;
	int nine = 9;
	one:
	if(nine <0) {
	value *= fractionval*(1<<(exponent-15));
	return value;
	}
	if(fraction &(1 << nine)){
	fractionval +=( 1.0 /(1 << (10-nine)));
	}
	nine--;
	goto one;
	
	
}


int main(int argc, char** argv){
	if(argc != 2){
	printf("insert IEEE754 string with length >= 16\n");
	return EXIT_FAILURE;
	}
	
	char* number = argv[1];
	int test = 0;
	
	xx:
	if(number[test] == NULL) goto nums;
	if(number[test] != '0' && number[test] != '1'){
	printf("invalid binary format\n");
		return EXIT_FAILURE;
	}
	test++;
	goto xx;
	
	nums:
	
	int length = strlen(argv[1]);
	
	if(length!= 16){
		printf("insert IEEE754 string with length >= 16\n");
		return EXIT_FAILURE;
	}
	long p = strtol((argv[1]), NULL, 2);
	float dec = halftodec(p);
	if (dec == 12345){
		printf("+infinity\n");
		goto end;
	}
	
	if (dec == 54321){
		printf("NaN\n");
		goto end;
	}
	if(dec==23){
		printf("-infinity\n");
		goto end;
	}
	
	printf("%0.8f", dec);
	
	end:
	return EXIT_SUCCESS;
    
}
