Gernan Razo 
CSCI551 

# Value of discovered tmin: 44083498

# Approached I used for the search of tmin
  
I approached the search for the tmin with the binary search method.

#Description of my approach
  
My method to find the tmin, first searches for the absolute error value (ABRTE) that is less than or equal to the criteria (0.5e-14), so my method iterates in a while loop to find the value less than or equal to criteria, however, if the (ABRTE) is not less than criteria the size of the trapezoids increments twice the current size of trapezoids, so I multiply N which is the size of the trapezoids by two n * 2. When the condition is met, so when the (ABRTE) is 
Less than or equal to the criteria I start the binary search method to find an (ABRTE) that is less than or equal than the criteria. After I found the result (n) from my method I used that number to run the trapezoid method again to get a better approximation to the integral result in 14 digits. 

#Problems I faced when searchin for the tmin 
 
When my method finished searching for the tmin, I noticed that sometimes the result of the (ABRTE) didn’t meet the criteri, because number was off by .5 or sometimes .8. So, this is something I had to fix in order to find a correct number of trapezoids that give correct number in 14 digits. To solve this issue, I change the number of trapezoids (n) found during my method, either subtracting or increasing the number by 500 and look for a better tmin that would meet the criteria and give the correct answer in 14 digits. 

#Time it took to find my tmin

My method took about less than an hour to find n number of trapezoids less than or equal to the criteria, however, as I mentioned sometimes the (ABSRTE) didn’t meet the criteria, so I used the n number of trapezoids found in my method to run the trap method, which gives the approximate define integral using the trapezoidal method and get the absolute relative true error(ABRTE)  after, so this way I could adjust the n to get a better result that would meet the criteria and give the correct result in 14 digits. Adjusting the number of trapezoids took me about a week to find good number because I ran my code many times and save the number of trapezoids to compare the results.


#Experience 

Besides the tmin, learning to use the binary search method, finding a tmin that would meet the criteria, and also give the correct numbers of the integral in 14 digits was a big learning experience, because I had to adjust the binary method to get the correct result. Also, thinking about a method that would give a correct result took me some time because I wanted to use an efficient method and a method that would give a better result. I started by using brute force and see what method could help me achieve better results. I found a method called the bisection method, and what this method does is finds the root of a given function, and searches in a range from a to b, however learning this method gave a better understanding of binary search. 
