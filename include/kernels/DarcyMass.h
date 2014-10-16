/**********************************************************************************/
/*                  Pika: Phase field snow micro-structure model                  */
/*                                                                                */
/*                     (C) 2014 Battelle Energy Alliance, LLC                     */
/*                              ALL RIGHTS RESERVED                               */
/*                                                                                */
/*                   Prepared by Battelle Energy Alliance, LLC                    */
/*                      Under Contract No. DE-AC07-05ID14517                      */
/*                      With the U. S. Department of Energy                       */
/**********************************************************************************/

#ifndef DARCYMASS_H
#define DARCYMASS_H

// MOOSE includes
#include "Diffusion.h"

// Pika includes
#include "PropertyUserObjectInterface.h"
#include "CoefficientKernelInterface.h"

//Forward Declarations
class DarcyMass;

template<>
InputParameters validParams<DarcyMass>();

/**
 * A conservation mass based on Darcy's Law. Assuming the fluid
 * is incompressible the equation becomes
 *
 * div(-(kappa/mu) * grad(pressure))= 0 
 *
 * This is essentially a diffusion kernel which is why we inherit from
 * the original diffusion kernel in Moose and use it's residual.
 */
class DarcyMass :
  public Diffusion,
  public PropertyUserObjectInterface,
  public CoefficientKernelInterface
{
public:

  /**
   * Class constructor
   */
  DarcyMass(const std::string & name, InputParameters parameters);

protected:

  /**
   * Compute residual
   * Utilizes Diffusion::computeQpResidual with applied coefficients
   */
  virtual Real computeQpResidual();

  /**
   * Compute residual
   * Utilizes Diffusion::computeQpJacobian with applied coefficients and scaling
   */
  virtual Real computeQpJacobian();

  /**
   * Permeability usually shown as Kappa in literature
   */
  const Real & _perm;

  /**
   * Dyanmic viscosity usually shown as Mu in literature
   */
  const Real & _mu;

};

#endif //DARCYMASS_H
