/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
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
  return params;
}

GLSTimeDerivative::GLSTimeDerivative(const std::string & name, InputParameters parameters) :
    TimeKernel(name, parameters),
    _lumping(getParam<bool>("lumping"))
{
}

Real
GLSTimeDerivative::computeQpResidual()
{
  return 0.5 * GLS_coefficient(qp) * _u_dot[_qp] * _u_dot[_qp] * _test[_i][_qp];
}

Real
GLSTimeDerivative::computeQpJacobian()
{
  return 0;
}

