
/* 
 * File:   tmin.c
 * Author: German Razo
 *
 * part 1
 * 
 * Purpose:  
 *
 43000000
  0 100 55500000
  5500000
  13107200   5.701955e-14
  1.3992905500000000000
  /26999999 - 50000000
  0 100 89000000
  44499999
  44083498
 *
 */

#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <limits.h>

long double trap(long double a, long double b,  unsigned int count);
long double f(long double x);
bool absRelTrueErr(long double t_v, long double v_a);
long double height(long double a, long double b, int n);
void trapMin(long double a, long double b, unsigned int n, long double true_value);
long double bisecMethod(
  long double a,
  long double b, 
  long double * abstr, 
  long double * i_r,
  unsigned int  fl, 
  unsigned int cel,
  long double t_v);
long double absrte(long double t_v, long double aprx);
void get_input(long double * a, long double * b, unsigned int * t);
void print();

int main(void){
    long double a, b;
    unsigned  int t;
    printf("Enter a, b, and n\n");
    scanf("%Lf %Lf %d",&a, &b, &t);
    //get_input(&a, &b,&t);
    long double t_v = 4754.0192288588181366L;
  // trapMin(a, b, t, t_v);
    long double t_r = trap(a, b, t);
    long double  a_e = absrte(t_r, t_v);
    printf("%.13Le %.19Le\n", t_r, a_e);
    return 0;
}

void get_input(long double * a, long double * b, unsigned int * t){
       printf("Enter a, b, and n\n");
       scanf("%Lf %Lf %d",a, b, t);
}

void trapMin(long double a,long double  b, unsigned int n, long double t_v){
 bool isLess = false;
  while(!isLess){
     long double t_r = trap(a, b, n);
     //printf("%s\n", );
     long double absre = absrte(t_v, t_r);
      printf("n:%d absrte:%Le t_r:%.13Le\n",n, absre, t_r);
      if(absre <= 0.000000000000005L){
        isLess = true;
        printf("second part\n");
        long double i_r = 0.0;
        long double absrte = 0.0;
        long double t_m = bisecMethod(a, b, &absrte, &i_r,a,n, t_v);
        printf("%.13Le %.19Le  %.19Le\n",i_r, t_m, absrte);
       
    }
     n =  n * 2;
  }
  // isLess = false;
  // n =  26214400;
  // while(!isLess){
  //   printf("second part %u\n",n);
  //    long double t_r = trap(a, b, n);
  //    long double absre = absrte(t_v, t_r);
  //     printf("n: %d absrte:%Le\n",n, absre);
  //      n -= 10000;
  //     if(absre > .00000000000005L){
  //       isLess = true;
       
  //   }
  // }
  // n++;

   // long double i_r = 0.0;
   //      long double absrte = 0.0;
   //      long double t_m = bisecMethod(a, b, &absrte, &i_r,13107200,26214400, t_v);
   //      printf("%13Le %.19Le  %.19Le\n",i_r, t_m, absrte);
}

long double absrte(long double t_v, long double aprx){
	long double true_error = fabsl(((t_v - aprx) / (t_v))); 
 //  printf("abserr %.13Le\n", true_error);
	return true_error;
}

long double bisecMethod(long double a, 
  long double b, 
  long double * abstr , 
  long double * i_r, 
  unsigned int fl,
  unsigned int cel, 
  long double t_v)
{
    long double mid = (cel + fl) / 2.0;
    if((unsigned int) mid == fl){
     return cel;
    }
    long double t_r = trap(a, b, mid);
    printf("t_r: %.13Le\n", t_r);
    printf("fl:%u  cel:%u mid:%.13Lf\n", fl, cel, mid);
    long double abserr =  absrte(t_v, t_r);
    printf("abserr %.13Le\n", abserr);
    long double stc = 0.000000000000005L;
     *abstr = abserr;
     *i_r = t_r;
    if(abserr  > stc){
      printf("T less\n");
     return bisecMethod(a, b, abstr, i_r,mid, cel,  t_v);
    }else if(stc > abserr){
      printf("T greater\n");
      return bisecMethod(a, b, abstr ,i_r, fl, mid, t_v);
    }
    //   if(t_r == 4754.0192288587){
    //     printf("stop t_r %.13Le\n", t_r);
    //     return cel;
    // }
    //  if(t_r > 4754.0192288588){
    //   mid /= 2;
    //   printf("less\n");
    //   return bisecMethod(a, b, abstr, i_r, mid, cel,  t_v);
    //  }else if(4754.0192288588 > t_r){
    //   printf("greater\n");
    //   mid *= 2;
    //   printf("mid: %Le\n",mid);
    //     return bisecMethod(a, b, abstr ,i_r, fl, mid, t_v);
    //  }

      return fl;
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
long double trap(long double a, long double b, unsigned int n){
	long double approx = (f(b) + f(a)) / 2.0;
	for(unsigned int i = 1; i <= n - 1; i++){
    //printf("%u\n",i );
		long double ith = a + i * height(a, b, n);
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
long double height(long double a, long double b, int n){
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
	long double true_error = fabsl(((t_v - v_a) / (t_v))); 
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