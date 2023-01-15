function disparity = optimize_energy(data_term, smoothness_term, optimization_algorithm)

% OPTIMIZE_ENERGE Gets the disparity matrix by minimizing the energy.
%    [DISPARITY] = OPTIMIZE_ENERGY(DATA_TERM_ALGORITHM,
%    SMOOTHNESS_TERM_ALGORITHM, OPTIMIZATION_ALGORITHM)takes as input the
%    precomputed data_term and smoothness_term, and the method to be used
%    for optimization, and returns the disparity matrix.
%
%    input parameters:
%       DATA_TERM                 - The precomputed data_term with
%                                   dimensionality height x width x
%                                   max_disparity.
%       SMOOTHNESS_TERM           - The precomputed smoothness_term with
%                                   dimensionality max_disparity x
%                                   max_disparity.
%       OPTIMIZATION_ALGORITHM    - Either 'dynamic_programming',
%                                   'graph_cut' or 'awesome', indicating
%                                   the method used to minimize the energy.
%
%       YOU CAN ADD MORE INPUT PARAMETERS IF NECESSARY
%
%    output_parameters: 
%       DISPARITY                 - A matrix showing the horizontal offsets 
%                                   in direction from INPUT_IMAGE_L to
%                                   INPUT_IMAGE_R. For example, a value of
%                                   8 in DISPARITY at pixel (y, x) means
%                                   that the corresponding pixel in
%                                   INPUT_IMAGE_R is 8 pixels to the left
%                                   of pixel (y, x) in INPUT_IMAGE_L.

switch optimization_algorithm
  case 'default'
    disparity = optimize_energy_dp(data_term, smoothness_term);

  case 'dynamic_programming'
    disparity = optimize_energy_dp(data_term, smoothness_term);

  case 'graph_cut'
    disparity = optimize_energy_gc(data_term, smoothness_term);
    
  otherwise
    error('optimize_energy(): invalid algorithm.');
end

end