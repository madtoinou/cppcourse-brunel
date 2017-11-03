#ifndef Neuron_H
#define Neuron_H

#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <random>
#include "constants.hpp"

/** 
 * Class to represent neurons, their caracteristics and shared constants:
 * Used to creat neurons network. Include several attribute allowing neuron to keep a history
 * of their spikes (timing), to store received spikes until they effectively influence 
 * the neuron's potential.
 */

class Neuron 
{
public:
	/**
  	@brief : Constructor
  	@param isExci : true if the neuron is excitatory (default : true, excitatory)
  	@param memb_pot : inital value of the membrane potential (default : V_reset mV)
  	@param local_clock : intial value of the local_clock, in steps (default : 0 step)
  	@param Iext : external current applied to the neuron (default : 0 mV)
  	@param last_spike_t : timing of last spike
  	@param nb_spike : number of spike the neuron reached
	*/
	Neuron(bool isExci=true, double memb_pot=V_RESET_, unsigned int local_clock=0, double Iext=0, unsigned int last_spike_t=0, unsigned int nb_spike=0);

	/**
  	@brief : Getter, neuron's membrane potential
  	@return : value of the neuron membrane potential
	*/
	double getMemPot() const;

	/**
  	@brief : Getter, number of spikes the neuron reached since the beginning of the simulation
  	@return : number of spikes the neuron reached
	*/
	unsigned int getNbSpike() const;

	/**
  	@brief : Getter, timing of the last spike which occured
  	@return : local time of the neuron (number of steps) when the last spike occured, -10 if
  	no spike occured
	*/
	double getLastSpike() const;
<<<<<<< HEAD
<<<<<<< HEAD
	unsigned int getReadoutBufferIndex() const;
=======
=======

	/**
  	@brief : Getter, local time of the neuron
  	@return : local time of the neuron (number of steps)
	*/
>>>>>>> cpppcourse-brunel
	unsigned int getLocalClock() const;

	/**
  	@brief : Getter, history of the time when spikes occured
  	@return : vector of local time (number of steps), each corresponding to a spike
	*/
	unsigned int getLastSpikeT() const;

	/**
  	@brief : Getter, allows to access the neuron's ring-buffer attribute
  	@return : array, the neuron's ring-buffer
	*/
	std::array<double, D+1> getBuffer() const;

	/**
  	@brief : Getter, indicate the index of the readout for the ring-buffer
  	@return : position in the ring-buffer corresponding to local_time
	*/
	unsigned int getReadOutPos() const;

	/**
  	@brief : Getter, return the nature of the neuron 
  	@return : true if the neuron is excitatory, else false
	*/
	bool isExcitatory() const;
>>>>>>> 2neurons

	/**
  	@brief : Setter, set the attribute memb_pot_ to pot
  	@param pot : membrane potential of the neuron 
	*/
	void setMemPot(double pot);

	/**
  	@brief : Setter, set the attribute Iext_ to Iext 
  	@param Iext : external (outside the neurons Network) current applied to the given neuron 
	*/
	void setIext(double Iext);

	/** 
  	@brief : Setter, set the attribute Excitatory to bo
  	@param bo true if the neuron is excitatory, else false
	*/
	void setExcitatory(bool bo);

	/** 
  	@brief : Store local time of the neuron, used when the membrane potential reachs the spike threshold
  	@param time : time (local) when the spike occured (in steps >=0)
	*/
	void addSpike(unsigned int time);

	/** 
  	@brief : Store a spike in the neuron's buffer
  	@param arriving_time : spike's time (global) of arrival (in steps >=)
  	@param ConnectionNature : number of connections between the given neurons multiplied by the constant corresponding
  	to the nature of the spiking neuron (1 if excitatory, g if inhibitor)
	*/
	void addArrivingSpike(unsigned int arriving_time, int ConnectionNature);

	/** 
  	@brief : Update the state of the neuron state from time t to time t+nbStep
  	@param nbStep : number of steps to be simulated, steps >=1
  	@param backgroundInfluence: backgroundInfluence : coefficient determining the impact of the background noise (1 for 100%, 0.5 for 50%)
  	@return : true if the neuron reachs the spike threshold, else false 
	*/
	bool update(unsigned int nbStep, double backgroundInfluence);

private:
	
	static const double THO_;	///< Constant, represents ...

	static const double C_;		///< Capacity of the neuron's membrane (THO.Ohm⁻1)

	static const double SPIKE_THRESHOLD_;	///< Potential value corresponding to a spike (mV)

	static const double V_RESET_;	///< Membrane potential value after it reached the threshold (mV)

	static const double REFRACT_TIME_;	///< Period during neuron's potential remains insensible to stimulation (ms)

	static const double EXP1_;	///< Constant, used to optimise calculus

	static const double R_;	///< Resistance of the neuron's membrane (Ohm)

	double memb_pot_;	///< Value of the neuron's membrane potential (mV)

	unsigned int local_clock_;	///< Number of steps the neuron went trought

	unsigned int last_spike_t_;	///< Last spike's timing

	unsigned int nb_spike_; ///< Number of spikes the neuron reached

	double Iext_;	///< External current applied to the neuron (mV)

	bool isExcitatory_;	///< Nature of the neuron, true stands for excitatory

	std::array<double, D+1> buffer_spikes_;		///< Ring-buffer, store the spikes sended by pre-synaptic neurons for the duration of the delay

};

#endif