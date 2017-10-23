#ifndef Network_H
#define Network_H

#include <iostream>
#include <vector>
#include <fstream>
#include <random>
#include "constants.hpp"
#include "neuron.hpp"

class Network
{
public:
	Network(unsigned int NbNeurons);
	Network(unsigned int nbExiNeurons, unsigned int nbInhNeurons);

	Neuron* getNeuron(unsigned int ID);
	unsigned int isPostSynap(unsigned int IDPreNeur, unsigned int IDPostNeur) const;
	void addPostSynap(unsigned int IDPreNeur, unsigned int IDPostNeur);
	void creatRandomCon(unsigned int nbExiNeurons, unsigned int nbInhNeurons);

	void update(double Iext, unsigned int nbStep, unsigned int Iext_start, unsigned int Iext_stop, double backgroundInfluence);
	void updateWriting (double Iext, unsigned int nbSteps, unsigned int Iext_start, unsigned int Iext_stop, double backgroundInfluence);


private:
	std::vector<Neuron*> Neurons_;
	std::vector<std::vector<unsigned int>> neurons_graphe_;
};

#endif