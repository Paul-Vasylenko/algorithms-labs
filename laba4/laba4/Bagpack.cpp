#include "Bagpack.h"

Bagpack::Bagpack( int P)
{
	this->P = P;
}

void Bagpack::createItems()
{
	vector<Item> allItems = Filehelper::readItemsFromFile("data.csv");
	this->allItems = allItems;
}

vector<vector<bool>> Bagpack::generatePlots(int number_plots)
{
	vector<vector<bool>> result;
	for (int i = 0; i < number_plots; i++)
	{
		vector<bool> plot;
		for (int j = 0; j < allItems.size(); j++)
		{
			plot.push_back(false);
		}
		bool added = true;
		while (added){
			added = false;
			int random = rand() % this->allItems.size();
			while (random < allItems.size() && plot[random]) {
				if (random == allItems.size() - 1) {
					random = -1;
				}
				random++;
			}
			int totalW = this->totalWeight(plot, allItems[random].getWeight());
			if (totalW >= this->P) {
				result.push_back(plot);
				break;
			}
			plot[random] = true;
			added = true;
		} while (added);
		
	}
	return result;
}

int Bagpack::totalWeight(vector<bool> taken, int toAdd=0)
{
	int res = 0;
	for (size_t i = 0; i < allItems.size(); i++)
	{
		if (taken[i]) {
			res += allItems[i].getWeight();
		}
	}
	res += toAdd;
	return res;
}

int Bagpack::totalPrice(vector<bool> taken)
{
	int count=0;
	for (size_t i = 0; i < taken.size(); i++)
	{
		if (taken[i]) {
			count += this->allItems[i].getPrice();
		}
	}
	return count;
}

vector<bool> Bagpack::sendForagers(vector<bool> before, int number_foragers)
{
	//number of foragers can't be larger than степень of a plot
	vector<bool> copy = before;

	int countItems = 0;
	for (int i = 0; i < before.size(); i++)
	{
		if (copy[i]) {
			countItems++;
		}
	}
	if (number_foragers > countItems) {
		number_foragers = countItems;
	}


	vector<int> selected;
	for (int i = 0; i < copy.size(); i++)
	{
		if (copy[i]) {
			selected.push_back(i);
		}
	}
	random_shuffle(selected.begin(), selected.end());
	for (int i = 0; i < number_foragers; i++)
	{
		copy[selected[i]] = false;
	}
	vector<int> sortedByPricePerWeight_ALL = this->getSortedByPricePerWeight();
	vector<int> sortedByPricePerWeight;
	for (int i = 0; i < sortedByPricePerWeight_ALL.size(); i++)
	{
		if (find(selected.begin(), selected.end(), sortedByPricePerWeight_ALL[i]) == selected.end()) {
			sortedByPricePerWeight.push_back(sortedByPricePerWeight_ALL[i]);
		}
	}
	int i = 0;
	while (this->totalWeight(copy) < this->P) {
		if (this->totalWeight(copy, allItems[sortedByPricePerWeight[i]].getWeight()) > this->P) break;
		copy[sortedByPricePerWeight[i]] = true;
		i++;
	}
	return this->totalPrice(before)<this->totalPrice(copy)?copy:before;
}

vector<int> Bagpack::getSortedByPricePerWeight()
{
	vector<int> result;
	for (int i = 0; i < this->allItems.size(); i++)
	{
		result.push_back(i);
	}

	for (int i = 0; i < this->allItems.size(); i++) {
		for (int j = i + 1; j < this->allItems.size(); j++)
		{
			float price_per_weight1 = static_cast<float> (allItems[result[j]].getPrice()) / static_cast<float>(allItems[result[j]].getWeight());
			float price_per_weight2 = static_cast<float> (allItems[result[i]].getPrice()) / static_cast<float> (allItems[result[i]].getWeight());

			if (price_per_weight1 > price_per_weight2) {
				int temp = result[i];
				result[i] = result[j];
				result[j] = temp;
			}
		}
	}
	return result;
}

void Bagpack::displayItem(int n)
{
	cout << '{' << allItems[n].getName() << ',' << allItems[n].getWeight() << ',' << allItems[n].getPrice() <<'}' << ',';
}
