% us = jorw(ur)
% [us, vs] = jorw(ur)
% [us, vs, ws] = jorw(ur)
%
% Wyrównywanie przebiegów metodą Rachunku Wyrównawczego wg Jana Oderfelda.
%
% Argumenty
%
%   ur - położenia surowe, wektor 1xk
%
% Zwraca
%
%   us - położenia wyrównane
%   vs - prędkości wyrównane (geometryczne)
%   ws - przyspieszenia wyrównane (geometryczne)
function varargout = jorw(ur)
  varargout{1} = jorw_pos(ur);
  if nargout >= 2
    varargout{2} = jorw_vel(ur);
  end
  if nargout >= 3
    varargout{3} = jorw_acc(ur);
  end
end
