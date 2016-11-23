function [P, status] = shaper_params_sim_gui(P)
% SHAPER_PARAMS_SIM_GUI  Display GUI for editing shaper simulation parameters
%
%   [P, status] = SHAPER_PARAMS_SIM_GUI(P)
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

  prompts = { 'k (int, 1 .. 720)',    ...
              'omega [rad/s]',        ...
              'initial phi [rad]',    ...
              'initial alpha [rad]',  ...
              'initial beta [rad]'    ...
            };

  values  = { sprintf('%d', P.k),      ...
              sprintf('%g', P.om),     ...
              sprintf('%g', P.q0(1)),  ...
              sprintf('%g', P.q0(2)),  ...
              sprintf('%g', P.q0(3))   ...
            };

  status = 1;
  while(true)
    values = inputdlg(prompts, sprintf('Simulation Parameters (%s)', P.model), 1, values);
    if length(values)
      % Check
      valid = 0;
      errmsg = 'Invalid values found:';
      try
        x = base2dec(values{1},10);
      catch
        x = NaN;
      end
      if isnan(x)
        errmsg = strcat(errmsg, sprintf('\n  %s = "%s" (not a positive integer)', prompts{1}, values{1} ));
      elseif x < 1 || x > 720
        errmsg = strcat(errmsg, sprintf('\n  %s = "%s" (out of range)', prompts{1}, values{1} ));
      else
        valid = valid + 1;
      end
      for i = 2:5
        x = str2double(values{i});
        if isnan(x)
          errmsg = strcat(errmsg, sprintf('\n  %s = "%s" (not a number)', prompts{i}, values{i} ));
        else
          valid = valid + 1;
        end
      end
      if valid == length(prompts)
        P.k  =   base2dec(values{1}, 10);
        P.om =   str2double(values{2});
        P.q0 =   [str2double(values{3}), str2double(values{4}), str2double(values{5})]';
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
