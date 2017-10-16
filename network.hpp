#ifndef Network_H
#define Network_H

#include <iostream>
#include <vector>
#include <array>
#include "constants.hpp"
#include "neuron.hpp"

class Network //: public sf::NonCopyable
{
public:
	Network(unsigned int NbNeurons=TotalNbNeurons);

	Neuron* getNeuron(unsigned int ID);
	bool isPostSynap(unsigned int IDPreNeur, unsigned int IDPostNeur) const;
	void addPostSynap(unsigned int IDPreNeur, unsigned int IDPostNeur);

private:
	std::vector<Neuron*> Neurons_;
	std::vector<std::vector<bool>> neurons_graphe_; //à la C, double pointeurs, provinet de la construction des array
};

#endif