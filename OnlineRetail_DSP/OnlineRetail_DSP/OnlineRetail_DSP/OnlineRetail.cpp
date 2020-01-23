#include "stdafx.h"
#include "OnlineRetail.h"
#include <iostream>
#include <fstream>

OnlineRetail::OnlineRetail(int size) {
	
	sizeOfHashTable = size;

	HashTable = new string[size];
	DescriptionArray = new string[size];
	QuantityArray = new int[size];

	statusOfHashIndex = new bool[size];

	for (auto i=0; i < size; i++)
	{
		statusOfHashIndex[i] = false;
		QuantityArray[i] = 0;
	}
	
		
}

OnlineRetail::~OnlineRetail() {
	delete[] statusOfHashIndex;
	delete[] HashTable;
	delete[] DescriptionArray;
	delete[] QuantityArray;
}

void OnlineRetail::ReadCsvAndFillHashTable(string filename) {
	

	fstream file(filename);

	string InvoiceNo, StockCode, Description, Quantity, InvoiceDate, UnitPrice, CustomerID, Country;
	
	if (file.is_open()) {

		while (file.good())
		{
			getline(file, InvoiceNo, ';');
			getline(file, StockCode, ';');
			getline(file, Description, ';');
			getline(file, Quantity, ';');
			getline(file, InvoiceDate, ';');
			getline(file, UnitPrice, ';');
			getline(file, CustomerID, ';');
			getline(file, Country, '\n');

			int asciiValue = int(StockCode.at(0));
						
			if ((Country == "United Kingdom") && (asciiValue >= 47) && (asciiValue <= 58)) {
				
				string convertedStockCode = StockCode.substr(0, 5);
				Add(stoi(convertedStockCode) % sizeOfHashTable, StockCode, Description, stoi(Quantity));

			}
						
		}
	}
}

void OnlineRetail::Add(int hashIndex, const string& stockCode, const string& description, const int& quantity) {

	auto p_count = 1;

	while (statusOfHashIndex[hashIndex] != false && HashTable[hashIndex] != stockCode && p_count < sizeOfHashTable)
	{
		hashIndex = (hashIndex+1)% sizeOfHashTable;
		p_count++;
	}
		
	HashTable[hashIndex] = stockCode;
	DescriptionArray[hashIndex] = description;
	QuantityArray[hashIndex] += quantity;
	statusOfHashIndex[hashIndex] = true;

}

void OnlineRetail::top10Analyzer() {
	
	cout << "Product(StockCode)" << "\t\tDescription" <<  "\t\t\t#TotalQuantity" << endl;

	for (int i = 0; i < 10; i++) {
		int topIndex = 0;
		int topQuantity = QuantityArray[0];

		for (int j = 0; j < sizeOfHashTable; j++) {

			if (QuantityArray[j] > topQuantity) {
				topQuantity = QuantityArray[j];

				topIndex = j;

			}
		}

		cout << i + 1 <<")  " << HashTable[topIndex] << "\t\t" << DescriptionArray[topIndex] << "\t\t\t" << topQuantity << endl;

		QuantityArray[topIndex] = 0;

	}
	
}
