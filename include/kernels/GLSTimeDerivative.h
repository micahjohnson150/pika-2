/****************************************************************/
/*       PIKA - Phase field snow micro-structure model          */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#ifndef GLSTIMEDERIVATIVE_H
#define GLSTIMEDERIVATIVE_H

//MOOSE includes
#include "TimeKernel.h"

// Pika includes
#include "PropertyUserObjectInterface.h"
#include "CoefficientKernelInterface.h"

// Forward Declaration
class GLSTimeDerivative;

template<>
InputParameters validParams<GLSTimeDerivative>();

/**
 * A Galerkin Least Squares Formulation of the Kernel PikaTimeDerivative.
 */

class GLSTimeDerivative :
  public TimeKernel,
  public PropertyUserObjectInterface,
  public CoefficientKernelInterface
{
public:
  GLSTimeDerivative(const std::string & name, InputParameters parameters);


  virtual void computeJacobian();

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

  bool _lumping;
};

#endif //GLSTIMEDERIVATIVE_H
