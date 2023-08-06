#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <algorithm>
#include "property.h"
#include "readCSV.h"
#include "sort.h"
#include "../lib/rapidcsv.h"


int main()
{
	readCSV read;
	std::string const path = "../AlachuaCountyHousingProject/data/NAL11F202201.csv";

	// Finds the time taken to read the CSV file and extract properties
	auto start = std::chrono::high_resolution_clock::now(); // Starts timer
	std::vector<Property> properties = read.CSVread(path);
	auto end = std::chrono::high_resolution_clock::now(); // Ends timer
	auto fileReadTime = std::chrono::duration_cast<std::chrono::seconds>(end - start).count(); // Finds time taken

	std::cout << properties.size() << " properties extracted from file in " << fileReadTime << " seconds." << std::endl;


	// Prints the last Property in the vector
	if (!properties.empty())
	{
		std::cout << std::endl;
		const Property& last = properties.back();
		std::cout << "Property Type: " << last.getPropertyType() << std::endl;
		std::cout << "Value: " << last.getMarketValue() << std::endl;
		std::cout << "Year: " << last.getYearBuilt() << std::endl;
		std::cout << "Address: " << last.getAddress() << std::endl;
		std::cout << "City: " << last.getCity() << std::endl;
		std::cout << "ZIP: " << last.getZipCode() << std::endl;
		std::cout << std::endl;
	}

	/*********************************************************************************/
	/*                    Comparing Merge Sort vs Standard Sort                      */
	/*                //Sorts Vector By City in Alphabetical Order//                 */
	/*********************************************************************************/
	
	// Find the time taken by Merge Sort to sort the vector by city O(n log n)
	std::vector<Property> mergeCitySortProperties = properties;
	start = std::chrono::high_resolution_clock::now(); // Starts timer
	mergeSort(mergeCitySortProperties, 0, mergeCitySortProperties.size() - 1, true);
	end = std::chrono::high_resolution_clock::now(); // Ends timer
	auto mergeSortCityTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count(); // Finds time taken
	std::cout << "Merge Sort by City Time: " << mergeSortCityTime << " milliseconds." << std::endl;

	// Finds the time taken by Standard Sort (std::sort) to sort the vector by city O(n log n)
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

	// Finds the time taken by Merge Sort to sort the vector by market value O(n log n)
	std::vector<Property> mergeValueSortProperties = properties;
	start = std::chrono::high_resolution_clock::now(); // Starts timer
	mergeSort(mergeValueSortProperties, 0, mergeValueSortProperties.size() - 1, false);
	end = std::chrono::high_resolution_clock::now(); // Ends timer
	auto mergeSortValueTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count(); // Finds time taken
	std::cout << "Merge Sort by Market Value Time: " << mergeSortValueTime << " milliseconds." << std::endl;

	// Finds the time taken by Quick Sort to sort vector by market value O(n^2)
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

	// Finds the Insertion time of Lower_Bound Insertion O(n)
	start = std::chrono::high_resolution_clock::now(); // Starts timer
	insertProperty(mergeValueSortProperties, newProperty);
	end = std::chrono::high_resolution_clock::now(); // Ends timer
	auto customInsertTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count(); // Finds time taken
	std::cout << "Custom Insert Time: " << customInsertTime << " milliseconds." << std::endl;

	// Finds the Insertion time of standard push_back and sort insertion O(n log n)
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
	
	// Finds the Deletion time of Lower_Bound Deletion O(n)
	start = std::chrono::high_resolution_clock::now(); // Starts timer
	deleteProperty(mergeValueSortProperties, newProperty); // Searches for and deletes the Property that was just added in customProperties vector
	end = std::chrono::high_resolution_clock::now(); // Ends timer
	auto customDeleteTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count(); // Finds time taken
	std::cout << "Custom Delete Time: " << customDeleteTime << " milliseconds." << std::endl;

	// // Finds the Deletion time of Standard Remove O(n)
	start = std::chrono::high_resolution_clock::now(); // Starts timer
	auto it = std::remove(quickValueSortProperties.begin(), quickValueSortProperties.end(), newProperty);
	quickValueSortProperties.resize(std::distance(quickValueSortProperties.begin(), it));
	end = std::chrono::high_resolution_clock::now(); // Ends timer
	auto stdDeleteTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count(); // Finds time taken
	std::cout << "Standard Delete Time: " << stdDeleteTime << " milliseconds." << std::endl;
	
	
	return 0;
}