#include "mex.h"


void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){

    float *bp_p;
    float *ap_p;
    float *bc_p;
    float *ac_p;
  
    
    double *error_pointer;
    
      
    
    
    
	#define SETPOINT 		1.0
	#define RESPONSE_LENGTH 10000
	
	double error = 0;
		
	float a [3] = { 0, 0, 0 };
	float b [3] = { 0, 0, 0 };
	
	float y_d [3] = { 0, 0, 0 };
	float u_d [3] = { 0, 0, 0 };
	float sum_y = 0;
	float sum_u = 0;
	float y;
	
	int jj = 0;
	int ii = 0;
    
    float b_c[2] = { 0, 0 };
    float a_c[2] = { 0, 0 };
    float b_p[2] = { 0, 0 };
    float a_p[2] = { 0, 0 };
    
    
    bc_p = mxGetData(prhs[0]);
    ac_p = mxGetData(prhs[1]);
    bp_p = mxGetData(prhs[2]);
    ap_p = mxGetData(prhs[3]);
    
    b_c[0] = bc_p[0]; b_c[1] = bc_p[1];
    a_c[0] = ac_p[0]; a_c[1] = ac_p[1];
    b_p[0] = bp_p[0]; b_p[1] = bp_p[1];
    a_p[0] = ap_p[0]; a_p[1] = ap_p[1];
    
  
	
	b[0] = b_c[0] * b_p[0];
	b[1] = b_c[0] * b_p[1] + b_c[1] * b_p[0];
	b[2] = b_c[1] * b_p[1];
	
	/* den of cont always seen as 1 -1 */
	a[0] = a_p[0] - 1;
	a[1] = a_p[1] - a_p[0];
	a[2] = -a_p[1];

	
	a[0] = a[0] + b[0];
	a[1] = a[1] + b[1];
	a[2] = a[2] + b[2];
	
    /*
    for (ii = 0; ii <= 2; ii ++){
        printf("%f \n",b[ii]);
    }    
	
	for (ii = 0; ii <= 2; ii ++){
        printf("%f \n",a[ii]);
    }    
	*/
    
	for( jj = 0; jj < RESPONSE_LENGTH; jj++) {
	
		sum_y = 0;
		for( ii = 0; ii < 3; ii++){
			sum_y = sum_y + -1 * a[ii]*y_d[ii];
		}
		
		sum_u = 0;
		for( ii = 0; ii < 3; ii++){
			sum_u = sum_u + b[ii]*u_d[ii];
		}
		
		
		y = sum_y + sum_u;
       
            
		for(ii = 2; ii>=0; ii--){
			
			if( ii > 0){
				u_d[ii] = u_d[ii-1];
			}else{
				u_d[ii] = SETPOINT;
			}	
		}
		
		for(ii = 3; ii>=0; ii--){
			
			if( ii > 0){
				y_d[ii] = y_d[ii-1];
			}else{
				y_d[ii] = y;
			}	
		}
		
		if(isnan( y ) | error>10000 ){
			
			error = 10000;
				break;
		}else{
			error += (y-SETPOINT)*(y-SETPOINT);
		}
		 
		
		
		
		
	}
    
    
    
    
    
    
    
    plhs[0] = mxCreateDoubleMatrix(1, 1, mxREAL);
    error_pointer = mxGetPr(plhs[0]);
    *error_pointer = error;
    
    
    
}
