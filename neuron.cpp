#include <iostream>
#include <cmath>
#include "neuron.hpp"

using namespace std;

const double Neuron::THO_ = 20;
const double Neuron::C_ = 1;
const double Neuron::SPIKE_THRESHOLD_ = 20;
const double Neuron::V_RESET_ = 10; 
const double Neuron::REFRACT_TIME_ = 2.0;
const double Neuron::R_= THO_/C_;
const double Neuron::EXP1_ = exp(-h/THO_);

Neuron::Neuron(double memb_pot, unsigned int local_clock)
: memb_pot_(memb_pot), local_clock_(local_clock)
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


vector<double> Neuron::getSpikeHistoric() const
{
	return spikes_historic_;
}

array<double, D> Neuron::getBuffer() const
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

void Neuron::addSpike(double time)
{
	spikes_historic_.push_back(time);
}

void Neuron::addTarget(Neuron* p_neuron)
{
	targets_list_.push_back(p_neuron);
}

void Neuron::addArrivingSpike(unsigned int arriving_time, double coef)
{
	buffer_spikes_[(arriving_time  % buffer_spikes_.size())] += J;
}


void Neuron::update(unsigned int nbStep, double I_ext)
{
	if (getMemPot() > SPIKE_THRESHOLD_) {
		addSpike(local_clock_*h);
		//neuron reached the spike, the value of the membrane potential is already
		//stored (value of the last step), it has now to be reset

		for (auto& tar_neuron : targets_list_)
		{
			tar_neuron->addArrivingSpike((this->getLocalClock() + D), 1.0);
			/*1.0 est facteur efficacy entre les deux neurones, cf les informations de 
			connected_neurons
			*/
		}

		setMemPot(V_RESET_);
	} else if ((!spikes_historic_.empty()) && (local_clock_*h < getLastSpike() + REFRACT_TIME_)) {
		//neuron is insensitive to stimulation during refract time, membrane potential 
		//doesn't change
	} else {
		setMemPot(EXP1_*memb_pot_ + I_ext*R_*(1-EXP1_) 
			+ buffer_spikes_.at(getReadOutPos()));
		buffer_spikes_.at(getReadOutPos()) = 0;
	}
	local_clock_+= nbStep;
}