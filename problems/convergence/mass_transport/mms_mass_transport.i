[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 5
  ny = 5
  elem_type = QUAD4
[]

[Variables]
  [./u]
    order = FIRST
    family = LAGRANGE
  [../]
[]

[AuxVariables]
  [./phi]
  [../]
  [./abs_error]
  [../]
[]

[Functions]
  [./u_func]
    type = ParsedFunction
    vars = a
    vals = 2
    value = sin(a*pi*x)
  [../]
  [./forcing_func]
    type = ParsedFunction
    vars = a
    vals = 2
    value = a*a*pi*pi*sin(a*pi*x)
  [../]
[]

[Kernels]
  [./u_diff]
    type = Diffusion
    variable = u
    #D_name = diffusion_coefficient
    block = 0
  [../]
  [./f]
    type = UserForcingFunction
    variable = u
    function = forcing_func
  [../]
[]

[BCs]
  [./all]
    type = FunctionDirichletBC
    variable = u
    boundary = 'bottom left right top'
    function = u_func
  [../]
[]

#[PikaMaterials]
#  phi = 1
#  temperature = 273.15
#[]

[Postprocessors]
  [./L2_error]
    type = ElementL2Error
    variable = u
    function = u_func
  [../]
  [./h_max]
    type = AverageElementSize
    variable = u
  [../]
  [./ndofs]
    type = NumDOFs
  [../]
[]

[Executioner]
  type = Steady
[]

[Outputs]
  output_initial = true
  console = true
  csv = true
[]

[ICs]
  [./u_ic]
    function = u_func
    variable = u
    type = FunctionIC
  [../]
[]
