
/**
 * @file  tmin.c
 * @author  German Razo 
 *
 * part 1 of program3
 *
 * @brief This is a serial program, 
 *        that performs the numerical integration
 *        using the trapezoidal method.
 *
 *  @Description The tmin I found is 44083498,
 *               I found the tmin with the methods: trapMin and bisecMethod,       
 * 
 */

#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <limits.h>

long double trap(long double a, long double b, unsigned int count);
long double f(long double x);
long double height(long double a, long double b, int n);
void trapMin(long double a, long double b, unsigned int n, long double true_value);
long double bisecMethod(
    long double a,
    long double b,
    long double *abstr,
    long double *i_r,
    unsigned int fl,
    unsigned int cel,
    long double t_v);
long double absrte(long double t_v, long double aprx);

int main(void)
{
  long double a, b;
  unsigned int t;
  printf("Enter a, b, and n\n");
  scanf("%Lf %Lf %d", &a, &b, &t);
  printf("\n");
  long double t_v = 4754.0192288588181366L;
  long double t_r = trap(a, b, t);
  long double a_e = absrte(t_r, t_v);
  printf("%.13Le %.19Le\n", t_r, a_e);
  return 0;
}

/**
 * @brief This function searches for the minimum
 *        total of trapezoids needed that gives
 *        the correct answer in 14 digits for
 *        the define integral with endpoints [a, b]  
 *            
 * 
 * @param a left endpoint of integral range
 * @param b right endpoint of integral range
 * @param n is the total number of trapezoids 
 * @param t_v is the true value 4754.0192288588181366
 */

void trapMin(long double a, long double b, unsigned int n, long double t_v)
{
  bool isLess = false;
  while (!isLess)
  {
    long double t_r = trap(a, b, n);
    long double absre = absrte(t_v, t_r);
    if (absre <= 0.5e-14L)
    {
      isLess = true;
      long double i_r = 0.0;
      long double absrte = 0.0;
      long double t_m = bisecMethod(a, b, &absrte, &i_r, a, n, t_v);
      printf("%.13Le %.19Le  %.19Le\n", i_r, t_m, absrte);
    }
    n = n * 2;
  }
}
/**
 * @brief This function calculates 
 *        the absolute relative true error 
 * 
 * @param t_v is the true value 4754.0192288588181366
 * @param aprx approximation result from the trapezoidal formula
 * @return long double is the result abosule relative true error
 */
long double absrte(long double t_v, long double aprx)
{
  long double true_error = fabsl(((t_v - aprx) / (t_v)));
  return true_error;
}
/**
 * @brief This function implements a binary search method
 *        to search for a number that is equal, 
 *        or less than the criteria 0.5e-14L
 * 
 * @param a left endpoint of integral range
 * @param b right endpoint of integral range
 * @param abstr is the absolute relative true error
 * @param i_r variable to store the result of the integral
 * @param fl is the floor of the range for the search 
 * @param cel is the ceiling of the range for the search 
 * @param t_v is the true value 4754.0192288588181366
 * @return long double the minimum number of trapezoids
 *         that is equal or less than the criteria 0.5e-14L
 */
long double bisecMethod(long double a,
                        long double b,
                        long double *abstr,
                        long double *i_r,
                        unsigned int fl,
                        unsigned int cel,
                        long double t_v)
{
  long double mid = (cel + fl) / 2.0;
  if (fl + 1 == cel)
  {
    return fl;
  }
  long double t_r = trap(a, b, mid);
  long double abserr = absrte(t_v, t_r);
  long double stc = 0.5e-14L;
  *abstr = abserr;
  *i_r = t_r;
  if (abserr > stc)
  {
    return bisecMethod(a, b, abstr, i_r, mid, cel, t_v);
  }
  else if (stc > abserr)
  {
    return bisecMethod(a, b, abstr, i_r, fl, mid, t_v);
  }

  return fl;
}

/**
 * @brief This function estimates a define integral  
 *        using the trapezoidal method
 * 
 * @param a is the leftendpoint of the integral range 
 * @param b is the right endpoint of the integral range
 * @param n is the number of trapezoids 
 * @return long double the result of the calculcated integral 
 */
long double trap(long double a, long double b, unsigned int n)
{
  long double approx = (f(b) + f(a)) / 2.0;
  for (unsigned int i = 1; i <= n - 1; i++)
  {
    long double ith = a + i * height(a, b, n);
    approx += f(ith);
  }
  return approx * height(a, b, n);
}

/**
 * @brief Calculates the height of the trapezoid 
 * 
 * @param a left endpoint from range [a,b]
 * @param b right endpoint from range [a,b]
 * @param n is the number of trapezoids 
 * @return long double the height of the trapezoid 
 */
long double height(long double a, long double b, int n)
{
  return (b - a) / (n);
}

/**
 * @brief This function calculcates value
 *        of the function below to be integrated:
 *        -3 cos(x/6) + sqrt(pow((5 * sinl(x / 9)) + (8 * sinl(x / 2),4)) 
 *        
 * 
 * @param x value to calculate 
 * @return long double value of result function
 */
long double f(long double x)
{
  long double sqrtIn = powl((5 * sinl(x / 9)) + (8 * sinl(x / 2)), 4);
  return (-3 * (cosl(x / 6))) + (sqrtl(sqrtIn)) + 1;
}