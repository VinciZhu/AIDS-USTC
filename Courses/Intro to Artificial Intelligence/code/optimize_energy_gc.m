function disparity = optimize_energy_gc(data_term, smoothness_term)

    % OPTIMIZE_ENERGE_DP Gets the disparity matrix by minimizing the energy
    % using graph cut.
    %    [DISPARITY] = OPTIMIZE_ENERGY_GC(DATA_TERM_ALGORITHM,
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
    %    output_parameters:
    %       DISPARITY                 - A matrix showing the horizontal offsets
    %                                   in direction from INPUT_IMAGE_L to
    %                                   INPUT_IMAGE_R. For example, a value of
    %                                   8 in DISPARITY at pixel (y, x) means
    %                                   that the corresponding pixel in
    %                                   INPUT_IMAGE_R is 8 pixels to the left
    %                                   of pixel (y, x) in INPUT_IMAGE_L.

    % YOUR IMPLEMENTATION GOES HERE...

    [height, width, label_num] = size(data_term);
    pixel_num = height * width;
    disparity = zeros(height, width);

    class = zeros(1, pixel_num);
    unary = zeros(label_num, pixel_num);
    pairwise = sparse(pixel_num, pixel_num);
    labelcost = smoothness_term;

    for i = 1:height

        for j = 1:width
            unary(:, (i - 1) * width + j) = data_term(i, j, :);

            if i > 1
                pairwise((i - 1) * width + j, (i - 2) * width + j) = 1;
            end

            if j > 1
                pairwise((i - 1) * width + j, (i - 1) * width + j - 1) = 1;
            end

            if i < height
                pairwise((i - 1) * width + j, i * width + j) = 1;
            end

            if j < width
                pairwise((i - 1) * width + j, (i - 1) * width + j + 1) = 1;
            end

        end

    end

    [labels, ~, ~] = GCMex(class, single(unary), pairwise, single(labelcost), 0);

    for i = 1:height

        for j = 1:width
            disparity(i, j) = labels((i - 1) * width + j);
        end

    end

end
