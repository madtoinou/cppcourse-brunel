#ifndef Network_H
#define Network_H

#include <iostream>
#include <vector>
#include <fstream>
#include <random>
#include <string>
#include "constants.hpp"
#include "neuron.hpp"

/** 
 * Class to represent a network of neurons with connections between them.
 * Store all the connections of the network in a vector of vector
 * Store all the neurons in a vector
 */
class Network
{
public:
	/**
  	@brief : Constructor, create a network of excitatory neurons with random
  	connections between them
  	@param NbNeurons : number of neurons
	*/
	Network(unsigned int NbNeurons);

	/**
  	@brief : Constructor, create a network of excitatory neurons and inhibitor
  	neurons, use creatRandomCon(...) to create connections between them
  	@param nbExiNeurons : number of excitatory neurons
  	@param nbInhNeurons : number of inhibitor neurons
	*/
	Network(unsigned int nbExiNeurons, unsigned int nbInhNeurons);

	/**
  	@brief : Getter, allow to manipulate neurons individually 
  	@param ID : index of the neuron in the attribute Neurons_
  	@return : a pointer to the neuron of index ID
	*/
	Neuron* getNeuron(unsigned int ID);

	/**
  	@brief : Setter, allow to add a connection between two neurons
  	@param IDPreNeur : index of the presynaptic neuron
  	@param IDPostNeur : index of the postsynaptic neuron
	*/
	void addPostSynap(unsigned int IDPreNeur, unsigned int IDPostNeur);

	/**
  	@brief : Create a graphe/network of neurons by creating random connections between them,
  	notice that a neuron have a number of connections with excitatory neurons equals to 10% of 
  	the total number of excitatory neurons and a number of connections with inhibitor neurons
  	equals to 10% of the total number of inhibitor neurons
  	@param nbExciNeurons : number of excitatory neurons
  	@param nbInhiNeurons : number of inhbitor neurons
	*/
	void creatRandomCon(unsigned int nbExciNeurons, unsigned int nbInhiNeurons);

	/**
  	@brief : update the network from the step t to the step t+number of step given
  	@param Iext : external (from oustide the network) current applied to the first created neuron (mv)
  	@param nbStep : number of step to the desired state of the network (>=1)
  	@param Iext_start : time (in steps) when the current Iext start being applied
  	@param Iext_stop : time (in steps) when the current Iext stop being applied
  	@param backgroundInfluence : influence of the background noise on the neuron behaviour (%)
	*/
	void update(double Iext, unsigned int nbStep, unsigned int Iext_start, unsigned int Iext_stop, double backgroundInfluence);

	/**
  	@brief : update the network state for a given number of steps, write the potential membrane
  	of all neurons at each stepin a file
  	@param Iext : external (from oustide the network) current applied to the first created neuron (mv)
  	@param nbSteps : number of step to the desired state of the network (>=1)
  	@param Iext_start : time (in steps) when the current Iext start being applied
  	@param Iext_stop : time (in steps) when the current Iext stop being applied
  	@param backgroundInfluence : backgroundInfluence : influence of the background noise on the neuron behaviour (1 for 100%, 0.5 for 50%)
  	@param filename : name of the file (.dat) where the data are writen
	*/
	void updateWritingPot (double Iext, unsigned int nbSteps, unsigned int Iext_start, unsigned int Iext_stop, double backgroundInfluence, std::string filename);

  /**
    @brief : update the network state for a given number of steps, write the spiking timing of 
    all the neurons in a file
    @param nbSteps : number of step to the desired state of the network (>=1)
    @param backgroundInfluence : backgroundInfluence : influence of the background noise on the neuron behaviour (1 for 100%, 0.5 for 50%)
    @param filename : name of the file (.dat) where the data are writen
  */
  void updateWritingSpi (unsigned int nbSteps, double backgroundInfluence, std::string filename);

private:

	std::vector<Neuron*> Neurons_;  ///< Store all the neurons of the network through pointers

	std::vector<std::vector<unsigned int>> neurons_graphe_;   ///< Store all the connexions between the neurons, each sub-vector i store the postsynaptic neurons of neuron i
};

#endif