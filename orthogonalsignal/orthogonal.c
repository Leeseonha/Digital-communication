#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <time.h>

#define ITER 1000000

main()
{
	double awgn();
	int SNRdB;
	int i;
	double E;
	double SNR;
	double temp;
	double sigma;
	double r0, r1;
	double decis;
	double error;
	double poe;
	double dsource;

	FILE *fp0;

	time_t t;
	srand((unsigned)time(&t));
	for (SNRdB = 0; SNRdB < 16; SNRdB++) {
		E = 1.0;
		SNR = pow(10.0, SNRdB / 10.0);

		sigma = E / sqrt(2.0*SNR);
		error = 0;

		if ((fp0 = fopen("./data3.txt", "w")) == NULL) {
			printf("File %s can not be treated as \%s\".\n", "./data3.txt", "w");
			exit(0);
		}

		for (i = 0; i < ITER; i++)
		{

			temp = (double)rand() / RAND_MAX;

			if (temp < 0.5)
			{
				dsource = 0;
			}
			else
			{
				dsource = 1.0;
			}

			if (dsource == 0)
			{
				r0 = E + awgn(sigma);	//반극 신호에서 0인 경우일때 E+N
			}
			else
			{
				r0 = -E + awgn(sigma);	//반극 신호에서 1인 경우일때 E+N
			}

			if (r0 >= 0)
			{
				decis = 0;
			}
			else
			{
				decis = 1.0;
			}

			if (decis != dsource)
			{
				error = error + 1.0;
			}
		}

		poe = error / ITER;

		printf("BER=%lf\n", poe);

		fp0 = fopen("./data3.txt", "a");
		fprintf(fp0, "%.1lf %lf\n", (double)SNRdB, poe);

	}
}
double awgn(double sigma)
{
	double w, x1, x2, theta, noise;
	x1 = (double)rand() / RAND_MAX;
	x2 = (double)rand() / RAND_MAX;

	if (x1 == 1.0) {
		x1 = (double)rand() / RAND_MAX;
	}

	w = sigma * sqrt(-2.0 * log(1.0 - x1));
	theta = 2.0 * M_PI * x2;

	noise = w * cos(theta);

	return (noise);
}