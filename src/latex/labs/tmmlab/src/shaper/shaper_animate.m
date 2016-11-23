function shaper_animate(P, Q)
  for i = 1:size(Q,2)
    clf;
    shaper_draw(P,Q(:,i));
    drawnow;
    pause(0.1);
  end
end
