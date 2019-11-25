function [P, status] = shaper_params_bbox_gui(P)
% SHAPER_PARAMS_BBOX_GUI  Display GUI for editing shaper bounding box parameters
%
%   [P, status] = SHAPER_PARAMS_BBOX_GUI(P)
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

  prompts = { 'xmin [mm]',         ...
              'xmax [mm]',         ...
              'ymin [mm]',         ...
              'ymax [mm]' };

  values  = { sprintf('%g', P.xlim(1)),  ...
              sprintf('%g', P.xlim(2)),  ...
              sprintf('%g', P.ylim(1)),  ...
              sprintf('%g', P.ylim(2)) };

  status = 1;
  while(true)
    values = inputdlg(prompts, sprintf('Bounding Box (%s)', P.model), 1, values);
    if length(values)
      % Check
      valid = 0;
      errmsg = 'Invalid values found:';
      for i = 1:4
        x = str2double(values{i});
        if isnan(x)
          errmsg = strcat(errmsg, sprintf('\n  %s = "%s" (not a number)', prompts{i}, values{i} ));
        else
          valid = valid + 1;
        end
      end
      if valid == length(prompts)
        P.xlim =   [str2double(values{1}), str2double(values{2})];
        P.ylim =   [str2double(values{3}), str2double(values{4})];
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
