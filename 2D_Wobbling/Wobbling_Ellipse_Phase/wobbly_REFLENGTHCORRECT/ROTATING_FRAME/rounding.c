#include <math.h>

double a = 1.23;
// double b;
FILE * fp;

int main() {
	{
    char name[200];
    sprintf(name, "a.dat");
    fp = fopen(name, "w");
  	}

  	a = (double)floor(a*10.0)/10.0;
  	// b = (double)ceil(a*10.0)/10.0;

	fprintf(fp, "a: %g -b: %g \n", a, -a);
	fclose(fp);
}