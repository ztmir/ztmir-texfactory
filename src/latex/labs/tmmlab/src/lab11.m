%
%   Laboratorium TMM
%   Ćw. 11 z TMM.
%   Analiza kinematyczna mechanizmu strugarki.
%

% Prevent octave from thinking that this is a function file
function lab11
  %clear all;

  % Add paths
  addpath('shaper');
  addpath('rachwyr');

  if isoctave
    pkg load geometry
    pkg load io
  end

  main_loop
  close all;
end

% Define our local functions
function P = shaper_params_open_file(varargin)
  if nargin > 0
    if(mod(nargin,2))
      error('odd number of arguments\n');
    end
    opts = struct(varargin{:});
  else
    opts = struct();
  end
  if(isfield(opts, 'Import') && opts.Import)
    title = 'Importuj Plik z Parametrami Strugarki';
    filter = { '*_params.m', 'Parametry Strugarki (M-file)'
               '*.m', 'M-file'};
  else
    title = 'Otwórz Plik z Parametrami Strugarki';
    filter = {'*.params', 'Parametry Strugarki'};
  end
  [fname, fpath, fltidx] = uigetfile(filter, title);
  if fname
    f = fullfile(fpath, fname);
    if(isfield(opts, 'Import') && opts.Import)
      P = shaper_params_import(f);
    else
      P = shaper_params_load(f);
    end
  else
    P = 0;
  end
end

function P = shaper_params_open_predefined(varargin)
  name = 'Wybierz model strugarki';
  patt = 'shaper/*.params';
  prompt = 'Model strugarki';
  files = glob(patt);
  Ps = {};
  choices = {};
  for i = [1:length(files)]
    Ps{i} = shaper_params_load(files{i}, varargin{:});
    if(~isfield(Ps{i}, 'model'))
      Ps{i}.model = files{i};
    end
    choices{i} = Ps{i}.model;
  end
  [sel, ok] = listdlg('SelectionMode', 'Single', ...
                      'Name', name, ...
                      'PromptString', prompt, ...
                      'ListString', choices);
  if(ok)
    P = Ps{i};
  else
    P = 0;
  end
end

function shaper_params_save_file(P)
  title = 'Zapisz Plik z Parametrami Strugarki';
  filter = {'*.params', 'Parametry Strugarki'};
  [fname, fpath, fltidx] = uiputfile(filter, title);
  if fname
    f = fullfile(fpath, fname);
    shaper_params_save(f, P);
  end
end

function [P, ok] = shaper_params_select()
  choices = {'Defaultowe', 'Predefiniowane', 'Z pliku', 'Import'};
  [sel, ok] = listdlg('Name', 'Parametry', ...
                      'PromptString', {'Parametry Strugarki',' - wybierz źródło danych'}, ...
                      'SelectionMode', 'Single', ...
                      'ListString', choices);
  if ok
    switch(sel)
      case 1
        P = shaper_params_default();
      case 2
        P = shaper_params_open_predefined();
      case 3
        P = shaper_params_open_file();
      case 4
        P = shaper_params_open_file('Import', 1);
    end
  else
    P = 0;
  end
end

function ans = exit_confirm_dialog()
  btn = questdlg('Zakończyć program?', 'Koniec?', 'Tak', 'Nie', 'Nie');
  ans = strcmp(btn, 'Tak');
end

%%function [P, ok] = main_menu_select()
%%  choices = { 'Wczytaj Parametry z Pliku',  ...
%%              'Edytuj Parametry Strugarki' };
%%  [sel, ok] = listdlg('Name', 'Menu Główne', ...
%%                      'PromptString', {'Wybierz Operację'}, ...
%%                      'SelectionMode', 'Single', ...
%%                      'ListString', choices);
%%  if ok
%%    switch(sel)
%%      case 1
%%        P = shaper_params_open_file();
%%        P = shaper_params_default();
%%      case 2
%%        P = shaper_params_open_predefined();
%%      case 3
%%        P = shaper_params_open_file();
%%      case 4
%%        P = shaper_params_open_file('Import', 1);
%%    end
%%  else
%%    P = 0;
%%  end
%%end

function choice = main_menu_dialog()
  choice = questdlg('Wybierz operację', 'Menu główne', 'Koniec', 'Parametry', 'Obliczenia', 'Obliczenia');
end

function choice = params_menu_dialog()
  choice = questdlg('Parametry:', 'Menu parametrów', 'Powrót', 'Nowe', 'Zapisz', 'Nowe');
end

function choice = comp_menu_dialog()
  choice = questdlg('Obliczenia:', 'Menu obliczeń', 'Powrót', 'Symulacja', 'Obróbka', 'Symulacja');
end

function comp_loop(shaper_params)
  done = 0;

  while(~done)
    choice = comp_menu_dialog;
    switch choice
      case 'Powrót'
        done = 1;
      case 'Symulacja'
        % TODO: choose simulation time-span tt
        [qq, vv, ww] = shaper_solve(shaper_params, shaper_params.q0, [0.1:0.1:2*pi]);
        shaper_animate(shaper_params, qq);
      case 'Obróbka'
    end
  end
end

function main_loop()
  done = 0;

  shaper_params = 0;

  %% Main loop
  while(~done)
    % Load shaper parameters if they're absent
    if(~isstruct(shaper_params))
      [shaper_params, ok] = shaper_params_select();
      if ~ok
        done = exit_confirm_dialog;
      end
    else
      %btn = questdlg();
      choice = main_menu_dialog;
      switch choice
        case 'Koniec'
          done = exit_confirm_dialog;
        case 'Parametry'
          choice2 = params_menu_dialog;
          switch choice2
            case 'Nowe'
              shaper_params = 0;
            case 'Zapisz'
              shaper_params_save_file(shaper_params);
          end
        case 'Obliczenia'
          comp_loop(shaper_params);
      end
    end
  end
end
