/**********************************************************************************/
/*                  Pika: Phase field snow micro-structure model                  */
/*                                                                                */
/*                     (C) 2014 Battelle Energy Alliance, LLC                     */
/*                              ALL RIGHTS RESERVED                               
/*                                                                                */
/*                   Prepared by Battelle Energy Alliance, LLC                    */
/*                      Under Contract No. DE-AC07-05ID14517                      */
/*                      With the U. S. Department of Energy                       */
/**********************************************************************************/


// MOOSE includes
#include "DarcyMass.h"

template<>
InputParameters validParams<DarcyMass>()
{
  InputParameters params = validParams<Diffusion>();
  params.addParam<Real>("permeability",1.0,"Permiability (Kappa) from Darcy's Law for flow in porous media");
  params.addParam<Real>("viscosity",3.58e-007,"Dynamic viscosity of air (mu)");
  params += validParams<PropertyUserObjectInterface>();
  params += validParams<CoefficientKernelInterface>();
  return params;
}

DarcyMass::DarcyMass(const std::string & name, InputParameters parameters) :
    Diffusion(name, parameters),
    _perm(getParam<Real>("permeability")),
    _mu(getParam<Real>("viscosity")),
    PropertyUserObjectInterface(name, parameters),
    CoefficientKernelInterface(name, parameters)
{
}

Real
DarcyMass::computeQpResidual()
{
  return * Diffusion::computeQpResidual();
}

Real
DarcyMass::computeQpJacobian()
{
  return coefficient(_qp) * Diffusion::computeQpJacobian();
}
