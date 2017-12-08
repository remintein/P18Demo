@echo off


@REM =====================================================================
@REM date=%Date:~0,4%%Date:~5,2%%Date:~8,2%%Time:~0,2%%Time:~3,2%%Time:~6,2%
svn update
svn info | findstr Revision: > ver.tmp
set /p version_name=<ver.tmp
set verion_name=%version_name:~10,5%
del /Q ver.tmp

set versiondate=%Date:~2,2%%Date:~5,2%%Date:~8,2%
set versiontime=%Time:~0,2%%Time:~3,2%%Time:~6,2%
set verion_name=.SVN%version_name:~10,5%
set version_h=.\src\version.h
set DEVICE_NAME=P18.0102.DC4
REM *** GENERATE THE DEFAULT VERSION ***

@echo =========== GENERATE THE DEFAULT VERSION ===========
@echo /** > %version_h%
@echo * Automatic Generate By Prebuild.bat, Should Not edit >>%version_h%
@echo * @file version.h >> %version_h%
@echo * @version 1.0   >>%version_h%
@echo * @date %Date:~0,4%-%Date:~5,2%-%Date:~8,2%  >>%version_h%
@echo *  >>%version_h%
@echo * @brief 终端版本定义  >>%version_h%
@echo *  \li 终端名称  >>%version_h%
@echo *  \li 终端硬件、软件版本  >>%version_h%
@echo *  \li 项目版本  >>%version_h%
@echo *  \todo 增加编译日期  >>%version_h%
@echo *   >>%version_h%
@echo *  >>%version_h%
@echo *   >>%version_h%
@echo */  >>%version_h%
@echo #ifndef _VERSION_H_  >>%version_h%
@echo #define _VERSION_H_  >>%version_h%
@echo #define STR_FIRMWARE_VERSION			"1.0.0"  >>%version_h%
@echo #define SIZE_HARDWARE_VERSION			5  >>%version_h%
@echo #define STR_HARDWARE_VESION			"1.0.0"  >>%version_h%
@echo #define DEVICE_VERSION		"%DEVICE_NAME%%verion_name%.%versiondate%"  >>%version_h%
@echo #define __BUILD_DATE__		"%versiondate%"  >>%version_h%
@echo #define __BUILD_TIME__		"%versiontime%"  >>%version_h%
@echo #endif >> %version_h%  >>%version_h%

@REM *** if silence: NO versionibuild echo****
IF /I "%1" NEQ "/S"  echo *** Build %version_name%, %versiondate%***

@REM start notepad %version_h%