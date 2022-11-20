\ProvidesClass{ned-article}

% 错误信息
\newcommand\ned@error[1]{%
\ClassError{ned-article}{#1}{}%
}
\newcommand\ned@warning[1]{%
\ClassWarning{ned-article}{#1}%
}

% 宏包

%%
\PassOptionsToPackage{quiet}{fontspec}

%% 修复minted宏包路径
\RequirePackage{ifthen,currfile-abspath}
\getabspath{\jobname.log}
\ifthenelse{\equal{\theabsdir}{\thepwd}}
    {}{\PassOptionsToPackage{outputdir=\theabsdir}{minted}}

%%
\LoadClass[zihao=-4,fontset=fandol]{ctexart}
\RequirePackage{lmodern,geometry,fancyhdr,titletoc,changepage,enumitem}
\RequirePackage{underscore,cprotect}
\RequirePackage[normalem]{ulem}
\RequirePackage{csvsimple-l3,siunitx,booktabs,caption,multirow}
\RequirePackage{xcolor,graphicx,tikz}
\RequirePackage{amsmath,amsthm,bm,mathtools,esdiff}
\RequirePackage{algorithm2e}
\RequirePackage[skins,minted,breakable]{tcolorbox}
\RequirePackage{xurl,nameref,hyperref}

\hypersetup{
  colorlinks,
  allcolors=blue,
  bookmarksnumbered=true,
  pdfstartview=FitH,
}

% 自定义信息
\newcommand\setinfo[1]{%
    \kvsetkeys{ned}{#1}%
}
\newcommand\getinfo[1]{%
    \expandafter\csname ned@#1\endcsname%
}
\newcommand\defineinfo[1]{%
\kvsetkeys{ned@key}{#1}%
}
\kv@set@family@handler{ned@key}{%
    \@namedef{ned@#1@@name}{#1}%
    \def\ned@@default{}%
    \def\ned@@choices{}%
    \kv@define@key{ned@value}{name}{%
        \@namedef{ned@#1@@name}{##1}%
    }%
    \@namedef{ned@#1@@check}{}%
    \@namedef{ned@#1@@code}{}%
    \kv@define@key{ned@value}{choices}{%
        \def\ned@@choices{##1}%
        \@namedef{ned@#1@@reset}{}%
        \@namedef{ned@#1@@check}{%
            \@ifundefined{%
                ifned@\@nameuse{ned@#1@@name}@\@nameuse{ned@\@nameuse{ned@#1@@name}}%
            }{%
                \ned@error{%
                    Invalid value "#1 = \@nameuse{ned@\@nameuse{ned@#1@@name}}"
                }%
            }%
            \@nameuse{ned@#1@@reset}%
            \@nameuse{ned@\@nameuse{ned@#1@@name}@\@nameuse{ned@\@nameuse{ned@#1@@name}}true}%
        }%
    }%
    \kv@define@key{ned@value}{default}{%
        \def\ned@@default{##1}%
    }%
    \kvsetkeys{ned@value}{#2}%
    \@namedef{ned@\@nameuse{ned@#1@@name}}{}%
    \kv@set@family@handler{ned@choice}{%
        \ifx\ned@@default\@empty
            \def\ned@@default{##1}%
        \fi
        \expandafter\newif\csname ifned@\@nameuse{ned@#1@@name}@##1\endcsname
        \expandafter\g@addto@macro\csname ned@#1@@reset\endcsname{%
            \@nameuse{ned@\@nameuse{ned@#1@@name}@##1false}%
        }%
    }%
    \kvsetkeys@expandafter{ned@choice}{\ned@@choices}%
    \expandafter\let\csname ned@\@nameuse{ned@#1@@name}\endcsname\ned@@default
    \expandafter%
    \ifx\csname ned@\@nameuse{ned@#1@@name}\endcsname\@empty\else
        \@nameuse{ned@#1@@check}%
    \fi
    \kv@define@key{ned}{#1}{%
        \@namedef{ned@\@nameuse{ned@#1@@name}}{##1}%
        \@nameuse{ned@#1@@check}%
        \@nameuse{ned@#1@@code}%
    }%
}

\defineinfo{
    type = {
        default = {类型}，
    },
    course = {
        default = {课程}，
    },
    title = {
        default = {标题}，
    },
    author = {
        default = {名字}，
    },
    date = {
        default = {2022-01-01},
    },
    id = {
        default = {学号}
    },
}

% 日期命令
\newcommand\monthenglish[1]{%
  \ifcase\number#1\or
    January\or February\or March\or April\or May\or June\or
    July\or August\or September\or October\or November\or December%
  \fi
}
\newcommand\ned@format@date[2]{%
    \edef\ned@@date{#2}%
    \def\ned@@process@date##1-##2-##3\@nil{%
        #1{##1}{##2}{##3}%
    }%
    \expandafter\ned@@process@date\ned@@date\@nil
}
\newcommand\formatdatezhsmall[3]{\number#1 年 \number#2 月 \number#3 日}
\newcommand\formatdatezhbig[3]{\zhdigits{#1}年\zhnumber{#2}月\zhnumber{#3}日}
\newcommand\formatdate[3]{\monthenglish{#2} \number#3, #1}
\newcommand\getdatezhsmall{\ned@format@date{\formatdatezhsmall}{\ned@date}}
\newcommand\getdatezhbig{\ned@format@date{\formatdatezhbig}{\ned@date}}
\newcommand\getdate{\ned@format@date{\formatdate}{\ned@date}}

% 字体&颜色命令
\newcommand\titlebf{\heiti\addCJKfontfeatures{BoldFont=*}\bfseries}
\newcommand\ustcblue{\color[cmyk]{1,0.8,0,0}}

% 数学命令
\newcommand\rmd{\mathrm{d}}
\newcommand\Tr{\mathrm{T}}
\newcommand\Hm{\mathrm{H}}
\newcommand\pmat[1]{\begin{pmatrix}#1\end{pmatrix}}
\newcommand\bmat[1]{\begin{bmatrix}#1\end{bmatrix}}
\newcommand\switch[1]{\begin{dcases}#1\end{dcases}}
\newcommand\rswitch[1]{\begin{drcases}#1\end{drcases}}
\DeclareMathOperator*{\argmax}{arg\,max}
\DeclareMathOperator*{\argmin}{arg\,min}
\DeclareMathOperator*{\st}{s.\,t.}

% 引用命令
\renewcommand\eqref[1]{(\ref{#1})~式}
\newcommand\tabref[1]{表~\ref{#1}}
\newcommand\figref[1]{图~\ref{#1}}

% 纸张、页面及字体
\geometry{
    paper      = a4paper,
    vmargin    = 2.04cm,
    hmargin    = 1.67cm,
    headheight = 0.75cm,
    headsep    = 0.29cm,
    footskip   = 0.79cm,
}

\ctexset{
    secnumdepth     = 3,
    section         = {
        format      = \bf,  
        name        = {,、},
        number      = \chinese{section},
        beforeskip  = 12bp,
        afterskip   = 6bp,
    },
    subsection      = {
        format      = \titlebf,
        name        = {,.},
        number      = \arabic{subsection},
        beforeskip  = 12bp,
        afterskip   = 6bp,
    },
    subsubsection      = {
        format      = \titlebf,
        number      = {\arabic{subsubsection})},
        beforeskip  = 12bp,
        afterskip   = 6bp,
    },
}

\newcommand\setupappendix{%
    \appendix%
    \ctexset{
        section         = {
            format      += \large\centering,  
            name        = {附录,},
            number      = \Alph{section},
            beforeskip  = 24bp,
            afterskip   = 6bp,
        },
    }%
}

\pagestyle{fancy}
\fancyhf{}
\fancyhead[C]{\small\ned@course：\ned@title}
\fancyfoot[C]{\small\thepage}

% 表格环境
\DeclareCaptionFont{titlebf}{\titlebf}
\captionsetup{labelfont=titlebf,font=small}
\sisetup{table-auto-round,table-alignment-mode=none,group-digits=none,tight-spacing}
\newcommand\includecsv[5][\textwidth]{
    \begin{tabular*}{#1}{c@{}@{\extracolsep{\fill}}#5@{}c}
        \toprule
        &#4&\\\midrule
        \csvreader[late after line=\\]{#2}{}{&#3&}
        \bottomrule
    \end{tabular*}
}
\newcommand\roundnum[3][]{\tablenum[round-mode=places,round-precision=#2,#1]{#3}}

% 定理环境  
\newtheoremstyle{zhplain}{}{}{}{2\ccwd}{\titlebf}{}{\ccwd}{}
\newcommand\thmitem[1]{\par{\titlebf#1}\hspace{\ccwd}}

\theoremstyle{zhplain}
\newtheorem{project}{程序}

% 算法环境
\LinesNumbered
\RestyleAlgo{ruled}
\SetKwInput{KwData}{输入}
\SetKwInput{KwResult}{输出}
\SetAlgorithmName{算法}{算法}{算法清单}
\SetAlgoLined
\SetAlCapSty{titlebf}
\SetKwSty{titlebf}
\SetAlCapSkip{6bp}
\SetAlgoCaptionSeparator{\unskip\hspace*{\ccwd}}

% 代码环境
\definecolor{codegray}{rgb}{0.95,0.95,0.95}
\newenvironment{restoreindent}{%
    \@parboxrestore\begin{adjustwidth}{}{\leftmargin}%
}{%
    \end{adjustwidth}%
}
\newtcbinputlisting{\includecode}[3][]{
    after={\par\smallskip\noindent}, enhanced, frame hidden, interior hidden, breakable, center, listing only,
    listing file={#3},
    minted language=#2,
    minted options={frame=lines, framesep=2mm, fontsize=\footnotesize, autogobble, linenos, breaklines,#1},
}
\newtcblisting{code}[2][]{
    after={\par\smallskip\noindent}, enhanced, frame hidden, colback=black!3!white, breakable, center, listing only,
    minted language=#2,
    minted options={frame=none, fontsize=\small, autogobble, breaklines, #1}
}

% 重定义标题
\renewcommand\maketitle{
    \pdfbookmark[1]{标题页}{title}
    \newgeometry{margin=2.54cm}
    \begin{titlepage}
        \centering\null
        \vskip 1cm
        \includegraphics[height=1.3cm]{assets/title-name.pdf}
        \par\vskip 1cm
        {\titlebf\fontsize{56bp}{56bp}\selectfont\ned@type}
        \par\vskip 2cm
        {\ustcblue\includegraphics[height=5cm]{assets/title-badge.pdf}}
        \par\vskip 1cm
        \parbox[t][3cm][c]{\textwidth}{
            \centering\titlebf\Huge
            \ned@course\\\ned@title
        }
        \par\vskip 1cm
        {
            \fontsize{16bp}{31bp}\selectfont
            \begin{tabular}{@{}l@{\hspace{\ccwd}}l@{}}
                \titlebf{学生姓名：} & \ned@author \\
                \titlebf{学生学号：} & \ned@id \\
                \titlebf{完成时间：} & \getdatezhbig \\
            \end{tabular}
        }
    \end{titlepage}
    \clearpage
    \restoregeometry
}

% 重定义目录
\renewcommand\tableofcontents{
    \pdfbookmark[1]{目录}{toc}
    \begin{center}      
        \large\bf\contentsname
    \end{center}
    \@starttoc{toc}
    \clearpage
}
\newcommand\tocleaders{\titlerule*[9bp]{\textperiodcentered}}
\titlecontents{section}
    [\z@]{\addvspace{6bp}}
    {\contentspush{\thecontentslabel\hspace{\ccwd}}}{}
    {\tocleaders\contentspage}
\titlecontents{subsection}
    [2\ccwd]{\addvspace{6bp}\fangsong}
    {\contentspush{\thecontentslabel\hspace{\ccwd}}}{}
    {\tocleaders\contentspage}
\titlecontents{subsubsection}
    [4\ccwd]{\addvspace{6bp}\fangsong}
    {\contentspush{\thecontentslabel\hspace{\ccwd}}}{}
    {\tocleaders\contentspage}

