#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/**
 * @brief calculate cluster availability
 *
 * @param n: nodes in cluster
 * @param m: MTTF for each node
 * @param t: recovery time for each node
 *
 * @return
 */

double all_ok(double n, double m, double t)
{
  return pow (1 - t / m, n);
}

double one_fail(double n, double m, double t)
{
  return n * t / m * pow (1 - t / m, n - 1);
}

double two_fail(double n, double m, double t)
{
  return n * (n - 1) * pow(t / m , 2) * pow(1 - t / m , n - 2) / 2;
}

double usable_2(double n, double m, double t)
{
  return all_ok(n, m, t) + one_fail(n, m, t);
}

double usable_3(double n, double m, double t)
{
  return all_ok(n, m, t) + one_fail(n, m, t) + two_fail(n, m, t);
}

int main(int argc, char* argv[])
{
  if (4 != argc)
  {
    fprintf(stderr, "%s node_count MTTF(hour) recovery_time(s)\n", argv[0]);
    return -1;
  }

  double n = (double)atoi(argv[1]);
  double m = (double)atoi(argv[2]);
  double t = (double)atoi(argv[3]) / 3600;

  printf("all ok  : %.15f\n", all_ok(n, m, t));
  printf("one fail: %.15f\n", one_fail(n, m, t));
  printf("two fail: %.15f\n", two_fail(n, m, t));
  printf("usable_2: %.15f\n", usable_2(n, m, t));
  printf("usable_3: %.15f\n", usable_3(n, m, t));

  return 0;
}







