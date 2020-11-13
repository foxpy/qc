# Quad C

I have gotten tired of repetitive stuff like writing `emalloc()`,
generating random, reopening stdin/stdout in binary or parsing
CLI arguments, so I have decided to move them all into this little
neat and quite manageable repo.

**Warning**: this library is in active development. Documentation might be 
srarce, hard to understand and outdated, nasty bugs might be chilling around,
and public API is unstable as hell. If you have found this library quite
neat and you are willing to use it in your project - feel free to include
it as git submodule as submodules are fixed to commit hash and anything
I do with this unversioned-mess library will not affect you. Just don't
expect everything to work correctly whenever you sync git submodule to
match upstream :p 

## Docs

For how to include this library in your project read this
[tutorial](https://git-scm.com/book/en/v2/Git-Tools-Submodules).
Your `CMakeLists.txt` should look like this:

```cmake
add_subdirectory(qc)
add_executable(hello-world hello_world.c)
target_link_libraries(hello-world PUBLIC qc)
```

Currently there are now adequate docs.
I have plans to add doxygen documentation though.
For now, just chek out some [examples](examples/).
Finally, check out
[this project](https://github.com/foxpy/inaccurate-pi) (**outdated!!!**),
it depends on qc.


## The name

`Quad C` stands for **Custom Cruel C Crate**.
Whenever you include this library in your project,
you should hear **Quad Damage** announcement.
Unlike Quake's power-up, this one is not time-limited,
and you don't loose it after you `die()`!
