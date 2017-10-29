#include <iostream>
#include <string>
#include "constants.hpp"
#include "neuron.hpp"
#include "network.hpp"

using namespace std;

unsigned int simtime (0);
unsigned int simduration(0);
double I_ext(0);
unsigned int I_ext_start(0);
unsigned int I_ext_stop(0);
unsigned int nbExciNeur(0);
unsigned int nbInhiNeur(0);
string filename("simulation");
char answer('n');

int main() 
{
	do {
	cout << "Enter the duration of the simulation (in steps)" << endl;
	cin >> simduration;
	} while (simduration <= 0);

	cout << "Do you want to apply a external current to a neuron of a network [y/n]" << endl;
	cin >> answer;
	if (answer == 'y') {
		do {
			cout << "Enter the external current applied to the first neuron of the network (in mV, recommended: 0)" << endl;
			cin >> I_ext;

			cout << "Enter the time where external current start to be applied (in steps, >=0)" << endl;
			cin >> I_ext_start;

			cout << "Enter the time where external current stop to be applied (in steps, >=0)" << endl;
			cin >> I_ext_stop;
	 	
		} while ((I_ext_stop < I_ext_start) || (I_ext_start < 0) || (I_ext_stop < 0));
	}

	do {
	cout << "Enter the number of excitatory neurons in the network (int, >= 0)" << endl;
	cin >> nbExciNeur;
	} while (nbExciNeur < 0);

	do {
	cout << "Enter the number of inhibitory neurons in the network (int, >= 0)" << endl;
	cin >> nbInhiNeur;
	} while (nbInhiNeur < 0);

	cout << "Enter the name of the where you want to store the membrane potential of the neurons" << endl;
	cin >> filename;

	Network smallBrain(nbExciNeur,nbInhiNeur);

	smallBrain.updateWriting(I_ext, simduration, I_ext_start, I_ext_stop, 1, filename);

}