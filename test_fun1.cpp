#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "constants.hpp"
#include "neuron.hpp"
#include "network.hpp"

using namespace std;

unsigned int simtime (0);
unsigned int simduration(10000);
double I_ext(1.01);
unsigned int I_ext_start(0);
unsigned int I_ext_end(10000);

int main() 
{
	Network twoneurons(2);

	twoneurons.addPostSynap(0, 1);

	vector<double> mempot_values (TotalNbNeurons);

	ofstream myfile;

	myfile.open ("simulation.txt");

	myfile << "Nb_of_neuron=" << TotalNbNeurons << "\n"; // important when we want to exploit the data

	while (simtime < simduration) {

		if((simtime >= I_ext_start) && (simtime <= I_ext_end)) {
			twoneurons.getNeuron(0)->setIext(I_ext);
		} else {
			twoneurons.getNeuron(0)->setIext(0.0);
		}

		for (unsigned int i(0); i < TotalNbNeurons; ++i) {
						
			if (twoneurons.getNeuron(i)->update(1)) {

				cout << "NEURON " << i << " SPIKE AT " << simtime*h << " ms!!!" << endl;

				for (unsigned int j(0); j < TotalNbNeurons; ++j) {

					if(twoneurons.isPostSynap(i, j)) {

						cout << "NEURON " << j << " EST AFFECTE" << endl;

						twoneurons.getNeuron(j)->addArrivingSpike(simtime+D);
					}
				}
			}				

			mempot_values[i] = twoneurons.getNeuron(i)->getMemPot();
		}

		for (unsigned int i(0); i < TotalNbNeurons; ++i) {

			myfile << "Buffer du Neuron " << i << "= ";
				
			for (auto val : twoneurons.getNeuron(i)->getBuffer())
			{
				myfile << val << " ; ";
			}

			myfile << "\n";
			myfile << "Local_time du Neurone = " << twoneurons.getNeuron(i)->getLocalClock()*h << "ms \n";

		}

		for (auto val : mempot_values)
		{
			myfile << val << " ";
		}
		myfile << "\n";

	simtime+=1;
	}
}