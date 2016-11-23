function PHIq = shaper_PHIq(P, q, t)
  A = norm(P.A);
  th = atan2(P.A(2), P.A(1)); % theta
  PHIq = [ 0,                  P.a*cos(q(2)),      P.b*cos(q(3)); ...
          -P.r*cos(q(1)-q(3)), P.a*cos(q(2)-q(3)), P.r*cos(q(1)-q(3)) - P.a*cos(q(2)-q(3)) - A*cos(th-q(3)) ];
end
