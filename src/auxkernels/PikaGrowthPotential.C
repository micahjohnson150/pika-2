/****************************************************************/
/*       PIKA - Phase field snow micro-structure model          */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#include "PikaGrowthPotential.h"

template<>
InputParameters validParams<PikaGrowthPotential>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addRequiredCoupledVar("chemical_potential", "Chemical potential variable");
  return params;
}

PikaGrowthPotential::PikaGrowthPotential(const std::string & name, InputParameters parameters) :
    AuxKernel(name, parameters),
    PropertyUserObjectInterface(name, parameters),
    _rho_i(getMaterialProperty<Real>("density_ice")),
    _s_eq(getMaterialProperty<Real>("equilibrium_concentration")),
    _s(coupledValue("chemical_potential"))
{
}

PikaGrowthPotential::~PikaGrowthPotential()
{
}

Real
PikaGrowthPotential::computeValue()
{
  return ( _s[_qp] - _s_eq[_qp] ) * _rho_i[_qp];

}
