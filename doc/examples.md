K9# Examples

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

All:
- [C++11 or highter](#c11-or-highter)
- [C++98](#c98)

## Argument
```cpp
#include "mblet/argparsor.h"
int main(int argc, char* argv[]) {
    mblet::Argparsor args;
    args.addArgument("ARG", NULL, "custom argument message", false);
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
#include "mblet/argparsor.h"
int main(int argc, char* argv[]) {
    mblet::Argparsor args;
    args.addArgument({"-a", "--append"}, "append", "custom append option message", false, NULL, 1);
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
#include "mblet/argparsor.h"
int main(int argc, char* argv[]) {
    mblet::Argparsor args;
    args.addArgument({"-a", "--append"}, "append", "custom append option message", false, NULL, 3);
    args.parseArguments(argc, argv);
    for (std::size_t i = 0; i < args["--append"].size(); ++i) {
        for (std::size_t j = 0; j < args["--append"][i].size() ; ++j) {
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
With nbArgs == 1
```cpp
#include "mblet/argparsor.h"
int main(int argc, char* argv[]) {
    mblet::Argparsor args;
    args.addArgument({"-e", "--extend"}, "extend", "custom extend option message", false, NULL, 1);
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
With nbArgs == 3
```cpp
#include "mblet/argparsor.h"
int main(int argc, char* argv[]) {
    mblet::Argparsor args;
    args.addArgument({"-e", "--extend"}, "extend", "custom extend option message", false, NULL, 3);
    args.parseArguments(argc, argv);
    for (std::size_t i = 0; i < args["--extend"].size(); ++i) {
        for (std::size_t j = 0; j < args["--extend"][i].size() ; ++j) {
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
#include "mblet/argparsor.h"
int main(int argc, char* argv[]) {
    mblet::Argparsor args;
    args.addArgument({"-h", "--help"}, "help", "custom help option message");
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
#include "mblet/argparsor.h"
int main(int argc, char* argv[]) {
    mblet::Argparsor args;
    args.addArgument({"-i", "--infinite"}, "infinite", "custom infinite option message", false, NULL, 1);
    // or
    // args.addArgument({"-i", "--infinite"}, NULL, "custom infinite option message", false, NULL, '+');
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
#include "mblet/argparsor.h"
int main(int argc, char* argv[]) {
    mblet::Argparsor args;
    args.addArgument({"-n", "--none"}, NULL, "custom none option message", false, NULL, 1);
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
#include "mblet/argparsor.h"
int main(int argc, char* argv[]) {
    mblet::Argparsor args;
    args.addArgument({"-n", "--none"}, NULL, "custom none option message", false, NULL, 3);
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
#include "mblet/argparsor.h"
int main(int argc, char* argv[]) {
    mblet::Argparsor args;
    args.addArgument({"-b", "--boolean"}, "store_true", "custom booblean option message", false);
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
#include "mblet/argparsor.h"
int main(int argc, char* argv[]) {
    mblet::Argparsor args;
    args.addArgument({"--no-boolean"}, "store_false", "custom not booblean option message", false);
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
#include "mblet/argparsor.h"
int main(int argc, char* argv[]) {
    mblet::Argparsor args;
    args.addArgument({"-v", "--version"}, "version", "custom version option message", false, NULL, 0, {"multi line", "Version: 0.0.0"});
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

## C++11 or highter
```cpp
#include "mblet/argparsor.h"

int main(int argc, char* argv[]) {
    mblet::Argparsor args;
    args.setDescription("custom description message");
    args.setEpilog("custom epilog message");
    args.addArgument({"-h", "--help"}, "help", "custom help option message");
    args.addArgument({"-v", "--version"}, "version", "help of version option", false, NULL, 0, "Version: 0.0.0");
    args.addArgument("REQUIRED", NULL, "help of required positional argument", true);
    args.addArgument("-b", "store_true", "help of boolean option");
    args.addArgument("-c", "store_false", "help of count option");
    args.addArgument({"-s", "--simple"}, NULL, "help of simple option", false, "argSimple", 1);
    args.addArgument({"-n", "--number"}, NULL, "help of number", false, "ARG1 ARG2", 2, {"foo", "bar"});
    args.addArgument("--infinite", NULL, "help of infinite", false, NULL, '+');
    args.addArgument({"-m", "--multi"}, "append", "help of multi", false, "MULTI", 1, {"0", "1", "2"});
    args.addArgument({"-N", "--multiAppend"}, "append", "help of multi", false, "MULTI", 2, {"0", "1", "2", "3"});
    args.addArgument({"-e", "--extend"}, "extend", "help of extend", false, "EXTEND", 1, {"0", "1", "2", "3"});
    args.addArgument({"-E", "--extend-number"}, "extend", "help of extend", false, "EXTEND", 2, {"0", "1", "2", "3"});
    try {
        args.parseArguments(argc, argv, true);
        std::cout << "-b: " << args["-b"] << std::endl;
        std::cout << "-c: (count) " << args["-c"].count() << std::endl;
        std::cout << "REQUIRED: " << args["REQUIRED"] << std::endl;
        if (args["-s"]) {
            std::cout << "-s: " << args["-s"] << std::endl;
        }
        std::cout << "-n: [0]: " << args["-n"][0] << ", [1]: " << args["-n"][1] << " (" << args["-n"] << ")" <<
                  std::endl;
        if (args["--infinite"]) {
            std::cout << "--infinite: " << args["--infinite"] << std::endl;
        }
        std::cout << "-m: " << args["-m"] << std::endl;
        std::cout << "-N: ";
        for (std::size_t i = 0; i < args["-N"].size(); ++i) {
            if (i > 0) {
                std::cout << ", ";
            }
            std::cout << '(' << args["-N"][i][0] << ", " << args["-N"][i][1] << ')';
        }
        std::cout << std::endl;
        std::cout << "-e: ";
        for (std::size_t i = 0; i < args["-e"].size(); ++i) {
            if (i > 0) {
                std::cout << ", ";
            }
            std::cout << args["-e"][i];
        }
        std::cout << std::endl;
        std::cout << "-E: ";
        for (std::size_t i = 0; i < args["-E"].size(); ++i) {
            if (i > 0) {
                std::cout << ", ";
            }
            std::cout << '(' << args["-E"][i][0] << ", " << args["-E"][i][1] << ')';
        }
        std::cout << std::endl;
    }
    catch (const mblet::Argparsor::ParseArgumentException& e) {
        std::cerr << args.getBynaryName() << ": " << e.what();
        std::cerr << " -- '" << e.argument() << "'" << std::endl;
        return 1; //END
    }
    return 0;
}
```

```
$ ./a.out -h
usage: ./a.out [-E] [-N MULTI] [-b] [-c] [-e EXTEND] [-h] [-m MULTI] [-n ARG1 ARG2] [-s argSimple] [-v] [--infinite INFINITE...] REQUIRED

custom description message

positional arguments:
  REQUIRED                 help of required positional argument (required)

optional arguments:
  -E, --extend-number      help of extend (default: (0, 1), (2, 3))
  -N, --multiAppend MULTI  help of multi (default: (0, 1), (2, 3))
  -b                       help of boolean option
  -c                       help of count option
  -e, --extend EXTEND      help of extend (default: 0, 1, 2, 3)
  -h, --help               custom help option message
  -m, --multi MULTI        help of multi (default: 0, 1, 2)
  -n, --number ARG1 ARG2   help of number (default: foo, bar)
  -s, --simple argSimple   help of simple option
  -v, --version            help of version option
  --infinite INFINITE...   help of infinite

custom epilog message
```
```
$ ./a.out -v
Version: 0.0.0
```
```
$ ./a.out -a
./a.out: invalid option -- 'a'
```
```
$ ./a.out --foo
./a.out: invalid option -- 'foo'
```
```
$ ./a.out 42
-b: false
-c: (count) 0
REQUIRED: 42
-n: [0]: foo, [1]: bar (foo, bar)
-m: 0, 1, 2
-N: (0, 1), (2, 3)
-e: 0, 1, 2, 3
-E: (0, 1), (2, 3)
```
```
$ ./a.out 42 -n 24 42.42
-b: false
-c: (count) 0
REQUIRED: 42
-n: [0]: 24, [1]: 42.42 (24, 42.42)
-m: 0, 1, 2
-N: (0, 1), (2, 3)
-e: 0, 1, 2, 3
-E: (0, 1), (2, 3)
```
```
$ ./a.out 42 -n 24 42.42 -s woot -N foo bar -E 0 1 -e foo bar --infinite -1 0 1 2 -m=foo -ecoffee -cccmbar -N coffee tea -E 2 3 4 5
-b: false
-c: (count) 3
REQUIRED: 42
-s: woot
-n: [0]: 24, [1]: 42.42 (24, 42.42)
--infinite: -1, 0, 1, 2
-m: foo, bar
-N: (foo, bar), (coffee, tea)
-e: foo, bar, coffee
-E: (0, 1), (2, 3), (4, 5)
```
