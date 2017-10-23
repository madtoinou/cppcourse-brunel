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

std::poisson_distribution<> Neuron::background_noise_(0.02);
random_device rd;
mt19937 gen(rd());

Neuron::Neuron(bool isExci, double memb_pot, unsigned int local_clock, double Iext)
: memb_pot_(memb_pot), local_clock_(local_clock), Iext_(Iext), isExcitatory_(isExci)
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


void Neuron::addSpike(double time)
{
	spikes_historic_.push_back(time);
}

void Neuron::addArrivingSpike(unsigned int arriving_time, int ConnectionNature)
{
	buffer_spikes_[(arriving_time  % buffer_spikes_.size())] += J*ConnectionNature;
}

/** 
  Update the state of the neuron state from time t to time t+nbStep
  @param : number of steps to be simulated, steps>=1
  @return : true if the neuron reachs the spike threshold, else false 
*/

bool Neuron::update(unsigned int nbStep, double backgroundInfluence)
{

	bool isSpiking(false);
	double ReceivedSpike(0);
	for (unsigned int k(0); k < nbStep; ++k) {
		isSpiking = false;
		if (getMemPot() > SPIKE_THRESHOLD_) {
			addSpike(local_clock_);	

			setMemPot(V_RESET_);

			isSpiking = true;

		} else if ((!spikes_historic_.empty()) && (local_clock_ < getLastSpike() + REFRACT_TIME_)) {
		} else {
			ReceivedSpike = buffer_spikes_.at(getReadOutPos()) + background_noise_(gen)*backgroundInfluence;

			setMemPot(EXP1_*memb_pot_ + Iext_*R_*(1-EXP1_) + ReceivedSpike);

			buffer_spikes_.at(getReadOutPos()) = 0;
		
		}
	local_clock_+= 1;
	}

	return isSpiking;
}