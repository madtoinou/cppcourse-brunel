#include <iostream>
#include <cmath>
#include "neuron.hpp"

using namespace std;

const double Neuron::THO_ = 20;
const double Neuron::C_ = 1;
const double Neuron::SPIKE_THRESHOLD_ = 20;
const double Neuron::V_RESET_ = 0; 
const double Neuron::REFRACT_TIME_ = 20; //2,0ms, 20 steps of 0.1
const double Neuron::R_= THO_/C_;
const double Neuron::EXP1_ = exp(-h/THO_);

Neuron::Neuron(double memb_pot, unsigned int local_clock, double Iext)
: memb_pot_(memb_pot), local_clock_(local_clock), Iext_(Iext)
{
	/*for (unsigned int i(0); i < D+1; ++i)
	{
		buffer_spikes_.push_back(0.0);
	}*/
}

//FAIRE UN JOLI DESTRUCTEUR QUI DETRUIT LES POINTEURS

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

unsigned int Neuron::getLocalClock() const
{
	return local_clock_;
}


vector<unsigned int> Neuron::getSpikeHistoric() const
{
	return spikes_historic_;
}

array<double, D+1> Neuron::getBuffer() const
{
	return buffer_spikes_;
}

unsigned int Neuron::getReadOutPos() const
{
	return (local_clock_) % (buffer_spikes_.size());
}


void Neuron::setMemPot(double pot)
{
	memb_pot_=pot;
}

void Neuron::setIext(double Iext)
{
	Iext_=Iext;
}

void Neuron::addSpike(double time)
{
	spikes_historic_.push_back(time);
}

void Neuron::addArrivingSpike(unsigned int arriving_time)
{
	buffer_spikes_[(arriving_time  % buffer_spikes_.size())] += J;
}

/** 
@brief : Determine the neuron's state for the next stop
@param : nbStep is the number of step you want the neurons evolute in time
@return : true if the neuron reachs the spike threshold, else false 
*/

bool Neuron::update(unsigned int nbStep)
{
	bool isSpiking(false);
	if (getMemPot() > SPIKE_THRESHOLD_) {
		addSpike(local_clock_);

		setMemPot(V_RESET_);

		isSpiking = true;

	} else if ((!spikes_historic_.empty()) && (local_clock_ < getLastSpike() + REFRACT_TIME_)) {
	} else {
		setMemPot(EXP1_*memb_pot_ + Iext_*R_*(1-EXP1_) + buffer_spikes_.at(getReadOutPos()));

		buffer_spikes_.at(getReadOutPos()) = 0;

	}
	local_clock_+= nbStep;

	return isSpiking;
}