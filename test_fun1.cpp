#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "constants.hpp"
#include "neuron.hpp"

using namespace std;

double simtime (0);
double simduration(100);
double I_ext(4);
double I_ext_start(0);
double I_ext_end(80);

vector<Neuron*> Neurons_; 

void addNeuron(double memPot)
{
	Neuron* p_neuron = new Neuron(memPot);
	Neurons_.push_back(p_neuron);	
}

int main() 
{
	addNeuron(19.0);
	addNeuron(0.0);

	Neurons_[0]->addTarget(Neurons_[1]);
	Neurons_[1]->addTarget(Neurons_[0]);

	vector<double> mempot_values (Neurons_.size());

	ofstream myfile;

	myfile.open ("test1.txt");

	myfile << "Nb_of_neuron=" << Neurons_.size() << "\n"; // important when we want to exploit the data

	while (simtime < simduration) {

		if((simtime >= I_ext_start) && (simtime <= I_ext_end)) {

			for (unsigned int i(0); i < Neurons_.size(); ++i) {

				Neurons_[i]->update(1, I_ext);

				if ((Neurons_[i]->getLastSpike() != -10) && (Neurons_[i]->getMemPot() != 10.0))
				{
					myfile << "Neuron " << i << " atteint un spike de " << Neurons_[i]->getMemPot() << " mV à " << Neurons_[i]->getLastSpike();
					myfile << "\n";
					myfile << "Buffer du Neuron " << 1-i << "= ";

					for (auto val : Neurons_[1-i]->getBuffer())
					{
						myfile << val << " ; ";
					}

					myfile << "Position du readout = indice " << Neurons_[1-i]->getReadOutPos();
					myfile << "\n";
				}

				mempot_values[i] = Neurons_[i]->getMemPot();
			}

		} else {
			for (unsigned int i(0); i < Neurons_.size(); ++i) {

				Neurons_[i]->update(1, 0);

				if ((Neurons_[i]->getLastSpike() != -10) && (Neurons_[i]->getMemPot() != 10.0))
				{
					myfile << "Neuron " << i << " atteint un spike de " << Neurons_[i]->getMemPot() << "à " << Neurons_[i]->getLastSpike();
					myfile << "\n";
					myfile << "Buffer du Neuron " << 1-i << "= ";

					for (auto val : Neurons_[1-i]->getBuffer())
					{
						myfile << val << " ; ";
					}
					myfile << "Position du readout = indice " << Neurons_[1-i]->getReadOutPos();
					myfile << "\n";
				}

				mempot_values[i] = Neurons_[i]->getMemPot();
			}
		}

		for (auto val : mempot_values)
		{
			myfile << val << " ";
		}
		myfile << "\n";

	simtime+=h;
	}
}