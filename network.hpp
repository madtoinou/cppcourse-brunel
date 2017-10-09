#ifndef Network_H
#define Network_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include "neuron.hpp"

class Network
{
public:
	Network(unsigned int nbNeurons=0);

	const std::vector<Neuron*>& getTargets(Neuron* neuron);

private:
	std::unordered_map<Neuron*, std::vector<Neuron*> > neurons_network_;
};




#endif