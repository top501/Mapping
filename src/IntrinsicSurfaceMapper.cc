/*
 * Medical Image Registration ToolKit (MIRTK)
 *
 * Copyright 2016 Imperial College London
 * Copyright 2016 Andreas Schuh
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

#include "mirtk/IntrinsicSurfaceMapper.h"

#include "mirtk/Math.h"
#include "mirtk/Triangle.h"

#include "vtkIdList.h"


namespace mirtk {


// =============================================================================
// Construction/destruction
// =============================================================================

// -----------------------------------------------------------------------------
void IntrinsicSurfaceMapper::CopyAttributes(const IntrinsicSurfaceMapper &other)
{
  _Lambda = other._Lambda;
}

// -----------------------------------------------------------------------------
IntrinsicSurfaceMapper::IntrinsicSurfaceMapper(double lambda)
:
  _Lambda(clamp(lambda, 0., 1.))
{
}

// -----------------------------------------------------------------------------
IntrinsicSurfaceMapper::IntrinsicSurfaceMapper(const IntrinsicSurfaceMapper &other)
:
  SymmetricWeightsSurfaceMapper(other)
{
  CopyAttributes(other);
}

// -----------------------------------------------------------------------------
IntrinsicSurfaceMapper &IntrinsicSurfaceMapper::operator =(const IntrinsicSurfaceMapper &other)
{
  if (this != &other) {
    SymmetricWeightsSurfaceMapper::operator =(other);
    CopyAttributes(other);
  }
  return *this;
}

// -----------------------------------------------------------------------------
IntrinsicSurfaceMapper::~IntrinsicSurfaceMapper()
{
}

// =============================================================================
// Execution
// =============================================================================

// -----------------------------------------------------------------------------
double IntrinsicSurfaceMapper::Weight(int i, int j) const
{
  double p1[3], p2[3], p3[3], w = 0.;

  vtkIdType npts, *pts;
  vtkIdType ptId1 = static_cast<vtkIdType>(i);
  vtkIdType ptId2 = static_cast<vtkIdType>(j);

  _Surface->GetPoint(ptId1, p1);
  _Surface->GetPoint(ptId2, p2);

  vtkSmartPointer<vtkIdList> cellIds = vtkSmartPointer<vtkIdList>::New();
  _Surface->GetCellEdgeNeighbors(-1, ptId1, ptId2, cellIds);

  double mu = (1. - _Lambda);
  if (mu != 0.) mu /= vtkMath::Distance2BetweenPoints(p1, p2);
  for (vtkIdType cellIdx = 0; cellIdx < cellIds->GetNumberOfIds(); ++cellIdx) {
    _Surface->GetCellPoints(cellIds->GetId(cellIdx), npts, pts);
    while (pts[0] == ptId1 || pts[0] == ptId2) ++pts;
    _Surface->GetPoint(pts[0], p3);
    if (_Lambda != 0.) {
      w += _Lambda * Triangle::Cotangent(p1, p3, p2);
    }
    if (mu != 0.) {
      w += mu * Triangle::Cotangent(p1, p2, p3);
    }
  }

  return w;
}


} // namespace mirtk