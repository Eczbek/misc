#include <type_traits>

// #define A template<template<
// #define B > class M,
// #define C > int z(std::type_identity<M<
// #define D >>);template<template<
// #define E >>);

// A
// class B class a C a D
// class... B class... a C a... D
// auto B auto a C a D
// auto... B auto... a C a... D
// class, auto B class a, auto b C a, b D
// class, auto... B class a, auto... b C a, b... D
// class, class, auto B class a, class b, auto c C a, b, c D
// class, class, auto... B class a, class b, auto... c C a, b, c... D
// class, class, class, auto B class a, class b, class c, auto d C a, b, c, d D
// class, class, class, auto... B class a, class b, class c, auto... d C a, b, c, d... D
// class, class, class, class, auto B class a, class b, class c, class d, auto e C a, b, c, d, e D
// class, class, class, class, auto... B class a, class b, class c, class d, auto... e C a, b, c, d, e... D
// class, class, class, class, class, auto B class a, class b, class c, class d, class e, auto f C a, b, c, d, e, f D
// class, class, class, class, class, auto... B class a, class b, class c, class d, class e, auto... f C a, b, c, d, e, f... D
// class, class, class, class, class, class, auto B class a, class b, class c, class d, class e, class f, auto g C a, b, c, d, e, f, g D
// class, class, class, class, class, class, auto... B class a, class b, class c, class d, class e, class f, auto... g C a, b, c, d, e, f, g... D
// class, class, class, class, class, class, class, auto B class a, class b, class c, class d, class e, class f, class g, auto h C a, b, c, d, e, f, g, h D
// class, class, class, class, class, class, class, auto... B class a, class b, class c, class d, class e, class f, class g, auto... h C a, b, c, d, e, f, g, h... D
// class, auto, class B class a, auto b, class c C a, b, c D
// class, auto, class... B class a, auto b, class... c C a, b, c... D
// class, class, auto, class B class a, class b, auto c, class d C a, b, c, d D
// class, class, auto, class... B class a, class b, auto c, class... d C a, b, c, d... D
// class, auto, auto, class B class a, auto b, auto c, class d C a, b, c, d D
// class, auto, auto, class... B class a, auto b, auto c, class... d C a, b, c, d... D
// class, class, class, auto, class B class a, class b, class c, auto d, class e C a, b, c, d, e D
// class, class, class, auto, class... B class a, class b, class c, auto d, class... e C a, b, c, d, e... D
// class, auto, class, auto, class B class a, auto b, class c, auto d, class e C a, b, c, d, e D
// class, auto, class, auto, class... B class a, auto b, class c, auto d, class... e C a, b, c, d, e... D
// class, class, auto, auto, class B class a, class b, auto c, auto d, class e C a, b, c, d, e D
// class, class, auto, auto, class... B class a, class b, auto c, auto d, class... e C a, b, c, d, e... D
// class, auto, auto, auto, class B class a, auto b, auto c, auto d, class e C a, b, c, d, e D
// class, auto, auto, auto, class... B class a, auto b, auto c, auto d, class... e C a, b, c, d, e... D
// class, class, class, class, auto, class B class a, class b, class c, class d, auto e, class f C a, b, c, d, e, f D
// class, class, class, class, auto, class... B class a, class b, class c, class d, auto e, class... f C a, b, c, d, e, f... D
// class, auto, class, class, auto, class B class a, auto b, class c, class d, auto e, class f C a, b, c, d, e, f D
// class, auto, class, class, auto, class... B class a, auto b, class c, class d, auto e, class... f C a, b, c, d, e, f... D
// class, class, auto, class, auto, class B class a, class b, auto c, class d, auto e, class f C a, b, c, d, e, f D
// class, class, auto, class, auto, class... B class a, class b, auto c, class d, auto e, class... f C a, b, c, d, e, f... D
// class, auto, auto, class, auto, class B class a, auto b, auto c, class d, auto e, class f C a, b, c, d, e, f D
// class, auto, auto, class, auto, class... B class a, auto b, auto c, class d, auto e, class... f C a, b, c, d, e, f... D
// class, class, class, auto, auto, class B class a, class b, class c, auto d, auto e, class f C a, b, c, d, e, f D
// class, class, class, auto, auto, class... B class a, class b, class c, auto d, auto e, class... f C a, b, c, d, e, f... D
// class, auto, class, auto, auto, class B class a, auto b, class c, auto d, auto e, class f C a, b, c, d, e, f D
// class, auto, class, auto, auto, class... B class a, auto b, class c, auto d, auto e, class... f C a, b, c, d, e, f... D
// class, class, auto, auto, auto, class B class a, class b, auto c, auto d, auto e, class f C a, b, c, d, e, f D
// class, class, auto, auto, auto, class... B class a, class b, auto c, auto d, auto e, class... f C a, b, c, d, e, f... D
// class, auto, auto, auto, auto, class B class a, auto b, auto c, auto d, auto e, class f C a, b, c, d, e, f D
// class, auto, auto, auto, auto, class... B class a, auto b, auto c, auto d, auto e, class... f C a, b, c, d, e, f... D
// class, class, class, class, class, class, class B class a, class b, class c, class d, class e, class f, class g C a, b, c, d, e, f, g D
// class, class, class, class, class, class, class... B class a, class b, class c, class d, class e, class f, class... g C a, b, c, d, e, f, g... D
// class, auto, class, class, class, class, class B class a, auto b, class c, class d, class e, class f, class g C a, b, c, d, e, f, g D
// class, auto, class, class, class, class, class... B class a, auto b, class c, class d, class e, class f, class... g C a, b, c, d, e, f, g... D
// class, class, auto, class, class, class, class B class a, class b, auto c, class d, class e, class f, class g C a, b, c, d, e, f, g D
// class, class, auto, class, class, class, class... B class a, class b, auto c, class d, class e, class f, class... g C a, b, c, d, e, f, g... D
// class, auto, auto, class, class, class, class B class a, auto b, auto c, class d, class e, class f, class g C a, b, c, d, e, f, g D
// class, auto, auto, class, class, class, class... B class a, auto b, auto c, class d, class e, class f, class... g C a, b, c, d, e, f, g... D
// class, class, class, auto, class, class, class B class a, class b, class c, auto d, class e, class f, class g C a, b, c, d, e, f, g D
// class, class, class, auto, class, class, class... B class a, class b, class c, auto d, class e, class f, class... g C a, b, c, d, e, f, g... D
// class, auto, class, auto, class, class, class B class a, auto b, class c, auto d, class e, class f, class g C a, b, c, d, e, f, g D
// class, auto, class, auto, class, class, class... B class a, auto b, class c, auto d, class e, class f, class... g C a, b, c, d, e, f, g... D
// class, class, auto, auto, class, class, class B class a, class b, auto c, auto d, class e, class f, class g C a, b, c, d, e, f, g D
// class, class, auto, auto, class, class, class... B class a, class b, auto c, auto d, class e, class f, class... g C a, b, c, d, e, f, g... D
// class, auto, auto, auto, class, class, class B class a, auto b, auto c, auto d, class e, class f, class g C a, b, c, d, e, f, g D
// class, auto, auto, auto, class, class, class... B class a, auto b, auto c, auto d, class e, class f, class... g C a, b, c, d, e, f, g... D
// class, class, class, class, auto, class, class B class a, class b, class c, class d, auto e, class f, class g C a, b, c, d, e, f, g D
// class, class, class, class, auto, class, class... B class a, class b, class c, class d, auto e, class f, class... g C a, b, c, d, e, f, g... D
// class, auto, class, class, auto, class, class B class a, auto b, class c, class d, auto e, class f, class g C a, b, c, d, e, f, g D
// class, auto, class, class, auto, class, class... B class a, auto b, class c, class d, auto e, class f, class... g C a, b, c, d, e, f, g... D
// class, class, auto, class, auto, class, class B class a, class b, auto c, class d, auto e, class f, class g C a, b, c, d, e, f, g D
// class, class, auto, class, auto, class, class... B class a, class b, auto c, class d, auto e, class f, class... g C a, b, c, d, e, f, g... D
// class, auto, auto, class, auto, class, class B class a, auto b, auto c, class d, auto e, class f, class g C a, b, c, d, e, f, g D
// class, auto, auto, class, auto, class, class... B class a, auto b, auto c, class d, auto e, class f, class... g C a, b, c, d, e, f, g... D
// class, class, class, auto, auto, class, class B class a, class b, class c, auto d, auto e, class f, class g C a, b, c, d, e, f, g D
// class, class, class, auto, auto, class, class... B class a, class b, class c, auto d, auto e, class f, class... g C a, b, c, d, e, f, g... D
// class, auto, class, auto, auto, class, class B class a, auto b, class c, auto d, auto e, class f, class g C a, b, c, d, e, f, g D
// class, auto, class, auto, auto, class, class... B class a, auto b, class c, auto d, auto e, class f, class... g C a, b, c, d, e, f, g... D
// class, class, auto, auto, auto, class, class B class a, class b, auto c, auto d, auto e, class f, class g C a, b, c, d, e, f, g D
// class, class, auto, auto, auto, class, class... B class a, class b, auto c, auto d, auto e, class f, class... g C a, b, c, d, e, f, g... D
// class, auto, auto, auto, auto, class, class B class a, auto b, auto c, auto d, auto e, class f, class g C a, b, c, d, e, f, g D
// class, auto, auto, auto, auto, class, class... B class a, auto b, auto c, auto d, auto e, class f, class... g C a, b, c, d, e, f, g... D
// class, class, class, class, class, auto, class B class a, class b, class c, class d, class e, auto f, class g C a, b, c, d, e, f, g D
// class, class, class, class, class, auto, class... B class a, class b, class c, class d, class e, auto f, class... g C a, b, c, d, e, f, g... D
// class, auto, class, class, class, auto, class B class a, auto b, class c, class d, class e, auto f, class g C a, b, c, d, e, f, g D
// class, auto, class, class, class, auto, class... B class a, auto b, class c, class d, class e, auto f, class... g C a, b, c, d, e, f, g... D
// class, class, auto, class, class, auto, class B class a, class b, auto c, class d, class e, auto f, class g C a, b, c, d, e, f, g D
// class, class, auto, class, class, auto, class... B class a, class b, auto c, class d, class e, auto f, class... g C a, b, c, d, e, f, g... D
// class, auto, auto, class, class, auto, class B class a, auto b, auto c, class d, class e, auto f, class g C a, b, c, d, e, f, g D
// class, auto, auto, class, class, auto, class... B class a, auto b, auto c, class d, class e, auto f, class... g C a, b, c, d, e, f, g... D
// class, class, class, auto, class, auto, class B class a, class b, class c, auto d, class e, auto f, class g C a, b, c, d, e, f, g D
// class, class, class, auto, class, auto, class... B class a, class b, class c, auto d, class e, auto f, class... g C a, b, c, d, e, f, g... D
// class, auto, class, auto, class, auto, class B class a, auto b, class c, auto d, class e, auto f, class g C a, b, c, d, e, f, g D
// class, auto, class, auto, class, auto, class... B class a, auto b, class c, auto d, class e, auto f, class... g C a, b, c, d, e, f, g... D
// class, class, auto, auto, class, auto, class B class a, class b, auto c, auto d, class e, auto f, class g C a, b, c, d, e, f, g D
// class, class, auto, auto, class, auto, class... B class a, class b, auto c, auto d, class e, auto f, class... g C a, b, c, d, e, f, g... D
// class, auto, auto, auto, class, auto, class B class a, auto b, auto c, auto d, class e, auto f, class g C a, b, c, d, e, f, g D
// class, auto, auto, auto, class, auto, class... B class a, auto b, auto c, auto d, class e, auto f, class... g C a, b, c, d, e, f, g... D
// class, class, class, class, auto, auto, class B class a, class b, class c, class d, auto e, auto f, class g C a, b, c, d, e, f, g D
// class, class, class, class, auto, auto, class... B class a, class b, class c, class d, auto e, auto f, class... g C a, b, c, d, e, f, g... D
// class, auto, class, class, auto, auto, class B class a, auto b, class c, class d, auto e, auto f, class g C a, b, c, d, e, f, g D
// class, auto, class, class, auto, auto, class... B class a, auto b, class c, class d, auto e, auto f, class... g C a, b, c, d, e, f, g... D
// class, class, auto, class, auto, auto, class B class a, class b, auto c, class d, auto e, auto f, class g C a, b, c, d, e, f, g D
// class, class, auto, class, auto, auto, class... B class a, class b, auto c, class d, auto e, auto f, class... g C a, b, c, d, e, f, g... D
// class, auto, auto, class, auto, auto, class B class a, auto b, auto c, class d, auto e, auto f, class g C a, b, c, d, e, f, g D
// class, auto, auto, class, auto, auto, class... B class a, auto b, auto c, class d, auto e, auto f, class... g C a, b, c, d, e, f, g... D
// class, class, class, auto, auto, auto, class B class a, class b, class c, auto d, auto e, auto f, class g C a, b, c, d, e, f, g D
// class, class, class, auto, auto, auto, class... B class a, class b, class c, auto d, auto e, auto f, class... g C a, b, c, d, e, f, g... D
// class, auto, class, auto, auto, auto, class B class a, auto b, class c, auto d, auto e, auto f, class g C a, b, c, d, e, f, g D
// class, auto, class, auto, auto, auto, class... B class a, auto b, class c, auto d, auto e, auto f, class... g C a, b, c, d, e, f, g... D
// class, class, auto, auto, auto, auto, class B class a, class b, auto c, auto d, auto e, auto f, class g C a, b, c, d, e, f, g D
// class, class, auto, auto, auto, auto, class... B class a, class b, auto c, auto d, auto e, auto f, class... g C a, b, c, d, e, f, g... D
// class, auto, auto, auto, auto, auto, class B class a, auto b, auto c, auto d, auto e, auto f, class g C a, b, c, d, e, f, g D
// class, auto, auto, auto, auto, auto, class... B class a, auto b, auto c, auto d, auto e, auto f, class... g C a, b, c, d, e, f, g... D
// class, class, class, class, class, class, class, class B class a, class b, class c, class d, class e, class f, class g, class h C a, b, c, d, e, f, g, h D
// class, class, class, class, class, class, class, class... B class a, class b, class c, class d, class e, class f, class g, class... h C a, b, c, d, e, f, g, h... D
// class, auto, class, class, class, class, class, class B class a, auto b, class c, class d, class e, class f, class g, class h C a, b, c, d, e, f, g, h D
// class, auto, class, class, class, class, class, class... B class a, auto b, class c, class d, class e, class f, class g, class... h C a, b, c, d, e, f, g, h... D
// class, class, auto, class, class, class, class, class B class a, class b, auto c, class d, class e, class f, class g, class h C a, b, c, d, e, f, g, h D
// class, class, auto, class, class, class, class, class... B class a, class b, auto c, class d, class e, class f, class g, class... h C a, b, c, d, e, f, g, h... D
// class, auto, auto, class, class, class, class, class B class a, auto b, auto c, class d, class e, class f, class g, class h C a, b, c, d, e, f, g, h D
// class, auto, auto, class, class, class, class, class... B class a, auto b, auto c, class d, class e, class f, class g, class... h C a, b, c, d, e, f, g, h... D
// class, class, class, auto, class, class, class, class B class a, class b, class c, auto d, class e, class f, class g, class h C a, b, c, d, e, f, g, h D
// class, class, class, auto, class, class, class, class... B class a, class b, class c, auto d, class e, class f, class g, class... h C a, b, c, d, e, f, g, h... D
// class, auto, class, auto, class, class, class, class B class a, auto b, class c, auto d, class e, class f, class g, class h C a, b, c, d, e, f, g, h D
// class, auto, class, auto, class, class, class, class... B class a, auto b, class c, auto d, class e, class f, class g, class... h C a, b, c, d, e, f, g, h... D
// class, class, auto, auto, class, class, class, class B class a, class b, auto c, auto d, class e, class f, class g, class h C a, b, c, d, e, f, g, h D
// class, class, auto, auto, class, class, class, class... B class a, class b, auto c, auto d, class e, class f, class g, class... h C a, b, c, d, e, f, g, h... D
// class, auto, auto, auto, class, class, class, class B class a, auto b, auto c, auto d, class e, class f, class g, class h C a, b, c, d, e, f, g, h D
// class, auto, auto, auto, class, class, class, class... B class a, auto b, auto c, auto d, class e, class f, class g, class... h C a, b, c, d, e, f, g, h... D
// class, class, class, class, auto, class, class, class B class a, class b, class c, class d, auto e, class f, class g, class h C a, b, c, d, e, f, g, h D
// class, class, class, class, auto, class, class, class... B class a, class b, class c, class d, auto e, class f, class g, class... h C a, b, c, d, e, f, g, h... D
// class, auto, class, class, auto, class, class, class B class a, auto b, class c, class d, auto e, class f, class g, class h C a, b, c, d, e, f, g, h D
// class, auto, class, class, auto, class, class, class... B class a, auto b, class c, class d, auto e, class f, class g, class... h C a, b, c, d, e, f, g, h... D
// class, class, auto, class, auto, class, class, class B class a, class b, auto c, class d, auto e, class f, class g, class h C a, b, c, d, e, f, g, h D
// class, class, auto, class, auto, class, class, class... B class a, class b, auto c, class d, auto e, class f, class g, class... h C a, b, c, d, e, f, g, h... D
// class, auto, auto, class, auto, class, class, class B class a, auto b, auto c, class d, auto e, class f, class g, class h C a, b, c, d, e, f, g, h D
// class, auto, auto, class, auto, class, class, class... B class a, auto b, auto c, class d, auto e, class f, class g, class... h C a, b, c, d, e, f, g, h... D
// class, class, class, auto, auto, class, class, class B class a, class b, class c, auto d, auto e, class f, class g, class h C a, b, c, d, e, f, g, h D
// class, class, class, auto, auto, class, class, class... B class a, class b, class c, auto d, auto e, class f, class g, class... h C a, b, c, d, e, f, g, h... D
// class, auto, class, auto, auto, class, class, class B class a, auto b, class c, auto d, auto e, class f, class g, class h C a, b, c, d, e, f, g, h D
// class, auto, class, auto, auto, class, class, class... B class a, auto b, class c, auto d, auto e, class f, class g, class... h C a, b, c, d, e, f, g, h... D
// class, class, auto, auto, auto, class, class, class B class a, class b, auto c, auto d, auto e, class f, class g, class h C a, b, c, d, e, f, g, h D
// class, class, auto, auto, auto, class, class, class... B class a, class b, auto c, auto d, auto e, class f, class g, class... h C a, b, c, d, e, f, g, h... D
// class, auto, auto, auto, auto, class, class, class B class a, auto b, auto c, auto d, auto e, class f, class g, class h C a, b, c, d, e, f, g, h D
// class, auto, auto, auto, auto, class, class, class... B class a, auto b, auto c, auto d, auto e, class f, class g, class... h C a, b, c, d, e, f, g, h... D
// class, class, class, class, class, auto, class, class B class a, class b, class c, class d, class e, auto f, class g, class h C a, b, c, d, e, f, g, h D
// class, class, class, class, class, auto, class, class... B class a, class b, class c, class d, class e, auto f, class g, class... h C a, b, c, d, e, f, g, h... D
// class, auto, class, class, class, auto, class, class B class a, auto b, class c, class d, class e, auto f, class g, class h C a, b, c, d, e, f, g, h D
// class, auto, class, class, class, auto, class, class... B class a, auto b, class c, class d, class e, auto f, class g, class... h C a, b, c, d, e, f, g, h... D
// class, class, auto, class, class, auto, class, class B class a, class b, auto c, class d, class e, auto f, class g, class h C a, b, c, d, e, f, g, h D
// class, class, auto, class, class, auto, class, class... B class a, class b, auto c, class d, class e, auto f, class g, class... h C a, b, c, d, e, f, g, h... D
// class, auto, auto, class, class, auto, class, class B class a, auto b, auto c, class d, class e, auto f, class g, class h C a, b, c, d, e, f, g, h D
// class, auto, auto, class, class, auto, class, class... B class a, auto b, auto c, class d, class e, auto f, class g, class... h C a, b, c, d, e, f, g, h... D
// class, class, class, auto, class, auto, class, class B class a, class b, class c, auto d, class e, auto f, class g, class h C a, b, c, d, e, f, g, h D
// class, class, class, auto, class, auto, class, class... B class a, class b, class c, auto d, class e, auto f, class g, class... h C a, b, c, d, e, f, g, h... D
// class, auto, class, auto, class, auto, class, class B class a, auto b, class c, auto d, class e, auto f, class g, class h C a, b, c, d, e, f, g, h D
// class, auto, class, auto, class, auto, class, class... B class a, auto b, class c, auto d, class e, auto f, class g, class... h C a, b, c, d, e, f, g, h... D
// class, class, auto, auto, class, auto, class, class B class a, class b, auto c, auto d, class e, auto f, class g, class h C a, b, c, d, e, f, g, h D
// class, class, auto, auto, class, auto, class, class... B class a, class b, auto c, auto d, class e, auto f, class g, class... h C a, b, c, d, e, f, g, h... D
// class, auto, auto, auto, class, auto, class, class B class a, auto b, auto c, auto d, class e, auto f, class g, class h C a, b, c, d, e, f, g, h D
// class, auto, auto, auto, class, auto, class, class... B class a, auto b, auto c, auto d, class e, auto f, class g, class... h C a, b, c, d, e, f, g, h... D
// class, class, class, class, auto, auto, class, class B class a, class b, class c, class d, auto e, auto f, class g, class h C a, b, c, d, e, f, g, h D
// class, class, class, class, auto, auto, class, class... B class a, class b, class c, class d, auto e, auto f, class g, class... h C a, b, c, d, e, f, g, h... D
// class, auto, class, class, auto, auto, class, class B class a, auto b, class c, class d, auto e, auto f, class g, class h C a, b, c, d, e, f, g, h D
// class, auto, class, class, auto, auto, class, class... B class a, auto b, class c, class d, auto e, auto f, class g, class... h C a, b, c, d, e, f, g, h... D
// class, class, auto, class, auto, auto, class, class B class a, class b, auto c, class d, auto e, auto f, class g, class h C a, b, c, d, e, f, g, h D
// class, class, auto, class, auto, auto, class, class... B class a, class b, auto c, class d, auto e, auto f, class g, class... h C a, b, c, d, e, f, g, h... D
// class, auto, auto, class, auto, auto, class, class B class a, auto b, auto c, class d, auto e, auto f, class g, class h C a, b, c, d, e, f, g, h D
// class, auto, auto, class, auto, auto, class, class... B class a, auto b, auto c, class d, auto e, auto f, class g, class... h C a, b, c, d, e, f, g, h... D
// class, class, class, auto, auto, auto, class, class B class a, class b, class c, auto d, auto e, auto f, class g, class h C a, b, c, d, e, f, g, h D
// class, class, class, auto, auto, auto, class, class... B class a, class b, class c, auto d, auto e, auto f, class g, class... h C a, b, c, d, e, f, g, h... D
// class, auto, class, auto, auto, auto, class, class B class a, auto b, class c, auto d, auto e, auto f, class g, class h C a, b, c, d, e, f, g, h D
// class, auto, class, auto, auto, auto, class, class... B class a, auto b, class c, auto d, auto e, auto f, class g, class... h C a, b, c, d, e, f, g, h... D
// class, class, auto, auto, auto, auto, class, class B class a, class b, auto c, auto d, auto e, auto f, class g, class h C a, b, c, d, e, f, g, h D
// class, class, auto, auto, auto, auto, class, class... B class a, class b, auto c, auto d, auto e, auto f, class g, class... h C a, b, c, d, e, f, g, h... D
// class, auto, auto, auto, auto, auto, class, class B class a, auto b, auto c, auto d, auto e, auto f, class g, class h C a, b, c, d, e, f, g, h D
// class, auto, auto, auto, auto, auto, class, class... B class a, auto b, auto c, auto d, auto e, auto f, class g, class... h C a, b, c, d, e, f, g, h... D
// class, class, class, class, class, class, auto, class B class a, class b, class c, class d, class e, class f, auto g, class h C a, b, c, d, e, f, g, h D
// class, class, class, class, class, class, auto, class... B class a, class b, class c, class d, class e, class f, auto g, class... h C a, b, c, d, e, f, g, h... D
// class, auto, class, class, class, class, auto, class B class a, auto b, class c, class d, class e, class f, auto g, class h C a, b, c, d, e, f, g, h D
// class, auto, class, class, class, class, auto, class... B class a, auto b, class c, class d, class e, class f, auto g, class... h C a, b, c, d, e, f, g, h... D
// class, class, auto, class, class, class, auto, class B class a, class b, auto c, class d, class e, class f, auto g, class h C a, b, c, d, e, f, g, h D
// class, class, auto, class, class, class, auto, class... B class a, class b, auto c, class d, class e, class f, auto g, class... h C a, b, c, d, e, f, g, h... D
// class, auto, auto, class, class, class, auto, class B class a, auto b, auto c, class d, class e, class f, auto g, class h C a, b, c, d, e, f, g, h D
// class, auto, auto, class, class, class, auto, class... B class a, auto b, auto c, class d, class e, class f, auto g, class... h C a, b, c, d, e, f, g, h... D
// class, class, class, auto, class, class, auto, class B class a, class b, class c, auto d, class e, class f, auto g, class h C a, b, c, d, e, f, g, h D
// class, class, class, auto, class, class, auto, class... B class a, class b, class c, auto d, class e, class f, auto g, class... h C a, b, c, d, e, f, g, h... D
// class, auto, class, auto, class, class, auto, class B class a, auto b, class c, auto d, class e, class f, auto g, class h C a, b, c, d, e, f, g, h D
// class, auto, class, auto, class, class, auto, class... B class a, auto b, class c, auto d, class e, class f, auto g, class... h C a, b, c, d, e, f, g, h... D
// class, class, auto, auto, class, class, auto, class B class a, class b, auto c, auto d, class e, class f, auto g, class h C a, b, c, d, e, f, g, h D
// class, class, auto, auto, class, class, auto, class... B class a, class b, auto c, auto d, class e, class f, auto g, class... h C a, b, c, d, e, f, g, h... D
// class, auto, auto, auto, class, class, auto, class B class a, auto b, auto c, auto d, class e, class f, auto g, class h C a, b, c, d, e, f, g, h D
// class, auto, auto, auto, class, class, auto, class... B class a, auto b, auto c, auto d, class e, class f, auto g, class... h C a, b, c, d, e, f, g, h... D
// class, class, class, class, auto, class, auto, class B class a, class b, class c, class d, auto e, class f, auto g, class h C a, b, c, d, e, f, g, h D
// class, class, class, class, auto, class, auto, class... B class a, class b, class c, class d, auto e, class f, auto g, class... h C a, b, c, d, e, f, g, h... D
// class, auto, class, class, auto, class, auto, class B class a, auto b, class c, class d, auto e, class f, auto g, class h C a, b, c, d, e, f, g, h D
// class, auto, class, class, auto, class, auto, class... B class a, auto b, class c, class d, auto e, class f, auto g, class... h C a, b, c, d, e, f, g, h... D
// class, class, auto, class, auto, class, auto, class B class a, class b, auto c, class d, auto e, class f, auto g, class h C a, b, c, d, e, f, g, h D
// class, class, auto, class, auto, class, auto, class... B class a, class b, auto c, class d, auto e, class f, auto g, class... h C a, b, c, d, e, f, g, h... D
// class, auto, auto, class, auto, class, auto, class B class a, auto b, auto c, class d, auto e, class f, auto g, class h C a, b, c, d, e, f, g, h D
// class, auto, auto, class, auto, class, auto, class... B class a, auto b, auto c, class d, auto e, class f, auto g, class... h C a, b, c, d, e, f, g, h... D
// class, class, class, auto, auto, class, auto, class B class a, class b, class c, auto d, auto e, class f, auto g, class h C a, b, c, d, e, f, g, h D
// class, class, class, auto, auto, class, auto, class... B class a, class b, class c, auto d, auto e, class f, auto g, class... h C a, b, c, d, e, f, g, h... D
// class, auto, class, auto, auto, class, auto, class B class a, auto b, class c, auto d, auto e, class f, auto g, class h C a, b, c, d, e, f, g, h D
// class, auto, class, auto, auto, class, auto, class... B class a, auto b, class c, auto d, auto e, class f, auto g, class... h C a, b, c, d, e, f, g, h... D
// class, class, auto, auto, auto, class, auto, class B class a, class b, auto c, auto d, auto e, class f, auto g, class h C a, b, c, d, e, f, g, h D
// class, class, auto, auto, auto, class, auto, class... B class a, class b, auto c, auto d, auto e, class f, auto g, class... h C a, b, c, d, e, f, g, h... D
// class, auto, auto, auto, auto, class, auto, class B class a, auto b, auto c, auto d, auto e, class f, auto g, class h C a, b, c, d, e, f, g, h D
// class, auto, auto, auto, auto, class, auto, class... B class a, auto b, auto c, auto d, auto e, class f, auto g, class... h C a, b, c, d, e, f, g, h... D
// class, class, class, class, class, auto, auto, class B class a, class b, class c, class d, class e, auto f, auto g, class h C a, b, c, d, e, f, g, h D
// class, class, class, class, class, auto, auto, class... B class a, class b, class c, class d, class e, auto f, auto g, class... h C a, b, c, d, e, f, g, h... D
// class, auto, class, class, class, auto, auto, class B class a, auto b, class c, class d, class e, auto f, auto g, class h C a, b, c, d, e, f, g, h D
// class, auto, class, class, class, auto, auto, class... B class a, auto b, class c, class d, class e, auto f, auto g, class... h C a, b, c, d, e, f, g, h... D
// class, class, auto, class, class, auto, auto, class B class a, class b, auto c, class d, class e, auto f, auto g, class h C a, b, c, d, e, f, g, h D
// class, class, auto, class, class, auto, auto, class... B class a, class b, auto c, class d, class e, auto f, auto g, class... h C a, b, c, d, e, f, g, h... D
// class, auto, auto, class, class, auto, auto, class B class a, auto b, auto c, class d, class e, auto f, auto g, class h C a, b, c, d, e, f, g, h D
// class, auto, auto, class, class, auto, auto, class... B class a, auto b, auto c, class d, class e, auto f, auto g, class... h C a, b, c, d, e, f, g, h... D
// class, class, class, auto, class, auto, auto, class B class a, class b, class c, auto d, class e, auto f, auto g, class h C a, b, c, d, e, f, g, h D
// class, class, class, auto, class, auto, auto, class... B class a, class b, class c, auto d, class e, auto f, auto g, class... h C a, b, c, d, e, f, g, h... D
// class, auto, class, auto, class, auto, auto, class B class a, auto b, class c, auto d, class e, auto f, auto g, class h C a, b, c, d, e, f, g, h D
// class, auto, class, auto, class, auto, auto, class... B class a, auto b, class c, auto d, class e, auto f, auto g, class... h C a, b, c, d, e, f, g, h... D
// class, class, auto, auto, class, auto, auto, class B class a, class b, auto c, auto d, class e, auto f, auto g, class h C a, b, c, d, e, f, g, h D
// class, class, auto, auto, class, auto, auto, class... B class a, class b, auto c, auto d, class e, auto f, auto g, class... h C a, b, c, d, e, f, g, h... D
// class, auto, auto, auto, class, auto, auto, class B class a, auto b, auto c, auto d, class e, auto f, auto g, class h C a, b, c, d, e, f, g, h D
// class, auto, auto, auto, class, auto, auto, class... B class a, auto b, auto c, auto d, class e, auto f, auto g, class... h C a, b, c, d, e, f, g, h... D
// class, class, class, class, auto, auto, auto, class B class a, class b, class c, class d, auto e, auto f, auto g, class h C a, b, c, d, e, f, g, h D
// class, class, class, class, auto, auto, auto, class... B class a, class b, class c, class d, auto e, auto f, auto g, class... h C a, b, c, d, e, f, g, h... D
// class, auto, class, class, auto, auto, auto, class B class a, auto b, class c, class d, auto e, auto f, auto g, class h C a, b, c, d, e, f, g, h D
// class, auto, class, class, auto, auto, auto, class... B class a, auto b, class c, class d, auto e, auto f, auto g, class... h C a, b, c, d, e, f, g, h... D
// class, class, auto, class, auto, auto, auto, class B class a, class b, auto c, class d, auto e, auto f, auto g, class h C a, b, c, d, e, f, g, h D
// class, class, auto, class, auto, auto, auto, class... B class a, class b, auto c, class d, auto e, auto f, auto g, class... h C a, b, c, d, e, f, g, h... D
// class, auto, auto, class, auto, auto, auto, class B class a, auto b, auto c, class d, auto e, auto f, auto g, class h C a, b, c, d, e, f, g, h D
// class, auto, auto, class, auto, auto, auto, class... B class a, auto b, auto c, class d, auto e, auto f, auto g, class... h C a, b, c, d, e, f, g, h... D
// class, class, class, auto, auto, auto, auto, class B class a, class b, class c, auto d, auto e, auto f, auto g, class h C a, b, c, d, e, f, g, h D
// class, class, class, auto, auto, auto, auto, class... B class a, class b, class c, auto d, auto e, auto f, auto g, class... h C a, b, c, d, e, f, g, h... D
// class, auto, class, auto, auto, auto, auto, class B class a, auto b, class c, auto d, auto e, auto f, auto g, class h C a, b, c, d, e, f, g, h D
// class, auto, class, auto, auto, auto, auto, class... B class a, auto b, class c, auto d, auto e, auto f, auto g, class... h C a, b, c, d, e, f, g, h... D
// class, class, auto, auto, auto, auto, auto, class B class a, class b, auto c, auto d, auto e, auto f, auto g, class h C a, b, c, d, e, f, g, h D
// class, class, auto, auto, auto, auto, auto, class... B class a, class b, auto c, auto d, auto e, auto f, auto g, class... h C a, b, c, d, e, f, g, h... D
// class, auto, auto, auto, auto, auto, auto, class B class a, auto b, auto c, auto d, auto e, auto f, auto g, class h C a, b, c, d, e, f, g, h D
// class, auto, auto, auto, auto, auto, auto, class... B class a, auto b, auto c, auto d, auto e, auto f, auto g, class... h C a, b, c, d, e, f, g, h... D
// auto, class B auto a, class b C a, b D
// auto, class... B auto a, class... b C a, b... D
// auto, auto, class B auto a, auto b, class c C a, b, c D
// auto, auto, class... B auto a, auto b, class... c C a, b, c... D
// auto, auto, auto, class B auto a, auto b, auto c, class d C a, b, c, d D
// auto, auto, auto, class... B auto a, auto b, auto c, class... d C a, b, c, d... D
// auto, auto, auto, auto, class B auto a, auto b, auto c, auto d, class e C a, b, c, d, e D
// auto, auto, auto, auto, class... B auto a, auto b, auto c, auto d, class... e C a, b, c, d, e... D
// auto, auto, auto, auto, auto, class B auto a, auto b, auto c, auto d, auto e, class f C a, b, c, d, e, f D
// auto, auto, auto, auto, auto, class... B auto a, auto b, auto c, auto d, auto e, class... f C a, b, c, d, e, f... D
// auto, auto, auto, auto, auto, auto, class B auto a, auto b, auto c, auto d, auto e, auto f, class g C a, b, c, d, e, f, g D
// auto, auto, auto, auto, auto, auto, class... B auto a, auto b, auto c, auto d, auto e, auto f, class... g C a, b, c, d, e, f, g... D
// auto, auto, auto, auto, auto, auto, auto, class B auto a, auto b, auto c, auto d, auto e, auto f, auto g, class h C a, b, c, d, e, f, g, h D
// auto, auto, auto, auto, auto, auto, auto, class... B auto a, auto b, auto c, auto d, auto e, auto f, auto g, class... h C a, b, c, d, e, f, g, h... D
// auto, class, auto B auto a, class b, auto c C a, b, c D
// auto, class, auto... B auto a, class b, auto... c C a, b, c... D
// auto, auto, class, auto B auto a, auto b, class c, auto d C a, b, c, d D
// auto, auto, class, auto... B auto a, auto b, class c, auto... d C a, b, c, d... D
// auto, class, class, auto B auto a, class b, class c, auto d C a, b, c, d D
// auto, class, class, auto... B auto a, class b, class c, auto... d C a, b, c, d... D
// auto, auto, auto, class, auto B auto a, auto b, auto c, class d, auto e C a, b, c, d, e D
// auto, auto, auto, class, auto... B auto a, auto b, auto c, class d, auto... e C a, b, c, d, e... D
// auto, class, auto, class, auto B auto a, class b, auto c, class d, auto e C a, b, c, d, e D
// auto, class, auto, class, auto... B auto a, class b, auto c, class d, auto... e C a, b, c, d, e... D
// auto, auto, class, class, auto B auto a, auto b, class c, class d, auto e C a, b, c, d, e D
// auto, auto, class, class, auto... B auto a, auto b, class c, class d, auto... e C a, b, c, d, e... D
// auto, class, class, class, auto B auto a, class b, class c, class d, auto e C a, b, c, d, e D
// auto, class, class, class, auto... B auto a, class b, class c, class d, auto... e C a, b, c, d, e... D
// auto, auto, auto, auto, class, auto B auto a, auto b, auto c, auto d, class e, auto f C a, b, c, d, e, f D
// auto, auto, auto, auto, class, auto... B auto a, auto b, auto c, auto d, class e, auto... f C a, b, c, d, e, f... D
// auto, class, auto, auto, class, auto B auto a, class b, auto c, auto d, class e, auto f C a, b, c, d, e, f D
// auto, class, auto, auto, class, auto... B auto a, class b, auto c, auto d, class e, auto... f C a, b, c, d, e, f... D
// auto, auto, class, auto, class, auto B auto a, auto b, class c, auto d, class e, auto f C a, b, c, d, e, f D
// auto, auto, class, auto, class, auto... B auto a, auto b, class c, auto d, class e, auto... f C a, b, c, d, e, f... D
// auto, class, class, auto, class, auto B auto a, class b, class c, auto d, class e, auto f C a, b, c, d, e, f D
// auto, class, class, auto, class, auto... B auto a, class b, class c, auto d, class e, auto... f C a, b, c, d, e, f... D
// auto, auto, auto, class, class, auto B auto a, auto b, auto c, class d, class e, auto f C a, b, c, d, e, f D
// auto, auto, auto, class, class, auto... B auto a, auto b, auto c, class d, class e, auto... f C a, b, c, d, e, f... D
// auto, class, auto, class, class, auto B auto a, class b, auto c, class d, class e, auto f C a, b, c, d, e, f D
// auto, class, auto, class, class, auto... B auto a, class b, auto c, class d, class e, auto... f C a, b, c, d, e, f... D
// auto, auto, class, class, class, auto B auto a, auto b, class c, class d, class e, auto f C a, b, c, d, e, f D
// auto, auto, class, class, class, auto... B auto a, auto b, class c, class d, class e, auto... f C a, b, c, d, e, f... D
// auto, class, class, class, class, auto B auto a, class b, class c, class d, class e, auto f C a, b, c, d, e, f D
// auto, class, class, class, class, auto... B auto a, class b, class c, class d, class e, auto... f C a, b, c, d, e, f... D
// auto, auto, auto, auto, auto, auto, auto B auto a, auto b, auto c, auto d, auto e, auto f, auto g C a, b, c, d, e, f, g D
// auto, auto, auto, auto, auto, auto, auto... B auto a, auto b, auto c, auto d, auto e, auto f, auto... g C a, b, c, d, e, f, g... D
// auto, class, auto, auto, auto, auto, auto B auto a, class b, auto c, auto d, auto e, auto f, auto g C a, b, c, d, e, f, g D
// auto, class, auto, auto, auto, auto, auto... B auto a, class b, auto c, auto d, auto e, auto f, auto... g C a, b, c, d, e, f, g... D
// auto, auto, class, auto, auto, auto, auto B auto a, auto b, class c, auto d, auto e, auto f, auto g C a, b, c, d, e, f, g D
// auto, auto, class, auto, auto, auto, auto... B auto a, auto b, class c, auto d, auto e, auto f, auto... g C a, b, c, d, e, f, g... D
// auto, class, class, auto, auto, auto, auto B auto a, class b, class c, auto d, auto e, auto f, auto g C a, b, c, d, e, f, g D
// auto, class, class, auto, auto, auto, auto... B auto a, class b, class c, auto d, auto e, auto f, auto... g C a, b, c, d, e, f, g... D
// auto, auto, auto, class, auto, auto, auto B auto a, auto b, auto c, class d, auto e, auto f, auto g C a, b, c, d, e, f, g D
// auto, auto, auto, class, auto, auto, auto... B auto a, auto b, auto c, class d, auto e, auto f, auto... g C a, b, c, d, e, f, g... D
// auto, class, auto, class, auto, auto, auto B auto a, class b, auto c, class d, auto e, auto f, auto g C a, b, c, d, e, f, g D
// auto, class, auto, class, auto, auto, auto... B auto a, class b, auto c, class d, auto e, auto f, auto... g C a, b, c, d, e, f, g... D
// auto, auto, class, class, auto, auto, auto B auto a, auto b, class c, class d, auto e, auto f, auto g C a, b, c, d, e, f, g D
// auto, auto, class, class, auto, auto, auto... B auto a, auto b, class c, class d, auto e, auto f, auto... g C a, b, c, d, e, f, g... D
// auto, class, class, class, auto, auto, auto B auto a, class b, class c, class d, auto e, auto f, auto g C a, b, c, d, e, f, g D
// auto, class, class, class, auto, auto, auto... B auto a, class b, class c, class d, auto e, auto f, auto... g C a, b, c, d, e, f, g... D
// auto, auto, auto, auto, class, auto, auto B auto a, auto b, auto c, auto d, class e, auto f, auto g C a, b, c, d, e, f, g D
// auto, auto, auto, auto, class, auto, auto... B auto a, auto b, auto c, auto d, class e, auto f, auto... g C a, b, c, d, e, f, g... D
// auto, class, auto, auto, class, auto, auto B auto a, class b, auto c, auto d, class e, auto f, auto g C a, b, c, d, e, f, g D
// auto, class, auto, auto, class, auto, auto... B auto a, class b, auto c, auto d, class e, auto f, auto... g C a, b, c, d, e, f, g... D
// auto, auto, class, auto, class, auto, auto B auto a, auto b, class c, auto d, class e, auto f, auto g C a, b, c, d, e, f, g D
// auto, auto, class, auto, class, auto, auto... B auto a, auto b, class c, auto d, class e, auto f, auto... g C a, b, c, d, e, f, g... D
// auto, class, class, auto, class, auto, auto B auto a, class b, class c, auto d, class e, auto f, auto g C a, b, c, d, e, f, g D
// auto, class, class, auto, class, auto, auto... B auto a, class b, class c, auto d, class e, auto f, auto... g C a, b, c, d, e, f, g... D
// auto, auto, auto, class, class, auto, auto B auto a, auto b, auto c, class d, class e, auto f, auto g C a, b, c, d, e, f, g D
// auto, auto, auto, class, class, auto, auto... B auto a, auto b, auto c, class d, class e, auto f, auto... g C a, b, c, d, e, f, g... D
// auto, class, auto, class, class, auto, auto B auto a, class b, auto c, class d, class e, auto f, auto g C a, b, c, d, e, f, g D
// auto, class, auto, class, class, auto, auto... B auto a, class b, auto c, class d, class e, auto f, auto... g C a, b, c, d, e, f, g... D
// auto, auto, class, class, class, auto, auto B auto a, auto b, class c, class d, class e, auto f, auto g C a, b, c, d, e, f, g D
// auto, auto, class, class, class, auto, auto... B auto a, auto b, class c, class d, class e, auto f, auto... g C a, b, c, d, e, f, g... D
// auto, class, class, class, class, auto, auto B auto a, class b, class c, class d, class e, auto f, auto g C a, b, c, d, e, f, g D
// auto, class, class, class, class, auto, auto... B auto a, class b, class c, class d, class e, auto f, auto... g C a, b, c, d, e, f, g... D
// auto, auto, auto, auto, auto, class, auto B auto a, auto b, auto c, auto d, auto e, class f, auto g C a, b, c, d, e, f, g D
// auto, auto, auto, auto, auto, class, auto... B auto a, auto b, auto c, auto d, auto e, class f, auto... g C a, b, c, d, e, f, g... D
// auto, class, auto, auto, auto, class, auto B auto a, class b, auto c, auto d, auto e, class f, auto g C a, b, c, d, e, f, g D
// auto, class, auto, auto, auto, class, auto... B auto a, class b, auto c, auto d, auto e, class f, auto... g C a, b, c, d, e, f, g... D
// auto, auto, class, auto, auto, class, auto B auto a, auto b, class c, auto d, auto e, class f, auto g C a, b, c, d, e, f, g D
// auto, auto, class, auto, auto, class, auto... B auto a, auto b, class c, auto d, auto e, class f, auto... g C a, b, c, d, e, f, g... D
// auto, class, class, auto, auto, class, auto B auto a, class b, class c, auto d, auto e, class f, auto g C a, b, c, d, e, f, g D
// auto, class, class, auto, auto, class, auto... B auto a, class b, class c, auto d, auto e, class f, auto... g C a, b, c, d, e, f, g... D
// auto, auto, auto, class, auto, class, auto B auto a, auto b, auto c, class d, auto e, class f, auto g C a, b, c, d, e, f, g D
// auto, auto, auto, class, auto, class, auto... B auto a, auto b, auto c, class d, auto e, class f, auto... g C a, b, c, d, e, f, g... D
// auto, class, auto, class, auto, class, auto B auto a, class b, auto c, class d, auto e, class f, auto g C a, b, c, d, e, f, g D
// auto, class, auto, class, auto, class, auto... B auto a, class b, auto c, class d, auto e, class f, auto... g C a, b, c, d, e, f, g... D
// auto, auto, class, class, auto, class, auto B auto a, auto b, class c, class d, auto e, class f, auto g C a, b, c, d, e, f, g D
// auto, auto, class, class, auto, class, auto... B auto a, auto b, class c, class d, auto e, class f, auto... g C a, b, c, d, e, f, g... D
// auto, class, class, class, auto, class, auto B auto a, class b, class c, class d, auto e, class f, auto g C a, b, c, d, e, f, g D
// auto, class, class, class, auto, class, auto... B auto a, class b, class c, class d, auto e, class f, auto... g C a, b, c, d, e, f, g... D
// auto, auto, auto, auto, class, class, auto B auto a, auto b, auto c, auto d, class e, class f, auto g C a, b, c, d, e, f, g D
// auto, auto, auto, auto, class, class, auto... B auto a, auto b, auto c, auto d, class e, class f, auto... g C a, b, c, d, e, f, g... D
// auto, class, auto, auto, class, class, auto B auto a, class b, auto c, auto d, class e, class f, auto g C a, b, c, d, e, f, g D
// auto, class, auto, auto, class, class, auto... B auto a, class b, auto c, auto d, class e, class f, auto... g C a, b, c, d, e, f, g... D
// auto, auto, class, auto, class, class, auto B auto a, auto b, class c, auto d, class e, class f, auto g C a, b, c, d, e, f, g D
// auto, auto, class, auto, class, class, auto... B auto a, auto b, class c, auto d, class e, class f, auto... g C a, b, c, d, e, f, g... D
// auto, class, class, auto, class, class, auto B auto a, class b, class c, auto d, class e, class f, auto g C a, b, c, d, e, f, g D
// auto, class, class, auto, class, class, auto... B auto a, class b, class c, auto d, class e, class f, auto... g C a, b, c, d, e, f, g... D
// auto, auto, auto, class, class, class, auto B auto a, auto b, auto c, class d, class e, class f, auto g C a, b, c, d, e, f, g D
// auto, auto, auto, class, class, class, auto... B auto a, auto b, auto c, class d, class e, class f, auto... g C a, b, c, d, e, f, g... D
// auto, class, auto, class, class, class, auto B auto a, class b, auto c, class d, class e, class f, auto g C a, b, c, d, e, f, g D
// auto, class, auto, class, class, class, auto... B auto a, class b, auto c, class d, class e, class f, auto... g C a, b, c, d, e, f, g... D
// auto, auto, class, class, class, class, auto B auto a, auto b, class c, class d, class e, class f, auto g C a, b, c, d, e, f, g D
// auto, auto, class, class, class, class, auto... B auto a, auto b, class c, class d, class e, class f, auto... g C a, b, c, d, e, f, g... D
// auto, class, class, class, class, class, auto B auto a, class b, class c, class d, class e, class f, auto g C a, b, c, d, e, f, g D
// auto, class, class, class, class, class, auto... B auto a, class b, class c, class d, class e, class f, auto... g C a, b, c, d, e, f, g... D
// auto, auto, auto, auto, auto, auto, auto, auto B auto a, auto b, auto c, auto d, auto e, auto f, auto g, auto h C a, b, c, d, e, f, g, h D
// auto, auto, auto, auto, auto, auto, auto, auto... B auto a, auto b, auto c, auto d, auto e, auto f, auto g, auto... h C a, b, c, d, e, f, g, h... D
// auto, class, auto, auto, auto, auto, auto, auto B auto a, class b, auto c, auto d, auto e, auto f, auto g, auto h C a, b, c, d, e, f, g, h D
// auto, class, auto, auto, auto, auto, auto, auto... B auto a, class b, auto c, auto d, auto e, auto f, auto g, auto... h C a, b, c, d, e, f, g, h... D
// auto, auto, class, auto, auto, auto, auto, auto B auto a, auto b, class c, auto d, auto e, auto f, auto g, auto h C a, b, c, d, e, f, g, h D
// auto, auto, class, auto, auto, auto, auto, auto... B auto a, auto b, class c, auto d, auto e, auto f, auto g, auto... h C a, b, c, d, e, f, g, h... D
// auto, class, class, auto, auto, auto, auto, auto B auto a, class b, class c, auto d, auto e, auto f, auto g, auto h C a, b, c, d, e, f, g, h D
// auto, class, class, auto, auto, auto, auto, auto... B auto a, class b, class c, auto d, auto e, auto f, auto g, auto... h C a, b, c, d, e, f, g, h... D
// auto, auto, auto, class, auto, auto, auto, auto B auto a, auto b, auto c, class d, auto e, auto f, auto g, auto h C a, b, c, d, e, f, g, h D
// auto, auto, auto, class, auto, auto, auto, auto... B auto a, auto b, auto c, class d, auto e, auto f, auto g, auto... h C a, b, c, d, e, f, g, h... D
// auto, class, auto, class, auto, auto, auto, auto B auto a, class b, auto c, class d, auto e, auto f, auto g, auto h C a, b, c, d, e, f, g, h D
// auto, class, auto, class, auto, auto, auto, auto... B auto a, class b, auto c, class d, auto e, auto f, auto g, auto... h C a, b, c, d, e, f, g, h... D
// auto, auto, class, class, auto, auto, auto, auto B auto a, auto b, class c, class d, auto e, auto f, auto g, auto h C a, b, c, d, e, f, g, h D
// auto, auto, class, class, auto, auto, auto, auto... B auto a, auto b, class c, class d, auto e, auto f, auto g, auto... h C a, b, c, d, e, f, g, h... D
// auto, class, class, class, auto, auto, auto, auto B auto a, class b, class c, class d, auto e, auto f, auto g, auto h C a, b, c, d, e, f, g, h D
// auto, class, class, class, auto, auto, auto, auto... B auto a, class b, class c, class d, auto e, auto f, auto g, auto... h C a, b, c, d, e, f, g, h... D
// auto, auto, auto, auto, class, auto, auto, auto B auto a, auto b, auto c, auto d, class e, auto f, auto g, auto h C a, b, c, d, e, f, g, h D
// auto, auto, auto, auto, class, auto, auto, auto... B auto a, auto b, auto c, auto d, class e, auto f, auto g, auto... h C a, b, c, d, e, f, g, h... D
// auto, class, auto, auto, class, auto, auto, auto B auto a, class b, auto c, auto d, class e, auto f, auto g, auto h C a, b, c, d, e, f, g, h D
// auto, class, auto, auto, class, auto, auto, auto... B auto a, class b, auto c, auto d, class e, auto f, auto g, auto... h C a, b, c, d, e, f, g, h... D
// auto, auto, class, auto, class, auto, auto, auto B auto a, auto b, class c, auto d, class e, auto f, auto g, auto h C a, b, c, d, e, f, g, h D
// auto, auto, class, auto, class, auto, auto, auto... B auto a, auto b, class c, auto d, class e, auto f, auto g, auto... h C a, b, c, d, e, f, g, h... D
// auto, class, class, auto, class, auto, auto, auto B auto a, class b, class c, auto d, class e, auto f, auto g, auto h C a, b, c, d, e, f, g, h D
// auto, class, class, auto, class, auto, auto, auto... B auto a, class b, class c, auto d, class e, auto f, auto g, auto... h C a, b, c, d, e, f, g, h... D
// auto, auto, auto, class, class, auto, auto, auto B auto a, auto b, auto c, class d, class e, auto f, auto g, auto h C a, b, c, d, e, f, g, h D
// auto, auto, auto, class, class, auto, auto, auto... B auto a, auto b, auto c, class d, class e, auto f, auto g, auto... h C a, b, c, d, e, f, g, h... D
// auto, class, auto, class, class, auto, auto, auto B auto a, class b, auto c, class d, class e, auto f, auto g, auto h C a, b, c, d, e, f, g, h D
// auto, class, auto, class, class, auto, auto, auto... B auto a, class b, auto c, class d, class e, auto f, auto g, auto... h C a, b, c, d, e, f, g, h... D
// auto, auto, class, class, class, auto, auto, auto B auto a, auto b, class c, class d, class e, auto f, auto g, auto h C a, b, c, d, e, f, g, h D
// auto, auto, class, class, class, auto, auto, auto... B auto a, auto b, class c, class d, class e, auto f, auto g, auto... h C a, b, c, d, e, f, g, h... D
// auto, class, class, class, class, auto, auto, auto B auto a, class b, class c, class d, class e, auto f, auto g, auto h C a, b, c, d, e, f, g, h D
// auto, class, class, class, class, auto, auto, auto... B auto a, class b, class c, class d, class e, auto f, auto g, auto... h C a, b, c, d, e, f, g, h... D
// auto, auto, auto, auto, auto, class, auto, auto B auto a, auto b, auto c, auto d, auto e, class f, auto g, auto h C a, b, c, d, e, f, g, h D
// auto, auto, auto, auto, auto, class, auto, auto... B auto a, auto b, auto c, auto d, auto e, class f, auto g, auto... h C a, b, c, d, e, f, g, h... D
// auto, class, auto, auto, auto, class, auto, auto B auto a, class b, auto c, auto d, auto e, class f, auto g, auto h C a, b, c, d, e, f, g, h D
// auto, class, auto, auto, auto, class, auto, auto... B auto a, class b, auto c, auto d, auto e, class f, auto g, auto... h C a, b, c, d, e, f, g, h... D
// auto, auto, class, auto, auto, class, auto, auto B auto a, auto b, class c, auto d, auto e, class f, auto g, auto h C a, b, c, d, e, f, g, h D
// auto, auto, class, auto, auto, class, auto, auto... B auto a, auto b, class c, auto d, auto e, class f, auto g, auto... h C a, b, c, d, e, f, g, h... D
// auto, class, class, auto, auto, class, auto, auto B auto a, class b, class c, auto d, auto e, class f, auto g, auto h C a, b, c, d, e, f, g, h D
// auto, class, class, auto, auto, class, auto, auto... B auto a, class b, class c, auto d, auto e, class f, auto g, auto... h C a, b, c, d, e, f, g, h... D
// auto, auto, auto, class, auto, class, auto, auto B auto a, auto b, auto c, class d, auto e, class f, auto g, auto h C a, b, c, d, e, f, g, h D
// auto, auto, auto, class, auto, class, auto, auto... B auto a, auto b, auto c, class d, auto e, class f, auto g, auto... h C a, b, c, d, e, f, g, h... D
// auto, class, auto, class, auto, class, auto, auto B auto a, class b, auto c, class d, auto e, class f, auto g, auto h C a, b, c, d, e, f, g, h D
// auto, class, auto, class, auto, class, auto, auto... B auto a, class b, auto c, class d, auto e, class f, auto g, auto... h C a, b, c, d, e, f, g, h... D
// auto, auto, class, class, auto, class, auto, auto B auto a, auto b, class c, class d, auto e, class f, auto g, auto h C a, b, c, d, e, f, g, h D
// auto, auto, class, class, auto, class, auto, auto... B auto a, auto b, class c, class d, auto e, class f, auto g, auto... h C a, b, c, d, e, f, g, h... D
// auto, class, class, class, auto, class, auto, auto B auto a, class b, class c, class d, auto e, class f, auto g, auto h C a, b, c, d, e, f, g, h D
// auto, class, class, class, auto, class, auto, auto... B auto a, class b, class c, class d, auto e, class f, auto g, auto... h C a, b, c, d, e, f, g, h... D
// auto, auto, auto, auto, class, class, auto, auto B auto a, auto b, auto c, auto d, class e, class f, auto g, auto h C a, b, c, d, e, f, g, h D
// auto, auto, auto, auto, class, class, auto, auto... B auto a, auto b, auto c, auto d, class e, class f, auto g, auto... h C a, b, c, d, e, f, g, h... D
// auto, class, auto, auto, class, class, auto, auto B auto a, class b, auto c, auto d, class e, class f, auto g, auto h C a, b, c, d, e, f, g, h D
// auto, class, auto, auto, class, class, auto, auto... B auto a, class b, auto c, auto d, class e, class f, auto g, auto... h C a, b, c, d, e, f, g, h... D
// auto, auto, class, auto, class, class, auto, auto B auto a, auto b, class c, auto d, class e, class f, auto g, auto h C a, b, c, d, e, f, g, h D
// auto, auto, class, auto, class, class, auto, auto... B auto a, auto b, class c, auto d, class e, class f, auto g, auto... h C a, b, c, d, e, f, g, h... D
// auto, class, class, auto, class, class, auto, auto B auto a, class b, class c, auto d, class e, class f, auto g, auto h C a, b, c, d, e, f, g, h D
// auto, class, class, auto, class, class, auto, auto... B auto a, class b, class c, auto d, class e, class f, auto g, auto... h C a, b, c, d, e, f, g, h... D
// auto, auto, auto, class, class, class, auto, auto B auto a, auto b, auto c, class d, class e, class f, auto g, auto h C a, b, c, d, e, f, g, h D
// auto, auto, auto, class, class, class, auto, auto... B auto a, auto b, auto c, class d, class e, class f, auto g, auto... h C a, b, c, d, e, f, g, h... D
// auto, class, auto, class, class, class, auto, auto B auto a, class b, auto c, class d, class e, class f, auto g, auto h C a, b, c, d, e, f, g, h D
// auto, class, auto, class, class, class, auto, auto... B auto a, class b, auto c, class d, class e, class f, auto g, auto... h C a, b, c, d, e, f, g, h... D
// auto, auto, class, class, class, class, auto, auto B auto a, auto b, class c, class d, class e, class f, auto g, auto h C a, b, c, d, e, f, g, h D
// auto, auto, class, class, class, class, auto, auto... B auto a, auto b, class c, class d, class e, class f, auto g, auto... h C a, b, c, d, e, f, g, h... D
// auto, class, class, class, class, class, auto, auto B auto a, class b, class c, class d, class e, class f, auto g, auto h C a, b, c, d, e, f, g, h D
// auto, class, class, class, class, class, auto, auto... B auto a, class b, class c, class d, class e, class f, auto g, auto... h C a, b, c, d, e, f, g, h... D
// auto, auto, auto, auto, auto, auto, class, auto B auto a, auto b, auto c, auto d, auto e, auto f, class g, auto h C a, b, c, d, e, f, g, h D
// auto, auto, auto, auto, auto, auto, class, auto... B auto a, auto b, auto c, auto d, auto e, auto f, class g, auto... h C a, b, c, d, e, f, g, h... D
// auto, class, auto, auto, auto, auto, class, auto B auto a, class b, auto c, auto d, auto e, auto f, class g, auto h C a, b, c, d, e, f, g, h D
// auto, class, auto, auto, auto, auto, class, auto... B auto a, class b, auto c, auto d, auto e, auto f, class g, auto... h C a, b, c, d, e, f, g, h... D
// auto, auto, class, auto, auto, auto, class, auto B auto a, auto b, class c, auto d, auto e, auto f, class g, auto h C a, b, c, d, e, f, g, h D
// auto, auto, class, auto, auto, auto, class, auto... B auto a, auto b, class c, auto d, auto e, auto f, class g, auto... h C a, b, c, d, e, f, g, h... D
// auto, class, class, auto, auto, auto, class, auto B auto a, class b, class c, auto d, auto e, auto f, class g, auto h C a, b, c, d, e, f, g, h D
// auto, class, class, auto, auto, auto, class, auto... B auto a, class b, class c, auto d, auto e, auto f, class g, auto... h C a, b, c, d, e, f, g, h... D
// auto, auto, auto, class, auto, auto, class, auto B auto a, auto b, auto c, class d, auto e, auto f, class g, auto h C a, b, c, d, e, f, g, h D
// auto, auto, auto, class, auto, auto, class, auto... B auto a, auto b, auto c, class d, auto e, auto f, class g, auto... h C a, b, c, d, e, f, g, h... D
// auto, class, auto, class, auto, auto, class, auto B auto a, class b, auto c, class d, auto e, auto f, class g, auto h C a, b, c, d, e, f, g, h D
// auto, class, auto, class, auto, auto, class, auto... B auto a, class b, auto c, class d, auto e, auto f, class g, auto... h C a, b, c, d, e, f, g, h... D
// auto, auto, class, class, auto, auto, class, auto B auto a, auto b, class c, class d, auto e, auto f, class g, auto h C a, b, c, d, e, f, g, h D
// auto, auto, class, class, auto, auto, class, auto... B auto a, auto b, class c, class d, auto e, auto f, class g, auto... h C a, b, c, d, e, f, g, h... D
// auto, class, class, class, auto, auto, class, auto B auto a, class b, class c, class d, auto e, auto f, class g, auto h C a, b, c, d, e, f, g, h D
// auto, class, class, class, auto, auto, class, auto... B auto a, class b, class c, class d, auto e, auto f, class g, auto... h C a, b, c, d, e, f, g, h... D
// auto, auto, auto, auto, class, auto, class, auto B auto a, auto b, auto c, auto d, class e, auto f, class g, auto h C a, b, c, d, e, f, g, h D
// auto, auto, auto, auto, class, auto, class, auto... B auto a, auto b, auto c, auto d, class e, auto f, class g, auto... h C a, b, c, d, e, f, g, h... D
// auto, class, auto, auto, class, auto, class, auto B auto a, class b, auto c, auto d, class e, auto f, class g, auto h C a, b, c, d, e, f, g, h D
// auto, class, auto, auto, class, auto, class, auto... B auto a, class b, auto c, auto d, class e, auto f, class g, auto... h C a, b, c, d, e, f, g, h... D
// auto, auto, class, auto, class, auto, class, auto B auto a, auto b, class c, auto d, class e, auto f, class g, auto h C a, b, c, d, e, f, g, h D
// auto, auto, class, auto, class, auto, class, auto... B auto a, auto b, class c, auto d, class e, auto f, class g, auto... h C a, b, c, d, e, f, g, h... D
// auto, class, class, auto, class, auto, class, auto B auto a, class b, class c, auto d, class e, auto f, class g, auto h C a, b, c, d, e, f, g, h D
// auto, class, class, auto, class, auto, class, auto... B auto a, class b, class c, auto d, class e, auto f, class g, auto... h C a, b, c, d, e, f, g, h... D
// auto, auto, auto, class, class, auto, class, auto B auto a, auto b, auto c, class d, class e, auto f, class g, auto h C a, b, c, d, e, f, g, h D
// auto, auto, auto, class, class, auto, class, auto... B auto a, auto b, auto c, class d, class e, auto f, class g, auto... h C a, b, c, d, e, f, g, h... D
// auto, class, auto, class, class, auto, class, auto B auto a, class b, auto c, class d, class e, auto f, class g, auto h C a, b, c, d, e, f, g, h D
// auto, class, auto, class, class, auto, class, auto... B auto a, class b, auto c, class d, class e, auto f, class g, auto... h C a, b, c, d, e, f, g, h... D
// auto, auto, class, class, class, auto, class, auto B auto a, auto b, class c, class d, class e, auto f, class g, auto h C a, b, c, d, e, f, g, h D
// auto, auto, class, class, class, auto, class, auto... B auto a, auto b, class c, class d, class e, auto f, class g, auto... h C a, b, c, d, e, f, g, h... D
// auto, class, class, class, class, auto, class, auto B auto a, class b, class c, class d, class e, auto f, class g, auto h C a, b, c, d, e, f, g, h D
// auto, class, class, class, class, auto, class, auto... B auto a, class b, class c, class d, class e, auto f, class g, auto... h C a, b, c, d, e, f, g, h... D
// auto, auto, auto, auto, auto, class, class, auto B auto a, auto b, auto c, auto d, auto e, class f, class g, auto h C a, b, c, d, e, f, g, h D
// auto, auto, auto, auto, auto, class, class, auto... B auto a, auto b, auto c, auto d, auto e, class f, class g, auto... h C a, b, c, d, e, f, g, h... D
// auto, class, auto, auto, auto, class, class, auto B auto a, class b, auto c, auto d, auto e, class f, class g, auto h C a, b, c, d, e, f, g, h D
// auto, class, auto, auto, auto, class, class, auto... B auto a, class b, auto c, auto d, auto e, class f, class g, auto... h C a, b, c, d, e, f, g, h... D
// auto, auto, class, auto, auto, class, class, auto B auto a, auto b, class c, auto d, auto e, class f, class g, auto h C a, b, c, d, e, f, g, h D
// auto, auto, class, auto, auto, class, class, auto... B auto a, auto b, class c, auto d, auto e, class f, class g, auto... h C a, b, c, d, e, f, g, h... D
// auto, class, class, auto, auto, class, class, auto B auto a, class b, class c, auto d, auto e, class f, class g, auto h C a, b, c, d, e, f, g, h D
// auto, class, class, auto, auto, class, class, auto... B auto a, class b, class c, auto d, auto e, class f, class g, auto... h C a, b, c, d, e, f, g, h... D
// auto, auto, auto, class, auto, class, class, auto B auto a, auto b, auto c, class d, auto e, class f, class g, auto h C a, b, c, d, e, f, g, h D
// auto, auto, auto, class, auto, class, class, auto... B auto a, auto b, auto c, class d, auto e, class f, class g, auto... h C a, b, c, d, e, f, g, h... D
// auto, class, auto, class, auto, class, class, auto B auto a, class b, auto c, class d, auto e, class f, class g, auto h C a, b, c, d, e, f, g, h D
// auto, class, auto, class, auto, class, class, auto... B auto a, class b, auto c, class d, auto e, class f, class g, auto... h C a, b, c, d, e, f, g, h... D
// auto, auto, class, class, auto, class, class, auto B auto a, auto b, class c, class d, auto e, class f, class g, auto h C a, b, c, d, e, f, g, h D
// auto, auto, class, class, auto, class, class, auto... B auto a, auto b, class c, class d, auto e, class f, class g, auto... h C a, b, c, d, e, f, g, h... D
// auto, class, class, class, auto, class, class, auto B auto a, class b, class c, class d, auto e, class f, class g, auto h C a, b, c, d, e, f, g, h D
// auto, class, class, class, auto, class, class, auto... B auto a, class b, class c, class d, auto e, class f, class g, auto... h C a, b, c, d, e, f, g, h... D
// auto, auto, auto, auto, class, class, class, auto B auto a, auto b, auto c, auto d, class e, class f, class g, auto h C a, b, c, d, e, f, g, h D
// auto, auto, auto, auto, class, class, class, auto... B auto a, auto b, auto c, auto d, class e, class f, class g, auto... h C a, b, c, d, e, f, g, h... D
// auto, class, auto, auto, class, class, class, auto B auto a, class b, auto c, auto d, class e, class f, class g, auto h C a, b, c, d, e, f, g, h D
// auto, class, auto, auto, class, class, class, auto... B auto a, class b, auto c, auto d, class e, class f, class g, auto... h C a, b, c, d, e, f, g, h... D
// auto, auto, class, auto, class, class, class, auto B auto a, auto b, class c, auto d, class e, class f, class g, auto h C a, b, c, d, e, f, g, h D
// auto, auto, class, auto, class, class, class, auto... B auto a, auto b, class c, auto d, class e, class f, class g, auto... h C a, b, c, d, e, f, g, h... D
// auto, class, class, auto, class, class, class, auto B auto a, class b, class c, auto d, class e, class f, class g, auto h C a, b, c, d, e, f, g, h D
// auto, class, class, auto, class, class, class, auto... B auto a, class b, class c, auto d, class e, class f, class g, auto... h C a, b, c, d, e, f, g, h... D
// auto, auto, auto, class, class, class, class, auto B auto a, auto b, auto c, class d, class e, class f, class g, auto h C a, b, c, d, e, f, g, h D
// auto, auto, auto, class, class, class, class, auto... B auto a, auto b, auto c, class d, class e, class f, class g, auto... h C a, b, c, d, e, f, g, h... D
// auto, class, auto, class, class, class, class, auto B auto a, class b, auto c, class d, class e, class f, class g, auto h C a, b, c, d, e, f, g, h D
// auto, class, auto, class, class, class, class, auto... B auto a, class b, auto c, class d, class e, class f, class g, auto... h C a, b, c, d, e, f, g, h... D
// auto, auto, class, class, class, class, class, auto B auto a, auto b, class c, class d, class e, class f, class g, auto h C a, b, c, d, e, f, g, h D
// auto, auto, class, class, class, class, class, auto... B auto a, auto b, class c, class d, class e, class f, class g, auto... h C a, b, c, d, e, f, g, h... D
// auto, class, class, class, class, class, class, auto B auto a, class b, class c, class d, class e, class f, class g, auto h C a, b, c, d, e, f, g, h D
// auto, class, class, class, class, class, class, auto... B auto a, class b, class c, class d, class e, class f, class g, auto... h C a, b, c, d, e, f, g, h... D

// auto, class B auto a, class b C a, b D
// auto, class... B auto a, class... b C a, b... D
// auto, class, auto B auto a, class b, auto c C a, b, c D
// auto, class, auto... B auto a, class b, auto... c C a, b, c...
// E
// template<template<class> class M, class _0> int f(std::type_identity<M<_0>>);
// template<template<class...> class M, class... _0> int f(std::type_identity<M<_0...>>);
// template<template<auto> class M, auto _0> int f(std::type_identity<M<_0>>);
// template<template<auto...> class M, auto... _0> int f(std::type_identity<M<_0...>>);
// template<template<class, auto> class M, class _0, auto _1> int f(std::type_identity<M<_0, _1>>);
// template<template<class, auto...> class M, class _0, auto... _1> int f(std::type_identity<M<_0, _1...>>);
// template<template<auto, class> class M, auto _0, class _1> int f(std::type_identity<M<_0, _1>>);















template<template<typename> typename M, typename a> int z(std::type_identity<M<a>>);
template<template<typename...> typename M, typename... a> int z(std::type_identity<M<a...>>);
template<template<auto> typename M, auto a> int z(std::type_identity<M<a>>);
template<template<auto...> typename M, auto... a> int z(std::type_identity<M<a...>>);
template<template<template<typename> typename> typename M, template<typename> typename a> int z(std::type_identity<M<a>>);
template<template<template<typename...> typename> typename M, template<typename...> typename a> int z(std::type_identity<M<a>>);
template<template<template<typename> typename...> typename M, template<typename> typename... a> int z(std::type_identity<M<a...>>);
template<template<template<typename...> typename...> typename M, template<typename...> typename... a> int z(std::type_identity<M<a...>>);
template<template<template<auto> typename> typename M, template<auto> typename a> int z(std::type_identity<M<a>>);
template<template<template<auto...> typename> typename M, template<auto...> typename a> int z(std::type_identity<M<a>>);
template<template<template<auto> typename...> typename M, template<auto> typename... a> int z(std::type_identity<M<a...>>);
template<template<template<auto...> typename...> typename M, template<auto...> typename... a> int z(std::type_identity<M<a...>>);
template<template<typename, auto> typename M, typename a, auto b> int z(std::type_identity<M<a, b>>);
template<template<typename, auto...> typename M, typename a, auto... b> int z(std::type_identity<M<a, b...>>);
template<template<typename, template<typename> typename> typename M, typename a, template<typename> typename b> int z(std::type_identity<M<a, b>>);
template<template<typename, template<typename...> typename> typename M, typename a, template<typename...> typename b> int z(std::type_identity<M<a, b>>);
template<template<typename, template<auto> typename> typename M, typename a, template<auto> typename b> int z(std::type_identity<M<a, b>>);
template<template<typename, template<auto...> typename> typename M, typename a, template<auto...> typename b> int z(std::type_identity<M<a, b>>);
template<template<auto, typename> typename M, auto a, typename b> int z(std::type_identity<M<a, b>>);
template<template<auto, typename...> typename M, auto a, typename... b> int z(std::type_identity<M<a, b...>>);
template<template<auto, template<typename> typename> typename M, auto a, template<typename> typename b> int z(std::type_identity<M<a, b>>);
template<template<auto, template<typename...> typename> typename M, auto a, template<typename...> typename b> int z(std::type_identity<M<a, b>>);
template<template<auto, template<auto> typename> typename M, auto a, template<auto> typename b> int z(std::type_identity<M<a, b>>);
template<template<auto, template<auto...> typename> typename M, auto a, template<auto...> typename b> int z(std::type_identity<M<a, b>>);
template<template<auto, template<typename> typename...> typename M, auto a, template<typename> typename... b> int z(std::type_identity<M<a, b...>>);
template<template<auto, template<typename...> typename...> typename M, auto a, template<typename...> typename... b> int z(std::type_identity<M<a, b...>>);
template<template<auto, template<auto> typename...> typename M, auto a, template<auto> typename... b> int z(std::type_identity<M<a, b...>>);
template<template<auto, template<auto...> typename...> typename M, auto a, template<auto...> typename... b> int z(std::type_identity<M<a, b...>>);
template<template<template<typename> typename, template<typename...> typename> typename M, template<typename> typename a, template<typename...> typename b> int z(std::type_identity<M<a, b>>);
template<template<template<typename> typename, template<auto> typename> typename M, template<typename> typename a, template<auto> typename b> int z(std::type_identity<M<a, b>>);
template<template<template<typename> typename, template<auto...> typename> typename M, template<typename> typename a, template<auto...> typename b> int z(std::type_identity<M<a, b>>);
template<template<template<typename...> typename, template<typename> typename> typename M, template<typename...> typename a, template<typename> typename b> int z(std::type_identity<M<a, b>>);
template<template<template<typename...> typename, template<auto> typename> typename M, template<typename...> typename a, template<auto> typename b> int z(std::type_identity<M<a, b>>);
template<template<template<typename...> typename, template<auto...> typename> typename M, template<typename...> typename a, template<auto...> typename b> int z(std::type_identity<M<a, b>>);
template<template<template<auto> typename, template<typename> typename> typename M, template<auto> typename a, template<typename> typename b> int z(std::type_identity<M<a, b>>);
template<template<template<auto> typename, template<typename...> typename> typename M, template<auto> typename a, template<typename...> typename b> int z(std::type_identity<M<a, b>>);
template<template<template<auto> typename, template<auto...> typename> typename M, template<auto> typename a, template<auto...> typename b> int z(std::type_identity<M<a, b>>);
template<template<template<auto...> typename, template<typename> typename> typename M, template<auto...> typename a, template<typename> typename b> int z(std::type_identity<M<a, b>>);
template<template<template<auto...> typename, template<typename...> typename> typename M, template<auto...> typename a, template<typename...> typename b> int z(std::type_identity<M<a, b>>);
template<template<template<auto...> typename, template<auto> typename> typename M, template<auto...> typename a, template<auto> typename b> int z(std::type_identity<M<a, b>>);

template<typename Type, auto validator>
concept Satisfies = requires { validator.template operator()<Type>(); };

#define SPECIALIZATION_OF(...) Satisfies<[]<typename Type> requires(requires{ ::z<__VA_ARGS__>(std::type_identity<Type>()); })

int main() {}
