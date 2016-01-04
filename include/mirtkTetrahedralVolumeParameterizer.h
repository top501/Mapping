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

#ifndef MIRTK_TetrahedralVolumeParameterizer_H
#define MIRTK_TetrahedralVolumeParameterizer_H

#include <mirtkVolumeParameterizer.h>

#include <vtkSmartPointer.h>
#include <vtkPointSet.h>
#include <vtkDataArray.h>


namespace mirtk {


/**
 * Base class of filters which re-parameterize the interior of a piecewise
 * linear complex (PLC) using the finite element method (FEM)
 *
 * Subclasses of this base class compute a volumetric map based on a tetrahedral
 * discretization of the interior of the input PLC.
 */
class TetrahedralVolumeParameterizer : public VolumeParameterizer
{
  mirtkAbstractMacro(TetrahedralVolumeParameterizer);

  // ---------------------------------------------------------------------------
  // Attributes

protected:

  /// Boolean array indicating which points are on the boundary, i.e., fixed
  mirtkPublicAttributeMacro(vtkSmartPointer<vtkDataArray>, InputMask);

  /// Discretized input domain, i.e., tetrahedral mesh
  mirtkReadOnlyAttributeMacro(vtkSmartPointer<vtkPointSet>, Volume);

  /// Output coordinates of volume mesh points
  mirtkReadOnlyAttributeMacro(vtkSmartPointer<vtkDataArray>, Coords);

  /// Boolean array indicating which points are on the boundary, i.e., fixed
  mirtkReadOnlyAttributeMacro(vtkSmartPointer<vtkDataArray>, BoundaryMask);

  /// Number of points
  mirtkReadOnlyAttributeMacro(int, NumberOfPoints);

  /// Number of boundary points
  mirtkReadOnlyAttributeMacro(int, NumberOfBoundaryPoints);

  /// Number of interior points
  mirtkReadOnlyAttributeMacro(int, NumberOfInteriorPoints);

  /// Copy attributes of this class from another instance
  void CopyAttributes(const TetrahedralVolumeParameterizer &);

  // ---------------------------------------------------------------------------
  // Construction/Destruction

protected:

  /// Default constructor
  TetrahedralVolumeParameterizer();

  /// Copy constructor
  TetrahedralVolumeParameterizer(const TetrahedralVolumeParameterizer &);

  /// Assignment operator
  TetrahedralVolumeParameterizer &operator =(const TetrahedralVolumeParameterizer &);

public:

  /// Destructor
  virtual ~TetrahedralVolumeParameterizer();

  // ---------------------------------------------------------------------------
  // Execution

  /// Whether a given point is on the boundary
  bool IsBoundaryPoint(vtkIdType) const;

protected:

  /// Initialize filter after input and parameters are set
  virtual void Initialize();

  /// Finalize filter execution
  virtual void Finalize();

};

////////////////////////////////////////////////////////////////////////////////
// Inline definitions
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
inline bool TetrahedralVolumeParameterizer::IsBoundaryPoint(vtkIdType ptId) const
{
  return (_BoundaryMask->GetComponent(ptId, 0) != .0);
}


} // namespace mirtk

#endif // MIRTK_TetrahedralVolumeParameterizer_H
