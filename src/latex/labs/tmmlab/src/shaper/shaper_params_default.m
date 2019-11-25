function P = shaper_params_default
% SHAPER_PARAMS_DEFAULT Default shaper parameters
%
%     P = SHAPER_PARAMS_DEFAULT
%
% The returned parameters structure contains the following information
%
%   - shaper model/name (string),
%   - spaher geometry (dimensions),
%   - simulation parameters,
%   - bounding box definition (for drawing/animation).
%
% RETURN VALUE
%
%   P   the structure containing the following fields
%
%       model (string)  shaper model name,
%
%       a    (real) dimension a (see documentation),
%       b    (real) dimension b (see documentation),
%       r    (real) dimention r (see documentation),
%       c    (real) dimension c (see documentation),
%       A    (2x1 vector) coordinates of the point A (see documentation),
%       D    (2x1 vector) coordinates of the point D (see documentation),
%
%       k    (integer) number of sample points (equidistantly distributed)
%       om   (real) angular velocity,
%       q0   (3x1 vector) initial guess ([phi0, alpha0, beta0]) for the first
%            step of simulation,
%
%       xlim (1x2 vector) [xmin, xmax] - bounding box x-coordinates,
%       ylim (1x2 vector) [ymin, ymax] - bounding box y-coordinates.
%
  P = struct(                       ...
    'model', 'Default Shaper',      ...
    'a',      100,                  ...
    'b',      340,                  ...
    'r',      50,                   ...
    'c',      5,                    ...
    'A',      [100, -187]',         ...
    'D',      [-130, 146]',         ...
    'k',      30,                   ...
    'om',     1,                    ...
    'q0',     [0, 3.0906, 1.3032]', ...
    'xlim',   [-150,  150],         ...
    'ylim',   [-210, 160]           ...
  );
end
