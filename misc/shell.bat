@echo off
pushd C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\
call vcvarsall.bat x64
popd

set path=C:\GIT\HandmadeHero\code;%path%

