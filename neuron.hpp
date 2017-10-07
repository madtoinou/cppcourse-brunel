#ifndef Neuron_H
#define Neuron_H

#include <iostream>
#include <list>

class Neuron 
{
public:
	Neuron(double memb_pot=V_RESET_);

	double getMemPot() const;
	unsigned int getNbSpike() const;
	//double getTimeSpike(int n) const;
	double getLastSpike() const;

	void setMemPot(double pot);
	void addSpike(double time);

	void update(double simtime, double I_ext);

private:
	double memb_pot_;
	std::list<double> spikes_historic_;

	//attribut de classe	
	static const double THO_;
	static const double C_;
	static const double SPIKE_THRESHOLD_;
	static const double V_RESET_;
	static const double REFRACT_TIME_;
	static const double EXP1_;
	static const double R_;


};

#endif