#include "network.hpp"

using namespace std;

Network::Network(unsigned int NbNeurons)
: neurons_graphe_(NbNeurons, vector<bool> (NbNeurons))
{
	// Neurons_ = vector<Neuron*> (NbNeurons);

	for (unsigned int i(0); i<NbNeurons; ++i)
	{
		Neuron* p_neuron (new Neuron());
		Neurons_.push_back(p_neuron);	
	}

	cout << "Naissance d'un network de " << Neurons_.size() << " neurones" << endl;
}

Neuron* Network::getNeuron(unsigned int ID)
{
	return Neurons_[ID];
}


bool Network::isPostSynap(unsigned int IDPreNeur, unsigned int IDPostNeur) const
{
	return neurons_graphe_[IDPreNeur][IDPostNeur];
}

void Network::addPostSynap(unsigned int IDPreNeur, unsigned int IDPostNeur)
{
	cout << "le neuron " << IDPostNeur << " va recevoir les spikes de " << IDPreNeur << endl;
	neurons_graphe_[IDPreNeur][IDPostNeur]=true;
}
