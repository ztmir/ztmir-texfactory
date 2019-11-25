% us = jorw_pos(ur)
%
% Wyrównywanie położeń metodą Rachunku Wyrównawczego wg Jana Oderfelda.
%
% Argumenty
%
%   ur - położenia surowe, wektor 1xk
%
% Zwraca
%
%   us - położenia wyrównane
function us = jorw_pos(ur)
  c = 1/21 * [-2, +3, +6, +7, +6, +3, -2];
  n = 3;
  if size(ur,2) == 1; d = 1; else; d = 2; end
  us = conv(cat(d, ur(end-(n-1):end), ur, ur(1:n)), c, 'valid');
end
