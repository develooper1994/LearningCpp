#pragma once

#include <iostream>
#include <iosfwd>
#include <string>
#include <vector>
#include <array>
#include <algorithm>
#include <random>
#include <chrono>
#include <typeinfo>
#include <type_traits>

using std::vector;
using std::array;
using std::cout;
using std::ostream;

//template<typename T, char deliminator = ',', int maxLineWidth = 16>
//std::ostream operator<<(std::ostream& out, const std::vector<T>& vec) {
//	out << "{";
//
//	size_t last = vec.size() - 1;
//	for (size_t i = 0; i < vec.size(); i++) {
//		out << vec[i];
//		if (i != last)
//			out << ", ";
//		if (i % maxLineWidth == maxLineWidth - 1)
//			out << '\n';
//	}
//
//	out << "}";
//}
//
//template<typename T, int size, char deliminator = ',', int maxLineWidth = 16>
//std::ostream operator<<(std::ostream& out, const std::array<T, size>& vec) {
//	out << "{";
//
//	size_t last = size - 1;
//	for (size_t i = 0; i < vec.size(); i++) {
//		out << vec[i];
//		if (i != last)
//			out << ", ";
//		if (i % maxLineWidth == maxLineWidth - 1)
//			out << '\n';
//	}
//
//	out << "}";
//}
//
//template<typename T, int size, char deliminator = ',', int maxLineWidth = 16>
//std::ostream& operator<< (std::ostream& out, const T(&v)[size]) {
//	out << '{';
//	size_t last = size - 1;
//	for (size_t i = 0; i < size; ++i) {
//		out << v[i];
//		if (i != last)
//			out << deliminator << ' ';
//		if (i % maxLineWidth == maxLineWidth - 1)
//			out << '\n';
//	}
//	out << '}';
//	return out;
//}

void Lambda_Main();
