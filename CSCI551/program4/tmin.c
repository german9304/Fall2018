
/* 
 * File:   tmin.c
 * Author: German Razo
 *
 * part 1
 * 
 * Purpose:  
 *
 *
 */
#include <stdio.h>
#include <math.h> 
#include <stdbool.h>


double trapMin(long double a, long double b, int count, long double *absError);
double initTrap(long double a, long double b, int count);
long double f(long double x);
bool absRelTrueErr(long double prev, long double cur, long double *absError);
double height(long double a, long double b, long double n);
long double searchMin(long double start, long double *absError);

void print();

int main(void){
    int a, b, t, total_trapezoids = 0;
    long double absError = 0.0;
    scanf("%d %d %d",&a,&b,&t);
    printf("a:%d b:%d t:%d\n",a,b,t);
    long double start_criteria = 4754.0192288588181366;
    //long double stop_criteria = .000000000000005;
    double res = initTrap(a, b, t);
    if(absRelTrueErr(res, start_criteria, &absError)){
     total_trapezoids = 1;

    }else{
     printf("false\n");
    }
    printf("res:  %.13e  abs_error: %.13Le\n ",res, absError);
    searchMin(res, &absError);
    return 0;
}
/*
 * Function:     searchMin
 * Purpose:      value of function to be integrated
 *
 * Input args:   x
 *
 * Return val:   
 */
long double searchMin(long double start, long double * absError){
  start++;
  absError++;
  // if(absError < ){

  // }
  // if(){

  // }
  return start;
}
/*
 * Function:     print
 * Purpose:      value of function to be integrated
 *
 * Input args:   x
 *
 * Return val:   
 */
void print(){

}
/*
 * Function:     trapMin
 * Purpose:      Serial function for estimating a definite integral 
 *               using the trapezoidal rule
 * Input args:   left_endpt
 *               right_endpt
 *               trap_count 
 *               base_len
 * Return val:   Trapezoidal rule estimate of integral from
 *               left_endpt to right_endpt using trap_count
 *               trapezoids
 */
double trapMin(long double a, long double b, int n, long double *absError){
	absError++;
	long double approx = (f(b) - f(a)) / n;
	for(int i = 1; i < n - 1; i++){
		long double ith = a + i * height(a, b, n);
		approx += f(ith);
		//printf("approx: %Lf\n", approx);

	}
	return approx * height(a, b, n);
}
/*
 * Function:     trapMin
 * Purpose:      Serial function for estimating a definite integral 
 *               using the trapezoidal rule
 * Input args:   left_endpt
 *               right_endpt
 *               trap_count 
 *               base_len
 * Return val:   Trapezoidal rule estimate of integral from
 *               left_endpt to right_endpt using trap_count
 *               trapezoids
 */
double initTrap(long double a, long double b, int n){
	long double approx = (f(b) - f(a)) / n;
	for(int i = 1; i < n - 1; i++){
		//printf(" iter: %d ", i);
		long double ith = a + i * height(a, b, n);
		approx += f(ith);
		//printf("approx: %Lf\n", approx);

	}
	return approx * height(a, b, n);
}
/*
 * Function:     height
 * Purpose:      value of function to be integrated
 *
 * Input args:   x
 *
 * Return val:   
 */
double height(long double a, long double b, long double n){
	return (b - a)/(n);
}
/*
 * Function:     absRelTrueErr
 * Purpose:      value of function to be integrated
 *
 * Input args:   prev
 *
 * Return val:   
 */
bool absRelTrueErr(long double cur, long double prev, long double *absError){
	//stoping criteria .000000000000005
	*absError = fabsl((cur - prev) / (prev)); 
	//printf("error: %Lf\n", *absError);
	return *absError < .00000000000005;
}
/*
 * Function:     f
 * Purpose:      value of function to be integrated
 *
 * Input args:   x
 *
 * Return val:   
 */
long double f(long double x){
 long double sqrtIn = pow((5 * sin(x / 9)) + (8 * sin(x / 2)), 4);
 return (-3 * (cos(x / 6))) + (sqrt(sqrtIn)) + 1;
}