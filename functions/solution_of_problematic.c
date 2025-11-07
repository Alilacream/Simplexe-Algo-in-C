#include "solving_problematic.c"
int find_pivot_col(struct simplexe *s) {
  int total_vars = (s->is_min == 0) ? (s->n + s->m) : (s->n + s->m + s->m);

  if (s->is_min == 0) {
    // For maximization: find most positive
    double max = s->tableau[s->m][0];
    int max_index = 0;

    for (int i = 0; i < total_vars; i++) {
      if (s->tableau[s->m][i] > max) {
        max = s->tableau[s->m][i];
        max_index = i;
      }
    }
    return max_index;
  } else {
    // For minimization: find most negative
    double min = s->tableau[s->m][0];
    int min_index = 0;

    for (int i = 0; i < total_vars; i++) {
      if (s->tableau[s->m][i] < min) {
        min = s->tableau[s->m][i];
        min_index = i;
      }
    }
    return min_index;
  }
}

// function to find the exiting row
int find_pivot_row(struct simplexe *s, int max_index) {
  int rhs_col = (s->is_min == 0) ? (s->n + s->m) : (s->n + s->m + s->m);

  double min = 1e9;
  int min_index =
      -1; // if it stays -1 then not found, we have a problem in our algo
  for (int i = 0; i < s->m; i++) {
    if (s->tableau[i][max_index] <= 0) {
      continue;
    } else {
      double ratio = s->tableau[i][rhs_col] / s->tableau[i][max_index];
      if (ratio < min) {
        min = ratio;
        min_index = i;
      }
    }
  }
  return min_index;
}

// pivot function to go to the next iteration
void pivot(struct simplexe *s, int pivotcol, int pivotrow) {
  int rhs_col = (s->is_min == 0) ? (s->n + s->m) : (s->n + s->m + s->m);

  double pivot = s->tableau[pivotrow][pivotcol];
  for (int i = 0; i <= rhs_col; i++) {
    s->tableau[pivotrow][i] /= pivot; // normalize the pivot row
  }
  for (int i = 0; i <= s->m; i++) {
    if (i == pivotrow)
      continue;

    double factor = s->tableau[i][pivotcol];
    for (int j = 0; j <= rhs_col; j++) {
      s->tableau[i][j] -= factor * s->tableau[pivotrow][j];
    }
  }
}

// solve
void solve(struct simplexe *s) {
  while (isoptimal(s) == 0) {
    int pivot_col = find_pivot_col(s);
    int pivot_row = find_pivot_row(s, pivot_col);
    if (pivot_row == -1) {
      printf("Unbounded solution or error!\n");
      return;
    }
    pivot(s, pivot_col, pivot_row);
    print_tableau(s);
  }
  printf("Optimal table found.\n");
}

void print_solution(struct simplexe *s) {
  int rhs_col = (s->is_min == 0) ? (s->n + s->m) : (s->n + s->m + s->m);

  printf("\nOptimal Solution:\n");
  printf("================\n");

  // Array to store the values of original variables
  double solution[MAX_VARS] = {0};

  // For each original variable (columns 0 to n-1)
  for (int j = 0; j < s->n; j++) {
    // Check if this column is a basic variable (has exactly one 1 and rest 0s)
    int basic_row = -1;
    int count_ones = 0;
    int count_zeros = 0;

    // Check the column structure
    for (int i = 0; i <= s->m; i++) {
      if (s->tableau[i][j] == 1.0) {
        count_ones++;
        basic_row = i;
      } else if (s->tableau[i][j] == 0.0) {
        count_zeros++;
      }
    }

    // If column has exactly one 1 and rest are 0s, it's a basic variable
    if (count_ones == 1 && count_zeros == s->m) {
      solution[j] = s->tableau[basic_row][rhs_col]; // RHS value
    } else {
      solution[j] = 0.0; // Non-basic variable = 0
    }
  }

  // Print the values
  for (int i = 0; i < s->n; i++) {
    printf("x%d = %.2f\n", i + 1, solution[i]);
  }

  // Print the optimal objective function value (Z value)
  printf("\nOptimal objective value (Z) = %.2f\n",
         (s->tableau[s->m][rhs_col]) * -1);
}
