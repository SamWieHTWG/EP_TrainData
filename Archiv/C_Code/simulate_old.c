#include <stdio.h>
#include <string.h>
#include "simulate.h" 
#include <time.h>
#include <stdlib.h>
#include <omp.h>

/*
void foo(char *buf, int count) {
    int i;
	for( i = 0; i < count; i++)
        buf[i] = i;
}

int *foo2(int count) {
	
    int *ret =calloc(count, sizeof(int));

	int i= 0;
    for( i = 0; i < count; i++) {
        ret[i] = i;
		printf("ret[%d] = %d \n",i,i);
	}

    return ret;
}
*/


int main(void) {  	
	
	
	
	float bc [2] = {1, 1};
	float ac [2] = { -0.2, 0.3};
	
	float bp [2] = {1, 1};
	float ap [2] = { -0.4, 0.5};
	
	
	float ones[10000];
	
	double cpu_time_used;
	
	
	float *y;
	int i;
	int id;
	
	
	clock_t start, end;
	
	/*
	
	p = foo2(100);
	for ( k = 0; k < 100; k++ ) 
		printf("%d \n",(int)p[k]);
	
	free(p);
	
	/*
	char arr[10] = {0};
    foo(arr, 10);
	
	
	int k;
	for ( k = 0; k < 10; k++ ) {
       printf( " out[%d] = %f \n", k, arr[k]); 
	
   }
	*/
	
	
	memset(ones, 1, sizeof(ones));
	
	
	start = clock();
	
	
	omp_set_num_threads(1000);
	
	#pragma omp parallel for
	
	 for ( i = 0; i < 1000; i++ ) {
   			
		 y = simulate(bc,ac,bp,ap,ones);
		 
		/* end = clock(); */
		  /* cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC; */
	
		/* printf("time used: %f \n", cpu_time_used);*/
		 
	 }
	
	end = clock();
	
	
	/*
	int var = 20;
	int var2 = 10;
	int* ip[2];
	ip[0] = &var;
	ip[1] = &var2;
	*/
	

	
	
	
/*
   for ( i = 0; i < 10000; i++ ) {
       printf( " out[%d] = %f \n", i, y[i]); 
	
   }
*/
	
   cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	
	printf("time used: %f", cpu_time_used);
	
	
	free(y);
	return 0;
}



float* simulate( const float b_c[3], const float a_c[2], const float b_p[2],
                const float a_p[2], const float setpoint[10000]){
	
	
	float* y_out = calloc(10000, sizeof(float));
	
	float yd_c_idx_0;
	float yd_c_idx_1;
	float ud_c_idx_0;
	float ud_c_idx_1;
	float yd_p_idx_0;
	float ud_p_idx_0;
	float yd_p_idx_1;
	float ud_p_idx_1;
	int ii;
	float yp;
	float b_setpoint[3];
	
	yd_c_idx_0 = 0.0F;
	yd_c_idx_1 = 0.0F;
	ud_c_idx_0 = 0.0F;
	ud_c_idx_1 = 0.0F;
	yd_p_idx_0 = 0.0F;
	ud_p_idx_0 = 0.0F;
	yd_p_idx_1 = 0.0F;
	ud_p_idx_1 = 0.0F;

	/*  -> Feedthrough of controller */
	/* setpoint= setpoint(1:1020) */
	
	for (ii = 0; ii < 10000; ii++) {
		
		yp = (-a_p[0] * yd_p_idx_0 + -a_p[1] * yd_p_idx_1) + (b_p[0] * ud_p_idx_0 +
		  b_p[1] * ud_p_idx_1);
		b_setpoint[1] = ud_c_idx_0;
		b_setpoint[2] = ud_c_idx_1;
		ud_c_idx_0 = setpoint[ii] - yp;
		ud_c_idx_1 = b_setpoint[1];

		/*  Input of controller = error */
		/* warning('order of controller - > kausality ?') */
		yd_p_idx_1 = (-a_c[0] * yd_c_idx_0 + -a_c[1] * yd_c_idx_1) + ((b_c[0] *
		  ud_c_idx_0 + b_c[1] * b_setpoint[1]) + b_c[2] * b_setpoint[2]);
		yd_c_idx_1 = yd_c_idx_0;
		yd_c_idx_0 = yd_p_idx_1;
		ud_p_idx_1 = ud_p_idx_0;
		ud_p_idx_0 = yd_p_idx_1;

		/*  input of plant = output of controller */
		yd_p_idx_1 = yd_p_idx_0;
		yd_p_idx_0 = yp;
		y_out[ii] = yd_p_idx_1;
		
	}
	
	
	/*
	int i;
	for ( i = 0; i < 10000; i++ ) {
       printf( " out[%d] = %f \n", i, y_out[i]); 
	
   }
	*/
	
	return y_out;
}
