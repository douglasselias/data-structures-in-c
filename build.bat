@echo off

cl

if %ERRORLEVEL% neq 0 (
  call "C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvars64.bat"
)

cls

rmdir /S /Q .\build
mkdir build
pushd .\build

set better_output=/nologo /diagnostics:caret /FC
set basic_optimizations=/Oi /fp:fast /fp:except- /jumptablerdata /kernel /GS- /Gs9999999
set warnings=/WX /W4
set disable_stupid_errors=/wd4189 /wd4700 /wd4100 /wd4996 /wd4244
set compiler_base_flags=%better_output% %basic_optimizations% %warnings% %disable_stupid_errors% /cgthreads8 /MD /utf-8

set compiler_debug_flags=/Z7 /Zo /RTCc
@REM set compiler_release_flags=/Gw /GL /O2

cl %compiler_base_flags% %compiler_debug_flags% "..\src\string.c"

string.exe

popd
