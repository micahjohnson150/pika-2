/****************************************************************/
/*       PIKA - Phase field snow micro-structure model          */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#ifndef AIRPROPERTIES_H
#define AIRPROPERTIES_H

// MOOSE includes
#include "Material.h"

// PIKA includes
#include "PropertyUserObjectInterface.h"

// Forward declarations
class AirProperties;

template<>
InputParameters validParams<AirProperties>();

/**
 * A material for defining properties associated with the phase-field equation
 */
class AirProperties :
  public Material,
  public PropertyUserObjectInterface
{
public:
  AirProperties(const std::string & name, InputParameters parameters);

  static InputParameters objectParams();

protected:
  virtual void computeQpProperties();

private:

  VariableValue & _temperature;

  const Real _k_a_input;

  const Real _c_a_input;

  const Real _D_v_input;

  MaterialProperty<Real> & _rho_a;

  MaterialProperty<Real> & _k_a;

  MaterialProperty<Real> & _c_a;

  MaterialProperty<Real> & _D_v;
};

#endif // AIRPROPERTIES_H
