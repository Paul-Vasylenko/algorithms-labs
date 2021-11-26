#include <iostream>
#include <vector>
#include "Item.h"
#include "Filehelper.h"
#include "BeeColonyAlgorithm.h"
#include <ctime>
using namespace std;


int main()
{
    srand(time(NULL));
    BeeColonyAlgorithm algo(500);
    algo.solve();
}

