/****************************************************************/
/*       PIKA - Phase field snow micro-structure model          */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#include "GLSConvection.h"

/**
 * A Kernel for the Galerkin Least Squares form of
 * the convection kernel for stabilization purposes.
 */
template<>
InputParameters validParams<GLSConvection>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredParam<RealVectorValue>("velocity", "Velocity Vector");
  params.addRequiredCoupledVar("phase_variable", "Variable containing phase");
  params += validParams<CoefficientKernelInterface>();
  return params;
}

GLSConvection::GLSConvection(const std::string & name, InputParameters parameters) :
  Kernel(name, parameters),
  PropertyUserObjectInterface(name, parameters),
  CoefficientKernelInterface(name, parameters),
  _velocity(getParam<RealVectorValue>("velocity")),
  _phase(coupledValue("phase_variable"))

{}

Real GLSConvection::computeQpResidual()
{
  Real residual = coefficient(_qp) * (_velocity*_grad_u[_qp])*(1.0-_phase[_qp]/2.0);
  // GLS= 1/2 * GLS_Coefficient * residual^2)* test function
  return 0.5 * GLS_coefficient(_qp) * (residual * residual) * _test[_qp];
}

Real GLSConvection::computeQpJacobian()
{
  return 0;
}
