/********* Uniformly distributed random variable generator *********/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define SIGMA 1	//표준편차 σ를 나타냄
#define ITER 1000000
#define MAX 1000
#define PI 3.141592654

main()
{
	int i, k;
	double count[2 * MAX];
	double x1,x2;
	double sum, mean, vay, pdis;

	FILE* fp;

	time_t t;
	srand((unsigned)time(&t));

	sum = 0;
	mean = 0;

	for (k = 0; k < 2 * MAX; k++)
		count[k] = 0;

	for (i = 0; i < ITER; i++) {
		x2 = (double)rand() / RAND_MAX;
		x1 = sqrt(2*2.0*2.0*log(1/(1-((double)rand() / RAND_MAX))))*cos(2*PI*x2);
		vay = x1;

		for (k = -MAX; k < MAX; k++) {
			if ((vay >= (double)(k / 100.0)) && vay < (double)(k + 1.0) / 100.0) {
				count[k + MAX] += 1.0;
			}
		}
		sum += vay*vay;
		mean += vay;
	}

	for (k = -MAX; k < MAX; k++)
		printf("%lf%lf\n", (double)(k + 1.0) / 100.0, count[k + MAX] / ITER);
	printf("var=%lf,mean=%lf\n", sum / ITER - pow(mean / ITER, 2), mean / ITER);

	/******* Probability Density Fuction (PDF) *******/
	if ((fp = fopen("./data1.txt", "w")) == NULL) {
		printf("File %s can not be treated as \"%s\".\n", ". / data1.txt", "w");
		exit(0);
	}

	fprintf(fp, "#========================================#\n");
	fprintf(fp, "# Iteration=%d \n", ITER);
	fprintf(fp, "# mean=%lf,variance=%lf\n", mean / ITER, sum / ITER - pow(mean / ITER, 2));
	fprintf(fp, "#========================================#\n");
	fclose(fp);

	fp = fopen("./data1.txt", "a");
	for (k = -MAX; k < MAX; k++) {
		fprintf(fp, "%lf %lf\n", (double)(k + 1.0) / 100.0, count[k + MAX] / ITER);
	}
	fclose(fp);
	/******* Probability Distribution Fuction (CDF) *******/
	if ((fp = fopen("./data2.txt", "w")) == NULL) {
		printf("File %s can cot be treated as \"%s\".\n", "./data2.txt", "w");
		exit(0);
	}

	pdis = 0;
	fp = fopen("./data2.txt", "a");
	for (k = -MAX; k < MAX; k++) {
		pdis += count[k + MAX];
		fprintf(fp, "%lf %lf\n", (double)(k + 1.0) / 100.0, pdis / ITER);
	}
	fclose(fp);
}