#include <string>
#include "Map.h"
#include "Map.cpp"
#include "CharacterCodes.h"
#include <iostream>

//Reads data from string and returns a map with weights
Map<char, float> & readData(std::string data) {
	Map<char, float> * weightedData =  new Map<char, float>(20);

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

//Node type for encodeData function
struct Node {
	//Node * root;
	Node * left;
	Node * right;
	float weight;
	char value;
};

//Encode data
Node * encodeData(Map<char, float> weightedData) {
	int orderedNodesSize = weightedData.getNumEntries();
	Node ** orderedNodes = new Node*[orderedNodesSize];
	for (int i = 0; i < weightedData.getNumEntries(); i++) {
		//Add all weights and characters into the array of nodes
		
		Node * newNode = new Node;
		newNode->value = weightedData.getKeyByIndex(i);
		newNode->weight = weightedData.getValue(newNode->value);
		newNode->left = nullptr;
		newNode->right = nullptr;
		orderedNodes[i] = newNode;
	}
	//Order all the nodes from least to greatest
	//Bubble sort
	for (int i = 0; i < orderedNodesSize-1; i++) {
		for (int j = 0; j < orderedNodesSize - i - 1; j++) {
			if (orderedNodes[j]->weight < orderedNodes[j + 1]->weight) {
				Node * temp = orderedNodes[j];
				orderedNodes[j] = orderedNodes[j + 1];
				orderedNodes[j + 1] = temp;
			}
		}
	}
	//test print out all orderedNodes
	for (int i = 0; i < orderedNodesSize; i++) {
		std::cout << "Value: " << orderedNodes[i]->value << " Weight: " << orderedNodes[i]->weight << std::endl;
	}

	//Loop through orderedNodeSize, creating a new node with null value, with the left
	//as the least weight node, and the right as the second least weight node
	//weight of this node is the left + right weight
	//Compare with the node in the next spots (2 indices over) 
	//If it is not greater than it, then insert the node into the spot before it.
	//else, move the node in that index 1 spot down
	//Repeat until we can insert
	//Then loop through indices i + 1;
	
	for (int i = 0; i < orderedNodesSize - 1; i++) {
		Node * newNode = new Node;
		newNode->left = orderedNodes[i];
		newNode->right = orderedNodes[i + 1];
		newNode->weight = orderedNodes[i]->weight + orderedNodes[i + 1]->weight;
		newNode->value = 'i';
		
		for (int j = i + 2; j < orderedNodesSize; j++) {
			if (newNode->weight < orderedNodes[j]->weight) {
				orderedNodes[j - 1] = newNode;
				break;
			}
			else {
				orderedNodes[j - 1] = orderedNodes[j];
				if (j == orderedNodesSize - 1) {
					orderedNodes[j] = newNode;
				}
			}
			//Special case that the newNode should be at the end
			
		}
		if (i == orderedNodesSize - 2) {
			orderedNodes[orderedNodesSize - 1] = newNode;
		}
	}


	//Print out the node at the end 
	std::cout << orderedNodes[orderedNodesSize -1]->weight << std::endl;

	//Test to print out all nodes
	//for (int i = 0; i < weightedData.getNumEntries(); i++) {
	//	std::cout << orderedNodes[i]->value << "->" << orderedNodes[i]->weight  << std::endl;
	//}

	return orderedNodes[orderedNodesSize -1];
}

void recursiveCoding(Node * root, std::string code, CharacterCodes * arrayOfCodes) {
	if (root->left != nullptr) {
		recursiveCoding(root->left, code + "1", arrayOfCodes);
		std::cout << "left" << std::endl;
	}
	if (root->right != nullptr) {
		recursiveCoding(root->right, code + "0", arrayOfCodes);
		std::cout << "right" << std::endl;
	}
	if ((root->left == nullptr) && (root->right == nullptr)) {
		//TODO: Add to arrayOfCodes 
		(*arrayOfCodes).addCode(root->value, code);
	}
}

//test to print out Node tree using preOrder 
void printTree(Node * nodeptr) {
	if (nodeptr != nullptr) {
		std::cout << nodeptr->value << std::endl;
		printTree(nodeptr->left);
		printTree(nodeptr->right);
	}
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

	Map<char, float> myWeightedData = readData("kkefavkloabc");
	myWeightedData.display();
	std::cout << "-----------Encoded data-------" << std::endl;
	Node * test = encodeData(myWeightedData);
	
	//FIXME: According to tree, all values are on the right
	printTree(test);

	CharacterCodes huffmanCodes = CharacterCodes::CharacterCodes(10);
	recursiveCoding(test, "", &huffmanCodes);
	huffmanCodes.display();

	system("PAUSE");
	return 0;
}