// --------------------------------------------------------------------------
//                   OpenMS -- Open-Source Mass Spectrometry               
// --------------------------------------------------------------------------
// Copyright The OpenMS Team -- Eberhard Karls University Tuebingen,
// ETH Zurich, and Freie Universitaet Berlin 2002-2013.
// 
// This software is released under a three-clause BSD license:
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//  * Neither the name of any author or any participating institution 
//    may be used to endorse or promote products derived from this software 
//    without specific prior written permission.
// For a full list of authors, refer to the file AUTHORS. 
// --------------------------------------------------------------------------
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL ANY OF THE AUTHORS OR THE CONTRIBUTING 
// INSTITUTIONS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR 
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
// ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// 
// --------------------------------------------------------------------------
// $Maintainer: Lars Nilse $
// $Authors: Lars Nilse $
// --------------------------------------------------------------------------

#include <OpenMS/CONCEPT/ClassTest.h>
#include <OpenMS/test_config.h>

#include <OpenMS/FILTERING/DATAREDUCTION/FilterResult.h>
#include <OpenMS/FILTERING/DATAREDUCTION/FilterResultRaw.h>
#include <OpenMS/FILTERING/DATAREDUCTION/FilterResultPeak.h>

using namespace OpenMS;

START_TEST(FilterResult, "$Id$")

std::vector<double> mz_shifts;
mz_shifts.push_back(0);
mz_shifts.push_back(0.501677);
mz_shifts.push_back(3.01591);
mz_shifts.push_back(3.51759);

std::vector<double> intensities;
intensities.push_back(1789.0714);
intensities.push_back(1492.1012);
intensities.push_back(333.1105);
intensities.push_back(325.0520);

std::vector<FilterResultRaw> results_raw;
FilterResultRaw result1_raw(816.6, mz_shifts, intensities);
results_raw.push_back(result1_raw);
FilterResultRaw result2_raw(817.1, mz_shifts, intensities);
results_raw.push_back(result2_raw);
FilterResultRaw result3_raw(817.2, mz_shifts, intensities);
results_raw.push_back(result3_raw);

FilterResult* nullPointer = 0;
FilterResult* ptr;

START_SECTION(FilterResult())
    FilterResult result;
    result.addFilterResultPeak(817.0411, 1694.1121, mz_shifts, intensities, results_raw);
    TEST_EQUAL(result.getMz(0), 817.0411);
    ptr = new FilterResult();
    TEST_NOT_EQUAL(ptr, nullPointer);
    delete ptr;
END_SECTION

FilterResult result;
result.addFilterResultPeak(817.0411, 1694.1121, mz_shifts, intensities, results_raw);

START_SECTION(addFilterResultPeak(double mz, double rt, std::vector<double> mzShifts, std::vector<double> intensities, std::vector<FilterResultRaw> result))
  result.addFilterResultPeak(818.0411, 1694.1121, mz_shifts, intensities, results_raw);
  TEST_EQUAL(result.getMz(1), 818.0411);
END_SECTION

START_SECTION(FilterResultPeak getFilterResultPeak(int i) const)
  TEST_EQUAL(result.getFilterResultPeak(0).getMz(), 817.0411);
END_SECTION

START_SECTION(FilterResultRaw getFilterResultRaw(int i, int j) const)
  TEST_EQUAL(result.getFilterResultRaw(0,1).getMz(), 817.1);
END_SECTION

START_SECTION(double getMz(int i) const)
  TEST_EQUAL(result.getMz(0), 817.0411);
END_SECTION

START_SECTION(std::vector<double> getMz() const)
  TEST_EQUAL(result.getMz()[0], 817.0411);
END_SECTION

START_SECTION(double getRt(int i) const)
  TEST_EQUAL(result.getRt(0), 1694.1121);
END_SECTION

START_SECTION(std::vector<double> getRt() const)
  TEST_EQUAL(result.getRt()[0], 1694.1121);
END_SECTION

START_SECTION(int size() const)
  TEST_EQUAL(result.size(), 2);
END_SECTION

END_TEST
