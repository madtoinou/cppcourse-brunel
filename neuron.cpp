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

Neuron::Neuron(bool isExci, double memb_pot, unsigned int local_clock, double Iext, unsigned int last_spike_t, unsigned int nb_spike)
: memb_pot_(memb_pot), local_clock_(local_clock), Iext_(Iext), isExcitatory_(isExci), last_spike_t_(last_spike_t), nb_spike_(nb_spike)
{}

double Neuron::getMemPot() const
{
	return memb_pot_;
}

unsigned int Neuron::getNbSpike() const
{
	return nb_spike_;
}

double Neuron::getLastSpike() const
{
	if (nb_spike_!=0) {
		return last_spike_t_;
	} else {
		//by convention
		return -10;
	}
}

unsigned int Neuron::getLocalClock() const
{
	return local_clock_;
}


unsigned int Neuron::getLastSpikeT() const
{
	return last_spike_t_;
}

array<double, D+1> Neuron::getBuffer() const
{
	return buffer_spikes_;
}

unsigned int Neuron::getReadOutPos() const
{
	return (local_clock_) % (buffer_spikes_.size());
}

bool Neuron::isExcitatory() const
{
	return isExcitatory_;
}

void Neuron::setMemPot(double pot)
{
	memb_pot_=pot;
}

void Neuron::setIext(double Iext)
{
	Iext_=Iext;
}

void Neuron::setExcitatory(bool bo)
{
	isExcitatory_=bo;
}

void Neuron::addSpike(unsigned int time)
{
	last_spike_t_=time;
}

void Neuron::addArrivingSpike(unsigned int arriving_time, int ConnectionNature)
{
	/*modulo is used to write the arriving spike right behing the readout index, thus
	the delay is well implemented (thanks to a well thought buffer size)*/
	buffer_spikes_[(arriving_time  % buffer_spikes_.size())] += J*ConnectionNature;
}

bool Neuron::update(unsigned int nbStep, double backgroundInfluence)
{
	bool isSpiking(false);
	double ReceivedSpike(0);

	for (unsigned int k(0); k < nbStep; ++k) {
		isSpiking = false;

		/*neuron reachs the spike threshold*/
		if (getMemPot() > SPIKE_THRESHOLD_) {
			addSpike(local_clock_);

			++nb_spike_;

			setMemPot(V_RESET_);

			isSpiking = true;

		/*neuron is refractory*/
		} else if ((nb_spike_ != 0) && (local_clock_ < last_spike_t_ + REFRACT_TIME_)) {

		/*neuron behave normally*/
		} else {

		static random_device rd;
		static mt19937 gen(rd());
		/*! Probability of noise (spike from outside the network), computed from the average number of spike and the simulation step*/
		static poisson_distribution<> background_noise_(Mu_ext*nbStep);

			ReceivedSpike = buffer_spikes_.at(getReadOutPos()) + background_noise_(gen)*backgroundInfluence;

			setMemPot(EXP1_*memb_pot_ + Iext_*R_*(1-EXP1_) + ReceivedSpike);

			buffer_spikes_.at(getReadOutPos()) = 0;
		
		}
	local_clock_+= 1;
	}

	return isSpiking;
}