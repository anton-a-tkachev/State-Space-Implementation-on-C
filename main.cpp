// Harmonic Oscillator State-Space Model
//-----------------------------------------------------------------------------

#include <iostream>
#include <math.h>

int main(int argc, char** argv) {
	// Oscillator parameters
	// m*q" + c*q' + k*q = f
	double m = 1;		// [kg] - mass
	double c = 1;		// [N/m.s-1] - damping
	double k = 50;		// [N/m] - stiffness
	
	// Initial conditions
	double x0 = 0;		// [m] - initial displacement
	double v0 = 0;		// [m/s] - initial velocity
	
	// Time properties
	double T  = 1E-3;	// [s] - time discretization
	double Tf = 10;		// [s] - final time to stop simulation
	
	// State-space matrices
	double A[2][2] = {{     1,         T},
			  {-k*T/m, 1 - c*T/m}};
					  
	double B[2] = {0, T/m};
	
	double C[2][2] = {{1, 0},	// [m] - displacement
			  {0, 1}};	// [m/s] - velocity
	
	double x1[2] = {x0, v0};	// old state vector values from previous iteration (initialized with the initial conditions)
	double x2[2] = {0, 0};		// new state vector values from current iteration
	
	double y[2] = {0, 0};		// output vector: [displacement, velocity]
	
	double u[2] = {0, 0};		// input vector: [0, force]
	
	// Implementation
	FILE *fp;
	fp = fopen("output.csv", "w");	// create a csv-file which can be opened in Excel
	
	// Input excitation parameters
	double f = 0.5;		// [Hz] - sinewave excitation frequency
	double a = 1;		// [a.u.] - sinewave excitation amplitude
	
	for(int i = 0; i < Tf/T; i++){
		u[1] = a*sin(2*M_PI*f*T*i);	// input force (change to any arbitrary input)
		
		x2[0] = A[0][0]*x1[0] + A[0][1]*x1[1]; // "+ B[0]*u[0];" this part is a formality and not required
		x2[1] = A[1][0]*x1[0] + A[1][1]*x1[1] + B[1]*u[1];
		
		y[0]  = C[0][0]*x2[0] + C[0][1]*x2[1];		// [m] - displacement
		y[1]  = C[1][0]*x2[0] + C[1][1]*x2[1];		// [m/s] - velocity
		
		fprintf(fp, "%f,%f,%f\n", T*i, y[0], y[1]);	// output time, displacement, velocity
		
		x1[0] = x2[0];		// exchange values between the current and the previous iterations
		x1[1] = x2[1];
	}
	
	fclose(fp);
	
	return 0;
}
