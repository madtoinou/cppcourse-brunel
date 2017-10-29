#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "constants.hpp"
#include "neuron.hpp"

using namespace std;

double simtime (0);
double simduration(1000);
double I_ext(12);
double I_ext_start(175);
double I_ext_end(840);

vector<Neuron*> Neurons_; 

void addNeuron(double memPot)
{
	Neuron* p_neuron = new Neuron(memPot);
	Neurons_.push_back(p_neuron);	
}

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

	addNeuron(0.0);
	addNeuron(0.0);

	Neurons_[0]->addTarget(Neurons_[1]);
	Neurons_[1]->addTarget(Neurons_[0]);

	vector<double> mempot_values (Neurons_.size());

	ofstream myfile;

	myfile.open ("simulation.dat");

	myfile << "Nb_of_neuron=" << Neurons_.size() << "\n"; // important when we want to exploit the data

	while (simtime < simduration) {
		if((simtime >= I_ext_start) && (simtime <= I_ext_end)) {
			Neurons_[0]->setIext(I_ext);
		} else {
			Neurons_[0]->setIext(0.0);
		}
			
		for (unsigned int i(0); i < Neurons_.size(); ++i) {

			Neurons_[i]->update(1);
			//where 1 is the number of steps the neuron should progress

			mempot_values[i] = Neurons_[i]->getMemPot();
		}

		for (auto val : mempot_values)
		{
			myfile << val << " ";
		}

	simtime+=h;
	}

}