#ifndef Constants_H
#define Constants_H

double const h (0.1); ///< step of simulation
unsigned int const D (15); ///<  number of step equals to the transmission delay (here = 1.5ms)
double const J (0.1); ///< EPSP amplitude
int const g (-5); ///< Relative strength of inhibitory synapses (J_I =J*g)
int const eta (2); ///< 
double const Nu_threshold (10); ///<
double const Nu_ext (eta*Nu_threshold); ///< number of spikes/second needed to reach threshold
double const n (Nu_ext*0.1); ///< the frequency of external input (spikes/step)

#endif