function data_term = compute_data_term(input_image_l, input_image_r, ...
        max_disparity, data_term_algorithm)

    % COMPUTE_DATA_TERM Estimates the cost of assigning disparities to pixels.
    %    [DATA_TERM] = COMPUTE_DATA_TERM(INPUT_IMAGE_L, INPUT_IMAGE_R,
    %    MAX_DISPARITY, DATA_TERM_ALGORITHM)takes as input a pair of grayscale
    %    images, the maximum disparity and an algorithm indicating string, and
    %    returns a matrix showing the data cost.
    %
    %    input parameters:
    %       INPUT_IMAGE_L             - The left image of the input stereo pair.
    %       INPUT_IMAGE_R             - The right image of the input stereo pair.
    %                                   Both input images are grayscale images
    %                                   with double intensity values ranging from
    %                                   0 to 255.
    %       MAX_DISPARITY             - The maximum disparity.
    %       DATA_TERM_ALGORITHM       - Either 'L1' or 'awesome', indicating
    %                                   the method used to estimate data term.
    %
    %       YOU CAN ADD MORE INPUT PARAMETERS IF NECESSARY
    %
    %    output_parameters:
    %       DATA_TERM                 - A matrix showing the cost of assigning
    %                                   disparities to pixels with
    %                                   dimensionality height x width x
    %                                   (max_disparity + 1).

    switch data_term_algorithm
        case 'default'
            data_term = compute_data_term_L1(input_image_l, input_image_r, max_disparity);

        case 'L1'
            data_term = compute_data_term_L1(input_image_l, input_image_r, max_disparity);

        otherwise
            error('compute_data_term(): invalid algorithm.');
    end

end
