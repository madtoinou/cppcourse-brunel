#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "constants.hpp"
#include "neuron.hpp"

using namespace std;

unsigned int simtime (0);
unsigned int simduration(1000);
double I_ext(4);
unsigned int I_ext_start(0);
unsigned int I_ext_end(700);

vector<Neuron*> Neurons_; 

void addNeuron(double memPot)
{
	Neuron* p_neuron (new Neuron(memPot));
	Neurons_.push_back(p_neuron);	
}

int main() 
{
	addNeuron(0.0);
	addNeuron(19.0);

	Neurons_[0]->addTarget(Neurons_[1]);
	Neurons_[1]->addTarget(Neurons_[0]);

	vector<double> mempot_values (Neurons_.size());

	ofstream myfile;

	myfile.open ("test2.txt");

	myfile << "Nb_of_neuron=" << Neurons_.size() << "\n"; // important when we want to exploit the data

	while (simtime < simduration) {

		if((simtime >= I_ext_start) && (simtime <= I_ext_end)) {

			for (unsigned int i(0); i < Neurons_.size(); ++i) {
							
				Neurons_[i]->update(1, I_ext);				

				mempot_values[i] = Neurons_[i]->getMemPot();
			}

		} else {
			for (unsigned int i(0); i < Neurons_.size(); ++i) {

				Neurons_[i]->update(1, 0);

				mempot_values[i] = Neurons_[i]->getMemPot();
			}
		}

		for (unsigned int i(0); i < Neurons_.size(); ++i) {

			myfile << "Buffer du Neuron " << i << "= ";
				
			for (auto val : Neurons_[i]->getBuffer())
			{
				myfile << val << " ; ";
			}

			myfile << "\n";
			myfile << "Local_time du Neurone = " << Neurons_[i]->getLocalClock() << "\n";

		}

		for (auto val : mempot_values)
		{
			myfile << val << " ";
		}
		myfile << "\n";

	simtime+=1;
	}
}