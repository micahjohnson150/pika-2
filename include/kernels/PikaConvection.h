/****************************************************************/
/*       PIKA - Phase field snow micro-structure model          */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#ifndef PIKACONVECTION_H
#define PIKACONVECTION_H

//MOOSE includes
#include "Kernel.h"

//Pika includes
#include "PropertyUserObjectInterface.h"
#include "CoefficientKernelInterface.h"


//Forward Declarations
class PikaConvection;

template<>
InputParameters validParams<PikaConvection>();
/** 
 * A coefficient convection Kernel
 *
 * This Kernel allows a coefficient to be applied to the convection term, assuming
 * the convection values are of the same magnitude as the diffusion terms
 *
 */


class PikaConvection :
  public Kernel,
  public PropertyUserObjectInterface,
  public CoefficientKernelInterface
{
  public:
    PikaConvection(const std::string & name, InputParameters parameters);

  protected:
    virtual Real computeQpResidual();
    virtual Real computeQpJacobian();

  private:
    RealVectorValue _velocity;
    const VariableValue & _phase;
};

#endif // PIKACONVECTION_H
