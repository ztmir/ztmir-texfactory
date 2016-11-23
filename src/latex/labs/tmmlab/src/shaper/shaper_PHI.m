function PHI = shaper_PHI(P, q, t)
  A = norm(P.A);
  th = atan2(P.A(2), P.A(1)); % theta
  PHI = [ P.A(2) + P.a*sin(q(2,:)) + P.b*sin(q(3,:)) - P.D(2,:); ...
         -P.r * sin(q(1,:)-q(3,:)) + P.a*sin(q(2,:)-q(3,:)) + A*sin(th-q(3,:)) ];
end
