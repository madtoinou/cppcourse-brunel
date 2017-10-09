//check slide 20 to creat the main
//on calcule exp(-h/tho) et (1-exp(-h/tho) une fois pour toute car il est constant au cours du temps
	//Iext est entré au début de la simulation, il s'agit d'une constante
	//qui est R?
	//tho= so called time of neuron, scaled time axis = 20 ms
	//takes 20 ms so V(t)=1/e V(b), speed of decay
	//t= n*h, ou h est infitésimal
//tho=R*C
	// Iext dans (0, 400) pA
	//1000 ms = durée simulation

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "neuron.hpp"

using namespace std;

double simtime (0);
double simduration(100);
double I_ext(7);
double I_ext_start(20);
double I_ext_end(70);

vector<Neuron*> Neurons_; 
//un vector qui regroupe des pointeurs sur neurons
//créer une table avec pour clef des int (nombre des neurones), contenant une XX qui regroupe les
//J (amplitudes des spikes des neurones connectés)

void addNeuron(Neuron neuron)
{
	Neuron* p_neuron = new Neuron (neuron);
	Neurons_.push_back(p_neuron);	
}

const double h (0.1); // = H du cpp, problème

int main() 
{
	Neuron neuron1(19,0);

	Neuron neuron2;

	addNeuron(neuron1);
	addNeuron(neuron2);

	neuron1.addTarget(neuron2);
	neuron2.addTarget(neuron1);

	vector<double> mempot_values (Neurons_.size());

	ofstream myfile;

	myfile.open ("simulation.dat");

	myfile << "Nb_of_neuron=" << Neurons_.size() << "\n"; // important when we want to exploit the data

	while (simtime < simduration) {
		if((simtime >= I_ext_start) && (simtime <= I_ext_end)) {
			for (unsigned int i(0); i < Neurons_.size(); ++i) {

				Neurons_[i]->update(1, I_ext);
				//where 1 is the number of steps the neuron should progress

				mempot_values[i] = Neurons_[i]->getMemPot();
			}

		} else {
			for (unsigned int i(0); i < Neurons_.size(); ++i) {

				Neurons_[i]->update(1, 0);
				//where 1 is the number of steps the neuron should progress

				mempot_values[i] = Neurons_[i]->getMemPot();
			}
		}

		for (auto val : mempot_values)
		{
			myfile << val << " ";
		}

		cout << "neu1 last spike" << Neurons_[0].getLastSpike() << " // ";
		cout << "readout buffer: " << AffBufferValue(Neurons_[0]->getReadoutBufferIndex()) << "\n";
		cout << "neu2 last spike" << Neurons_[1].getLastSpike() << " // ";
		cout << 
	simtime+=h;
	}
}