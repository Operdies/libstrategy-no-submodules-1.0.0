/* 
 * Copyright (C) 2016  Peter G. Jensen <root@petergjoel.dk>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
// Created by Peter G. Jensen on 12/9/16.
#define BOOST_TEST_MODULE PTrieMap
#include <boost/test/unit_test.hpp>

#include <ptrie_map.h>

#include <vector>
#include "utils.h"

using namespace ptrie;
using namespace std;

BOOST_AUTO_TEST_CASE(PseudoRand1)
{
    for(size_t seed = 314; seed < (314+10); ++seed) {
        ptrie::map<size_t> set;

        for(size_t i = 0; i < 1024*10; ++i) {
            binarywrapper_t data = rand_data(i + seed, 20);
            auto res = set.insert(data);
            BOOST_CHECK(res.first);
            set.get_data(res.second) = i;
            data.release();
        }

        // let us unwrap everything and check that it is there!

        for(size_t i = 0; i < 1024*10; ++i) {
            binarywrapper_t data = rand_data(i + seed, 20);
            auto res = set.exists(data);
            BOOST_CHECK(res.first);
            BOOST_CHECK_EQUAL(set.get_data(res.second), i);
            data.release();
        }
    }
}

BOOST_AUTO_TEST_CASE(PseudoRandSplitHeap)
{
    for(size_t seed = 512; seed < (512+10); ++seed) {
        ptrie::map<size_t,sizeof(size_t ) + 1, 4> set;
        for(size_t i = 0; i < 1024*10; ++i) {
            binarywrapper_t data = rand_data(i + seed, 20);
            auto res = set.insert(data);
            BOOST_CHECK(res.first);
            set.get_data(res.second) = i;
            data.release();
        }

        // let us unwrap everything and check that it is there!

        for(size_t i = 0; i < 1024*10; ++i) {
            binarywrapper_t data = rand_data(i + seed, 20);
            auto res = set.exists(data);
            BOOST_CHECK(res.first);
            BOOST_CHECK_EQUAL(set.get_data(res.second), i);
            data.release();
        }
    }
}