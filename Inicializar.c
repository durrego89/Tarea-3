#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define MAX(x,y) x>y?x:y


double rand_double();/* 0.0 to 1.0, unif. dist. */
void calcular_f(int N, double g, double m1, double m2, float  *x,  float  *y,  float  *z, float  *fx,  float  *fy,  float  *fz);


int main() {
   

 
    
    int i;              //Contadores
    int j;
    
    int j1, j2;
    int N = 100;         //Numero de Particulas

    double G=1;         //Constante Gravitacional
    double M1=1;        // Masa 1
    double M2=1;        //Masa 2
    
    double r1,r2,r3,r;
    double u1,u2,u3;     // Vectores
    double F;
    double f1;
    double f2;          //Componentes de fuerzas
    double f3;
    
    
    float *X;
    float *Y;
    float *Z;           //Array posiciones y fuerzas
    float *F1;
    float *F2;
    float *F3;
    

    srand((long)time(NULL)); /* initialize rand() */


        
        X = malloc(N * sizeof(double *));
        Y = malloc(N * sizeof(double *));
        Z = malloc(N * sizeof(double *));
 
    
//------------------------------------------- Inicializacion --------------------------------------------------
    
        //Inicializa las masas de interes sobre una interceccion de la malla.
    float m1, m2, m3, valor;
    
    i=0;
    
    while(i <= N){
        m1 = 2*(floorf(rand_double()*100)/100) -1;
        m2 = 2*(floorf(rand_double()*100)/100) -1;           //Numeros Aleatorios amplificados 2 y desplazados -1
        m3 = 2*(floorf(rand_double()*100)/100) -1;
            
        valor = m1*m1 + m2*m2 + m3*m3; // Parametro para verificar existencia dentro de la esfera unidad
            
      
            
        if (valor <=1.0) {
               
            X[i]=m1;
            Y[i]=m2;
            Z[i]=m3;
            i=i+1;
            
        }
        else{
            i=i;
            }
        }
    
    
    
//-------------------------------------------- Imprimir Inicializacion -------------------------------------------
        //Imprimir las ubicaciones de las masas
    
    for(i = 0; i < N; i++){
        printf("%g %g %g \n", X[i], Y[i], Z[i]);
    }
    
 //------------------------------------------- Sumatoria de fuerza --------------------------------------------
    
    F1 = malloc(N * sizeof(double *));
    F2 = malloc(N * sizeof(double *));
    F3 = malloc(N * sizeof(double *));

    calcular_f(N, G, M1, M2, X, Y, Z, F1, F2, F3);
    
    
//------------------------------------------ Imprimir Fuerza Por Sumatoria ---------------------------------------
    //Imprimir las ubicaciones de las masas
    
//    for(i = 0; i < N; i++){
//        printf("%g %g %g \n", F1[i], F2[i], F3[i]);
//    }
    
//------------------------------------------- Sumatoria de fuerza ------------------------------------------------
    
    
   
    return 0;
}


//========================================   Subfunciones   =====================================================

//========================   Funcion Generadora de numeros aleatorios   =========================================

double rand_double() {
    return rand()/(double)RAND_MAX;
}


//===================================== Calcular la fuerza para cada particula ==================================

void calcular_f(int N, double g, double m1, double m2, float  *x,  float  *y,  float  *z, float  *fx,  float  *fy,  float  *fz){
 
    int i,j;
    
    double G=1;         //Constante Gravitacional
    double M1=1;        // Masa 1
    double M2=1;        //Masa 2
    double r1,r2,r3,r;
    double u1,u2,u3;     // Vectores
    double F;
    double f1;
    double f2;          //Componentes de fuerzas
    double f3;
    
    
    f1=0;
    f2=0;
    f3=0;
    for(i=0;i<N;i++){
        for(j=0; j<N; j++) {
            if(j!=i){
                
                r1=x[j]-x[i];
                r2=y[j]-y[i];
                r3=z[j]-z[i];
                
                r=sqrt(r1*r1+r2*r2+r3*r3);
                
                u1=r1/r;
                u2=r2/r;
                u3=r3/r;
                
                F=G*M1*M2*(1/(r*r));
                
                f1=f1+(F*u1);
                f2=f2+(F*u2);
                f3=f3+(F*u2);
                
                //printf(" %.15f %.15f %.15f \n",  f1, f2, f3);
            }
            
            fx[i]=f1;
            fy[i]=f2;
            fz[i]=f3;
        }
    }


}












