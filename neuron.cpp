#include <iostream>
#include "neuron.hpp"

using namespace std;

const double H = 0.1;

const double Neuron::THO_ = 20;
const double Neuron::R_ = 1;
const double Neuron::SPIKE_THRESHOLD_ = 200;
const double Neuron::REFRACT_TIME_ = 1.0;
const double Neuron::EXP1_ = exp(-H/THO_);

double Neuron::getMemPot() const
{
	return memb_pot_;
}

unsigned int Neuron::getNbSpike() const
{
	return spikes_historic_.size();
}

double Neuron::getLastSpike() const
{
	if (!spikes_historic_.empty()) {
		return spikes_historic_.back();
	} else {
		return -1.1;
	}
}

void Neuron::setMemPot(double pot)
{
	memb_pot_=pot;
}

void Neuron::addSpike(double time)
{
	spikes_historic_.push_back(time);
}

void Neuron::update(double simtime, double I_ext)
{
	if (simtime < getLastSpike() + REFRACT_TIME_) {
		setMemPot(0);		
	} else if (getMemPot() > SPIKE_THRESHOLD_) {
		addSpike(simtime);
	}

	setMemPot(EXP1_*memb_pot_ + I_ext*R_*(1-EXP1_)/THO_);

}