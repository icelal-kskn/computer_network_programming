/*
    A program to calculate Factorial numbers
 */
#include <stdio.h>
int
main( ){
  long int        f_numb, calc_fact(int);
  int             number;
  printf("Factorial Calculator\n");
  printf("Enter a positive integer value ");
  scanf("%d", &number);
  if (number < 0)
    printf("Positive values only!\n");
  else if ((f_numb = calc_fact(number)) > 0)
    printf("%d! = %d\n", number, f_numb);
  else
    printf("Sorry %d! is out of my range!\n", number);
  return 0;
}
/*
   Calculate the factorial number and return the result or return 0
   if value is out of range.
 */
long int
calc_fact(int n){
  long int        total = 1, last = 0;
  int             idx;
  for (idx = n; idx - 1; --idx) {
    total *= idx;
    if (total <= last)                 /* Have we gone out of range? */
      return (0);
    last = total;
  }
  return (total);
}
