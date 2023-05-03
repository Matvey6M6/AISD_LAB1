#include "tests.hpp"
#include "../BiTree/BiTree.hpp"
#include <time.h>
#include <vector>
#include <list>
#include <chrono>
#include <algorithm>
#include <iostream>
#include <fstream>

using namespace std;

size_t lcg()
{
	static size_t x = 0;
	x = (1021 * x + 24631) % 116640;
	return x;
}

float fill_time(int count)
{
	// int start = clock();
	auto start = chrono::high_resolution_clock::now();
	BiTree myTree;
	for (int i = 0; i < count; i++)
	{
		myTree.insert(lcg());
	}
	auto end = chrono::high_resolution_clock::now();
	// int end = clock();
	chrono::duration<float> result = end - start;
	return result.count();
}
float seek_time(int count)
{
	BiTree myTree;
	for (int i = 0; i < count; i++)
	{
		myTree.insert(lcg());
	}
	auto start = chrono::high_resolution_clock::now();
	for (int i = 0; i < 1000; i++)
	{
		myTree.contains(lcg());
	}
	auto end = chrono::high_resolution_clock::now();
	chrono::duration<float> result = end - start;
	return result.count() / 1000;
}
float insert_time(int count)
{
	BiTree myTree;
	for (int i = 0; i < count; i++)
	{
		myTree.insert(lcg());
	}
	auto start = chrono::high_resolution_clock::now();
	for (int i = 0; i < 1000; i++)
	{
		myTree.insert(lcg());
	}
	auto end = chrono::high_resolution_clock::now();
	chrono::duration<float> result = end - start;
	return result.count() / 1000;
}
float erase_time(int count)
{
	BiTree myTree;
	for (int i = 0; i < count; i++)
	{
		myTree.insert(lcg());
	}
	auto start = chrono::high_resolution_clock::now();
	for (int i = 0; i < 1000; i++)
	{
		myTree.erase(lcg());
	}
	auto end = chrono::high_resolution_clock::now();
	chrono::duration<float> result = end - start;
	return result.count() / 1000;
}

void speed_test_for_tree()
{
	ofstream out; // поток для записи
	out.open("../Test/speed_test_for_tree.txt");

	if (!out.is_open())
	{
		cout << "Can't open file! Change path." << endl;
		return;
	}

	cout << "speed_test_for_tree\n\n";
	double mid_value = 0;
	float fill_val;

	out << "filling" << endl;

	for (int i = 0; i < 100; i++)
	{
		fill_val = fill_time(1000);
		mid_value += fill_val;
	}
	cout << "Filling 1,000 elements: " << mid_value / 100 << endl;
	out << 1000 << ':' << mid_value / 100 << endl;

	mid_value = 0;
	for (int i = 0; i < 100; i++)
	{
		fill_val = fill_time(10000);
		mid_value += fill_val;
	}
	cout << "Filling 10,000 elements: " << mid_value / 100 << endl;
	out << 10000 << ':' << mid_value / 100 << endl;

	mid_value = 0;
	for (int i = 0; i < 100; i++)
	{
		fill_val = fill_time(100000);
		mid_value += fill_val;
	}
	cout << "Filling 100,000 elements: " << mid_value / 100 << endl
		 << endl;

	out << 100000 << ':' << mid_value / 100 << endl;

	mid_value = 0;

	/*for (int i = 0; i < 1000; i++)
	{
		fill_val = seek_time(1000);
		mid_value += fill_val;
	}*/
	cout << "=============================================================" << endl;
	out << "seeking" << endl;

	cout << "Seeking 1,000 elemnts: " << seek_time(1000) << endl;
	out << 1000 << ':' << seek_time(1000) << endl;

	cout << "Seeking 10,000 elements: " << seek_time(10000) << endl;
	out << 10000 << ':' << seek_time(10000) << endl;

	cout << "Seeking 100,000 elements: " << seek_time(100000) << endl
		 << endl;
	out << 100000 << ':' << seek_time(100000) << endl;

	cout << "=============================================================" << endl;
	out << "insert" << endl;

	cout << "Insert 1,000 elements: " << insert_time(1000) << endl;
	out << 1000 << ':' << insert_time(1000) << endl;

	cout << "Insert 10,000 elements: " << insert_time(10000) << endl;
	out << 10000 << ':' << insert_time(10000) << endl;

	cout << "Insert 100,000 elements: " << insert_time(100000) << endl
		 << endl;
	out << 100000 << ':' << insert_time(100000) << endl;

	cout << "=============================================================" << endl;
	out << "erase" << endl;

	cout << "Erasing 1,000 elements: " << erase_time(1000) << endl;
	out << 1000 << ':' << erase_time(1000) << endl;

	cout << "Erasing 10,000 elements: " << erase_time(10000) << endl;
	out << 10000 << ':' << erase_time(10000) << endl;

	cout << "Erasing 100,000 elements: " << erase_time(100000) << endl
		 << endl;
	out << 100000 << ':' << erase_time(100000) << endl;

	out.close();
}

float vec_fill(int count)
{
	vector<int> myV;
	auto start = chrono::high_resolution_clock::now();
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < count; j++)
		{ //
			myV.push_back(lcg());
		}
	}
	auto end = chrono::high_resolution_clock::now();
	chrono::duration<float> result = end - start;
	return result.count() / 100;
}
float vec_seek(int count)
{
	vector<int> myV;
	int mid_time = 0;
	for (int j = 0; j < count; j++)
	{
		myV.push_back(lcg());
	}
	mid_time = 0;
	auto start = chrono::high_resolution_clock::now();
	for (int i = 0; i < 1000; i++)
	{
		find(myV.begin(), myV.end(), lcg()) != myV.end();
	}
	auto end = chrono::high_resolution_clock::now();
	chrono::duration<float> result = end - start;
	return result.count() / 1000;
}

void speed_test_for_vector()
{
	ofstream out;
	out.open("../Test/speed_test_for_vector.txt");
	if (!out.is_open())
	{
		cout << "Can't open file! Change path." << endl;
		return;
	}

	cout << "speed_test_for_vector\n\n";
	out << "filling" << endl;

	cout << "Filling up 1000 elements: " << vec_fill(1000) << endl;
	out << 1000 << ':' << vec_fill(1000) << endl;

	cout << "Filling up 10000 elements: " << vec_fill(10000) << endl;
	out << 10000 << ':' << vec_fill(10000) << endl;

	cout << "Filling up 100000 elements: " << vec_fill(100000) << endl
		 << endl;
	out << 100000 << ':' << vec_fill(100000) << endl;

	cout << "=============================================================" << endl;
	out << "seeking" << endl;

	cout << "Seeking 1000 elements: " << vec_seek(1000) << endl;
	out << 1000 << ':' << vec_seek(1000) << endl;

	cout << "Seeking 10000 elements: " << vec_seek(10000) << endl;
	out << 10000 << ':' << vec_seek(10000) << endl;

	cout << "Seeking 100000 elements: " << vec_seek(100000) << endl
		 << endl;
	out << 100000 << ':' << vec_seek(100000) << endl;

	out.close();
}

void tests()
{
	speed_test_for_vector();
	speed_test_for_tree();
}