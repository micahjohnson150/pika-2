/****************************************************************/
/*       PIKA - Phase field snow micro-structure model          */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#ifndef GLSCOUPLEDTIMEDERIVATIVE_H
#define GLSCOUPLEDTIMEDERIVATIVE_H

// Pika includes
#include "PikaTimeDerivative.h"

// Forward Declarations
class GLSCoupledTimeDerivative;

template<>
InputParameters validParams<GLSCoupledTimeDerivative>();

 /**
 * This Kernel behaves exactly as GLSTimeDerivative, but instead the
 * time derivative is for a coupled variable.
 *
 * @see GLSTimeDerivative
 */

class GLSCoupledTimeDerivative :
  public PikaTimeDerivative
{
public:

  /**
   * Class constructor
   */
  GLSCoupledTimeDerivative(const std::string & name, InputParameters parameters);

protected:

  /**
   * Compute residual
   */
  virtual Real computeQpResidual();

  /**
   * Compute jacobian
   * The Jacobian entry for this Kernel is zero.
   */
  virtual Real computeQpJacobian();

  /**
   * Compute off-diagonal jacobian
   * The off-diagonal jacobian term, i.e., the derivative of the coupled time derivative with respect
   * to the coupled variable.
   */
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

private:

  /// Time derivative of coupled variable
  const VariableValue & _var_dot;

  /// Derivative of time derivative of the coupled variable
  const VariableValue & _dvar_dot_dvar;

  /// The coupled variable number
  unsigned int _v_var;

};

#endif //GLSCOUPLEDTIMEDERIVATIVE
