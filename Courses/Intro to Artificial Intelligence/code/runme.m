function [] = runme(force_overwrite)
    %RUNME Entry point
    %   [] = RUNME(FORCE_OVERWRITE) executes the various steps needed for this
    %   assignment.
    %
    %   INPUT: FORCE_OVERWRITE - Optional. If 'true', all outputs will be
    %          generated, even if they already exist. Default is 'false'.

    close all

    if ~exist('GCMex.m', 'file')
        addpath('GCMex');
    end

    % By default we do not overwrite results
    if (nargin < 1)
        force_overwrite = false;
    end

    % Edit this cell array to decide on the specific configurations you would like to execute.
    % Each cell is a cell array on its own. The first member of that array is the name of the input
    % example (i.e. filename without the '_0?.jpg' suffix). 'all' is a reserved word that causes all
    % inputs to run with the specified parameters. The rest of the cells specify the algorithm for each
    % of the steps.

    run_configurations = { ...
    % {'test01', 'L1', 'L1', 'graph_cut'}, ...
                        %   {'all', 'L1', 'L1', 'dynamic_programming'}, ...
                          {'all', 'L1', 'L1', 'graph_cut'}
                          };

    % Iterate all running configurations
    for configuration = run_configurations

        % Will hold the error for each disparity image
        errors = [];

        basename = configuration{1}{1};

        if (strcmpi('all', basename))
            % Iterate over all files and run with the given parameters

            % Get list of all filenames in input directory
            filenames = dir('../input');

            % Process all filenames in input directory
            for i = 1:size(filenames)
                filename = filenames(i).name;

                % Check if filename is an image
                if (contains(filename, '_l.png'))

                    % Determine the base filename
                    base_filename = strrep(filename, '_l.png', '');

                    % Do the heavy lifting
                    err = processtestcase(base_filename, configuration{1}{2:end}, force_overwrite);
                    % Record the error for each pair of test images
                    errors(end + 1) = err;

                end

            end

        else
            % Do the heavy lifting
            err = processtestcase(basename, configuration{1}{2:end}, force_overwrite);
            % Record the error for each pair of test images
            errors(end + 1) = err;
        end

        % Plot cdf of errors and save to file.
        % Note that only the errors computed in the last run will be plotted, thus in order to get a CDF of
        % all your inputs, use runme(true) to force recalculation of all results.
        if (~isempty(errors) && ~all(isnan(errors)))
            disp('RMSE:' + string(errors));
            h = figure('Visible', 'Off');
            cdfplot(errors);
            print(h, '-djpeg', '-r300', ['../error/cdf_', configuration{1}{2}, '_', ...
                              configuration{1}{3}, '_', configuration{1}{4}, '.jpg']);
            close(h);
        end

    end

    % processtestcase() implements the various steps, as described on the assignment website.
    function [err] = processtestcase(base_filename, a_method, b_method, c_method, force_overwrite)

        err = nan;

        % Generate file names
        base_filename_full = strjoin({base_filename, a_method, b_method, c_method}, '_');

        input_filename1 = ['../input/', base_filename, '_l.png'];
        input_filename2 = ['../input/', base_filename, '_r.png'];
        disparity_filename = ['../disparity/', base_filename_full, '.jpg'];
        error_filename = ['../error/', base_filename_full, '.jpg'];
        groundtruth_filename = ['../groundtruth/', base_filename, '.mat'];

        % Make sure files exist
        assert(2 == exist(input_filename1, 'file'), ['Missing file detected: ' input_filename1]);
        assert(2 == exist(input_filename2, 'file'), ['Missing file detected: ' input_filename2]);
        assert(2 == exist(groundtruth_filename, 'file'), ['Missing file detected: ' groundtruth_filename]);

        % Create the disparity image, if it does not already exist
        if (force_overwrite || ...
            ~exist(disparity_filename, 'file') || ...
                ~exist(error_filename, 'file'))

            % Read the input images
            input_image1 = imread(input_filename1);
            input_image2 = imread(input_filename2);

            % Convert the input images to grayscale
            if (size(input_image1, 3) == 3)
                input_image1 = rgb2gray(input_image1);
            end

            if (size(input_image2, 3) == 3)
                input_image2 = rgb2gray(input_image2);
            end

            % Convert to double precision without scaling the intensity value
            input_image1 = double(input_image1);
            input_image2 = double(input_image2);

            % Compute the disparity for the given stereo pair of input images
            % using algorithms according to the configuration
            disp(['[+] Computing disparity for ', base_filename, ' ...']);
            tic
            disparity = computedisparity(input_image1, input_image2, a_method, ...
                b_method, c_method);
            toc

            % Evaluate the output image by computing the root mean square error
            % with respect to the groundtruth image and visualize difference at
            % every pixel
            groundtruth_file = load(groundtruth_filename);
            groundtruth = groundtruth_file.groundtruth;
            [err, error_image] = evaluatedisparity(disparity, groundtruth);

            % Write the computed images
            disparity_image = uint8(disparity / 60 * 255);
            imwrite(disparity_image, disparity_filename);
            imwrite(error_image, error_filename);
        else
            disp(['[-] Skipping ' base_filename]);
        end

    end

    % Compute the root mean square error between the disparity image and the
    % groundtruth and visualize the difference at each pixel, red for positive
    % error and green for negative
    function [err, error_image] = evaluatedisparity(disparity, groundtruth)
        % Ignore the boundary
        disparity_trunc = disparity(:, 61:end);
        groundtruth_trunc = groundtruth(:, 61:end);

        % Compute the root mean square error
        err = (sum(sum((disparity_trunc - groundtruth_trunc) .^ 2)) / ...
        numel(groundtruth_trunc)) ^ 0.5;

        % Compute the error image
        error_image = zeros(size(groundtruth_trunc, 1), size(groundtruth_trunc, 2), 3);
        difference_pos = disparity_trunc - groundtruth_trunc;
        difference_pos(difference_pos < 0) = 0;
        difference_neg = disparity_trunc - groundtruth_trunc;
        difference_neg(difference_neg > 0) = 0;
        difference_neg = abs(difference_neg);
        error_image(:, :, 1) = difference_pos / 60;
        error_image(:, :, 2) = difference_neg / 60;
        error_image = uint8(error_image * 255);
        error_image(groundtruth_trunc == 0) = 0;
    end

end
