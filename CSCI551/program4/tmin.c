#include <stdio.h>
#include <math.h> 


double trapMethod(int a, int b, int t);
double f(double x);


int main(){
    int a, b, t;
    scanf("%d %d %d",&a,&b,&t);
    printf("a:%d b:%d t:%d\n",a,b,t);
    double res = f(4.0);
    printf("res: %f\n",res);
    return 0;
}

double trapMethod(int a, int b, int t){
	a++;
	b++;
	t++;
	return 0.0;
}

double f(double x){
 double sqrtIn = pow((5 * sin(x / 9)) + (8 * sin(x / 2)), 4);
 return (-3 * (cos(x / 6))) + (sqrt(sqrtIn)) + 1;
}