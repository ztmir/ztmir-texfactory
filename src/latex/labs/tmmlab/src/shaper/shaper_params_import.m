function P = shaper_params_import(fname)
  [names, values] = textread(fname, '%s %s', 'delimiter', '=');
  P = struct();
  for i = 1:numel(names)
    eval(strcat('P.', names{i}, '=', values{i}));
  end
end
