#include "property.h"

Property::Property()
    : marketValue(0), zipCode(0), yearBuilt(0), address(""), city(""), propertyType("") {}

Property::Property(int MARKETVALUE, int ZIPCODE, int YEARBUILT, std::string ADDRESS, std::string CITY, std::string PROPERTYTYPE)
    : marketValue(MARKETVALUE), zipCode(ZIPCODE), yearBuilt(YEARBUILT), address(ADDRESS), city(CITY), propertyType(PROPERTYTYPE) {};

bool Property::operator==(const Property& other) const
{
    return marketValue == other.marketValue &&
        zipCode == other.zipCode &&
        yearBuilt == other.yearBuilt &&
        address == other.address &&
        city == other.city &&
        propertyType == other.propertyType;
}

int Property::getMarketValue() const
{
    return marketValue;
}

void Property::setMarketValue(int newMarketValue)
{
    marketValue = newMarketValue;
}

int Property::getZipCode() const
{
    return zipCode;
}

void Property::setZipCode(int newZipCode)
{
    zipCode = newZipCode;
}

int Property::getYearBuilt() const
{
    return yearBuilt;
}

void Property::setYearBuilt(int newYearBuilt)
{
    yearBuilt = newYearBuilt;
}

std::string Property::getAddress() const
{
    return address;
}

void Property::setAddress(const std::string& newAddress)
{
    address = newAddress;
}

std::string Property::getCity() const
{
    return city;
}

void Property::setCity(const std::string& newCity)
{
    city = newCity;
}

std::string Property::getPropertyType() const
{
    return propertyType;
}

void Property::setPropertyType(const std::string& newPropertyType)
{
    propertyType = newPropertyType;
}