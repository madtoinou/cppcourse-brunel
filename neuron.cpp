#include <iostream>
#include <cmath>
#include "neuron.hpp"

using namespace std;

const double H = 0.1;

const double Neuron::THO_ = 20;
const double Neuron::C_ = 1;
const double Neuron::SPIKE_THRESHOLD_ = 20;
const double Neuron::V_RESET_ = 10; 
const double Neuron::REFRACT_TIME_ = 2.0;
const double Neuron::R_= THO_/C_;
const double Neuron::EXP1_ = exp(-H/THO_);

Neuron::Neuron(double memb_pot)
: memb_pot_(memb_pot)
{}

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
		return -10; //by convention
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
	if ((!spikes_historic_.empty()) && (simtime < getLastSpike() + REFRACT_TIME_)) {
		//neuron is insensitive to stimulation during refract time, membrane potential 
		//doesn't change
	} else if (getMemPot() > SPIKE_THRESHOLD_) {
		addSpike(simtime);
		//neuron reached the spike, the value of the membrane potential is already
		//stored (value of the last step), it has now to be reset
		setMemPot(V_RESET_);
	} else {
		setMemPot(EXP1_*memb_pot_ + I_ext*R_*(1-EXP1_));
	}

}