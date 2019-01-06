#include <stdio.h>
#include <string.h>
#include "simulate.h" 
#include <time.h>
#include <stdlib.h>
#include <math.h>


#define SETPOINT 		1.0

#define RESPONSE_LENGTH 	20


int main(void) {  	
	
	
	
	float bc [2] = {1, 0};
	float ac [2] = { -1, 0};
	
	float bp [2] = {1, 1};
	float ap [2] = { -0.9, -0.05};
	
	
	
	double cpu_time_used, error;

	
	float *y;
	int i;
	int y_executed = 0;
	
	
	clock_t start, end;
	
	
	
	
	start = clock();
	
	
	if(1){
		
		y = simulate(bc,ac,bp,ap);
		y_executed = 1;
	}else {
	 for ( i = 0; i < 1; i++ ) {
   			
		 error = simulate_error(bc,ac,bp,ap);
		 
		 printf("error = %lf",error);

		 
	 }
	}
	
	end = clock();
	
	if(1){
		
		for ( i = 0; i < RESPONSE_LENGTH; i++ ) {
       printf( " out[%d] = %f \n", i, y[i]); 
						
 		  }	
	}	
		
		
	
   	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	
	printf("time used: %f", cpu_time_used);
	
	if(y_executed)
		free(y);
	
	return 0;
}

float simulate_error(const float b_c[3], const float a_c[2], const float b_p[2],
                const float a_p[2]){
		double error = 0;
	
		error = 0;	
	
		float yd_c_0=0;
		float yd_c_1=0;
		float ud_c_0=0;
		float ud_c_1=0;
		float yd_p_0=0;
		float ud_p_0=0;
		float yd_p_1=0;
		float ud_p_1=0;
		int ii;
		float yp;
		float b_setpoint[3];




		/*  -> Feedthrough of controller */
		/* setpoint= setpoint(1:1020) */

		for (ii = 0; ii < RESPONSE_LENGTH; ii++) {

			yp = (-a_p[0] * yd_p_0 + -a_p[1] * yd_p_1) + (b_p[0] * ud_p_0 +
			  b_p[1] * ud_p_1);
			b_setpoint[1] = ud_c_0;
			b_setpoint[2] = ud_c_1;
			ud_c_0 = SETPOINT - yp;
			ud_c_1 = b_setpoint[1];

			/*  Input of controller = error */
			/* warning('order of controller - > kausality ?') */
			yd_p_1 = (-a_c[0] * yd_c_0 + -a_c[1] * yd_c_1) + ((b_c[0] *
			  ud_c_0 + b_c[1] * b_setpoint[1]) + b_c[2] * b_setpoint[2]);
			yd_c_1 = yd_c_0;
			yd_c_0 = yd_p_1;
			ud_p_1 = ud_p_0;
			ud_p_0 = yd_p_1;

			/*  input of plant = output of controller */
			yd_p_1 = yd_p_0;
			yd_p_0 = yp;
			
			if(isnan(yd_p_1) | error>10000 ){
				error = 10000;
				break;
			}else{
				error += abs(1-yd_p_1);
			}
		}


			return error;	
}
	


float* simulate( const float b_c[3], const float a_c[2], const float b_p[2],
                const float a_p[2] ){
	
	
	float* y_out = calloc(RESPONSE_LENGTH, sizeof(float));
	
	float yd_c_0=0;
	float yd_c_1=0;
	float ud_c_0=0;
	float ud_c_1=0;
	float yd_p_0=0;
	float ud_p_0=0;
	float yd_p_1=0;
	float ud_p_1=0;
	int ii;
	float yp;
	float b_setpoint[3];
	


	
	for (ii = 0; ii < RESPONSE_LENGTH; ii++) {
		
		yp = (-a_p[0] * yd_p_0 + -a_p[1] * yd_p_1) + (b_p[0] * ud_p_0 + b_p[1] * ud_p_1);

		b_setpoint[1] = ud_c_0;
		b_setpoint[2] = ud_c_1;
		ud_c_0 = SETPOINT - yp;
		ud_c_1 = b_setpoint[1];

		/*  Input of controller = error */
		/* warning('order of controller - > kausality ?') */
		yd_p_1 = (-a_c[0] * yd_c_0 + -a_c[1] * yd_c_1) + ((b_c[0] *
		  ud_c_0 + b_c[1] * b_setpoint[1]) + b_c[2] * b_setpoint[2]);
		yd_c_1 = yd_c_0;
		yd_c_0 = yd_p_1;
		ud_p_1 = ud_p_0;
		ud_p_0 = yd_p_1;

		/*  input of plant = output of controller */
		yd_p_1 = yd_p_0;
		yd_p_0 = yp;
		y_out[ii] = yd_p_1;
		
	}

	
	return y_out;
}
