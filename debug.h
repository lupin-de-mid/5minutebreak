//
// debug.h
// Copyright (c) Czarek Tomczak. All rights reserved.
//

#pragma once

#define CONCAT_NX(s1, s2) s1 ## s2
#define CONCAT(s1, s2) CONCAT_NX(s1, s2)

#define STRINGIZE_NX(A) #A
#define STRINGIZE(A) STRINGIZE_NX(A)

#define ASSERT(expr, message) if (!expr) MessageBoxA(NULL, CONCAT(message, CONCAT("\n\nFile: ", CONCAT(__FILE__, CONCAT("\nLine: ", CONCAT(STRINGIZE(__LINE__), CONCAT("\nFunc: ", __FUNCTION__)))))), "Assertion failed", MB_ICONERROR)

#define ASSERT_EXIT(expr, message) if (!expr) { MessageBoxA(NULL, CONCAT(message, CONCAT("\n\nFile: ", CONCAT(__FILE__, CONCAT("\nLine: ", CONCAT(STRINGIZE(__LINE__), CONCAT("\nFunc: ", __FUNCTION__)))))), "Assertion failed - exiting", MB_ICONERROR); exit(-1); }

#define FATAL_ERROR(message) MessageBoxA(NULL, CONCAT(message, CONCAT("\n\nFile: ", CONCAT(__FILE__, CONCAT("\nLine: ", CONCAT(STRINGIZE(__LINE__), CONCAT("\nFunc: ", __FUNCTION__)))))), "Fatal error", MB_ICONERROR); exit(-1)

#define DEBUG_INT(A) { char tmpstr[4096]; sprintf_s(tmpstr, 4096, "%i\n\nFile: %s\nLine: %s\nFunc: %s()", A, __FILE__, STRINGIZE(__LINE__), __FUNCTION__); MessageBoxA(NULL, tmpstr, "DEBUG int", MB_ICONINFORMATION); }

#define DEBUG_INT4(A, B, C, D) { char tmpstr[4096]; sprintf_s(tmpstr, 4096, "%i,%i,%i,%i\n\nFile: %s\nLine: %s\nFunc: %s()", A, B, C, D, __FILE__, STRINGIZE(__LINE__), __FUNCTION__); MessageBoxA(NULL, tmpstr, "DEBUG int4", MB_ICONINFORMATION); }

#define DEBUG_DWORD(A) { char tmpstr[4096]; sprintf_s(tmpstr, 4096, "%lu\n\nFile: %s\nLine: %s\nFunc: %s()", A, __FILE__, STRINGIZE(__LINE__), __FUNCTION__); MessageBoxA(NULL, tmpstr, "DEBUG int", MB_ICONINFORMATION); }

#define DEBUG_ASCII(A) { char tmpstr[4096]; sprintf_s(tmpstr, 4096, "%s\n\nFile: %s\nLine: %s\nFunc: %s()", A, __FILE__, STRINGIZE(__LINE__), __FUNCTION__); MessageBoxA(NULL, tmpstr, "DEBUG", MB_ICONINFORMATION); }

#define DEBUG_ASCII_2(A, B) { char tmpstr[4096]; sprintf_s(tmpstr, 4096, "%s\n%s\n\nFile: %s\nLine: %s\nFunc: %s()", A, B, __FILE__, STRINGIZE(__LINE__), __FUNCTION__); MessageBoxA(NULL, tmpstr, "DEBUG2", MB_ICONINFORMATION); }

char* WideToAscii(wchar_t* wide);

#define DEBUG_WIDE(A) { char tmpstr[4096]; sprintf_s(tmpstr, 4096, "%s\n\nFile: %s\nLine: %s\nFunc: %s()", WideToAscii(A), __FILE__, STRINGIZE(__LINE__), __FUNCTION__); MessageBoxA(NULL, tmpstr, "DEBUG", MB_ICONINFORMATION); }

#define DEBUG_WIDE_2(A, B) { char tmpstr[4096]; sprintf_s(tmpstr, 4096, "%s\n%s\n\nFile: %s\nLine: %s\nFunc: %s()", WideToAscii(A), WideToAscii(B), __FILE__, STRINGIZE(__LINE__), __FUNCTION__); MessageBoxA(NULL, tmpstr, "DEBUG", MB_ICONINFORMATION); }
