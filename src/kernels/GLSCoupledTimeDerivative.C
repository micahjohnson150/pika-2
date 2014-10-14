/****************************************************************/
/*       PIKA - Phase field snow micro-structure model          */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#include "GLSCoupledTimeDerivative.h"

template<>
InputParameters validParams<GLSCoupledTimeDerivative>()
{
  InputParameters params = validParams<PikaTimeDerivative>();
  params.addRequiredCoupledVar("coupled_variable", "Variable to being differentiated with respect to time");
  return params;
}

GLSCoupledTimeDerivative::GLSCoupledTimeDerivative(const std::string & name, InputParameters parameters) :
    PikaTimeDerivative(name,parameters),
    _var_dot(coupledDot("coupled_variable")),
    _dvar_dot_dvar(coupledDotDu("coupled_variable")),
    _v_var(coupled("coupled_variable"))
{
}

Real
GLSCoupledTimeDerivative::computeQpResidual()
{
  return 0.5 * GLScoefficient(_qp) * (coefficient(_qp) * _var_dot[_qp])* (coefficient(_qp) * _var_dot[_qp]) *  _test[_i][_qp];
}

Real
GLSCoupledTimeDerivative::computeQpJacobian()
{
  return 0.0;
}

Real
GLSCoupledTimeDerivative::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _v_var)
    return 0.0 //coefficient(_qp) * _test[_i][_qp]*_phi[_j][_qp]*_dvar_dot_dvar[_qp];
  else
    return 0.0;
}
