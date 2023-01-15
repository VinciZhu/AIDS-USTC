function disparity = optimize_energy_dp(data_term, smoothness_term)

    % OPTIMIZE_ENERGE_DP Gets the disparity matrix by minimizing the energy
    % using dynamic programming.
    %    [DISPARITY] = OPTIMIZE_ENERGY_DP(DATA_TERM_ALGORITHM,
    %    SMOOTHNESS_TERM_ALGORITHM)takes as input the
    %    precomputed data_term and smoothness_term and returns the disparity
    %    matrix.
    %
    %    input parameters:
    %       DATA_TERM                 - The precomputed data_term with
    %                                   dimensionality height x width x
    %                                   max_disparity.
    %       SMOOTHNESS_TERM           - The precomputed smoothness_term with
    %                                   dimensionality max_disparity x
    %                                   max_disparity.
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

    % YOUR IMPLEMENTATION GOES HERE...

    [height, width] = size(data_term(:, :, 1));
    disparity = zeros(height, width);
    max_disparity = size(data_term, 3) - 1;

    for i = 1:height
        cost = zeros(width, max_disparity + 1);
        cost(1, :) = data_term(i, 1, :);

        for j = 2:width

            for k = 1:max_disparity + 1

                cost(j, k) = data_term(i, j, k) + min(cost(j - 1, :) + smoothness_term(k, :));

            end

        end

        % Backtracking

        [~, index] = min(cost(j, :));
        disparity(i, width) = index - 1;

        for j = width - 1:-1:1

            [~, index] = min(cost(j, :) + smoothness_term(index, :));
            disparity(i, j) = index - 1;

        end

    end

end
