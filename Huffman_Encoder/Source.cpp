#include <string>
#include "Map.h"
#include "Map.cpp"
#include "CharacterCodes.h"
#include <iostream>
#include <fstream>

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

	//Test to print out all nodes
	//for (int i = 0; i < weightedData.getNumEntries(); i++) {
	//	std::cout << orderedNodes[i]->value << "->" << orderedNodes[i]->weight  << std::endl;
	//}

	return orderedNodes[orderedNodesSize -1];
}

void recursiveCoding(Node * root, std::string code, CharacterCodes * arrayOfCodes) {
	if (root->left != nullptr) {
		recursiveCoding(root->left, code + "1", arrayOfCodes);
	}
	if (root->right != nullptr) {
		recursiveCoding(root->right, code + "0", arrayOfCodes);
	}
	if ((root->left == nullptr) && (root->right == nullptr)) {
		//TODO: Add to arrayOfCodes 
		(*arrayOfCodes).addCode(root->value, code);
	}
}

std::string createCode(std::string initCode, CharacterCodes charCodes) {
	std::string code;

	for (int i = 0; i < initCode.length(); i++) {
		code += charCodes.getCodeByChar(initCode[i]);
	}
	return code;
}

std::string decode(std::string initCode, CharacterCodes charCodes) {
	std::string iString = "";
	std::string decodedString = "";
	for (int i = 0; i < initCode.length(); i++) {
		iString += initCode[i];
		//'~' character is returned if the character is not found
		if (charCodes.getCharByCode(iString) != '~') {
			decodedString += charCodes.getCharByCode(iString);
			iString = "";
		}
	}
	return decodedString;
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
	std::string locationOfFile;
	std::string dataFromFile;
	std::string fileName;
	std::cout << "Welcome, please enter the location of the .txt file to encode" << std::endl;
	std::getline(std::cin, locationOfFile);
	std::cout << "Please enter the file name." << std::endl;
	std::getline(std::cin, fileName);

	std::string reformattedLocation = "";
	for (int i = 0; i < locationOfFile.length(); i++) {
		if (locationOfFile[i] == '\\') {
			reformattedLocation += "\\\\";
		}
		else {
			reformattedLocation += locationOfFile[i];
		}
	}

	std::ifstream dataFile(reformattedLocation + "\\" + fileName);
	//TODO: add double backslash to location to be able to read location

	if (dataFile.is_open()) {
		while (std::getline(dataFile, dataFromFile)) {
			std::cout << dataFromFile << std::endl;
		}
		dataFile.close();
	}
	else {
		std::cout << "Could not open file" << std::endl;
	}

	Map<char, float> weightedMap = readData(dataFromFile);
	Node * root = encodeData(weightedMap);
	CharacterCodes huffmanValues = CharacterCodes::CharacterCodes(20);
	recursiveCoding(root, "", &huffmanValues);
	std::string encodedData = createCode(dataFromFile, huffmanValues);

	std::cout << "Encoded data" << std::endl;
	std::cout << encodedData << std::endl;

	std::cout << "Huffman Values" << std::endl;
	huffmanValues.display();

	//Create a text file with the encodedData push to desktop
	std::ofstream encodedFile;
	encodedFile.open(locationOfFile + "\\" + "encodedData.txt");
	encodedFile << encodedData << std::endl;
	encodedFile.close();

	//Create a text file with the huffman values push to desktop
	std::ofstream huffmanFile;
	huffmanFile.open(locationOfFile + "\\" + "huffmanValues.txt");
	for (int i = 0; i < huffmanValues.getNumOfCodes(); i++) {
		huffmanFile << huffmanValues.getCharByIndex(i) << "->" << huffmanValues.getValueByIndex(i) << std::endl;
	}
	huffmanFile.close();

	system("PAUSE");
	return 0;
}