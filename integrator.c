#include "integrator.h"

double rfunc(double coeff[10], double nu){
    //Set up as a LC of orthogonal set of polynomials
    
    //


    return 1;
}

double integrand(double nu, double T, double coeff[10]){
    return (nu*nu*nu)/(exp(nu)-1)* rfunc(coeff, nu);
}

double integrator(double lowerlim, double upperlim, double errtol, double T,double coeff[10]){

    //Setup
    double rough_ans = 0;
    double ans = 0;

    //https://en.wikipedia.org/wiki/Gaussian_quadrature#Change_of_interval
    //Compute coefficient
    double C = 2*h*h/(25*kb*T*c*c);

    //10 Point
    for (int i=0;i<10;i++){
        rough_ans += C*wi[i]*integrand((25*kb*T/h)*(xi[i]+1),T,coeff);
    }
    //21 Point
    for (int i=0; i<21; i++){
        ans += C*wi2[i]*integrand((25*kb*T/h)*(xi2[i]+1),T,coeff);
    }

    //Error Estimate
    double err = abs(ans-rough_ans);
    
    //If error tolerance not met, then split the interval and recurse
    if ( (err/(upperlim-lowerlim)) > errtol){
        double mid = 0.5*(upperlim-lowerlim);
        ans = integrator(lowerlim,mid,errtol,T,coeff) + integrator(mid,upperlim,errtol,T,coeff);
    }
    return ans;
}