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
double simduration(1000);
double I_ext(12);
double I_ext_start(175);
double I_ext_end(840);

vector<Neuron*> Neurons_; 
//un vector qui regroupe des pointeurs sur neurons
//créer une table avec pour clef des int (nombre des neurones), contenant une XX qui regroupe les
//J (amplitudes des spikes des neurones connectés)

//void addNeuron(Neuron neuron);

void addNeuron(Neuron neuron)
{
	Neuron* p_neuron = new Neuron (neuron);
	Neurons_.push_back(p_neuron);	
}

const double h (0.1); // = H du cpp, problème

int main() 
{
	cout << "How long do you want the simulation to be? (in ms, 1000 is good)" << endl;
	cin >> simduration;

	cout << "Please specify an external current I_ext (between 0 and 400, 12 is great)" << endl;
	cin >> I_ext;

	cout << "Please specify the time_start of I_ext (between 0 and the above promted simduration)";
	cout << " 175 is great" << endl;
	cin >> I_ext_start;

	cout << "Please specify the time_end of I_ext (between time_start and simduration)";
	cout << " 840 is great" << endl;
	cin >> I_ext_end;

	Neuron neuron1;

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

	simtime+=h;
	}
}