#ifndef Constants_H
#define Constants_H

double const h (0.1); // step of simulation
unsigned int const D (15); // Delay/h ie 1.5ms/0.1ms; nb of step in Delay
double const J (0.1); // PSP
int const g (-5);
double const Mu_thre (0.01);
double const Mu_ext (2*Mu_thre);

#endif


/*
Ne=10 000, Ce = 1000, Je= 0.1
Ni=2500, Ci=250, Ji=0.5

g=5
*/