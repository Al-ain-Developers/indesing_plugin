@echo off
if "%1" EQU "" goto badargs
if "%2" EQU "" goto badargs

set str=%1
set str=%str:\"="%

set RESFILE=%str%\%2.res
set TEMPRESFILE=%str%\_%2.res

if "%3" NEQ "" goto fresspecified
set FRESFILE=%str%\%2.fres
goto fresset

:fresspecified
set FRESFILE=%str%\%3.fres

:fresset

rem echo %RESFILE%
rem echo %FRESFILE%
rem echo %TEMPRESFILE%

if not exist %RESFILE% goto ResourceFileNotExist
if not exist %FRESFILE% goto FResFileNotExist

if exist %TEMPRESFILE% goto checktime
goto doconcat

:checktime
cmpmodtime.exe %RESFILE% %TEMPRESFILE%
rem If res file time stamp is not same as temp res file, doconcat
if %errorlevel% NEQ 0 goto doconcat

echo Checking against fres file.
cmpmodtime.exe %FRESFILE% %RESFILE% 
rem If fres file is not newer than res file skipconcat
if %errorlevel% NEQ 1 goto skipconcat
copy %TEMPRESFILE% %RESFILE%

:doconcat
echo merge_res.cmd - calling ConcatRes
copy %RESFILE% %TEMPRESFILE%
ConcatRes %RESFILE% %FRESFILE%
set CONCATRETVAL=%errorlevel%
if %CONCATRETVAL% EQU 2 goto ConcatFailure
if %CONCATRETVAL% EQU 1 goto NothingConcatenated
atouch %RESFILE% %TEMPRESFILE%
goto done

:ConcatFailure
del %TEMPRESFILE% 
echo ConcatRes command failed.
goto done

:NothingConcatenated
echo ConcatRes skipped since %FRESFILE% is an empty file.
goto done

:ResourceFileNotExist
echo %RESFILE% doesn't exist
goto badargs

:FResFileNotExist
echo %FRESFILE% doesn't exist
goto badargs

:badargs
echo Bad arguments to merge_res.cmd  
echo    Usage 
echo       1)merge_res.cmd $(IntDir) ResourceFile
echo       2)merge_res.cmd $(IntDir) ResourceFile CoreResourceFile
echo	Use 1) if the platform and core resourfile names are the same.
echo    Use 2) if they are different.
echo    Where ResourceFile is the filename without .res 
echo          CoreResourceFile is the filename without .fres 
echo    Example: 1) merge_res.cmd $(IntDir) TableModel
echo             2) merge_res.cmd $(IntDir) TableModel TableModelCore
goto done

:skipconcat
echo merge_res.cmd Skipping ConcatRes

:done
echo merge_res.cmd done.
