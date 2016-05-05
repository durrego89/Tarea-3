#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define PI 3.14159265358979323846

void random_polar(int N, double r, double P[]);

int main (int argc, char **argv)
{
  /*VARIABLE INITIALIZATION*/
  
  int N=atoi(argv[1]); //Char argument as number of masses (int)
  double n=(double)N; //Number of masses as double
  
  double X[3*N]; // Cartesian Coordinates
  double P[3*N]; // Spherical coordinates
  
  // Dimensions of the space
  double s=pow(n,1.0/3); // Side of the cube
  double r=0.6205*s; // Radius of sphere


  /* CREATE RANDOM VARIABLES*/

  random_polar(N,r,P);
  // Prints 3 columns
  int i;
  for (i=0;i<N;i++)
    {
      printf("%.3f \t %.3f \t %.3f \n",P[i],P[i+N],P[i+2*N]);
    }
}
/* Create random points in spherical coordinates*/
void random_polar(int N, double r, double P[])
{
  int i;
  srand48(time(NULL)); //random seed
  double max=r;
  double min=-r;
  int cont=0;
  for (i=0;i<3*N;i++)
    {
      if ((i+1)%N==0)
	{
	  P[i]=(max-min)*drand48()+min;
	  if(cont==0)
	    {
	      max=2*PI;
	      min=0;
	      cont++;
	    }
	  else if (cont==1)
	    {
	      max=PI;
	      min=0;
	    }
	  srand48(time(NULL));
	}
      else
	{
	  P[i]=(max-min)*drand48()+min;
	}
    }
}
