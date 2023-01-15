function smoothness_term = compute_smoothness_term(max_disparity, smoothness_term_algorithm)

    % COMPUTE_SMOOTHNESS_TERM Estimates the cost of assigning disparities to
    % neighboring pixels.
    %    [SMOOTHNESS_TERM] = COMPUTE_SMOOTHNESS_TERM(MAX_DISPARITY,
    %    SMOOTHNESS_TERM_ALGORITHM) takes as input the maximum disparity and an
    %    algorithm indicating string, and returns a matrix showingthe cost of
    %    assigning disparities to neighboring pixels.
    %
    %    input parameters:
    %       MAX_DISPARITY             - The maximum disparity.
    %
    %       SMOOTHNESS_TERM_ALGORITHM - Either 'L1' or 'awesome', indicating
    %                                   the method used to estimate smoothness
    %                                   term.
    %
    %       YOU CAN ADD MORE INPUT PARAMETERS IF NECESSARY
    %
    %    output_parameters:
    %       SMOOTHNESS_TERM           - A matrix showing the cost of assigning
    %                                   disparities to neighboring pixels with
    %                                   dimensionality (max_disparity + 1) x
    %                                   (max_disparity + 1).

    switch smoothness_term_algorithm
        case 'default'
            smoothness_term = compute_smoothness_term_L1(max_disparity);

        case 'L1'
            smoothness_term = compute_smoothness_term_L1(max_disparity);

        otherwise
            error('compute_smoothness_term(): invalid algorithm.');
    end

end
