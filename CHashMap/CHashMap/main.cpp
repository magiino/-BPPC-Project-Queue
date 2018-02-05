//
//  main.cpp
//  CHashMap
//
//  Created by Petr Petyovsky on 21/09/2017.
//  Copyright (c) 2017 Petr Petyovsky. All rights reserved.
//  $Id: main.cpp 2 2017-11-06 10:01:25Z petyovsky $

#include <iostream>
#include "CHashMap.h"

using namespace std;

int main()
	{
	ostringstream oss;
	oss << "(#99," << CValue::TestStringValue1() << ')';
	CPair p(oss.str().c_str());
	cout << p << endl;
	CHashMap map;
	cout << '#'<< map.ID() << endl;
		{
		CHashMap map1;
		cout << '#'<< map1.ID() << endl;
		CHashMap map2(std::move(map1));
		cout << '#'<< map1.ID() << endl;
		cout << '#'<< map2.ID() << endl;
		map = std::move(map2);
		}

	map.Insert( {0, CValue(CValue::TestValueRandom())} );
	map.Insert(p);
	map.Insert( {0, CValue(CValue::TestValueRandom())} , CHashMap::TInsert::EBeforeFirstKeyDuplicity);
	map.Insert( {0, CValue(CValue::TestValueRandom())} , CHashMap::TInsert::EBeforeFirstKeyDuplicity);
	map.Insert( {0, CValue(CValue::TestValueRandom())} , CHashMap::TInsert::EAfterLastKeyDuplicity);
	map.Insert( {1, CValue(CValue::TestValueRandom())} , CHashMap::TInsert::EUniqueKey);
	map.Insert( {256, CValue(CValue::TestValueRandom())} );
	map.Insert( {1, CValue(CValue::TestValueRandom())} , CHashMap::TInsert::EBeforeFirstKeyDuplicity);
	map.Insert( {1, CValue(CValue::TestValueRandom())} , CHashMap::TInsert::EByPair);
	map.Insert( {1, CValue(CValue::TestValueRandom())} , CHashMap::TInsert::EAfterLastKeyDuplicity);
	map.Insert( {1, CValue(CValue::TestValueRandom())} , CHashMap::TInsert::EBeforeFirstKeyDuplicity);
	map.Insert( {1, CValue(CValue::TestValueRandom())} , CHashMap::TInsert::EByPair);
	map.Insert( {1, CValue(CValue::TestValueRandom())} , CHashMap::TInsert::EByPair);
	map.Insert( {1, CValue(CValue::TestValueRandom())} , CHashMap::TInsert::EByPair);
	map.Insert( {256, CValue(CValue::TestValue1()) }, CHashMap::TInsert::EByPair);
	auto it = map.Insert({0, CValue(CValue::TestValue0())}, CHashMap::TInsert::EByPair);
	for(CHashMap::CForwardIterator iter = it; iter; ++iter)
		cout << "(#" << iter->Key() << ", " << iter->Value() << ')' << endl;
	cout << "Remove ------------------------------------------------------------" << endl;

	for(const auto &i: map)
		cout << i << ", ";
	cout << endl;
	map.Erase(it);
	for(const auto &i: map)
		cout << i << ", ";
	cout << endl;

	map.Erase(it);
	it = map.At({256,CValue(CValue::TestValue1())});
	map.Erase(it);
	map.Erase(it);
	for(const auto &i: map)
		cout << i << ", ";
	cout << endl;
	cout << "------------------------------------------------------------" << endl;
	
	auto it2 = map.Insert({0, CValue(CValue::TestValue0())}, CHashMap::TInsert::EByPair);
	for(CHashMap::CForwardIterator iter = it2; iter; ++iter)
		cout << "(#" << iter->Key() << ", " << iter->Value() << ')' << endl;

	cout << "------------------------------------------------------------" << endl;
	for(CHashMap::CForwardIterator iter = map.At(256, CHashMap::TAt::ELastDuplicity); iter; ++iter)
		cout << "(#" << iter->Key() << ", " << iter->Value() << ')' << endl;
	cout << "Count(0): " << map.Count(0) << endl;
	cout << "Count(1): " << map.Count(1) << endl;
	cout << "Count(CPair(0, 0)): " << map.Count(CPair(0, CValue(CValue::TestValue0()))) << endl;
	cout << "TotalCount: " << map.Count() << endl;

	cout << "Map:" << endl;
	for(CHashMap::CForwardIterator iter = map.begin(); iter; ++iter)
		cout << "(#" << iter->Key() << ", " << iter->Value() << ')' << endl;

	cout << endl;

	cout << "Count(0): " << map.Count(0) << endl;
	auto i = map.Erase(map.At(0));
	cout << "Pair: " << *i << endl;
	cout << "Count(0): " << map.Count(0) << endl;
	
	cout << "Map:" << endl;
	for(CHashMap::CForwardIterator iter = map.begin(); iter; ++iter)
		cout << "(#" << iter->Key() << ", " << iter->Value() << ')' << endl;

	cout << "TotalCount: " << map.Count() << endl;
	map.Clear();
	cout << "TotalCount: " << map.Count() << endl;
	cout << "Count(0): " << map.Count(0) << endl;

	cout << "------------------------------------------------------------" << endl;
	CHashMap map1;
	CHashMap map2;
	map1.Insert( {1, CValue(CValue::TestValueRandom())}, CHashMap::TInsert::EBeforeFirstKeyDuplicity);
	map1.Insert( {1, CValue(CValue::TestValueRandom())}, CHashMap::TInsert::EBeforeFirstKeyDuplicity);
	map1.Insert( {1, CValue(CValue::TestValueRandom())}, CHashMap::TInsert::EBeforeFirstKeyDuplicity);

	map2.Insert( {1, CValue(CValue::TestValueRandom())}, CHashMap::TInsert::EBeforeFirstKeyDuplicity);
	map2.Insert( {1, CValue(CValue::TestValueRandom())}, CHashMap::TInsert::EBeforeFirstKeyDuplicity);
	map2.Insert( {1, CValue(CValue::TestValueRandom())}, CHashMap::TInsert::EBeforeFirstKeyDuplicity);
	cout << "Map1:" << endl;
	for(CHashMap::CForwardIterator iter = map1.begin(); iter; ++iter)
		cout << "(#" << iter->Key() << ", " << iter->Value() << ')' << endl;

	cout << "Map2:" << endl;
	for(CHashMap::CForwardIterator iter = map2.begin(); iter; ++iter)
	cout << "(#" << iter->Key() << ", " << iter->Value() << ')' << endl;

	for(CHashMap::CForwardIterator iter = map1.begin(); iter; ++iter)
		cout << "(#" << iter->Key() << ", " << iter->Value() << ')' << endl;

	//for(auto i = map1.begin(), end = map1.end(); i != end; ++i)
	//    cout << "(#"  << i.Key() << ", " << *i << ')' << endl;
	for(const auto &i: map1)
		cout << "(#" << i.Key() << ", " << i.Value() << ')' << endl;

	for(const auto &i: map1)
		cout << i << endl;
	
	return 0;
	}
