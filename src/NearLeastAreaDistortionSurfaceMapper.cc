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

#include "mirtk/NearLeastAreaDistortionSurfaceMapper.h"


namespace mirtk {


// =============================================================================
// Construction/destruction
// =============================================================================

// -----------------------------------------------------------------------------
void NearLeastAreaDistortionSurfaceMapper
::CopyAttributes(const NearLeastAreaDistortionSurfaceMapper &other)
{
}

// -----------------------------------------------------------------------------
NearLeastAreaDistortionSurfaceMapper::NearLeastAreaDistortionSurfaceMapper()
{
}

// -----------------------------------------------------------------------------
NearLeastAreaDistortionSurfaceMapper
::NearLeastAreaDistortionSurfaceMapper(const NearLeastAreaDistortionSurfaceMapper &other)
:
  NearOptimalSurfaceMapper(other)
{
  CopyAttributes(other);
}

// -----------------------------------------------------------------------------
NearLeastAreaDistortionSurfaceMapper &NearLeastAreaDistortionSurfaceMapper
::operator =(const NearLeastAreaDistortionSurfaceMapper &other)
{
  if (this != &other) {
    NearOptimalSurfaceMapper::operator =(other);
    CopyAttributes(other);
  }
  return *this;
}

// -----------------------------------------------------------------------------
NearLeastAreaDistortionSurfaceMapper::~NearLeastAreaDistortionSurfaceMapper()
{
}

// =============================================================================
// Execution
// =============================================================================

// -----------------------------------------------------------------------------
double NearLeastAreaDistortionSurfaceMapper
::ComputeLambda(vtkDataArray *u, vtkDataArray *v) const
{
  // TODO: Find lambda that minimizes the area distortion
  return 1.;
}


} // namespace mirtk
