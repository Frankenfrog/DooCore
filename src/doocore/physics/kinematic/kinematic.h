#ifndef DOOCORE_PHYSICS_KINEMATIC_H
#define DOOCORE_PHYSICS_KINEMATIC_H

// from STL

// from ROOT
#include "TLorentzVector.h"
#include "TMath.h"

// from RooFit

// forward decalarations

/**
 * @namespace doocore::physics
 * @brief DooCore physics functionality namespace
 *
 * This namespace contains all DooCore functionality that does physics 
 * calculations (kinematics and such).
 */

/**
 * @namespace doocore::physics::kinematic
 * @brief DooCore kinematic functionality namespace
 *
 * This namespace contains all DooCore functionality that does kinematic
 * calculations.
 */

namespace doocore {
namespace physics {
namespace kinematic {
  
/**
 *  @brief Two body wrong mass hypothesis mother calculator
 *
 *  Based on two TLorentzVectors (the daughter particles) a mother particle
 *  is calculated under the assumption that the first daughter's mass hypothesis 
 *  is wrong and needs to be replaced by another mass.
 *
 *  Time per call (on my MacBook, -O0): 1.1466e-06 s
 *
 *  @param daughter1 first daughter to use with different mass hypothesis
 *  @param daughter2 second daughter
 *  @param new_mass new mass hypothesis for daughter1
 *  @return the mother
 */
TLorentzVector MotherTwoBodyWrongMassHypothesis(const TLorentzVector& daughter1,
                                                const TLorentzVector& daughter2,
                                                double new_mass) {
  TLorentzVector daughter1_new;
  daughter1_new.SetVectM(daughter1.Vect(), new_mass);
  
  return daughter1_new + daughter2;
}

/**
 *  @brief Two body decay mother calculator
 *
 *  Based on two daughter particle properties a mother particle is calculated 
 *  under the assumption of daughter's masses.
 *
 *  Time per call (on my MacBook, -O0): 2.853e-07 s
 *
 *  @param d1_px first daughter px
 *  @param d1_py first daughter py
 *  @param d1_pz first daughter pz
 *  @param d1_m first daughter mass
 *  @param d2_px second daughter px
 *  @param d2_py second daughter py
 *  @param d2_pz second daughter pz
 *  @param d2_m second daughter mass
 *  @return the mother
 */
TLorentzVector MotherTwoBodyDecay(double d1_px, double d1_py,
                                  double d1_pz, double d1_m,
                                  double d2_px, double d2_py,
                                  double d2_pz, double d2_m) {
  // calculation by hand more efficient
  //  TLorentzVector daughter1;
  //  daughter1.SetXYZM(d1_px, d1_py, d1_pz, d1_m);
  //  TLorentzVector daughter2;
  //  daughter2.SetXYZM(d2_px, d2_py, d2_pz, d2_m);
  //
  //  return daughter1 + daughter2;
  
  double d1_E = TMath::Sqrt(d1_m*d1_m + d1_px*d1_px + d1_py*d1_py + d1_pz*d1_pz);
  double d2_E = TMath::Sqrt(d2_m*d2_m + d2_px*d2_px + d2_py*d2_py + d2_pz*d2_pz);
  
  double m_px = (d1_px+d2_px);
  double m_py = (d1_py+d2_py);
  double m_pz = (d1_pz+d2_pz);
  double m_E  = (d1_E+d2_E);
  
  return TLorentzVector(m_px, m_py, m_pz, m_E);
}

/**
 *  @brief Two body decay mother mass calculator
 *
 *  Based on two daughter particle properties a mother mass is calculated 
 *  under the assumption of daughter's masses. This function is more efficient 
 *  than the other functions calculating the mother's TLorentzVector.
 *
 *  Time per call (on my MacBook, -O0): 4.27e-08 s
 *
 *  @param d1_px first daughter px
 *  @param d1_py first daughter py
 *  @param d1_pz first daughter pz
 *  @param d1_m first daughter mass
 *  @param d2_px second daughter px
 *  @param d2_py second daughter py
 *  @param d2_pz second daughter pz
 *  @param d2_m second daughter mass
 *  @return the mother mass
 */
double MotherTwoBodyDecayMass(double d1_px, double d1_py,
                                  double d1_pz, double d1_m,
                                  double d2_px, double d2_py,
                                  double d2_pz, double d2_m) {
//  double d1_E = TMath::Sqrt(d1_m*d1_m + d1_px*d1_px + d1_py*d1_py + d1_pz*d1_pz);
//  double d2_E = TMath::Sqrt(d2_m*d2_m + d2_px*d2_px + d2_py*d2_py + d2_pz*d2_pz);
  
  double m_px = (d1_px+d2_px);
  double m_py = (d1_py+d2_py);
  double m_pz = (d1_pz+d2_pz);
  double m_E  = (TMath::Sqrt(d1_m*d1_m + d1_px*d1_px + d1_py*d1_py + d1_pz*d1_pz)
                +TMath::Sqrt(d2_m*d2_m + d2_px*d2_px + d2_py*d2_py + d2_pz*d2_pz));
  
  //return TLorentzVector(m_px, m_py, m_pz, m_e);
  
  return TMath::Sqrt(m_E*m_E - (m_px*m_px + m_py*m_py + m_pz*m_pz));
}

} // namespace kinematic
} // namespace physics
} // namespace doofit

#endif // DOOCORE_PHYSICS_KINEMATIC_H