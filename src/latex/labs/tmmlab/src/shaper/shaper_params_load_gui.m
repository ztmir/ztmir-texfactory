function P = shaper_params_load_gui
  title = 'Load Shaper Parameters';
  filter = {'*.params', 'Shaper Parameters'};
  [fname, fpath] = uigetfile(filter, title);
  if fname
    f = fullfile(fpath, fname);
    P = shaper_params_load(f);
  else
    P = false;
  end
end
