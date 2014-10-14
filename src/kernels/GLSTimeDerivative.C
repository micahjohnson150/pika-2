/****************************************************************/
/*       PIKA - Phase field snow micro-structure model          */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#include "GLSTimeDerivative.h"

template<>
InputParameters validParams<GLSTimeDerivative>()
{
  InputParameters params = validParams<TimeKernel>();
  params.addParam<bool>("lumping", false, "True for mass matrix lumping, false otherwise");
  params += validParams<PropertyUserObjectInterface>();
  params += validParams<CoefficientKernelInterface>();
  return params;
}

GLSTimeDerivative::GLSTimeDerivative(const std::string & name, InputParameters parameters) :
    TimeKernel(name, parameters),
    _lumping(getParam<bool>("lumping")),
    PropertyUserObjectInterface(name, parameters),
    CoefficientKernelInterface(name, parameters)
{
  // The getMaterialProperty method cannot be replicated in interface
  if (useMaterial())
    setMaterialPropertyPointer(&getMaterialProperty<Real>(getParam<std::string>("property")));

}

Real
GLSTimeDerivative::computeQpResidual()
{
  return 0.5 * GLS_coefficient(qp) * (coefficient(_qp) * _u_dot[_qp]) * (coefficient(_qp) * _u_dot[_qp]) * _test[_i][_qp];
}

Real
GLSTimeDerivative::computeQpJacobian()
{
  return 0;
}

