#ifndef Neuron_H
#define Neuron_H

#include <iostream>
#include <vector>
#include <array>
#include "constants.hpp"

class Neuron 
{
public:
	Neuron(double memb_pot=V_RESET_, unsigned int local_clock=0, double Iext_=0);

	double getMemPot() const;
	unsigned int getNbSpike() const;
	double getLastSpike() const;
	unsigned int getLocalClock() const;
	std::vector<unsigned int> getSpikeHistoric() const;
	std::array<double, D+1> getBuffer() const;
	unsigned int getReadOutPos() const;

	void setMemPot(double pot);
	void setIext(double Iext);
	void addSpike(double time);

	void addArrivingSpike(unsigned int arriving_time);
	bool update(unsigned int nbStep);

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
	std::vector<unsigned int> spikes_historic_;
	double Iext_;

	std::array<double, D+1> buffer_spikes_; 
};

#endif