#pragma once
#include <vector>
#include <string>
#include "property.h"

void merge(std::vector<Property>& properties, size_t left, size_t mid, size_t right, bool city);

void mergeSort(std::vector<Property>& properties, size_t left, size_t right, bool city);

size_t partitionValue(std::vector<Property>& properties, size_t low, size_t high);

void quickSortValue(std::vector<Property>& properties, size_t low, size_t high);

void insertProperty(std::vector<Property>& properties, const Property& newProperty);

void deleteProperty(std::vector<Property>& properties, const Property& newProperty);
