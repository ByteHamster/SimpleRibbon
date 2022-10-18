# SimpleRibbon

[BuRR](https://github.com/lorenzhs/BuRR) (bumped ribbon retrieval), but with CMake support and a non-header library to reduce compile times.

### Library usage

Add the following to your `CMakeLists.txt`.

```
add_subdirectory(path/to/SimpleRibbon)
target_link_libraries(YourTarget PRIVATE SimpleRibbon)
```

### License

This code is licensed under the [Apache 2.0 license](/LICENSE).
