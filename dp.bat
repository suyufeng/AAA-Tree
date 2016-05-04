@echo off
:again
call test
call std
call my
fc forest.standard forest.output
if %errorlevel% == 1 pause > nul & exit
goto again