#include "network.hpp"

using namespace std;

Network::Network(unsigned int NbNeurons)
: neurons_graphe_(NbNeurons, vector<unsigned int> (NbNeurons))
{
	for (unsigned int i(0); i<NbNeurons; ++i)
	{
		Neuron* p_neuron (new Neuron());
		Neurons_.push_back(p_neuron);	
	}
}

Network::Network(unsigned int nbExiNeurons, unsigned int nbInhNeurons)
: neurons_graphe_(nbExiNeurons+nbInhNeurons, vector<unsigned int> (nbExiNeurons+nbInhNeurons))
{
	for (unsigned int i(0); i<nbExiNeurons; ++i)
	{
		Neuron* p_neuron (new Neuron(true));
		Neurons_.push_back(p_neuron);	
	}

	for (unsigned int i(0); i<nbInhNeurons; ++i)
	{
		Neuron* p_neuron (new Neuron(false));
		Neurons_.push_back(p_neuron);	
	}

	creatRandomCon(nbExiNeurons, nbInhNeurons);
}

Neuron* Network::getNeuron(unsigned int ID)
{
	return Neurons_[ID];
}

unsigned int Network::isPostSynap(unsigned int IDPreNeur, unsigned int IDPostNeur) const
{
	return neurons_graphe_[IDPreNeur][IDPostNeur];
}

void Network::addPostSynap(unsigned int IDPreNeur, unsigned int IDPostNeur)
{
	neurons_graphe_[IDPreNeur][IDPostNeur]+=1;
}

void Network::creatRandomCon(unsigned int nbExiNeurons, unsigned int nbInhNeurons)
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> distExci(0, nbExiNeurons-1);
	uniform_int_distribution<> distInhi(nbExiNeurons, nbExiNeurons+nbInhNeurons-1);


	for (unsigned int i(0); i< Neurons_.size(); ++i) {

		for (unsigned int j(0); j < nbExiNeurons/10; ++j) {
			addPostSynap(distExci(gen), i);
		}

		for (unsigned int k(0); k < nbInhNeurons/10; ++k) {
			addPostSynap(distInhi(gen), i);
		}
	}
}


void Network::update (double Iext, unsigned int nbSteps, unsigned int Iext_start, unsigned int Iext_stop, double backgroundInfluence)
{
	unsigned int TotNbNeurons(Neurons_.size());

	for (unsigned int k(0); k < nbSteps; ++k) {

		if((k >= Iext_start) && (k <= Iext_stop)) {
			getNeuron(0)->setIext(Iext);
		} else {
			getNeuron(0)->setIext(0.0);
		}
			
		for (unsigned int i(0); i < TotNbNeurons; ++i) {
						
			if (getNeuron(i)->update(1, backgroundInfluence)) {

				for (unsigned int j(0); j < TotNbNeurons; ++j) {

					if(isPostSynap(i, j)!=0) {

						if(getNeuron(i)->isExcitatory()) {
						getNeuron(j)->addArrivingSpike(k+D, isPostSynap(i, j));						
						} else {
						getNeuron(j)->addArrivingSpike(k+D, g*isPostSynap(i, j));
						}
					}
				}
			}				
		}
	}
}

void Network::updateWriting (double Iext, unsigned int nbSteps, unsigned int Iext_start, unsigned int Iext_stop, double backgroundInfluence)
{
	unsigned int TotNbNeurons(Neurons_.size());

	vector<double> mempot_values (TotNbNeurons);

	ofstream myfile;

	myfile.open ("simulation.txt");

	myfile << TotNbNeurons << "\n";

	for (unsigned int k(0); k < nbSteps; ++k) {

		if((k >= Iext_start) && (k <= Iext_stop)) {
			getNeuron(0)->setIext(Iext);
		} else {
			getNeuron(0)->setIext(0.0);
		}
			
		for (unsigned int i(0); i < TotNbNeurons; ++i) {
						
			if (getNeuron(i)->update(1, backgroundInfluence)) {

				for (unsigned int j(0); j < TotNbNeurons; ++j) {

					if(isPostSynap(i, j)!=0) {

						if(getNeuron(i)->isExcitatory()) {
						getNeuron(j)->addArrivingSpike(k+D, isPostSynap(i, j));						
						} else {
						getNeuron(j)->addArrivingSpike(k+D, -1*isPostSynap(i, j));
						}
					}
				}
			}

		mempot_values[i] = getNeuron(i)->getMemPot();

		}

		for (auto val : mempot_values)
		{
			myfile << val << " ";
		}
	}
}
