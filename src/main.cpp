#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <algorithm>
#include "property.h"
#include "readCSV.h"
#include "sort.h"

int main()
{
	readCSV read;
	std::string const path = "NAL11F202201.csv";

	auto start = std::chrono::high_resolution_clock::now();
	std::vector<Property> properties = read.CSVread(path);
	auto end = std::chrono::high_resolution_clock::now();
	auto fileReadTime = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();

	std::cout << properties.size() << " properties extracted from file in " << fileReadTime << " seconds." << std::endl;


	/*********************************************************************************/
	/*                    Comparing Merge Sort vs Standard Sort                      */
	/*                //Sorts Vector By City in Alphabetical Order//                 */
	/*********************************************************************************/
	
	std::vector<Property> mergeCitySortProperties = properties;
	start = std::chrono::high_resolution_clock::now(); // Starts timer
	mergeSort(mergeCitySortProperties, 0, mergeCitySortProperties.size() - 1, true);
	end = std::chrono::high_resolution_clock::now(); // Ends timer
	auto mergeSortCityTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count(); // Finds time taken
	std::cout << "Merge Sort by City Time: " << mergeSortCityTime << " milliseconds." << std::endl;

	std::vector<Property> propertiesForStdSort = properties;
	start = std::chrono::high_resolution_clock::now(); // Starts timer
	std::sort(propertiesForStdSort.begin(), propertiesForStdSort.end(), [](const Property& a, const Property& b)
		{
			return a.getCity() < b.getCity();
		});
	end = std::chrono::high_resolution_clock::now(); // Ends timer
	auto stdSortTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count(); // Finds time taken
	std::cout << "Standard Sort by City Time : " << stdSortTime << " milliseconds." << std::endl;
	

	/*********************************************************************************/
	/*                     Comparing Merge Sort vs Quick Sort                        */
	/*             //Sorts Vector by Market Value in Ascending Order//               */
	/*********************************************************************************/
	std::vector<Property> mergeValueSortProperties = properties;
	start = std::chrono::high_resolution_clock::now(); // Starts timer
	mergeSort(mergeValueSortProperties, 0, mergeValueSortProperties.size() - 1, false);
	end = std::chrono::high_resolution_clock::now(); // Ends timer
	auto mergeSortValueTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count(); // Finds time taken
	std::cout << "Merge Sort by Market Value Time: " << mergeSortValueTime << " milliseconds." << std::endl;

	std::vector<Property> quickValueSortProperties = properties;
	start = std::chrono::high_resolution_clock::now(); // Starts timer
	quickSortValue(quickValueSortProperties, 0, quickValueSortProperties.size() - 1);
	end = std::chrono::high_resolution_clock::now(); // Ends timer
	auto quickSortValueTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count(); // Finds time taken
	std::cout << "Quick Sort by Market Value Time: " << quickSortValueTime << " milliseconds." << std::endl;


	/*********************************************************************************/
	/*             Comparing Lower_Bound Insertion vs Standard Insertion             */
	/*                                                                               */
	/*********************************************************************************/

	Property newProperty(150000, 111111, 2000, "123 Street", "Gainesville", "Residential"); // Property that will be inserted in the vector

	//std::vector<Property> customProperties = properties; // Vector that will be used to store Lower_Bound Insert
	start = std::chrono::high_resolution_clock::now(); // Starts timer
	insertProperty(mergeValueSortProperties, newProperty);
	end = std::chrono::high_resolution_clock::now(); // Ends timer
	auto customInsertTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count(); // Finds time taken
	std::cout << "Custom Insert Time: " << customInsertTime << " milliseconds." << std::endl;

	//std::vector<Property> standardProperties = properties; // Vector that will be used to store the Standard Insert
	start = std::chrono::high_resolution_clock::now(); // Starts timer
	quickValueSortProperties.push_back(newProperty);
	std::sort(quickValueSortProperties.begin(), quickValueSortProperties.end(), [](const Property& a, const Property& b)
		{
			return a.getMarketValue() < b.getMarketValue();
		});
	end = std::chrono::high_resolution_clock::now(); // Ends timer
	auto stdInsertTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count(); // Finds time taken
	std::cout << "Standard Insert Time: " << stdInsertTime << " milliseconds." << std::endl;


	/*********************************************************************************/
	/*             Comparing Lower_Bound Deletion vs Standard Deletion               */
	/*                                                                               */
	/*********************************************************************************/
	
	start = std::chrono::high_resolution_clock::now(); // Starts timer
	deleteProperty(mergeValueSortProperties, newProperty); // Searches for and deletes the Property that was just added in customProperties vector
	end = std::chrono::high_resolution_clock::now(); // Ends timer
	auto customDeleteTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count(); // Finds time taken
	std::cout << "Custom Delete Time: " << customDeleteTime << " microseconds." << std::endl;

	start = std::chrono::high_resolution_clock::now(); // Starts timer
	auto it = std::remove(quickValueSortProperties.begin(), quickValueSortProperties.end(), newProperty);
	quickValueSortProperties.resize(std::distance(quickValueSortProperties.begin(), it));
	end = std::chrono::high_resolution_clock::now(); // Ends timer
	auto stdDeleteTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count(); // Finds time taken
	std::cout << "Standard Delete Time: " << stdDeleteTime << " microseconds." << std::endl;
	
	/*
	for (const auto& it : mergeCitySortProperties)
	{
		std::cout << "Property Type: " << it.getPropertyType() << std::endl;
		std::cout << "Value: " << it.getMarketValue() << std::endl;
		std::cout << "Year: " << it.getYearBuilt() << std::endl;
		std::cout << "Address: " << it.getAddress() << std::endl;
		std::cout << "City: " << it.getCity() << std::endl;
		std::cout << "ZIP: " << it.getZipCode() << std::endl;
		std::cout << "------------------" << std::endl;
	}
	*/

	return 0;
}