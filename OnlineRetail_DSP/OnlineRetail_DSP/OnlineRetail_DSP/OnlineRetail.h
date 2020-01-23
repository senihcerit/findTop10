#pragma once
#include <string>

using namespace std;

class OnlineRetail {
public:
	
	OnlineRetail(int); // Constructor for Online Retail System
	~OnlineRetail();   // Destructor for Online Retail System

	void ReadCsvAndFillHashTable(string); // Read Csv File, Create Hash Table Data Structure and Fill this HT

	void Add(int, const string&, const string&, const int&); // Add items into Hash Table
			
	void top10Analyzer(); // Find top 10 products ordered
	
private:
	
	string *HashTable; //Hash Table pointer
	
	string *DescriptionArray; // *Description Array keeps descriptions of all products
	
	int *QuantityArray; // *Quantity Array keeps quantities of products. When program read csv file it adds quantities with previous.

	bool *statusOfHashIndex; // This array keeps status of Hash Index. If there is item in hash index it will be true,
	
	int sizeOfHashTable; // Hash Table Size

};