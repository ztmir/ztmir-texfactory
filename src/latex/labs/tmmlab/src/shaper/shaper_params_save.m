function  shaper_params_save(fname, P)
% SHAPER_PARAMS_SAVE Save shaper's parameters
%
%     SHAPER_PARAMS_SAVE(fname, P)
%
% ARGUMENTS
%
%   fname   File name (output file)
%   P       Structure containing shaper's parameters
%
% The parameters P are saved as Matlab's v6 binary file. Saved parameters may
% be further read from file by SHAPER_PARAMS_LOAD.
  save('-v6', fname, '-struct', 'P');
end
