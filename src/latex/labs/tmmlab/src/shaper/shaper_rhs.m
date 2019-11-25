function [F, varargout] = shaper_rhs(P,q,t)
  F = shaper_F(P,q,t);
  if nargout >= 2
    varargout{1} = shaper_J(P,q);
  end
end
