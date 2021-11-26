#include "BeeColonyAlgorithm.h"

void BeeColonyAlgorithm::sortPlotsByPrice()
{
	for (int i = 0; i < this->number_plots; i++) {
		for (int j = i + 1; j < this->number_plots; j++)
		{
			if (this->prices[j] < this->prices[i]) {
				vector<bool> temp = plots[i];
				int temp_price = prices[i];
				plots[i] = plots[j];
				prices[i] = prices[j];
				plots[j] = temp;
				prices[j] = temp_price;
			}
		}
	}
}

BeeColonyAlgorithm::BeeColonyAlgorithm( int P)
{
	this->bagpack = Bagpack(P);
	this->bagpack.createItems();

}

void BeeColonyAlgorithm::solve()
{
	this->plots = this->bagpack.generatePlots(this->number_plots);
	for (int i = 0; i < number_plots; i++)
	{
		prices.push_back(this->bagpack.totalPrice(plots[i]));
	}

	for (int iter = 0; iter < this->number_iter; iter++)
	{
		this->sortPlotsByPrice();
		vector<int> chosenPlots;
		for (int i = 0; i < this->number_best_scouts; i++)
		{
			chosenPlots.push_back(i); //best scouts choose best solutions
		}
		set<int> randomSet;
		for (int i = 0; i < this->number_random_scouts; i++)
		{
			int counter = 0;
			int random = (rand() % (this->number_plots - this->number_best_scouts)) + this->number_best_scouts;
			while (randomSet.find(random) != randomSet.end()) {
				counter++;
				random = (rand() % (this->number_plots - this->number_best_scouts)) + this->number_best_scouts;
				if (counter >= 100) return;
			}
			counter = 0;
			randomSet.insert(random);
			chosenPlots.push_back(random);
		}
		

		for (int i = 0; i < chosenPlots.size(); i++)
		{
			this->plots[i] = this->bagpack.sendForagers(this->plots[chosenPlots[i]], this->n_foragers);
		}
		for (int i = 0; i < chosenPlots.size(); i++)
		{
			prices[i]=(this->bagpack.totalPrice(plots[i]));
			if (prices[i] > this->best_solution_price) {
				this->best_solution_price = prices[i];
				this->best_solution_weight = this->bagpack.totalWeight(plots[i],0);
				this->best_solution = plots[i];
			}
		}

		//cout << "iteration: " << iter<<endl;
		
	}
	cout << "Best price: " << this->best_solution_price << endl;
	cout << "Weight for this price: " << this->best_solution_weight << endl;
	cout << "Items taken: " << endl;
	cout << "#Name,weight,price" << endl;
	for (int i = 0; i < this->best_solution.size(); i++)
	{
		if (this->best_solution[i]) {
			this->bagpack.displayItem(i);
		}
	}
	cout << endl;
}
