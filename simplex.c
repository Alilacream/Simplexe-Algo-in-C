#include "functions/solution_of_problematic.c"
#include <stdio.h>

// function to enter fill the table

int main() {
  struct simplexe s;
  inputproblem(&s);
  printf("Tableau N:0");
  print_tableau(&s);
  solve(&s);
  print_solution(&s);
  getchar();
  getchar();
  return 0;
}
