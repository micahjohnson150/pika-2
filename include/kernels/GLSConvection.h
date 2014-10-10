/****************************************************************/
/*       PIKA - Phase field snow micro-structure model          */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#ifndef GLSCONVECTION_H
#define GLSCONVECTION_H

//MOOSE includes
#include "Kernel.h"

//Pika includes
#include "PropertyUserObjectInterface.h"
#include "CoefficientKernelInterface.h"


//Forward Declarations
class GLSConvection;

template<>
InputParameters validParams<GLSConvection>();
/** 
 * This is a stabilization kernel for the convection kernel PikaConvection
 * using Galerkin Least Squares (GLS)
 *
 */


class GLSConvection :
  public Kernel,
  public PropertyUserObjectInterface,
  public CoefficientKernelInterface
{
  public:
    GLSConvection(const std::string & name, InputParameters parameters);

  protected:
    virtual Real computeQpResidual();
    virtual Real computeQpJacobian();

  private:
    RealVectorValue _velocity;
    const VariableValue & _phase;
};

#endif // GLSCONVECTION_H
