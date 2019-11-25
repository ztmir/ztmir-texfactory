function F = shaper_F(P, q, t)
  F = [ shaper_PHI(P,q); q(1) - t*P.om ];
end
