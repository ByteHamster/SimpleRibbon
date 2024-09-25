# SimpleRibbon

[BuRR](https://github.com/lorenzhs/BuRR) (bumped ribbon retrieval), but with CMake support and a **non**-header-only library to reduce compile times.

Due to this being a static library, only a small selection of configurations is available.
You can find these in the [source file](/SimpleRibbon.cpp).

### Library usage

Clone this repository (with submodules) and add the following to your `CMakeLists.txt`.

```
add_subdirectory(path/to/SimpleRibbon)
target_link_libraries(YourTarget PRIVATE SimpleRibbon)
```

You can then use it as follows:

```
#include <SimpleRibbon.h>

std::vector<std::pair<uint64_t, uint8_t>> inputData = ...;
SimpleRibbon<1> ribbon(inputData); // 1-bit BuRR
std::cout << ribbon1->retrieve(hashedKey) << std::endl;
```

### Citation

If you use SimpleRibbon in the context of an academic publication, we ask that you please cite the BuRR paper:

```bibtex
@inproceedings{BuRR2022,
    author={Peter C. Dillinger, Lorenz Hübschle-Schneider, Peter Sanders, and Stefan Walzer},
    title={Fast Succinct Retrieval and Approximate Membership using Ribbon},
    booktitle={20th International Symposium on Experimental Algorithms (SEA 2022)},
    pages={4:1--4:20},
    year={2022},
    doi={10.4230/LIPIcs.SEA.2022.4}
}
```

### License

This code is licensed under the [Apache 2.0 license](/LICENSE).
