#include <string>
#include <vector>
#include "property.h"
#include "readCSV.h"
#include "../lib/rapidcsv.h"

namespace rapidcsv
{
	// This section works with the GetColumn function so that if a cell is empty, the value is stored as 0
	template<>
	void Converter<int>::ToVal(const std::string& pStr, int& pVal) const
	{
		if (pStr == "")
			pVal = 0;
		else
			pVal = std::stoi(pStr);
	}
}

// Function that reads a CSV file and converts it to vector of Property
std::vector<Property> readCSV::CSVread(const std::string& filepath)
{
	std::vector<Property> properties;

	rapidcsv::Document csv(filepath);

	// Extract each column from the CSV with these specific titles and stores them in seperate vectors
	const auto& propertyTypeValue = csv.GetColumn<int>("DOR_UC");
	const auto& marketValue = csv.GetColumn<int>("JV");
	const auto& yearBuiltValue = csv.GetColumn<int>("ACT_YR_BLT");
	const auto& addressValue = csv.GetColumn<std::string>("PHY_ADDR1");
	const auto& cityValue = csv.GetColumn<std::string>("PHY_CITY");
	const auto& zipCodeValue = csv.GetColumn<int>("PHY_ZIPCD");

	// Every row has a propertyTypeValue, so it is safe to use as numRows
	size_t numRows = propertyTypeValue.size();

	std::vector<std::string> propertyType(numRows);
	std::vector<int> yearBuilt(numRows);
	std::vector<std::string> address(numRows);
	std::vector<std::string> city(numRows);
	std::vector<int> zipCode(numRows);

	// Loops through the rows and converts the Land Code Values to their actual types
	for (size_t i = 0; i < numRows; i++)
	{
		if (propertyTypeValue[i] != 3 && propertyTypeValue[i] <= 9)
		{
			propertyType[i] = "Residential";
		}
		else if (propertyTypeValue[i] == 3)
		{
			propertyType[i] = "Apartment Complex";
		}
		else if (propertyTypeValue[i] >= 10 && propertyTypeValue[i] <= 39)
		{
			propertyType[i] = "Commercial";
		}
		else if (propertyTypeValue[i] >= 40 && propertyTypeValue[i] <= 49)
		{
			propertyType[i] = "Industrial";
		}
		else if (propertyTypeValue[i] >= 50 && propertyTypeValue[i] <= 69)
		{
			propertyType[i] = "Agricultural";
		}
		else if (propertyTypeValue[i] >= 70 && propertyTypeValue[i] <= 79)
		{
			propertyType[i] = "Institutional";
		}
		else if (propertyTypeValue[i] >= 80 && propertyTypeValue[i] <= 89)
		{
			propertyType[i] = "Governmental";
		}
		else
		{
			propertyType[i] = "Miscellaneous";
		}

		// If address is not available (farmland,lumberyard,etc.) store it as N/A
		if (!addressValue[i].empty())
		{
			address[i] = addressValue[i];
		}
		else
		{
			address[i] = "N/A";
		}

		// If city is not available store it as N/A
		if (!cityValue[i].empty())
		{
			city[i] = cityValue[i];
		}
		else
		{
			city[i] = "N/A";
		}

		// Create property object with all extracted values and add it to the return vector
		properties.push_back(Property(marketValue[i], zipCodeValue[i], yearBuiltValue[i], address[i], city[i], propertyType[i]));

	}

	return properties;
}
