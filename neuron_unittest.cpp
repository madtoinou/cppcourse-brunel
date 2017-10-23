#include <iostream>
#include "constants.hpp"
#include "neuron.hpp"
#include "network.hpp"
#include "gtest/gtest.h"
#include <cmath>

TEST (NeuronTest, MembranePotential_1step) {
	Neuron neuron;
	neuron.setIext(1.0);

	//First update test
	neuron.update(1);
	EXPECT_EQ(20.0*(1.0-std::exp(-0.1/20.0)), neuron.getMemPot());
}

TEST (NeuronTest, MembranePotential_10000step) {
	Neuron neuron;
	neuron.setIext(1.0);

	neuron.update(10000);

	EXPECT_EQ(0, neuron.getNbSpike());
	ASSERT_LT(neuron.getMemPot(), 20.0);
}

TEST (NeuronTest, MembranePotential_noIext) {
	Neuron neuron;
	neuron.setIext(0.0);

	neuron.update(100000);
	EXPECT_EQ(0, neuron.getNbSpike());
	ASSERT_LT(0.00001, std::fabs(20 - neuron.getMemPot()));
}

TEST (NeuronTest, SpikeTiming) {
	Neuron neuron;
	neuron.setIext(1.01);

	//Iext is applied during all the simulation
	//1e spike should occur at 92.4ms
	neuron.update(925);
	EXPECT_EQ(1, neuron.getNbSpike());
	//2e spike should occur at 186.8ms, 94.4 ms after the first spike
	neuron.update(944);
	EXPECT_EQ(2, neuron.getNbSpike());
	//3e spike should occur at 281.2ms, 94.4 ms after the second spike
	neuron.update(944);
	EXPECT_EQ(3, neuron.getNbSpike());
	//4e spike should occur at 375.6ms, 94.4 ms after the third spike
	neuron.update(944);
	EXPECT_EQ(4, neuron.getNbSpike());
}

TEST (NetworkTest, 2Neurons_Buffertest) {
	Network twoneurons(2);
	twoneurons.addPostSynap(0,1);

	//update the Network until the first spike of Neuron0
	twoneurons.update(1.01, 925, 0, 925);
	//update the Neuron1 for the numbers of steps equals to the delay
	twoneurons.getNeuron(1)->update(D);

	EXPECT_EQ(twoneurons.getNeuron(1)->getMemPot(), 0.1);
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

//FAIRE UNE PARTIE AVEC POSITIVE INPUT, NEGATIVE INPUT & 


//timing des spikes, pour un neuron seul!
//92.4ms, 186.8ms, 281.2ms, 375.6ms, Iext=1.01 faire 4000 update

