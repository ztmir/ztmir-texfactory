function Z = shaper_out(P,Q,varargin)
  Z = zeros(nargin-2,size(Q,2));
  Z(1,:) = P.A(1) + P.a * cos(Q(2,:)) + P.b * cos(Q(3,:)) - P.c - P.D(1);
  if nargin >= 3;
    V = varargin{1};
    Z(2,:) = - P.a * sin(Q(2,:)) .* V(2,:) - P.b * sin(Q(3,:)) .* V(3,:);
  end;
  if nargin >= 4;
    W = varargin{2};
    Z(3,:) = - P.a * sin(Q(2,:)) .* W(2,:) - P.b * sin(Q(3,:)) .* W(3,:) ...
             - P.a * cos(Q(2,:)) .* V(2,:).^2 - P.b * cos(Q(3,:)) .* V(3,:).^2;
  end;
end
