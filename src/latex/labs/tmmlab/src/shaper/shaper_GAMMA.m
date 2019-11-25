function GAMMA = shaper_GAMMA(P, q, v, t)
  A = norm(P.A);
  th = atan2(P.A(2), P.A(1)); % theta
  foo = P.r*sin(q(3)-q(1)) + P.a*sin(q(2)-q(3)) + A*sin(th - q(3));
  GAMMA = - [ 0,                        -v(2)*P.a*sin(q(2)),      -v(3)*P.b*sin(q(3)); ...
             -v(1)*P.r*sin(q(3)-q(1)),  -v(2)*P.a*sin(q(2)-q(3)), -v(3)*foo;  ...
             0, 0, 0 ] * v;
end
