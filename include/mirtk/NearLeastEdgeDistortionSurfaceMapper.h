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

#ifndef MIRTK_NearLeastEdgeDistortionSurfaceMapper_H
#define MIRTK_NearLeastEdgeDistortionSurfaceMapper_H

#include "mirtk/NearOptimalSurfaceMapper.h"


namespace mirtk {


/**
 * Compute a near-optimal intrinsic surface map which minimizes edge-length distortion
 *
 * - Desbrun, Meyer, and Alliez (2002). Intrinsic parameterizations of surface meshes.
 *   Computer Graphics Forum, 21(3), 209–218.
 */
class NearLeastEdgeDistortionSurfaceMapper : public NearOptimalSurfaceMapper
{
  mirtkObjectMacro(NearLeastEdgeDistortionSurfaceMapper);

  // ---------------------------------------------------------------------------
  // Attributes

  /// Copy attributes of this class from another instance
  void CopyAttributes(const NearLeastEdgeDistortionSurfaceMapper &);

  // ---------------------------------------------------------------------------
  // Construction/Destruction

public:

  /// Default constructor
  NearLeastEdgeDistortionSurfaceMapper();

  /// Copy constructor
  NearLeastEdgeDistortionSurfaceMapper(const NearLeastEdgeDistortionSurfaceMapper &);

  /// Assignment operator
  NearLeastEdgeDistortionSurfaceMapper &operator =(const NearLeastEdgeDistortionSurfaceMapper &);

  /// Destructor
  virtual ~NearLeastEdgeDistortionSurfaceMapper();

  // ---------------------------------------------------------------------------
  // Execution

protected:

  /// Compute affine combination weight that minimizes a given distortion measure
  ///
  /// \param[in] u Discrete conformal surface map values.
  /// \param[in] v Discrete authalic  surface map values.
  ///
  /// \returns Affine combination weight \f$\lambda\f$, where final surface map values
  ///          are computed as \f$\lambda u + (1 - \lambda) * v\f$.
  virtual double ComputeLambda(vtkDataArray *u, vtkDataArray *v) const;

};


} // namespace mirtk

#endif // MIRTK_NearLeastEdgeDistortionSurfaceMapper_H
