#ifndef Network_H
#define Network_H

#include <iostream>
<<<<<<< HEAD
#include <unordered_map>
#include <vector>
=======
#include <vector>
#include <fstream>
#include <random>
#include "constants.hpp"
>>>>>>> 2neurons
#include "neuron.hpp"

class Network
{
public:
<<<<<<< HEAD
	Network(unsigned int nbNeurons=0);

	const std::vector<Neuron*>& getTargets(Neuron* neuron);

private:
	std::unordered_map<Neuron*, std::vector<Neuron*> > neurons_network_;
};



=======
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
	std::vector<std::vector<unsigned int>> neurons_graphe_; //axe horizontal: receveur, axe vertical envoyeur
};
>>>>>>> 2neurons

#endif