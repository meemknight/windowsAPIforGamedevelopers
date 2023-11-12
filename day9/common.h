#pragma once


extern "C" __declspec(dllexport) void foo();
typedef void foo_t();

//shorthand trick
//#define FOO(x) void x()
//extern "C" __declspec(dllexport) FOO(foo);
//typedef FOO(foo_t);
//#undef FOO