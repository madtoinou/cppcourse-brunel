#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "constants.hpp"
#include "neuron.hpp"
#include "network.hpp"

using namespace std;

unsigned int simtime (0);
unsigned int simduration(1000);
double I_ext(1.01);
unsigned int I_ext_start(0);
unsigned int I_ext_end(10000);

int main() 
{
	Network smallBrain(1000,250);

	smallBrain.updateWriting(I_ext, simduration, I_ext_start, I_ext_end, 0);

}