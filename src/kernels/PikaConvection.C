/****************************************************************/
/*       PIKA - Phase field snow micro-structure model          */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#include "PikaConvection.h"

/**
 * This function defines the valid parameters for
 * this Kernel and their default values
 */
template<>
InputParameters validParams<PikaConvection>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredParam<RealVectorValue>("velocity", "Velocity Vector");
  params.addRequiredCoupledVar("phase_variable", "Variable containing phase");
  params += validParams<CoefficientKernelInterface>();
  return params;
}

PikaConvection::PikaConvection(const std::string & name, InputParameters parameters) :
  Kernel(name, parameters),
  PropertyUserObjectInterface(name, parameters),
  CoefficientKernelInterface(name, parameters),
  _velocity(getParam<RealVectorValue>("velocity")),
  _phase(coupledValue("phase_variable"))

{}

Real PikaConvection::computeQpResidual()
{
  return _test[_i][_qp] * coefficient(_qp) * (_velocity*_grad_u[_qp]);
}

Real PikaConvection::computeQpJacobian()
{
  // the partial derivative of _grad_u is just _grad_phi[_j]
  return _test[_i][_qp] * coefficient(_qp) * (_velocity * _grad_phi[_j][_qp]) * (1.0 - _phase[_qp]) / 2.0;
}
