double rfunc(double coeff){

    //Set up as a LC of orthogonal set of polynomials
    return 1;
}

double integrand(double nu, double T, double coeff[]){

    static const double kb = 1.380649E-23;
    static const double h = 6.62607015E-34;
    static const double c = 2.998E8;

    double x = h*nu/(kb*T);

    return 2*(kb*kb*kb*kb)*(T*T*T*T)/(h*h*c*c) * (x*x*x)/(exp(x)-1)* rfunc(coeff);
}

double integrator(double lowerlim, double upperlim, double errtol){

    //Setup
    double err = 0;
    double rough_ans=0;
    double ans=0;

    //Weights and eval points for 10 and 21 point gaussian
    static const double xi[10]={-0.1488743389816312,0.1488743389816312
                                -0.4333953941292472,0.4333953941292472,
                                -0.6794095682990244,0.6794095682990244,
                                -0.8650633666889845,0.8650633666889845,
                                -0.9739065285171717,0.9739065285171717};

    static const double wi[10]={0.2955242247147529,0.2955242247147529,
                                0.2692667193099963,0.2692667193099963,
                                0.2190863625159820,0.2190863625159820,
                                0.1494513491505806,0.1494513491505806,
                                0.0666713443086881,0.0666713443086881};

    static const double xi2[21] = {0,
                                    -0.1455618541608951,0.1455618541608951,
                                    -0.2880213168024011,0.2880213168024011,
                                    -0.4243421202074388,0.4243421202074388,
                                    -0.5516188358872198,0.5516188358872198,
                                    -0.6671388041974123,0.6671388041974123,
                                    -0.7684399634756779,0.7684399634756779,
                                    -0.8533633645833173,0.8533633645833173,
                                    -0.9200993341504008,0.9200993341504008,
                                    -0.9672268385663063,0.9672268385663063,
                                    -0.9937521706203895,0.9937521706203895};

    static const double wi2[21] = {0.1460811336496904,
                                    0.1445244039899700,0.1445244039899700,
                                    0.1398873947910731,0.1398873947910731,
                                    0.1322689386333375,0.1322689386333375,
                                    0.1218314160537285,0.1218314160537285,
                                    0.1087972991671484,0.1087972991671484,
                                    0.0934444234560339,0.0934444234560339,
                                    0.0761001136283793,0.0761001136283793,
                                    0.0571344254268572,0.0571344254268572,
                                    0.0369537897708525,0.0369537897708525,
                                    0.0160172282577743,0.0160172282577743};

    //Do integral
    //https://en.wikipedia.org/wiki/Gaussian_quadrature#Change_of_interval

    //10 Point
    for (int i=0;i<10;i++){
        rough_ans += wi[i]*integrand();
    }
    //21 Point
    for (int i=0; i<21; i++){
        rough_ans += wi2[i]*integrand();
    }


    //Error Estimate
    

    if ( (err/(upperlim-lowerlim)) > errtol){
        double mid = 0.5*(upperlim-lowerlim);
        ans = integrator(lowerlim,mid,errtol) + integrator(mid,upperlim,errtol);
    }
    return ans;
}