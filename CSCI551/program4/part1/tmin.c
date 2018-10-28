
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
/*

No, in this case it doesn't have anything to do with the endpoints other then calculating the integral.
The answer your looking for is the minimum size
So you floor is 0 right now and the ceiling is 100 right now, but that's not correct
So you keep increasing your ceiling (the top size) until you know it is above the answer you're looking for (when ARTE is less than the t condition)
Then when you found it, you can start the bisection method to find your answer.
Okay, let's say your floor is 0 and your ceiling is 100 and the answer you are looking for is 20.
That should be your ceiling, because that means the correct answer is below 12000.


You start by finding the midpoint between 0 and 100, which is 50.
You know that 50 is greater than 20 (in case of the trapezoids your ARTE would be less than the T condition), so you change your celing to 50 and keep 0 as the floor.
Then you would find the midpoint of 0 and 50, which is 25. And you keep repeating this cycle until you find your answer, 20.

If your midpoint is less than the answer (or in our case the ARTE is greater than the T condition) you make the midpoint your floor and keep the current ceiling.

*/
#include <stdio.h>
#include <math.h>
#include <stdbool.h>


long double trap(long double a, long double b, unsigned long long int count);
double initTrap(long double a, long double b, int count);
long double f(long double x);
bool absRelTrueErr(long double t_v, long double v_a);
long double height(long double a, long double b, unsigned long long int);
long double searchMin(long double a, long double b, int n, long double true_value, long double t_m);
void trapMin(long double a, long double b, unsigned long long int n, long double true_value);
long double bisecMethod(long double a, long double b, long double fl, long double cel, long double t_v);
long double absrte(long double t_v, long double aprx);
void print();

int main(void){
    long double a, b;
    unsigned long long int t;
    scanf("%Lf",&a);
    scanf("%Lf",&b);
    scanf("%lld",&t);
   // printf("after\n");
    printf("a:%Lf  b:%Lf  t:%llu\n",a,b,t);
    long double t_v = 4754.0192288588181366L;
    //long double stop_criteria = .000000000000005;
    ;
    //long double res = trapMin(a, b, t);
   //printf("first res: %.19Le\n", res);
    trapMin(a, b, t, t_v);
    return 0;
}

void trapMin(long double a,long double  b, unsigned long long int n, long double t_v){
 bool isLess = false;
  while(!isLess){
     long double t_r = trap(a, b, n);
     isLess = absRelTrueErr(t_v, t_r);
      n = (unsigned long long) n * 2;
      printf("before n: %llu\n", n);
        if(isLess){
        	printf("Misection Method\n");
        	printf("True\n");
        	printf("n: %llu\n", n/2);
        	bisecMethod(a, b, a, n/2, t_v);
        }
  }
}

long double absrte(long double t_v, long double aprx){
	//printf("t_v:%.19Le v_a: %.19Le \n",t_v, aprx);
	long double true_error = fabsl(((t_v - aprx) / (t_v))); 
	printf("error: %.14Le\n", true_error);
	return true_error;
}

long double bisecMethod(long double a, long double b, long double fl, long double cel, long double t_v){
    long double mid = (cel + fl) / 2.0;
    printf("flor: %Lf cel: %Lf  mid: %Lf \n",fl, cel, mid);
    long double t_r = trap(a, b, mid);
    printf("tm: %.14Le\n",t_r);
    long double abserr =  absrte(t_v, t_r);
    long double stc = .00000000000005L;
    printf("stc: %.14Le\n",stc);
    // 00000000000005.L
    // 000000000000005.
    //return abserr;
    if(abserr  > stc){
    	printf("greater abserror: %.14Le\n", abserr);
    	//return abserr;
     return bisecMethod(a, b, mid, cel,  t_v);
    }else if(stc > abserr){
    	printf("stc greater: %.14Le\n", abserr);
       return bisecMethod(a, b, fl, mid, t_v);
    }else{
    	printf("equal: %.14Le\n", abserr);
    }
      return cel;
    
}

/*
 * Function:     searchMin
 * Purpose:      value of function to be integrated
 *
 * Input args:   x
 *
 * Return val:   
 */
// long double searchMin(int a, int b, int n, long double t_v, long double t_m){
//      bool res = absRelTrueErr(t_v, t_m);
//      // printf("%Le\n",res);
//    if(res){
//    	 return res;
//    }
//    n += 55000;
//    long double t_r = trapMin(a, b, n);
//   // printf("t_r: %.19Le\n", t_r);
//   return searchMin(a,b, n, t_v, t_r);
// }
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
long double trap(long double a, long double b, unsigned long long int n){
	long double approx = (f(b) + f(a)) / 2.0;
	//printf("approx: %.14Le\n", approx);
	for(unsigned int i = 1; i <= n - 1; i++){
		//printf("i: %d\n",i);
		long double ith = a + i * height(a, b, n);
		approx += f(ith);
		//printf("f: %Lf\n", approx);

	}
	//printf("n: %d\n", n);
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
	long double approx = (f(b) + f(a)) / 2.0;
	for(int i = 1; i < n - 1; i++){
		//printf(" iter: %d ", i);
		long double ith = a + i * height(a, b, n);
		//printf(" ith: %Le ", ith);
		approx += f(ith);
		

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
long double height(long double a, long double b, unsigned long long int n){
	return (b - a) / (n);
}
/*
 * Function:     absRelTrueErr
 * Purpose:      value of function to be integrated
 *
 * Input args:   prev
 *
 * Return val:   
 */
bool absRelTrueErr(long double t_v, long double v_a){
	//stoping criteria .000000000000005
	printf("t_v:%.19Le v_a: %.19Le \n",t_v, v_a);
	long double true_error = fabsl(((t_v - v_a) / (t_v))); 
	printf("error: %.14Le\n", true_error);
	return true_error <= .00000000000005L;
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
 long double sqrtIn = powl((5 * sinl(x / 9)) + (8 * sinl(x / 2)), 4);
 return (-3 * (cosl(x / 6))) + (sqrtl(sqrtIn)) + 1;
}