[Mesh]
  type = FileMesh
  file = phi_temp_diffusion_0010_mesh.xdr
  dim = 2
[]

[Variables]
  [./T]
  [../]
  [./u]
  [../]
  [./phi]
  [../]
[]

[AuxVariables]
  [./phi_aux]
  [../]
[]

[Functions]
  [./T_func]
    type = SolutionFunction
    from_variable = T
    solution = initial_uo
  [../]
  [./phi_func]
    type = SolutionFunction
    from_variable = phi
    solution = initial_uo
  [../]
[]

[Kernels]
  active = 'vapor_time phi_transition heat_diffusion phi_double_well heat_phi_time heat_time vapor_phi_time vapor_diffusion phi_time phi_square_gradient heat_convection'
  [./heat_diffusion]
    type = PikaDiffusion
    variable = T
    use_temporal_scaling = true
    property = conductivity
  [../]
  [./heat_time]
    type = PikaTimeDerivative
    variable = T
    property = heat_capacity
    scale = 1.0
  [../]
  [./heat_phi_time]
    type = PikaCoupledTimeDerivative
    variable = T
    property = latent_heat
    scale = -0.5
    use_temporal_scaling = true
    coupled_variable = phi
  [../]
  [./vapor_time]
    type = PikaTimeDerivative
    variable = u
    coefficient = 1.0
    scale = 1.0
  [../]
  [./vapor_diffusion]
    type = PikaDiffusion
    variable = u
    use_temporal_scaling = true
    property = diffusion_coefficient
  [../]
  [./vapor_phi_time]
    type = PikaCoupledTimeDerivative
    variable = u
    coefficient = 0.5
    coupled_variable = phi
    use_temporal_scaling = true
  [../]
  [./phi_time]
    type = PikaTimeDerivative
    variable = phi
    property = relaxation_time
    scale = 1.0
  [../]
  [./phi_transition]
    type = PhaseTransition
    variable = phi
    mob_name = mobility
    chemical_potential = u
    coefficient = 1.0
    lambda = phase_field_coupling_constant
  [../]
  [./phi_double_well]
    type = DoubleWellPotential
    variable = phi
    mob_name = mobility
  [../]
  [./phi_square_gradient]
    type = ACInterface
    variable = phi
    mob_name = mobility
    kappa_name = interface_thickness_squared
  [../]
  [./heat_convection]
    type = PikaConvection
    variable = T
    coefficient = 1.0
    use_temporal_scaling = true
    phase_variable = phi
    velocity = '0 1 0'
  [../]
  [./vapor_convection]
    type = PikaConvection
    variable = u
    coefficient = 1.0
    use_temporal_scaling = true
    phase_variable = phi
    velocity = '0 10 0'
  [../]
[]

[AuxKernels]
  [./phi_correct]
    type = PikaPhaseInitializeAux
    variable = phi_aux
    phase = phi
  [../]
[]

[BCs]
  active = 'insulated_sides T_hot T_cold'
  [./T_hot]
    type = DirichletBC
    variable = T
    boundary = bottom
    value = 267.515 # -5
  [../]
  [./T_cold]
    type = DirichletBC
    variable = T
    boundary = top
    value = 264.8 # -20
  [../]
  [./insulated_sides]
    type = NeumannBC
    variable = T
    boundary = 'left right'
  [../]
  [./phi_bc]
    type = DirichletBC
    variable = phi
    boundary = '0 1 2 3 '
    value = 1.0
  [../]
  [./u_bottom]
    type = DirichletBC
    variable = u
    boundary = bottom
    value = -4.7e-6
  [../]
  [./u_top]
    type = DirichletBC
    variable = u
    boundary = top
    value = 4.7e-6
  [../]
[]

[UserObjects]
  [./initial_uo]
    type = SolutionUserObject
    system = nl0
    mesh = phi_temp_diffusion_0010_mesh.xdr
    nodal_variables = 'T phi'
    execute_on = initial
    es = phi_temp_diffusion_0010.xdr
  [../]
[]

[Executioner]
  # Preconditioned JFNK (default)
  type = Transient
  dt = 100
  solve_type = PJFNK
  petsc_options = -
  petsc_options_iname = '-ksp_gmres_restart -pc_type -pc_hypre_type'
  petsc_options_value = '500 hypre boomeramg'
  end_time = 7200
  reset_dt = true
  dtmax = 25
  dtmin = .001
  [./TimeStepper]
    type = SolutionTimeAdaptiveDT
    dt = .5
    percent_change = .1
    reset_dt = true
  [../]
[]

[Adaptivity]
  max_h_level = 7
  initial_marker = u_marker
  marker = combo_mark
  initial_steps = 3
  [./Indicators]
    [./phi_grad_indicator]
      type = GradientJumpIndicator
      variable = phi
    [../]
    [./u_jump_indicator]
      type = GradientJumpIndicator
      variable = u
      block = 0
    [../]
  [../]
  [./Markers]
    active = 'phi_marker u_tol_marker combo_mark u_marker'
    [./phi_marker]
      type = ErrorToleranceMarker
      coarsen = 1e-6
      indicator = phi_grad_indicator
      refine = 1e-6
    [../]
    [./T_marker]
      type = ErrorFractionMarker
      coarsen = 0.2
      indicator = T_jump_indicator
      refine = 0.7
    [../]
    [./u_marker]
      type = ErrorFractionMarker
      indicator = u_jump_indicator
      refine = .95
      block = 0
    [../]
    [./combo_mark]
      type = ComboMarker
      block = 0
      markers = 'u_marker phi_marker u_tol_marker'
    [../]
    [./u_tol_marker]
      type = ErrorToleranceMarker
      coarsen = 1e-10
      indicator = u_jump_indicator
      refine = 1e-7
    [../]
  [../]
[]

[Outputs]
  output_initial = true
  exodus = true
  [./console]
    type = Console
    perf_log = true
    nonlinear_residuals = true
    linear_residuals = true
  [../]
[]

[ICs]
  active = 'phase_ic vapor_ic temperature_ic'
  [./phase_ic]
    variable = phi
    type = FunctionIC
    function = phi_func
  [../]
  [./temperature_ic]
    variable = T
    type = FunctionIC
    function = T_func
  [../]
  [./vapor_ic]
    variable = u
    type = ChemicalPotentialIC
    block = 0
    phase_variable = phi
    temperature = T
  [../]
  [./constant_temp_ic]
    variable = T
    type = ConstantIC
    value = 264.8
  [../]
[]

[PikaMaterials]
  phi = phi
  temperature = T
  interface_thickness = 1e-5
  temporal_scaling = 1e-4
  outputs = all
  condensation_coefficient = .001
  phase = phi
[]

[PikaCriteriaOutput]
  air_criteria = false
  velocity_criteria = false
  time_criteria = false
  vapor_criteria = false
  chemical_potential = u
  phase = phi
  use_temporal_scaling = true
  ice_criteria = false
  interface_velocity_postprocessors = 'average max min'
  temperature = T
[]

