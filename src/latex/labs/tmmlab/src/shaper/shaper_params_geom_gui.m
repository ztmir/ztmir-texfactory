function [P, status] = shaper_params_geom_gui(P)
% SHAPER_PARAMS_GEOM_GUI  Display GUI for editing shaper dimensions
%
%   [P, status] = SHAPER_PARAMS_GEOM_GUI(P)
%
% ARGUMENTS
%
%   P   Initial parameter values (see shaper_params_default)
%
% RETURN VALUES
%
%  P      Modified parameters structure,
%  status 1 if user confirmed (OK) modifications or 0 otherwise (CANCEL).
%

  prompts = { 'a [mm]',         ...
              'b [mm]',         ...
              'r [mm]',         ...
              'c [mm]',         ...
              'Ax [mm]',        ...
              'Ay [mm]',        ...
              'Dx [mm]',        ...
              'Dy [mm]' };

  values  = { sprintf('%g',P.a),        ...
              sprintf('%g',P.b),        ...
              sprintf('%g',P.r),        ...
              sprintf('%g',P.c),        ...
              sprintf('%g',P.A(1)),     ...
              sprintf('%g',P.A(2)),     ...
              sprintf('%g',P.D(1)),     ...
              sprintf('%g',P.D(2)) };

  status = 1;
  while(true)
    values = inputdlg(prompts, sprintf('Shaper Geometry (%s)', P.model), 1, values);
    if length(values)
      % Check
      valid = 0;
      errmsg = 'Invalid values found:';
      for i = 1:8
        x = str2double(values{i});
        if isnan(x)
          errmsg = strcat(errmsg, sprintf('\n  %s = "%s" (not a number)', prompts{i}, values{i} ));
        else
          valid = valid + 1;
        end
      end
      if valid == length(prompts)
        P.a =   str2double(values{1});
        P.b =   str2double(values{2});
        P.r =   str2double(values{3});
        P.c =   str2double(values{4});
        P.A =   [str2double(values{5}), str2double(values{6})]';
        P.D =   [str2double(values{7}), str2double(values{8})]';
        status = true;
        break;
      else
        errordlg(strcat(errmsg,sprintf('\nPlease enter valid numbers')), 'Validation failed!');
      end
    else
      status = false;
      break;
    end
  end
end
