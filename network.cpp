#include <iostream>
#include "network.hpp"

using namespace std;

Network::Network(unsigned int nbNeurons)
:
{
	for(unsigned int i(0); i< nbNeurons; ++i)
	{
		Neuron* p_newNeuron = new Neuron;
		neurons_network_.push_back(p_newNeuron);
	}
}

const std::vector<Neuron*>& Network::getTargets(Neuron* neuron)
{
	return neurons_network_[neuron];
}
