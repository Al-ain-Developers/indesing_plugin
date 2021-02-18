@echo off
if "%1" EQU "" goto badargs
if "%2" EQU "" goto badargs

set str=%1
set str=%str:\"="%

set RESFILE=%str%\%2.res
set TEMPRESFILE=%str%\_%2.res

if not exist %TEMPRESFILE% goto :done
copy %TEMPRESFILE%  %RESFILE% 
del %TEMPRESFILE% 

goto done

:badargs
echo Bad arguments to restore_res.cmd
echo    Usage restore_res.cmd $(IntDir) ResourceFile
echo    Where ResourceFile is the filename without .res 
echo    Example: restore_res.cmd $(IntDir) TableModel

goto done

:done
echo restore_res.cmd done.
