function retval = isoctave
  persistent cacheval;
  if isempty(cacheval)
    cacheval= (exist('OCTAVE_VERSION', 'builtin') > 0);
  end
  retval = cacheval;
end

