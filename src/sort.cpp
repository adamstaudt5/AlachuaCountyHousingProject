#include <vector>
#include <string>
#include <stack>
#include <algorithm>
#include "property.h"
#include "sort.h"

void merge(std::vector<Property>& properties, size_t left, size_t mid, size_t right, bool city)
{
    size_t n1 = mid - left + 1;
    size_t n2 = right - mid;

    std::vector<Property> leftSplit(n1);
    std::vector<Property> rightSplit(n2);

    for (size_t i = 0; i < n1; i++)
    {
        leftSplit[i] = properties[left + i];
    }
    for (size_t j = 0; j < n2; j++)
    {
        rightSplit[j] = properties[mid + 1 + j];
    }

    size_t i = 0;
    size_t j = 0;
    size_t k = left;

    while (i < n1 && j < n2)
    {
        if (city)
        {
            if (leftSplit[i].getCity() <= rightSplit[j].getCity())
            {
                properties[k] = leftSplit[i];
                i++;
            }
            else
            {
                properties[k] = rightSplit[j];
                j++;
            }
        }
        else
        {
            if (leftSplit[i].getMarketValue() <= rightSplit[j].getMarketValue())
            {
                properties[k] = leftSplit[i];
                i++;
            }
            else
            {
                properties[k] = rightSplit[j];
                j++;
            }
        }
        k++;
    }

    while (i < n1)
    {
        properties[k] = leftSplit[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        properties[k] = rightSplit[j];
        j++;
        k++;
    }
}

void mergeSort(std::vector<Property>& properties, size_t left, size_t right, bool city)
{
    if (left < right)
    {
        size_t mid = left + (right - left) / 2;
        mergeSort(properties, left, mid, city);
        mergeSort(properties, mid + 1, right, city);

        merge(properties, left, mid, right, city);
    }
}


size_t partitionValue(std::vector<Property>& properties, size_t low, size_t high)
{
    Property pivot = properties[high];
    size_t i = low;

    for (size_t j = low; j < high; j++)
    {
        if (properties[j].getMarketValue() <= pivot.getMarketValue())
        {
            std::swap(properties[i], properties[j]);
            i++;
        }
    }

    std::swap(properties[i], properties[high]);
    return i;
}

void quickSortValue(std::vector<Property>& properties, size_t low, size_t high)
{
    if (low < high)
    {
        size_t pivot = partitionValue(properties, low, high);
        if (pivot > 0)
            quickSortValue(properties, low, pivot - 1);
        quickSortValue(properties, pivot + 1, high);
    }
}

void insertProperty(std::vector<Property>& properties, const Property& newProperty)
{
    if (properties.empty() || newProperty.getMarketValue() >= properties.back().getMarketValue())
    {
        properties.push_back(newProperty);
        return;
    }

    auto it = std::lower_bound(properties.begin(), properties.end(), newProperty,
        [](const Property& a, const Property& b) {
            return a.getMarketValue() < b.getMarketValue();
        });

    properties.insert(it, newProperty);
}

void deleteProperty(std::vector<Property>& properties, const Property& newProperty)
{
    auto it = std::lower_bound(properties.begin(), properties.end(), newProperty,
        [](const Property& a, const Property& b) 
        {
            return a.getMarketValue() < b.getMarketValue();
        });

    // Check if the element is found and equal to the target
    if (it != properties.end() && *it == newProperty) 
    {
        // Erase the element from the vector
        properties.erase(it);
    }
}