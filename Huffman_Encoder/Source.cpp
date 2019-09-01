#include <string>
#include "Map.h"
#include "Map.cpp"



//Reads data from string and returns a map with weights
Map<char, float> & readData(std::string data) {
	Map<char, float> * weightedData =  new Map<char, float>(20);
	//FIXME: This map is not referenced again after the function is run

	for (int i = 0; i < data.length(); i++) {
		char iChar = data[i];

		if ((*weightedData).isInMap(iChar)) {
			(*weightedData).setValue(iChar, (*weightedData).getValue(iChar) + 1.0);
		}
		else {
			(*weightedData).addEntry(iChar, 1.0);
		}
	}

	for (int i = 0; i < (*weightedData).getNumEntries(); i++) {
		(*weightedData).setValueByIndex(i, ((*weightedData).getValueByIndex(i) / data.length()));
	}

	return *weightedData;
}

int main() {
	std::string myString = "ABCDEF";
	//Map<std::string, std::string> myDic = Map<std::string, std::string>::Map(10);
	//myDic.display();

	//Map<char, float> myWeightedGraph = Map<char, float>::Map(10);
	//myWeightedGraph.addEntry('a', 1.0);
	//myWeightedGraph.addEntry('b', 1.0);
	//myWeightedGraph.addEntry('c', 2.0);
	//myWeightedGraph.setValue('b', 3.5);

	Map<char, float> myWeightedData = readData("abbccddee");


	myWeightedData.display();

	system("PAUSE");
	return 0;
}