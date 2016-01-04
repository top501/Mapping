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

#include <mirtkHarmonicTetrahedralVolumeParameterizer.h>

#include <mirtkMatrix3x3.h>

#include <vtkMath.h>


namespace mirtk {


// =============================================================================
// Construction/destruction
// =============================================================================

// -----------------------------------------------------------------------------
HarmonicTetrahedralVolumeParameterizer::HarmonicTetrahedralVolumeParameterizer()
{
}

// -----------------------------------------------------------------------------
HarmonicTetrahedralVolumeParameterizer
::HarmonicTetrahedralVolumeParameterizer(const HarmonicTetrahedralVolumeParameterizer &other)
:
  LinearTetrahedralVolumeParameterizer(other)
{
}

// -----------------------------------------------------------------------------
HarmonicTetrahedralVolumeParameterizer &HarmonicTetrahedralVolumeParameterizer
::operator =(const HarmonicTetrahedralVolumeParameterizer &other)
{
  if (this != &other) {
    LinearTetrahedralVolumeParameterizer::operator =(other);
  }
  return *this;
}

// -----------------------------------------------------------------------------
HarmonicTetrahedralVolumeParameterizer
::~HarmonicTetrahedralVolumeParameterizer()
{
}

// =============================================================================
// Auxiliary functions
// =============================================================================

// -----------------------------------------------------------------------------
Matrix3x3 HarmonicTetrahedralVolumeParameterizer
::GetWeight(vtkIdType, const double v0[3], const double v1[3],
                       const double v2[3], const double v3[3], double volume) const
{
  double a[3], b[3], n0[3], n1[3];

  vtkMath::Subtract(v2, v1, a);
  vtkMath::Subtract(v3, v1, b);
  vtkMath::Cross(a, b, n0);

  vtkMath::Subtract(v3, v0, a);
  vtkMath::Subtract(v2, v0, b);
  vtkMath::Cross(a, b, n1);

  const double c = vtkMath::Dot(n0, n1) / (36.0 * volume);
  return Matrix3x3(c, .0, .0,  .0, c, .0,  .0, .0, c);
}


} // namespace mirtk
