function disparity = computedisparity(input_image_l, input_image_r, data_term_algorithm, ...
        smoothness_term_algorithm, optimization_algorithm)

    % COMPUTEDISPARITY Estimates disparities between image pairs
    %    [DISPARITY] = COMPUTEDISPARITY(INPUT_IMAGE_L, INPUT_IMAGE_R,
    %    DATA_TERM_ALGORITHM, SMOOTHNESS_TERM_ALGORITHM,
    %    OPTIMIZATION_ALGORITHM) takes as input a pair of grayscale images
    %    and three algorithm indicating strings, and returns a matrix with
    %    the disparity between the input image pair. Assume that the input
    %    images are rectified (there are only horizontal shifts of pixels)
    %    and all the shifts are less than 60 pixels.
    %
    %    input parameters:
    %       INPUT_IMAGE_L             - The left image of the input stereo pair.
    %       INPUT_IMAGE_R             - The right image of the input stereo pair.
    %                                   Both input images are grayscale images
    %                                   with double intensity values ranging from
    %                                   0 to 255.
    %       DATA_TERM_ALGORITHM       - 'L1', indicating
    %                                   the method used to estimate data term.
    %       SMOOTHNESS_TERM_ALGORITHM - 'L1', indicating
    %                                   the method used to estimate smoothness
    %                                   term.
    %       OPTIMIZATION_ALGORITHM    - Either 'dynamic_programming' or
    %                                   'graph_cut', indicating
    %                                   the method used to minimize the energy.
    %
    %    output_parameters:
    %       DISPARITY                 - A matrix showing the horizontal offsets
    %                                   in direction from INPUT_IMAGE_L to
    %                                   INPUT_IMAGE_R. For example, a value of
    %                                   8 in DISPARITY at pixel (y, x) means
    %                                   that the corresponding pixel in
    %                                   INPUT_IMAGE_R is 8 pixels to the left
    %                                   of pixel (y, x) in INPUT_IMAGE_L.

    % Set the parameter
    max_disparity = 60;

    % Step A: compute data term
    data_term = compute_data_term(input_image_l, input_image_r, max_disparity, data_term_algorithm);

    % Step B: compute smoothness term
    smoothness_term = compute_smoothness_term(max_disparity, smoothness_term_algorithm);

    % Step C: minimize the energy
    disparity = optimize_energy(data_term, smoothness_term, optimization_algorithm);
