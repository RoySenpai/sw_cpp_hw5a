/*
 *  Software Systems CPP Course Assignment 5
 *  Copyright (C) 2023  Roy Simanovich
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "doctest.h"
#include "sources/MagicalContainer.hpp"
#include <iostream>

using namespace std;
using namespace ariel;

TEST_CASE("Test 1 - MagicalContainer::addElement and MagicalContainer::removeElement") {
	MagicalContainer mc;
	CHECK_EQ(mc.size(), 0);

	mc.addElement(1);
	CHECK_EQ(mc.size(), 1);

	mc.addElement(2);
	mc.addElement(3);

	CHECK_EQ(mc.size(), 3);

	mc.removeElement(2);
	CHECK_EQ(mc.size(), 2);

	mc.removeElement(1);
	mc.removeElement(3);

	CHECK_EQ(mc.size(), 0);
}

TEST_CASE("Test 2 - Iterator Sorted") {
	MagicalContainer mc;
	mc.addElement(3);
	mc.addElement(4);
	mc.addElement(2);

	MagicalContainer::AscendingIterator ascIter(mc);

	CHECK_EQ(*ascIter, 2);
	++ascIter;
	CHECK_EQ(*ascIter, 3);
	++ascIter;
	CHECK_EQ(*ascIter, 4);
	++ascIter;
	CHECK_EQ(ascIter, ascIter.end());
}

TEST_CASE("Test 3 - Iterator SideCross") {
	MagicalContainer mc;
	mc.addElement(3);
	mc.addElement(4);
	mc.addElement(2);

	MagicalContainer::SideCrossIterator crossIter(mc);

	CHECK_EQ(*crossIter, 2);
	++crossIter;
	CHECK_EQ(*crossIter, 4);
	++crossIter;
	CHECK_EQ(*crossIter, 3);
	++crossIter;
	CHECK_EQ(crossIter, crossIter.end());
}

TEST_CASE("Test 4 - Iterator Prime") {
	MagicalContainer mc;
	mc.addElement(3);
	mc.addElement(4);
	mc.addElement(2);

	MagicalContainer::PrimeIterator primesIter(mc);

	CHECK_EQ(*primesIter, 2);
	++primesIter;
	CHECK_EQ(*primesIter, 3);
	++primesIter;
	CHECK_EQ(primesIter, primesIter.end());
}

TEST_CASE("Test 5 - Check iterators comparison") {
	MagicalContainer mc;
	mc.addElement(3);
	mc.addElement(4);
	mc.addElement(2);

	MagicalContainer::AscendingIterator ascIter1(mc);
	MagicalContainer::AscendingIterator ascIter2(mc);
	MagicalContainer::SideCrossIterator crossIter1(mc);
	MagicalContainer::SideCrossIterator crossIter2(mc);
	MagicalContainer::PrimeIterator primesIter1(mc);
	MagicalContainer::PrimeIterator primesIter2(mc);

	CHECK_EQ(ascIter1, ascIter2);
	CHECK_EQ(crossIter1, crossIter2);
	CHECK_EQ(primesIter1, primesIter2);

	++ascIter1;
	++crossIter1;
	++primesIter1;
	
	CHECK_NE(ascIter1, ascIter2);
	CHECK_GT(ascIter1, ascIter2);
	CHECK_LT(ascIter2, ascIter1);

	CHECK_NE(crossIter1, crossIter2);
	CHECK_GT(crossIter1, crossIter2);
	CHECK_LT(crossIter2, crossIter1);

	CHECK_NE(primesIter1, primesIter2);
	CHECK_GT(primesIter1, primesIter2);
	CHECK_LT(primesIter2, primesIter1);

	++ascIter2;
	++crossIter2;
	++primesIter2;

	CHECK_EQ(ascIter1, ascIter2);
	CHECK_EQ(crossIter1, crossIter2);
	CHECK_EQ(primesIter1, primesIter2);
}