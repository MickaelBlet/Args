# Examples

Positionnal:
- [Argument](#argument)

Actions:
- [Append](#append)
- [Extend](#extend)
- [Help](#help)
- [Infinite](#infinite)
- [None](#none)
- [StoreTrue](#storetrue)
- [StoreFalse](#storefalse)
- [Version](#version)

## Argument
```cpp
#include <iostream>

#include "mblet/argparsor.h"

int main(int argc, char* argv[]) {
    mblet::Argparsor args;
    args.addArgument("ARG").help("custom argument message");
    args.parseArguments(argc, argv);
    if (args["ARG"]) {
        std::cout << args["ARG"] << std::endl;
    }
    if (args.getAdditionalArguments().size() > 0) {
        std::cout << "Additionnal argument(s):" << std::endl;
        for (std::size_t i = 0; i < args.getAdditionalArguments().size(); ++i) {
            std::cout << args.getAdditionalArguments()[i] << std::endl;
        }
    }
    return 0;
}
```
```
$ ./a.out
$ ./a.out 42
42
$ ./a.out -- 42
42
$ ./a.out -- 42 1 2 3
42
Additionnal argument(s):
1
2
3
```

## Append
With nbArgs == 1
```cpp
#include <iostream>

#include "mblet/argparsor.h"

int main(int argc, char* argv[]) {
    mblet::Argparsor args;
    args.addArgument(args.vector("-a", "--append"))
        .action(args.APPEND)
        .help("custom append option message")
        .nargs(1);
    args.parseArguments(argc, argv);
    for (std::size_t i = 0; i < args["--append"].size(); ++i) {
        std::cout << args["--append"][i] << std::endl;
    }
    return 0;
}
```
```
$ ./a.out -a1 --append=2 -a=3
1
2
3
```
With nbArgs == 3
```cpp
#include <iostream>

#include "mblet/argparsor.h"

int main(int argc, char* argv[]) {
    mblet::Argparsor args;
    args.addArgument(args.vector("-a", "--append"))
        .action(args.APPEND)
        .help("custom append option message")
        .nargs(3);
    args.parseArguments(argc, argv);
    for (std::size_t i = 0; i < args["--append"].size(); ++i) {
        for (std::size_t j = 0; j < args["--append"][i].size(); ++j) {
            if (j > 0) {
                std::cout << ", ";
            }
            std::cout << args["--append"][i][j];
        }
        std::cout << std::endl;
    }
    return 0;
}
```
```
$ ./a.out -a 1 2 3 --append 4 5 6
1, 2, 3
4, 5, 6
```

## Extend
With nargs == 1
```cpp
#include <iostream>

#include "mblet/argparsor.h"

int main(int argc, char* argv[]) {
    mblet::Argparsor args;
    args.addArgument(args.vector("-e", "--extend")).action(args.EXTEND).help("custom extend option message").nargs(1);
    args.parseArguments(argc, argv);
    for (std::size_t i = 0; i < args["--extend"].size(); ++i) {
        std::cout << args["--extend"][i] << std::endl;
    }
    return 0;
}
```
```
$ ./a.out -e1 --extend=2 -e=3 --extend 4 5 6
1
2
3
4
5
6
```
With nargs == 3
```cpp
#include <iostream>

#include "mblet/argparsor.h"

int main(int argc, char* argv[]) {
    mblet::Argparsor args;
    args.addArgument(args.vector("-e", "--extend"))
        .action(mblet::Argparsor::EXTEND)
        .help("custom extend option message")
        .nargs(3);
    args.parseArguments(argc, argv);
    for (std::size_t i = 0; i < args["--extend"].size(); ++i) {
        for (std::size_t j = 0; j < args["--extend"][i].size(); ++j) {
            if (j > 0) {
                std::cout << ", ";
            }
            std::cout << args["--extend"][i][j];
        }
        std::cout << std::endl;
    }
    return 0;
}
```
```
$ ./a.out -e 1 2 3 4 5 6 --extend 7 8 9
1, 2, 3
4, 5, 6
7, 8, 9
```

## Help
```cpp
#include <iostream>

#include "mblet/argparsor.h"

int main(int argc, char* argv[]) {
    mblet::Argparsor args(false);
    args.addArgument(args.vector("-h", "--help")).action(mblet::Argparsor::HELP).help("custom help option message");
    args.parseArguments(argc, argv);
    std::cout << "do nothing" << std::endl;
    return 0;
}
```
```
$ ./a.out
do nothing
$ ./a.out --help
usage: ./a.out [-h]

optional arguments:
  -h, --help  custom help option message
```

## Infinite
```cpp
#include <iostream>

#include "mblet/argparsor.h"

int main(int argc, char* argv[]) {
    mblet::Argparsor args;
    args.addArgument(args.vector("-i", "--infinite"))
        .action(mblet::Argparsor::INFINITE)
        .help("custom infinite option message")
        .nargs(1);
    args.parseArguments(argc, argv);
    for (std::size_t i = 0; i < args["--infinite"].size(); ++i) {
        std::cout << args["--infinite"][i] << std::endl;
    }
    return 0;
}
```
```
$ ./a.out -i 1 2 3
1
2
3
$ ./a.out -i 1 2 3 -i
$ ./a.out -i1 --infinite=2 -i=3 --infinite 4 5 6
4
5
6
```

## None
With nbArgs == 1
```cpp
#include <iostream>

#include "mblet/argparsor.h"

int main(int argc, char* argv[]) {
    mblet::Argparsor args;
    args.addArgument(args.vector("-n", "--none")).help("custom none option message");
    args.parseArguments(argc, argv);
    std::cout << args["--none"] << std::endl;
    return 0;
}
```
```
$ ./a.out -n 1
1
$ ./a.out -n 1 --none 2
2
```
With nbArgs == 3
```cpp
#include <iostream>

#include "mblet/argparsor.h"

int main(int argc, char* argv[]) {
    mblet::Argparsor args;
    args.addArgument(args.vector("-n", "--none")).help("custom none option message").nargs(3);
    args.parseArguments(argc, argv);
    for (std::size_t i = 0; i < args["--none"].size(); ++i) {
        std::cout << args["--none"][i] << std::endl;
    }
    return 0;
}
```
```
$ ./a.out -n 1 2 3
1
2
3
$ ./a.out -n 1 2 3 --none 4 5 6
4
5
6
```

## StoreTrue
```cpp
#include <iostream>

#include "mblet/argparsor.h"

int main(int argc, char* argv[]) {
    mblet::Argparsor args;
    args.addArgument(args.vector("-b", "--boolean"))
        .action(mblet::Argparsor::STORE_TRUE)
        .help("custom booblean option message");
    args.parseArguments(argc, argv);
    if (args["--boolean"]) {
        std::cout << "true" << std::endl;
        std::cout << "count: " << args["--boolean"].count() << std::endl;
    }
    else {
        std::cout << "false" << std::endl;
    }
    return 0;
}
```
```
$ ./a.out
false
$ ./a.out -b
true
count: 1
$ ./a.out -bbb
true
count: 3
$ ./a.out -bb -bb
true
count: 4
```

## StoreFalse
```cpp
#include <iostream>

#include "mblet/argparsor.h"

int main(int argc, char* argv[]) {
    mblet::Argparsor args;
    args.addArgument("--no-boolean").action(mblet::Argparsor::STORE_FALSE).help("custom not booblean option message");
    args.parseArguments(argc, argv);
    if (args["--no-boolean"]) {
        std::cout << "true" << std::endl;
    }
    else {
        std::cout << "false" << std::endl;
    }
    return 0;
}
```
```
$ ./a.out
true
$ ./a.out --no-boolean
false
```

## Version
```cpp
#include <iostream>

#include "mblet/argparsor.h"

int main(int argc, char* argv[]) {
    mblet::Argparsor args;
    args.addArgument(args.vector("-v", "--version"))
        .action(mblet::Argparsor::VERSION)
        .help("custom help option message")
        .defaults(args.vector("multi line", "Version: 0.0.0"));
    args.parseArguments(argc, argv);
    std::cout << "do nothing" << std::endl;
    return 0;
}
```
```
$ ./a.out
do nothing
$ ./a.out --version
multi line
Version: 0.0.0
```