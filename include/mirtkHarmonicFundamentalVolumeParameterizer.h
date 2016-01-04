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

#ifndef MIRTK_HarmonicFundamentalVolumeParameterizer_H
#define MIRTK_HarmonicFundamentalVolumeParameterizer_H

#include <mirtkFundamentalVolumeParameterizer.h>

#include <mirtkMatrix.h>
#include <mirtkHarmonicMap.h>


namespace mirtk {


/**
 * Harmonic volumetric map using the method of fundamental solutions (MFS)
 *
 * This class finds a harmonic volumetric map which maps each point of the
 * input volume to a point in the target domain using the method of fundamental
 * solutions (MFS).
 *
 * - Li et al. (2009). Meshless harmonic volumetric mapping using fundamental solution methods.
 *   IEEE Transactions on Automation Science and Engineering, 6(3), 409–422.
 * - Li et al. (2010). Feature-aligned harmonic volumetric mapping using MFS.
 *   Computers and Graphics (Pergamon), 34(3), 242–251.
 */
class HarmonicFundamentalVolumeParameterizer : public FundamentalVolumeParameterizer
{
  mirtkObjectMacro(HarmonicFundamentalVolumeParameterizer);

  // ---------------------------------------------------------------------------
  // Attributes

  /// Precomputed kernel function values
  mirtkAttributeMacro(Matrix, Kernel);

  /// Whether to use SVD to solve linear system
  mirtkPublicAttributeMacro(bool, UseSVD);

  /// Copy attributes of this class from another instance
  void CopyAttributes(const HarmonicFundamentalVolumeParameterizer &);

  // ---------------------------------------------------------------------------
  // Construction/Destruction

public:

  /// Default constructor
  HarmonicFundamentalVolumeParameterizer();

  /// Copy constructor
  HarmonicFundamentalVolumeParameterizer(const HarmonicFundamentalVolumeParameterizer &);

  /// Assignment operator
  HarmonicFundamentalVolumeParameterizer &operator =(const HarmonicFundamentalVolumeParameterizer &);

  /// Destructor
  virtual ~HarmonicFundamentalVolumeParameterizer();

  // ---------------------------------------------------------------------------
  // Execution

protected:

  /// Initialize filter after input and parameters are set
  virtual void Initialize();

  /// Add source point after filter initialization
  ///
  /// \param[in] q Source point coordinates.
  ///
  /// \returns Whether source point was added or too close to existing point.
  virtual bool AddSourcePoint(double q[3]);

  /// Parameterize interior of input data set
  virtual void Parameterize();

  // ---------------------------------------------------------------------------
  // Linear system

  /// Get coefficients matrix corresponding to the least squares fitting term(s)
  /// of the quadratic energy function at constraints points
  ///
  /// \param[in]  k     Index of source points subset.
  /// \param[out] coeff Coefficients matrix.
  virtual void GetCoefficients(int k, Matrix &coeff) const;

  /// Get right-hand side of linear system
  ///
  /// \param[in]  k Index of source points subset.
  /// \param[out] b Right-hand side of linear system.
  virtual void GetConstraints(int k, Matrix &b) const;

  /// Add solution of linear system to weights of volumetric map
  ///
  /// \param[in] k Index of source points subset.
  /// \param[in] w Solution of linear system.
  virtual void AddWeights(int k, const Matrix &w);

};


} // namespace mirtk

#endif // MIRTK_HarmonicFundamentalVolumeParameterizer_H
