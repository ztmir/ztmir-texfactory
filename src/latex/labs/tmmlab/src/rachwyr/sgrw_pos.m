% us = sgrw_pos(ur)
%
% Wyrównywanie położeń przy użyciu funkcji sgolayfilt().
%
% Argumenty
%
%   ur - surowe współrzędne, wektor 1xk
%
% Zwraca
%
%   us - wyrównane położenia.
function us = sgrw_pos(ur)
  us = sgolayfilt(cat(2, ur(end-2:end), ur, ur(1:3)), 3, 7)(4:end-3);
end
