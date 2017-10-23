#include <iostream>
#include "constants.hpp"
#include "neuron.hpp"
#include "network.hpp"
#include "gtest/gtest.h"
#include <cmath>

TEST (NeuronTest, MembPot_1step_positivInput) {
	Neuron neuron;
	neuron.setIext(1.0);

	//First update test
	neuron.update(1,0);
	EXPECT_EQ(20.0*(1.0-std::exp(-0.1/20.0)), neuron.getMemPot());
}

TEST (NeuronTest, MembPot_ManyStep_posInput) {
	Neuron neuron;
	neuron.setIext(1.0);

	neuron.update(10000,0);

	EXPECT_EQ(0, neuron.getNbSpike());
	ASSERT_LT(neuron.getMemPot(), 20.0);
}

TEST (NeuronTest, MembPot_ManyStep_noInput) {
	Neuron neuron;
	neuron.setIext(0.0);

	neuron.update(100000,0);
	EXPECT_EQ(0, neuron.getNbSpike());
	//ASSERT_LT(0.00000001, std::fabs(neuron.getMemPot()));
}

TEST (NeuronTest, MembPot_ManyStep_negInput) {
	Neuron neuron;
	neuron.setIext(-1.0);

	neuron.update(10000,0);

	EXPECT_EQ(0, neuron.getNbSpike());
	ASSERT_LT(0.00001, std::fabs(20 - neuron.getMemPot()));
}

TEST (NeuronTest, SpikeTiming) {
	Neuron neuron;
	neuron.setIext(1.01);

	//Iext is applied during all the simulation
	//1e spike should occur at 92.4ms
	neuron.update(925,0);
	EXPECT_EQ(1, neuron.getNbSpike());
	EXPECT_EQ(924, neuron.getLastSpike());

	//2e spike should occur at 186.8ms, 94.4 ms after the first spike
	neuron.update(944,0);
	EXPECT_EQ(2, neuron.getNbSpike());
	EXPECT_EQ(1868, neuron.getLastSpike());

	//3e spike should occur at 281.2ms, 94.4 ms after the second spike
	neuron.update(944,0);
	EXPECT_EQ(3, neuron.getNbSpike());
	EXPECT_EQ(2812, neuron.getLastSpike());

	//4e spike should occur at 375.6ms, 94.4 ms after the third spike
	neuron.update(944,0);
	EXPECT_EQ(4, neuron.getNbSpike());
	EXPECT_EQ(3756, neuron.getLastSpike());

}

TEST (NetworkTest, Buffertest) {
	Network twoneurons(2);
	twoneurons.addPostSynap(0,1);

	//update the Network until the first spike of Neuron0
	twoneurons.update(1.01, 925, 0, 925, 0);
	//update the Neuron1 for the numbers of steps equals to the delay
	twoneurons.getNeuron(1)->update(D, 0);

	EXPECT_EQ(twoneurons.getNeuron(1)->getMemPot(), 0.1);
	ASSERT_LT(std::fabs(0.1 - twoneurons.getNeuron(1)->getMemPot()), 1E-5);

}

TEST (NetworkTest, Buffertest_InhtoExci) {
	Network twoneurons(2);
	twoneurons.addPostSynap(0,1);
	twoneurons.getNeuron(0)->setExcitatory(false);
	//update the Network until the first spike of Neuron0
	twoneurons.update(1.01, 925, 0, 925, 0);
	//update the Neuron1 for the numbers of steps equals to the delay
	twoneurons.getNeuron(1)->update(D, 0);

	EXPECT_EQ(twoneurons.getNeuron(1)->getMemPot(), -0.5);
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}