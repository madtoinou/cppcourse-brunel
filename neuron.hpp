#ifndef Neuron_H
#define Neuron_H

#include <iostream>
#include <vector>
#include <array>
#include "constants.hpp"

class Neuron 
{
public:
	Neuron(double memb_pot=V_RESET_, unsigned int local_clock=0);

	double getMemPot() const;
	unsigned int getNbSpike() const;
	double getLastSpike() const;
	unsigned int getLocalClock() const;
	std::vector<double> getSpikeHistoric() const;
	std::vector<double> getBuffer() const;

	void setMemPot(double pot);
	void addSpike(double time);
	void addTarget(Neuron* p_neuron);

	void addArrivingSpike(unsigned int arriving_time, double J);
	void update(unsigned int nbStep, double I_ext);

private:
	//attribut de classe	
	static const double THO_;
	static const double C_;
	static const double SPIKE_THRESHOLD_;
	static const double V_RESET_;
	static const double REFRACT_TIME_;
	static const double EXP1_;
	static const double R_;

	double memb_pot_;
	unsigned int local_clock_; //number of step the neuron went trought
	std::vector<double> spikes_historic_;

	/*CREAT A STRUCTURE <NEURON*, DOUBLE> conNeuron where the double is the efficacy; J_ij
	in the paper, then use it for targets_list_
	*/
	std::vector<Neuron*> targets_list_;

	std::vector<double> buffer_spikes_; 
};

#endif