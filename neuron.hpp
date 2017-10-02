#ifndef Neuron_H
#define Neuron_H

#include <iostream>
#include <list>
#include <cmath>

class Neuron 
{
public:
	double getMemPot() const;
	unsigned int getNbSpike() const;
	//double getTimeSpike(int n) const;
	double getLastSpike() const;

	void setMemPot(double pot);
	void addSpike(double time);

	void update(double simtime, double I_ext);

	//static int getTHO();

private:
	double memb_pot_;
	std::list<double> spikes_historic_;

	//attribut de classe	
	static const double THO_;
	static const double R_;
	static const double SPIKE_THRESHOLD_;
	static const double REFRACT_TIME_;
	static const double EXP1_;


};

#endif