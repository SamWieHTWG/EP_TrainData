float simulate_error(const float b_c[3], const float a_c[2], const float b_p[2],
                const float a_p[2]){

	#define SETPOINT 		1.0
	double error = 0;
		
	float a [4] = { 0, 0, 0, 0 };
	float b [4] = { 0, 0, 0 };
	
	float y_d [4] = { 0, 0, 0, 0 };
	float u_d [3] = { 0, 0, 0 };
	float sum_y = 0;
	float sum_u = 0;
	float y;
	
	int jj = 0;
	int ii = 0;
	
	b[0] = b_c[0] * b_p[0];
	b[1] = b_c[0] * b_p[1] + b_c[1] * b_p[0];
	b[2] = b_c[1] * b_p[1];
	
	a[0] = a_c[0] + a_p[0];
	a[1] = a_c[1] + a_p[1] + a_c[0] * a_p[0];
	a[2] = a_c[0] * a_p[1] + a_c[1] * a_p[0];
	a[3] = a_c[1] * a_p[1];
	
	a[1] = a[1] + b[0];
	a[2] = a[2] + b[1];
	a[3] = a[3] + b[2];
	
	
	
	for( jj = 0; jj < RESPONSE_LENGTH; jj++){
	
		sum_y = 0;
		for( ii = 0; ii < 4; ii++){
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
		
	return error;	
}
	