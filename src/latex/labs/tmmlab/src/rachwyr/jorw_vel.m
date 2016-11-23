% vs = jorw_vel(ur)
%
% Wyrównywanie prędkości metodą Rachunku Wyrównawczego wg Jana Oderfelda.
%
% Argumenty
%
%   ur - położenia surowe, wektor 1xk
%
% Zwraca
%
%   vs - prędkości wyrównane (geometryczne)
function vs = jorw_vel(ur)
  c = 1/252 * [-2, +19, -18, -57, -24, 0, +24, +57, +18, -19, +2];
  n = 5;
  if size(ur,2) == 1; d = 1; else; d = 2; end
  vs = conv(cat(d, ur(end-(n-1):end), ur, ur(1:n)), c, 'valid');
end
