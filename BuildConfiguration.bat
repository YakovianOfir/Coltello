@ECHO off
ECHO:

REM ECHO ************************************************************
REM ECHO *               	  Beautify Console						*  
REM ECHO ************************************************************
REM ECHO .

TITLE Coltello Enlistment
COLOR 1F

REM ECHO ************************************************************
REM ECHO *            Resolve Enlistment Folder						*  
REM ECHO ************************************************************
REM ECHO .

SET EnlistmentDir=%~dp0
SET EnlistmentDir=%EnlistmentDir:~0,-1%

REM ECHO ************************************************************
REM ECHO *              Assign Wrokspace Folders					*  
REM ECHO ************************************************************
REM ECHO .

SET SourcesDir=%EnlistmentDir%\Source
SET BuildDir=%EnlistmentDir%\Build

REM ECHO ************************************************************
REM ECHO *                Assign Build Variables 					*  
REM ECHO ************************************************************
REM ECHO .

SET COLTELLO_BUILD_CONFIG=%1
SET COLTELLO_BUILD_PLATFORM=%2

REM ECHO ************************************************************
REM ECHO *               	  Beautify Console						*  
REM ECHO ************************************************************
REM ECHO .

TITLE Coltello Build [%COLTELLO_BUILD_CONFIG%^|^%COLTELLO_BUILD_PLATFORM%]
COLOR 1F

ECHO ************************************************************
ECHO *    		Activating Build   
ECHO ************************************************************
ECHO .

MSBuild.exe %SourcesDir%\Coltello.sln /property:Configuration=%COLTELLO_BUILD_CONFIG% /property:Platform=%COLTELLO_BUILD_PLATFORM% /property:OutputPath=%BuildDir% /t:Clean;Rebuild

REM ECHO ************************************************************
REM ECHO *               	  Beautify Console						*  
REM ECHO ************************************************************
REM ECHO .

TITLE Coltello Enlistment
COLOR 1F	