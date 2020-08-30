# Quad C

I have gotten tired of repetitive stuff like writing `emalloc()`,
generating random, reopening stdin/stdout in binary or parsing
CLI arguments, so I have decided to move them all into this little
neat and quite manageable repo.

## Docs

For how to include this library in your project read this
[tutorial](https://git-scm.com/book/en/v2/Git-Tools-Submodules).
Your `CMakeLists.txt` should look like this:

```cmake
add_subdirectory(qc)
add_executable(hello-world hello_world.c)
target_link_libraries(hello-world PUBLIC qc)
```

All docs are in a single header file.
Go [check it out](src/qc.h),
turns out header files may actually be readable!
Also, there are some [examples](examples/).
Finally, check out
[this project](https://github.com/foxpy/inaccurate-pi) (**outdated**),
it depends on qc.


## The name

`Quad C` stands for **Custom Cruel C Crate**.
Whenever you include this library in your project,
you should hear **Quad Damage** announcement.
Unlike Quake's power-up, this one is not time-limited,
and you don't loose it after you `die()`!
