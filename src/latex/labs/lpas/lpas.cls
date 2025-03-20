% lpas.cls
% Materials for Lab on Theory of Machines and Mechanisms.
%
\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{lpas}[2016/11/25 Laboratory on Theory of Machnies and Mechanisms]
\LoadClassWithOptions{scrartcl}
\RequirePackage{scrlayer-scrpage}
\RequirePackage{etoolbox}


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                            %
%                           REQUIRED PACKAGES                                %
%                                                                            %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                            %
%                  SAVE COMMANDS THAT ARE TO BE REDEFINED                    %
%               (PLEASE KEEP THIS LIST SORTED ALPHABETICALLY)                %
%                                                                            %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
\let\lpas@saved@maketitle\maketitle
\let\lpas@saved@@maketitle\@maketitle

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                            %
%                      DEFINITION OF CUSTOM COMMANDS                         %
%                                                                            %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
\newcommand{\supertitle}[1]{\gdef\@supertitle{#1}}
\def\@supertitle{}

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                            \titlepagestyle
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
\renewcommand\titlepagestyle{empty}

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Patch \@maketitle to include \supertitle above the \title
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
\patchcmd{\@maketitle}{{\usekomafont{title}{\huge \@title \par}}}{%
  \ifx\@supertitle\@empty \else%
  \vskip 1.5em%
  {\usekomafont{supertitle}{\LARGE \@supertitle \par}}%
  \vskip 1.5em%
  \fi%
  {\usekomafont{title}{\huge \@title \par}}%
}

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                            %
%                       CUSTOM ENVIRONMENTS                                  %
%                                                                            %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                          abstract                                          %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
\if@titlepage
  \renewenvironment{abstract}{%
    \titlepage%
    \null\vfil%
    \@beginparpenalty\@lowpenalty
  }{\par\vfil\null\endtitlepage}
\else
  \renewenvironment{abstract}{%
    \if@twocolumn%
      \section*{\abstractname}%
    \else%
      \section*{\abstractname}%
      \small%
    \fi%
  }{\if@twocolumn\else\fi}
\fi

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                            %
%                             SETTINGS                                       %
%                                                                            %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
\pagestyle{scrheadings}
\chead{\ifx\@supertitle\@empty{}\else{\@supertitle: }\fi\@title\headmark}

\setkomafont{disposition}{\bfseries}
\addtokomafont{subject}{\normalfont}
\newkomafont{supertitle}{\usekomafont{disposition}\normalfont}

% vim: set expandtab spell tabstop=2 shiftwidth=2 syntax=tex ff=unix spelllang=en:
