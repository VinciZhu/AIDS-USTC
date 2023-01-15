function smoothness_term = compute_smoothness_term_L1(max_disparity, max_smoothness_term_value)

    % COMPUTE_SMOOTHNESS_TERM_L1 Estimates the cost of assigning disparities to
    % neighboring pixels using the method suggested by the assignment page.
    %    [SMOOTHNESS_TERM] = COMPUTE_SMOOTHNESS_TERM(MAX_DISPARITY) takes as
    %    input the maximum disparity, and returns a matrix showingthe cost of
    %    assigning disparities to neighboring pixels.
    %
    %    input parameters:
    %       MAX_DISPARITY             - The maximum disparity.
    %
    %       YOU CAN ADD MORE INPUT PARAMETERS IF NECESSARY
    %
    %    output_parameters:
    %       SMOOTHNESS_TERM           - A matrix showing the cost of assigning
    %                                   disparities to neighboring pixels with
    %                                   dimensionality (max_disparity + 1) x
    %                                   (max_disparity + 1).

    % YOUR IMPLEMENTATION GOES HERE...

    arguments
        max_disparity (1, 1) {mustBeInteger}
        max_smoothness_term_value (1, 1) double = 1.7
    end

    smoothness_term = zeros(max_disparity + 1, max_disparity + 1);

    for i = 1:max_disparity + 1

        for j = 1:max_disparity + 1
            smoothness_term(i, j) = min(max_smoothness_term_value, abs(i - j));
        end

    end

end
