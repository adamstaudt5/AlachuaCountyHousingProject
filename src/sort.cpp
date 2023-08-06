#include <vector>
#include <string>
#include <stack>
#include <algorithm>
#include "property.h"
#include "sort.h"

void merge(std::vector<Property>& properties, size_t left, size_t mid, size_t right, bool city)
{
    size_t n1 = mid - left + 1; // Calculates the size of the first subvector
    size_t n2 = right - mid; // Calculate the size of the second subvector

    std::vector<Property> leftSplit(n1);
    std::vector<Property> rightSplit(n2);

    // Copies data from properties to the subvectors
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

    // Merges the two subvectors
    while (i < n1 && j < n2)
    {
        // If city = true, we are sorting alphabetically by city
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

    // If any remaining elements are left copy them to left subvector
    while (i < n1)
    {
        properties[k] = leftSplit[i];
        i++;
        k++;
    }

    // If any remaining elements are left copy them to right subvector
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
        size_t mid = left + (right - left) / 2; // Finds middle index
        mergeSort(properties, left, mid, city); // Sorts left subvector
        mergeSort(properties, mid + 1, right, city); // Sorts right subvector

        merge(properties, left, mid, right, city); // Merges the two together
    }
}


size_t partitionValue(std::vector<Property>& properties, size_t low, size_t high)
{
    Property pivot = properties[high]; // Chooses the pivot as the last element
    size_t i = low;

    // Makes elements smaller than pivot go left and larger than pivot go right
    for (size_t j = low; j < high; j++)
    {
        if (properties[j].getMarketValue() <= pivot.getMarketValue())
        {
            std::swap(properties[i], properties[j]);
            i++;
        }
    }

    // Moves pivot to correct position
    std::swap(properties[i], properties[high]);
    return i;
}

void quickSortValue(std::vector<Property>& properties, size_t low, size_t high)
{
    if (low < high)
    {
        size_t pivot = partitionValue(properties, low, high); // Gets the pivot
        if (pivot > 0)
        {
            quickSortValue(properties, low, pivot - 1); // Sorts left subvector
        }
        quickSortValue(properties, pivot + 1, high); // Sorts right
    }
}

void insertProperty(std::vector<Property>& properties, const Property& newProperty)
{
    // Automatically adds property to end if vector empty or larger than last value
    if (properties.empty() || newProperty.getMarketValue() >= properties.back().getMarketValue())
    {
        properties.push_back(newProperty);
        return;
    }

    // Uses lower_bound to find a position to insert
    auto it = std::lower_bound(properties.begin(), properties.end(), newProperty,
        [](const Property& a, const Property& b) {
            return a.getMarketValue() < b.getMarketValue();
        });

    properties.insert(it, newProperty);
}

void deleteProperty(std::vector<Property>& properties, const Property& newProperty)
{
    // Use lower_bound to find the position in the sorted vector
    auto it = std::lower_bound(properties.begin(), properties.end(), newProperty,
        [](const Property& a, const Property& b) 
        {
            return a.getMarketValue() < b.getMarketValue();
        });

    // Check if the element is found and equal to the target
    if (it != properties.end() && *it == newProperty) 
    {
        // Deletes the element
        properties.erase(it);
    }
}