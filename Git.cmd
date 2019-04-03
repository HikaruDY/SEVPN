@echo off

set GIT=git.exe
%GIT% >nul 2>nul
IF "%ERRORLEVEL%" == "9009" set GIT=T:\git\bin\git.exe

set GIT_AUTHOR_NAME="Hikaru Kurosaki"
set GIT_AUTHOR_EMAIL="hikaru-oss@dark-x.org"
set GIT_COMMITTER_NAME=%GIT_AUTHOR_NAME%
set GIT_COMMITTER_EMAIL=%GIT_AUTHOR_EMAIL%

IF "%~1" == "push-all" GOTO PUSH_ALL

:MAIN
%GIT% %*
GOTO EOF

:PUSH_ALL
%GIT% push origin %2 %3 %4 %5 %6 %7 %8 %9
%GIT% push github %2 %3 %4 %5 %6 %7 %8 %9
GOTO EOF

:EOF
