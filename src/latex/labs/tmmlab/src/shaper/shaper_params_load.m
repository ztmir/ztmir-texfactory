function P = shaper_params_load(fname)
% SHAPER_PARAMS_LOAD Load shaper's parameters from file
%
%   P = SHAPER_PARAMS_LOAD(fname)
%
% ARGUMENTS
%
%   fname   File name (input file)
%
% RETURNS
%
%   P       The data (structure) read from file
%
% This function may be used to load parameters previously saved with
% SHAPER_PARAMS_SAVE.
  P = load('-v6', fname);
end
