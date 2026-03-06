#pragma once

#include <functional>

template <typename T>
void iter(T *arrayAddress, const int arrayLength, void (*func)(T))
{
	for (int i = 0; i < arrayLength; i++)
		func(arrayAddress[i]);
};

template <typename T>
void iter(const T *arrayAddress, const int arrayLength, void (*func)(const T &))
{
	for (int i = 0; i < arrayLength; i++)
		func(arrayAddress[i]);
};
