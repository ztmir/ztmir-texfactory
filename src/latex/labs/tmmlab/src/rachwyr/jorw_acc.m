% ws = jorw_acc(ur)
%
% Wyrównywanie przyspieszeń metodą Rachunku Wyrównawczego wg Jana Oderfelda.
%
% Argumenty
%
%   ur - położenia surowe, wektor 1xk
%
% Zwraca
%
%   ws - przyspieszenia wyrównane (geometryczne)
function ws = jorw_acc(ur)
  c = 1/252 * [-2, -35, +102, -33, -24, -24, -24, -33, +102, -35, +2];
  n = 5;
  if size(ur,2) == 1; d = 1; else; d = 2; end
  vs = conv(cat(d, ur(end-(n-1):end), ur, ur(1:n)), c, 'valid');
end
