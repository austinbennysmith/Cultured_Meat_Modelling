// #include

double uxvals[201];

int main()
{
	FILE * fp = fopen("blayer", "a");
	// for (int y=0; y<201; y+=1) {
	// 	uxvals[y] = y;
	// }

	for (double y=2.0; y<=4.0; y+=0.01) {
		// uxvals[(y-2)*100] = 1.232;
		int my_int;
		float my_float;
		my_float = 100.0*(y-2.0);
		my_int = (int)my_float;
		// fprintf(fp, "%d\n", my_int);
		uxvals[my_int] = y;
	}
	
	for (int loop=0; loop<201; loop++)
		fprintf(fp, "%g\n", uxvals[loop]);
	// fprintf (fp, "%g\n", uxvals[9]);
	fclose (fp);
}