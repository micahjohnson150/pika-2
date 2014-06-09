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

#ifndef ERRORFUNCTIONAUX_H
#define ERRORFUNCTIONAUX_H

// MOOSE includes
#include "FunctionAux.h"

// Forward declarations
class ErrorFunctionAux;

template<>
InputParameters validParams<ErrorFunctionAux>();

/**
 *
 */
class ErrorFunctionAux : public FunctionAux
{
public:

  /**
   * Class constructor
   * @param name
   * @param parameters
   */
  ErrorFunctionAux(const std::string & name, InputParameters parameters);

protected:
  virtual Real computeValue();

private:
  const VariableValue & _soln;

  MooseEnum _error_type;

};

#endif //ERRORFUNCTIONAUX_H