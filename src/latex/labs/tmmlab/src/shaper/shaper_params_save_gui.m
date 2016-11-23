function shaper_params_save_gui(P)
  title = 'Save Shaper Parameters';
  filter = {'*.params', 'Shaper Parameters'};
  [fname, fpath] = uiputfile(filter, title);
  if fname
    f = fullfile(fpath, fname);
    shaper_params_save(f, P);
  end
end
