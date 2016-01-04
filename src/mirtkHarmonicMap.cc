/*
 * Medical Image Registration ToolKit (MIRTK)
 *
 * Copyright 2013-2015 Imperial College London
 * Copyright 2013-2015 Andreas Schuh
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <mirtkHarmonicMap.h>

#include <mirtkPoint.h>


namespace mirtk {


// =============================================================================
// Construction/destruction
// =============================================================================

// -----------------------------------------------------------------------------
HarmonicMap::HarmonicMap()
{
}

// -----------------------------------------------------------------------------
HarmonicMap::HarmonicMap(const HarmonicMap &other)
:
  FundamentalMap(other)
{
}

// -----------------------------------------------------------------------------
HarmonicMap &HarmonicMap::operator =(const HarmonicMap &other)
{
  FundamentalMap::operator =(other);
  return *this;
}

// -----------------------------------------------------------------------------
VolumetricMap *HarmonicMap::NewCopy() const
{
  return new HarmonicMap(*this);
}

// -----------------------------------------------------------------------------
HarmonicMap::~HarmonicMap()
{
}

// =============================================================================
// Evaluation
// =============================================================================

// -----------------------------------------------------------------------------
bool HarmonicMap::Evaluate(double *v, double x, double y, double z) const
{
  Point  p(x, y, z);
  double d, h;

  for (int j = 0; j < _Coefficients.Cols(); ++j) {
    v[j] = .0;
  }

  for (int i = 0; i < _SourcePoints.Size(); ++i) {
    d = p.Distance(_SourcePoints(i));
    if (d < 1e-12) {
      for (int j = 0; j < _Coefficients.Cols(); ++j) {
        v[j] = _OutsideValue;
      }
      return false;
    }
    h = H(d);
    for (int j = 0; j < _Coefficients.Cols(); ++j) {
      v[j] += h * _Coefficients(i, j);
    }
  }

  return true;
}

// -----------------------------------------------------------------------------
double HarmonicMap::Evaluate(double x, double y, double z, int l) const
{
  Point p(x, y, z);
  double    d, v = .0;

  for (int i = 0; i < _SourcePoints.Size(); ++i) {
    d = p.Distance(_SourcePoints(i));
    if (d < 1e-12) return _OutsideValue;
    v += H(d) * _Coefficients(i, l);
  }

  return v;
}


} // namespace mirtk
