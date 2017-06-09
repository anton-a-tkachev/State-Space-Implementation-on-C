// Harmonic Oscillator State-Space Model
//-----------------------------------------------------------------------------

#include <iostream>
#include <math.h>

int main(int argc, char** argv) {
	// Oscillator parameters
	double m = 1;		// [kg] - mass
	double c = 1;		// [N/m.s-1] - damping
	double k = 50;		// [N/m] - stiffness
	
	// Initial conditions
	double x0 = 0;		// [m] - initial displacement
	double v0 = 0;		// [m/s] - initial velocity
	
	// Time properties
	double T  = 1E-3;	// [s] - discretization step
	double Tf = 10;		// [s] - final time
	
	// State-space matrices
	double A[2][2] = {{     1,         T},
					  {-k*T/m, 1 - c*T/m}};
					  
	double B[2] = {0, T/m};
	
	double C[2][2] = {{1, 0},
					  {0, 1}};
	
	double x1[2] = {x0, v0};	// previous step
	double x2[2] = {0, 0};		// next step
	
	double y[2] = {0, 0};
	
	double u[2] = {0, 0};
	
	// Implementation
	FILE *fp;
	fp = fopen("output.csv", "w");
	
	for(int i = 0; i < Tf/T; i++){
		u[1] = 10*sin(2*M_PI*1*T*i);
		
		x2[0] = A[0][0]*x1[0] + A[0][1]*x1[1] + B[0]*u[0];
		x2[1] = A[1][0]*x1[0] + A[1][1]*x1[1] + B[1]*u[1];
		y[0]  = C[0][0]*x2[0] + C[0][1]*x2[1];
		y[1]  = C[1][0]*x2[0] + C[1][1]*x2[1];
		
		fprintf(fp, "%f,%f,%f\n", T*i, y[0], y[1]);
		
		x1[0] = x2[0];
		x1[1] = x2[1];
	}
	
	fclose(fp);
	
	return 0;
}
