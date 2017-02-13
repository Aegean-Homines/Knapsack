#include "knapsack_brute_force_minchange.h"
#include <cmath>
#include <iostream>

GreyCode::GreyCode(int s) : size(s), current_count(0), lastElement(0), num_total(1<<s)
{
	//num_total = 1 << s;
	int half = (current_count) >> 1;
	lastElement = current_count ^ half;
	current_count++;
}

////////////////////////////////////////////////////////////////////////////////
std::pair< bool, std::pair< bool, int > > GreyCode::Next() {
	int half = (current_count) >> 1;
	int gray_code = current_count ^ half;
	int dif = lastElement ^ gray_code;
    
	lastElement = gray_code;
	current_count++;
    
	int  pos = log2(dif);// which position is modified 
	bool add = gray_code & dif;// is true if new value is 1 (add item), false otherwise 
	bool last = current_count == num_total;// is this the last permutation 
    return std::make_pair( !last, std::make_pair( add, pos ) );
}

////////////////////////////////////////////////////////////////////////////////
std::vector<bool> knapsack_brute_force( std::vector<Item> const& items, Weight const& W )
{
	std::vector<bool> currentCombination;
	Weight currentWeight;
	int bestValue = std::numeric_limits<int>::min();
	int totalValue = 0;
	currentCombination.resize(items.size(), false);
	std::vector<bool> bestCombination = currentCombination;

	bool go = true;
	GreyCode gc(items.size());


	while (go) {
		std::pair< bool, std::pair< bool, int > > r = gc.Next();
		go = r.first;
		bool add = r.second.first;
		int  pos = r.second.second;
		if (add) {
			currentCombination[pos] = true;
			totalValue += items[pos].GetValue();
			currentWeight += items[pos].GetWeight();
		}
		else {
			currentCombination[pos] = false;
			totalValue -= items[pos].GetValue();
			currentWeight -= items[pos].GetWeight();
		}

		if(totalValue > bestValue && currentWeight <= W) {
			bestValue = totalValue;
			bestCombination = currentCombination;
		}
	}


	return bestCombination;
}
