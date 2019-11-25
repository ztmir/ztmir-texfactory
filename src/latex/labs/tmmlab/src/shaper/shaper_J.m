function J = shaper_J(P, q)
  J = [ shaper_PHIq(P, q); 1, 0, 0 ];
end
