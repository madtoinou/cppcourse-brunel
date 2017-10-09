#ifndef Neuron_H
#define Neuron_H

#include <iostream>
#include <vector>
#include <array>

class Neuron 
{
public:
	Neuron(double memb_pot=V_RESET_, unsigned int local_clock=0);

	double getMemPot() const;
	unsigned int getNbSpike() const;
	double getLastSpike() const;

	void setMemPot(double pot);
	void addSpike(double time);
	void addTarget(Neuron neuron);

	void addArrivingSpike(unsigned int firing_local_clock, double J);
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
	//static const unsigned int NbStepsequalDelay = 15;

	double memb_pot_;
	unsigned int local_clock_; //number of step the neuron went trought
	std::vector<double> spikes_historic_;

	/*vector<Neuron_connection> where Neuron_connection is <&neuron, efficacy> 
	connected_neurons_; efficacy is J_ij in the paper
	*/
	std::vector<Neuron*> targets_list_;

	/*
	utiliser une map (unordered_map<unsigned int, double> buffer_spikes) avec pour clef le 
	multiple de h qui sépare l'horloge locale de l'heure d'arrivée du signal
	*/
	std::array<double, 15> buffer_spikes_; 
	/* à initialiser  de taille D/h  ou D/h + 1, ici D/h est égal à 15
	*/

};

#endif