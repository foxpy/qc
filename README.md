# Quad C

I have gotten tired of repetitive stuff like writing `emalloc()`,
generating random, reopening stdin/stdout in binary or parsing
CLI arguments, so I have decided to move them all to this little
neat and quite manageable repo.

## Status

Features:
- [ ] CLI arguments parsing
- [x] `emalloc()`, `die()` and friends
- [ ] usable random library (high quality `rand()` replacement)
- [ ] reopening file streams in binary (apparently, in Microsoft world `freopen()` is not enough)
- [ ] neat generic math helpers like `lcm()` and `gcm()`
- [ ] test helpers, because `assert()` is not good enough

Usability:
- [x] test coverage
- [ ] readable documentation
- [ ] convenient Cmake integration
- [ ] super cool ASCII logo

## The name

`Quad C` stands for **Custom Cruel C Crate**.
Whenever you include this library in your project,
you should hear **Quad Damage** announcement.
Unlike Quake's power-up, this one is not time-limited,
and you don't loose it after you `die()`!
