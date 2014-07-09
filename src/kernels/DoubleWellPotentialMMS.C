#include "DoubleWellPotentialMMS.h"

template<>
InputParameters validParams<DoubleWellPotentialMMS>()
{
  InputParameters params = validParams<Kernel>();
  return params;
}

DoubleWellPotentialMMS::DoubleWellPotentialMMS(const std::string & name, InputParameters parameters) :
    Kernel(name, parameters)
{
}

Real
DoubleWellPotentialMMS::computeQpResidual()
{
  Real t = _t;
  Real x = _q_point[_qp](0);
  Real y = _q_point[_qp](1);
  Real f = 
    -t*(pow(x - 0.5, 2) + pow(y - 0.5, 2) - 0.125) + pow(t*(pow(x - 0.5, 2) + pow(y - 0.5, 2) - 0.125), 3.0);
  return -_test[_i][_qp] * f;
}