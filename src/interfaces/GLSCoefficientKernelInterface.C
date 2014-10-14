/****************************************************************/
/*       PIKA - Phase field snow micro-structure model          */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

// STL includes
#include <string>

// MOOSE includes
#include "FEProblem.h"
#include "InputParameters.h"

// PIKA includes
#include "GLSCoefficientKernelInterface.h"

template<>
InputParameters validParams<GLSCoefficientKernelInterface>()
{
  InputParameters params = emptyInputParameters();
  params.addParam<bool>("use_temporal_scaling", false, "Temporally scale this Kernel with a value specified in PikaMaterials");
  return params;
}

GLSCoefficientKernelInterface::GLSCoefficientKernelInterface(const std::string & name, InputParameters & parameters) :
    _coefficient(parameters.isParamValid("coefficient") ? parameters.get<Real>("coefficient") : 0.0)
{
}

void

Real
GLSCoefficientKernelInterface::coefficient(unsigned int qp)
{
    return _);

}
