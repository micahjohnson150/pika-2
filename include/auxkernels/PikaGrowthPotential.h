/****************************************************************/
/*       PIKA - Phase field snow micro-structure model          */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#ifndef PIKAGROWTHPOTENTIAL_H
#define PIKAGROWTHPOTENTIAL_H

// MOOSE includes
#include "AuxKernel.h"

// Pika includes
#include "PropertyUserObjectInterface.h"

// Forward declarations
class PikaGrowthPotential;

template<>
InputParameters validParams<PikaGrowthPotential>();

/**
 *
 */
class PikaGrowthPotential :
  public AuxKernel,
  public PropertyUserObjectInterface
{
public:

  /**
   * Class constructor
   * @param name
   */
  PikaGrowthPotential(const std::string & name, InputParameters parameters);

  /**
   * Class destructor
   */
  virtual ~PikaGrowthPotential();

protected:

  /**
   *
   */
  virtual Real computeValue();

private:
  MaterialProperty<Real> & _rho_i;
  MaterialProperty<Real> & _s_eq;
  VariableValue & _s;

};

#endif //PIKAGROWTHPOTENTIAL_H
