#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "constants.hpp"
#include "neuron.hpp"
#include "network.hpp"

using namespace std;

unsigned int simtime (0);
unsigned int simduration(3000);
double I_ext(1.01);
unsigned int I_ext_start(200);
unsigned int I_ext_end(1800);

int main() 
{
	Network smallBrain(10000,2500);

	smallBrain.updateWriting(I_ext, simduration, I_ext_start, I_ext_end, 0);

}