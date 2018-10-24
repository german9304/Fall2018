#include <stdio.h>
#include <math.h> 


double trapMethod(int left_endpt, int right_endpt, int count);
double f(double x);


int main(){
    int a, b, t;
    scanf("%d %d %d",&a,&b,&t);
    printf("a:%d b:%d t:%d\n",a,b,t);
    double res = f(4.0);
    printf("res: %f\n",res);
    return 0;
}
/*
 * Function:     trapMethod
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
double trapMethod(int left_endpt, int right_endpt, int count){
	left_endpt++;
	right_endpt++;
	count++;
	return 0.0;
}
/*
 * Function:     f
 * Purpose:      value of function to be integrated
 *
 * Input args:   x
 *
 * Return val:   
 */
double f(double x){
 double sqrtIn = pow((5 * sin(x / 9)) + (8 * sin(x / 2)), 4);
 return (-3 * (cos(x / 6))) + (sqrt(sqrtIn)) + 1;
}