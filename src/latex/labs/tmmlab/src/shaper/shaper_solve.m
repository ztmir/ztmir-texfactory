function [qk, varargout] = shaper_solve(P, q, tk, varargin)
% SHAPER_SOLVE  Solve the forward kinematics problem for shaper P
%
%   qk = SHAPER_SOLVE(P, q, tk)
%   [qk, vk] = SHAPER_SOLVE(P, q, tk)
%   [qk, vk, wk] = SHAPER_SOLVE(P, q, tk)
%   ... = SHAPER_SOLVE(P, q, tk, options)
%
% ARGUMENTS
%
%   P       shaper's parameters, see shaper_params_default,
%   q       initial coordinates -- initial guess for the first step of simulation,
%   tk      1 x k vector of time-points at which the kinematic problem is to be solved,
%   options options for the nonlinear solver, created with optimset().
%
% RETURN VALUES
%
%   qk      3 x k vector of consecutive positions at times tk,
%   vk      3 x k vector of consecutive velocities at times tk,
%   wk      3 x k vector of consecutive accelerations at times tk.
%
  nk = [size(q,1), size(tk,2)];
  qk = zeros(nk);
  for i=1:2; if nargout >= 1+i; varargout{i} = zeros(nk); end; end
  options = optimset('Jacobian', 'on', 'Display', 'off'); % defaults
  if nargin >= 4; options = optimset(options, varargin{1}); end
  i = 1;
  for t = tk
    q = fsolve(@(uu)shaper_rhs(P, uu, t), q, options);
    qk(:,i) = q;
    if nargout >= (1 + 1)
      v = - shaper_J(P,q)\shaper_Ft(P,q,t);
      varargout{1}(:,i) = v;
    end
    if nargout >= (1 + 2)
      w = - shaper_J(P,q)\shaper_GAMMA(P,q,v,t);
      varargout{2}(:,i) = w;
    end
    i = i + 1;
  end
end
