#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define PI 3.14159265358979323846
#define G 4.301*10^(-9)

void random_polar(int N, double r, double P[]);
void polar2cartesian(int N, double P[], double X[]);
void print3columns(int N, double vec[]);
void getAccelerations(int N, double X[], double A[],double eps);

int main (int argc, char **argv)
{
  /*Variable Initialization*/
  
  int N=atoi(argv[1]); //Char argument as number of masses (int)
  double eps=atof(argv[2]); // Prevent infinite accelerations
  double n=(double)N; //Number of masses as double
  
  double X[3*N]; // Cartesian Coordinates
  double P[3*N]; // Spherical coordinates
  double V[3*N]; // Cartesian Velocities
  double A[3*N]; // Cartesian Acceleration
  
  // Dimensions of the space
  double s=pow(n,1.0/3); // Side of the cube (Euclidean)
  double r=0.6205*s; // Radius of sphere (Polar)


  /* Create polar coordinate data*/
  random_polar(N,r,P);
  /*Transform to cartesian coordinates*/
  polar2cartesian(N,P,X);
  /* Calculate accelerations*/
  getAccelerations(N,X,A,eps);
  /* Print Polar coordinates*/
  //print3columns(N,P);
  //printf("\n");
  /* Print cartesian coordinates */
  //print3columns(N,X);
  /* Print accelerations*/
  print3columns(N,A);
}

void print3columns(int N, double vec[])
/*
Prints a 3N length array of 3D coordinates of the form
[q1 q2 q3] in three columns using printf
 */
{
  int i;
  for (i=0;i<N;i++)
    {
      printf("%6.3f\t%6.3f\t%6.3f\n",vec[i],vec[i+N],vec[i+2*N]);
    }
}

void polar2cartesian(int N, double P[], double X[])
/*
 Transforms a 3N lenght array of shperical coordinates
of the form [R Th Phi] to a cartesian coordinate array
of the form [X Y Z].
*/ 
{
  int i;
  double R;
  double Th;
  double Phi;
  for (i=0;i<N;i++)
    {
      R=P[i];
      Th=P[i+N];
      Phi=P[i+2*N];
      
      X[i]=R*cos(Th)*sin(Phi);
      X[i+N]=R*sin(Th)*sin(Phi);
      X[i+2*N]=R*cos(Phi);
    }
}

void random_polar(int N, double r, double P[])
/*
 Create random points in spherical coordinates:
The array P is a linear array of length 3N
in which the first N entries are R coordinates,
the next N are polar angle coordinates (Theta),
and the last N entries are azimuthal angles (Phi)
*/
{
  int i;
  srand48(time(NULL)); //random seed
  double max=r;
  int cont=0;
  for (i=0;i<3*N;i++)
    {
      if ((i+1)%N==0)
	{
	  P[i]=max*drand48();
	  if(cont==0)
	    {
	      max=2*PI;
	      cont++;
	    }
	  else if (cont==1)
	    {
	      max=PI;
	    }
	}
      else
	{
	  P[i]=max*drand48();
	}
    }
}

void getAccelerations(int N, double X[], double A[],double eps)
/* 
Calculate acceleration on each particle given the positions
of all the particles calculating the gravitational
force using spherical aproximation
*/
{
  double x,y,z;
  double norm;
  int cont;
  int i,j;
  double ri,rj;
  for (i=0; i<N; i++)
  {
    // Center of mass coordinates (of internal sphere)
    x=0;
    y=0;
    z=0;
    // Number of masses inside the shpere
    cont=0;
    // Radius of particle i
    ri=pow(pow(X[i],2)+pow(X[N+i],2)+pow(X[2*N+i],2),0.5);
    
    // Second loop: Calculate the force of each mass on the particle
    for (j=0;j<N;j++)
      {
	//Radius of particle j
	rj=pow(pow(X[j],2)+pow(X[N+j],2)+pow(X[2*N+j],2),0.5);
	//Do not calculate force on itself & particle inside sphere
	if(j!=i && rj<ri) 
	  {
	    cont++;
	    x+=X[j];
	    y+=X[N+j];
	    z+=X[2*N+j];
	  }
      }
    norm=pow((X[i]-x),2)+pow((X[N+i]-y),2)+pow((X[2*N]-z),2);
    A[i]=cont*G*(X[i]-x)/(pow(norm,1.5)+eps); //X acc
    A[N+i]=cont*G*(X[N+i]-y)/(pow(norm,1.5)+eps);// Y acc
    A[2*N+i]=cont*G*(X[2*N+i]-x)/(pow(norm,1.5)+eps);// Z acc
  }  
}
