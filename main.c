
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

# define NoOfPOINTS 1000
# define MAX 1000

void verifypoint(void);

struct comp{
    double r;
    double i;
};

struct comp c;
int outside_no = 0;

int main(){
    int i, j;
    double area, error, eps  = 1.0e-5;

#pragma omp parallel for default(shared) private(c,eps)
    for (i=0; i<NoOfPOINTS; i++) {
        for (j=0; j<NoOfPOINTS; j++) {
            c.r = -2.0+2.5*(double)(i)/(double)(NoOfPOINTS)+eps;
            c.i = 1.125*(double)(j)/(double)(NoOfPOINTS)+eps;
            verifypoint();
        }
    }


    area=2.0*2.5*1.125*(double)(NoOfPOINTS*NoOfPOINTS-outside_no)/(double)(NoOfPOINTS*NoOfPOINTS);
    error=area/(double)NoOfPOINTS;

    printf("Area of Mandlebrot set = %12.8f +/- %12.8f\n",area,error);

}

void verifypoint(void){

    struct comp x;
    int iter;
    double temp;

    x=c;
    for (iter=0; iter<MAX; iter++){
        temp = (x.r*x.r)-(x.i*x.i)+c.r;
        x.i = x.r*x.i*2+c.i;
        x.r = temp;
        if ((x.r*x.r+x.i*x.i)>4.0) {
            outside_no++;
            break;
        }
    }

}