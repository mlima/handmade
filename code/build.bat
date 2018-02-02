@echo off

mkdir ..\..\build

pushd ..\..\build
cl ..\HandmadeHero\code\win32_handmade.cpp
popd