function shaper_draw(P, q)
% SHAPER_DRAW   Draw shaper P in a given position q
%
%     SHAPER_DRAW(P, q)
%
% ARGUMENTS
%
%     P   structure of shaper's parameters (see shaper_params_default)
%     q   3x1 vector of coordinates of the shaper's position [phi, alpha, beta]'
%
%
  xlim(P.xlim);
  ylim(P.ylim);
  daspect([1 1 1]);
  R = P.r * [ cos(q(1)), sin(q(1)) ]';
  B = P.A + P.a * [ cos(q(2)), sin(q(2)) ]';
  C = B + P.b *  [ cos(q(3)), sin(q(3)) ]';
  line(1.1 * [P.D(1), -P.D(1)], [P.D(2), P.D(2)], 'linestyle', '-', 'linewidth', 1, 'color', 'k');
  hold on;
  plot(P.D(1), P.D(2), 'k.');
  % circle representing tip of the "r" crank
  rectangle('Position', [-P.r, -P.r, 2*P.r, 2*P.r], 'Curvature', 1, 'LineStyle', '--', 'EdgeColor', 'r');
  % crank "r"
  line([0, R(1)], [0, R(2)], 'linestyle', '-', 'linewidth', 1, 'color', 'k');
  plot(0, 0, 'k.');
  plot(R(1), R(2), 'k.');
  % cicrle representing the link "a"
  rectangle('Position', [P.A(1)-P.a, P.A(2)-P.a, 2*P.a, 2*P.a], 'Curvature', 1, 'LineStyle', '--', 'EdgeColor', 'r');
  % link "a"
  line([P.A(1), B(1)], [P.A(2), B(2)], 'linestyle', '-', 'linewidth', 1, 'color', 'k');
  plot(P.A(1), P.A(2), 'k.');
  plot(B(1), B(2), 'k.');
  % link "b"
  line([B(1), C(1)], [B(2), C(2)], 'linestyle', '-', 'linewidth', 1, 'color', 'k');
  plot(B(1), B(2), 'k.');
  plot(C(1), C(2), 'k.');
end
