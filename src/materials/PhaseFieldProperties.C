/****************************************************************/
/*       PIKA - Phase field snow micro-structure model          */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

// PIKA includes
#include "PhaseFieldProperties.h"

template<>
InputParameters validParams<PhaseFieldProperties>()
{
  InputParameters params = validParams<Material>();
  params += validParams<PropertyUserObjectInterface>();
  params.addCoupledVar("temperature", 273.15, "The temperature variable to couple (default: 273.15)");
  params.addCoupledVar("phi", 1.0, "The phase-field variable to couple");
  return params;
}


PhaseFieldProperties::PhaseFieldProperties(const std::string & name, InputParameters parameters) :
    Material(name, parameters),
    PropertyUserObjectInterface(name, parameters),
    _temperature(coupledValue("temperature")),
    _phase(coupledValue("phi")),
    _a1((5./8.)*std::sqrt(2.)),
    _interface_velocity(declareProperty<Real>("interface_velocity")),
    _lambda(declareProperty<Real>("lambda")),
    _tau(declareProperty<Real>("tau")),
    _conductivity(declareProperty<Real>("conductivity")),
    _heat_capacity(declareProperty<Real>("heat_capacity")),
    _diffusion_coefficient(declareProperty<Real>("diffusion_coefficient")),
    _interface_thickness_squared(declareProperty<Real>("interface_thickness_squared")),
    _equilibrium_concentration(declareProperty<Real>("equilibrium_concentration")),
    _saturation_pressure_of_water_vapor_over_ice(declareProperty<Real>("saturation_pressure_of_water_vapor_over_ice")),
    _specific_humidity_ratio(declareProperty<Real>("specific_humidity_ratio")),
    _rho_vs(declareProperty<Real>("equilibrium_water_vapor_concentration_at_saturation")),
    _xi(_property_uo.temporalScale()),
    _d_o(getMaterialProperty<Real>("capillary_length")),
    _d_o_prime(declareProperty<Real>("capillary_length_prime")),
    _beta(getMaterialProperty<Real>("interface_kinetic_coefficient")),
    _beta_prime(declareProperty<Real>("beta_prime")),
    _convert_meters(_property_uo.getParam<Real>("conversion_factor")),
    _gamma(_property_uo.getParam<Real>("interface_free_energy")),
    _a(_property_uo.getParam<Real>("mean_molecular_spacing")),
    _k(_property_uo.getParam<Real>("boltzmann")),
    _alpha(_property_uo.getParam<Real>("condensation_coefficient")),
    _m(_property_uo.getParam<Real>("mass_water_molecule")),
    _w(_property_uo.getParam<Real>("interface_thickness")),
    _L_sg(_property_uo.getParam<Real>("latent_heat")),
    _rho_i(getMaterialProperty<Real>("density_ice")),
    _ki(getMaterialProperty<Real>("conductivity_ice")),
    _ka(getMaterialProperty<Real>("conductivity_air")),
    _ci(getMaterialProperty<Real>("heat_capacity_ice")),
    _ca(getMaterialProperty<Real>("heat_capacity_air")),
    _dv(getMaterialProperty<Real>("water_vapor_diffusion_coefficient"))

{
}

void
PhaseFieldProperties::computeQpProperties()
{
  _rho_vs[_qp] = _property_uo.equilibriumWaterVaporConcentrationAtSaturation(_temperature[_qp]);
  //_capillary_length[_qp] =  (_rho_vs[_qp]/(rho_i[_qp])) * (gamma * std::pow(a, 3.) ) / (k * _property_uo.referenceTemp());
  _d_o_prime[_qp] =  (_rho_vs[_qp]/( _rho_i[_qp])) * _d_o[_qp];

  //_beta[_qp] = (1./(alpha)) * std::sqrt((2.*libMesh::pi*m) / (k * _property_uo.referenceTemp()));
  _beta_prime[_qp] =(_rho_vs[_qp]/( _rho_i[_qp])) * _beta[_qp];

  _lambda[_qp] = (_a1 * _w  / _d_o_prime[_qp]);

  _tau[_qp] = (_beta_prime[_qp] * _w * _lambda[_qp]) / _a1;

  _conductivity[_qp] = _convert_meters * (_ki[_qp] * (1. + _phase[_qp]) / 2. + _ka[_qp] * (1. - _phase[_qp]) / 2.);

  _heat_capacity[_qp] =(1.0/(_convert_meters)) * _ci[_qp] * (1. + _phase[_qp]) / 2. + _ca[_qp] * (1. - _phase[_qp]) / 2.;

  _diffusion_coefficient[_qp] = _convert_meters * _convert_meters * _dv[_qp] * (1. - _phase[_qp]) / 2. ;

  _interface_thickness_squared[_qp] = _convert_meters * _convert_meters * _w * _w;

  _equilibrium_concentration[_qp] =  _property_uo.equilibriumConcentration(_temperature[_qp]);

  // x_s, Eq. (1)
  _specific_humidity_ratio[_qp] = _property_uo.specificHumidityRatio(_temperature[_qp]);

  // P_{vs}, Eq. (2)
  _saturation_pressure_of_water_vapor_over_ice[_qp] =  _property_uo.saturationPressureOfWaterVaporOverIce(_temperature[_qp]);
}
