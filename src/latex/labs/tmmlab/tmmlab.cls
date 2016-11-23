% tmmlab.cls
% Materials for Lab on Theory of Machines and Mechanisms.
%
\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{tmmlab}[2016/11/25 Laboratory on Theory of Machnies and Mechanisms]
\LoadClassWithOptions{scrartcl}


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
\let\tmm@saved@maketitle\maketitle
\let\tmm@saved@@maketitle\@maketitle

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                            %
%                      DEFINITION OF CUSTOM COMMANDS                         %
%                                                                            %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
\newcommand{\serietitle}[1]{\gdef\@serietitle{#1}}
\def\@serietitle{Serie Title}

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                            \@maketitle                                     %
% The \@maketitle is used internally by \maketitle                           %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
\def\@maketitle{%
  \begin{center}
    \Huge
    \textbf{\@serietitle}
  \end{center}
  \tmm@saved@@maketitle
  %\newpage
  %\vspace{1cm}
  \hrule
  \vspace{1cm}
} % end \@maketitle

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                            \maketitle                                      %
% The standard article uses "empty" page style for the tile page.
% This is hardcoded in the definition of \maketitle. For that reason, we
% redefine \maketitle command to just add \thispagestyle{plain}.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
\renewcommand\maketitle{\tmm@saved@maketitle\thispagestyle{plain}}

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                            %
%                       CUSTOM ENVIRONMENTS                                  %
%                                                                            %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                          abstract                                          %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
\if@titlepage
  \renewenironment{abstract}{%
    \titlepage
    \null\vfil
    \@beginparpenalty\@lowpenalty
  }{\par\vfil\null\endtitlepage}
\else
  \renewenvironment{abstract}{%
    \if@twocolumn%
      \section*{\abstractname}%
    \else%
      \small%
      %\quotation%
    \fi%
  }{\if@twocolumn\else\fi}
\fi

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                            %
%                             SETTINGS                                       %
%                                                                            %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
\pagestyle{headings}


% vim: set expandtab spell tabstop=2 shiftwidth=2 syntax=tex ff=unix spelllang=en:
