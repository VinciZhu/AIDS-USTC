function data_term = compute_data_term_L1(input_image_l, input_image_r, ...
        max_disparity, window_radius, max_data_term_value, lambda)

    % COMPUTE_DATA_TERM Estimates the cost of assigning disparities to pixels
    % using the method suggested by the assignment page.
    %    [DATA_TERM] = COMPUTE_DATA_TERM(INPUT_IMAGE_L, INPUT_IMAGE_R,
    %    MAX_DISPARITY) takes as input a pair of grayscale images and the
    %    maximum disparity, and returns a matrix showing the data cost.
    %
    %    input parameters:
    %       INPUT_IMAGE_L             - The left image of the input stereo pair.
    %       INPUT_IMAGE_R             - The right image of the input stereo pair.
    %                                   Both input images are grayscale images
    %                                   with double intensity values ranging from
    %                                   0 to 255.
    %       MAX_DISPARITY             - The maximum disparity.
    %
    %       YOU CAN ADD MORE INPUT PARAMETERS IF NECESSARY
    %
    %    output_parameters:
    %       DATA_TERM                 - A matrix showing the cost of assigning
    %                                   disparities to pixels with
    %                                   dimensionality height x width x
    %                                   (max_disparity + 1).

    % YOUR IMPLEMENTATION GOES HERE...

    arguments
        input_image_l (:, :) double
        input_image_r (:, :) double
        max_disparity (1, 1) {mustBeInteger}
        window_radius (1, 1) {mustBeInteger} = 3
        max_data_term_value (1, 1) double = 10
        lambda (1, 1) double = 0.04
    end

    [height, width] = size(input_image_l);
    data_term = zeros(height, width, max_disparity + 1);

    for i = 1:height
        row_start = max(1, i - window_radius);
        row_end = min(height, i + window_radius);

        for j = 1:width
            col_start = max(1, j - window_radius);
            col_end = min(width, j + window_radius);
            window_l = input_image_l(row_start:row_end, col_start:col_end);

            for d = 0:max_disparity

                if col_start - d < 1
                    data_term(i, j, d + 1) = lambda * max_data_term_value;
                else
                    window_r = input_image_r(row_start:row_end, col_start - d:col_end - d);
                    data_term(i, j, d + 1) = lambda * min(mean(mean(abs(window_l - window_r))), max_data_term_value);

                end

            end

        end

    end

end
