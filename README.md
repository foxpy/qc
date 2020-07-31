# Quad C

I have gotten tired of repetitive stuff like writing `emalloc()`,
generating random, reopening stdin/stdout in binary or parsing
CLI arguments, so I have decided to move them all to this little
neat and quite manageable repo.

## Docs

For how to include this library in your project read
[tutorial](https://git-scm.com/book/en/v2/Git-Tools-Submodules).

All docs are in a single header file.
Go [check it out](src/qc.h),
turns out header files may actually be readable!

## Status

Features:
- [ ] CLI arguments parsing
- [x] `emalloc()`, `die()` and friends
- [x] usable random library (high quality `rand()` replacement)
- [ ] reopening file streams in binary (apparently, in Microsoft world `freopen()` is not enough)
- [ ] neat generic math helpers like `lcm()` and `gcm()`
- [x] test helpers, because `assert()` is not good enough

Usability:
- [x] test coverage
- [x] readable documentation
- [x] convenient Cmake integration
- [ ] super cool ASCII logo
- [ ] clang-format

## The name

`Quad C` stands for **Custom Cruel C Crate**.
Whenever you include this library in your project,
you should hear **Quad Damage** announcement.
Unlike Quake's power-up, this one is not time-limited,
and you don't loose it after you `die()`!
