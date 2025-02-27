# Examples

## All Type

```cpp
#include <iostream>

#include "blet/args.h"

struct CustomStruct {
    std::string a;
    double b;
};

int main(int argc, char* argv[]) {
    using namespace blet;

    struct {
        char notrequired[32];
        const char* required;
        bool b;
        bool c;
        double simple;
        std::vector<std::string> number;
        std::vector<std::string> infinite;
        std::vector<std::string> multi;
        std::vector<std::vector<double> > multiAppend;
        std::vector<std::string> extend;

        std::vector<CustomStruct> extendNumber;

        static void toExtendNumber(std::vector<CustomStruct>& extendNumber, bool /*isExists*/,
                                   const std::vector<std::string>& arguments) {
            for (std::size_t i = 0; i < arguments.size(); i += 2) {
                CustomStruct number = {arguments[i], ::strtod(arguments[i + 1].c_str(), NULL)};
                extendNumber.push_back(number);
            }
        }
    } options;

    ::memcpy(options.notrequired, "default notrequired", sizeof("default notrequired"));
    options.required = "default required";
    options.b = false;
    options.c = false;

    Args args;
    args.setVersion("Version: 0.0.0");
    args.setDescription("custom description message");
    args.setEpilog("custom epilog message");
    args.addArgument("-h").flag("--help").action(args.HELP).help("custom help option message");
    args.addArgument("-v").flag("--version").help("help of version option").action(args.VERSION);
    args.addArgument("NOTREQUIRED").help("help of positional argument").defaults("foo").dest(options.notrequired);
    args.addArgument("REQUIRED")
        .help("help of required positional argument")
        .valid(new Args::ValidNumber())
        .dest(options.required)
        .required(true);
    args.addArgument("-b").action(args.STORE_TRUE).help("help of boolean option").dest(options.b);
    args.addArgument("-c").action(args.STORE_FALSE).help("help of count option").dest(options.c);
    args.addArgument("-s")
        .flag("--simple")
        .help("help of simple option")
        .required(true)
        .metavar("argSimple")
        .nargs(1)
        .valid(new Args::ValidChoise(args.vector("0", "100", "200")))
        .dest(options.simple);
    args.addArgument("-n")
        .flag("--number")
        .help("help of number")
        .required(true)
        .metavar("ARG1 ARG2")
        .nargs(2)
        .dest(options.number);
    args.addArgument("--infinite").help("help of infinite").nargs('+').dest(options.infinite);
    args.addArgument(args.vector("-m", "--multi"))
        .action(args.APPEND)
        .help("help of multi")
        .metavar("MULTI")
        .nargs(1)
        .defaults(args.vector("0", "1", "2"))
        .dest(options.multi);
    args.addArgument(args.vector("-N", "--multiAppend"))
        .action(args.APPEND)
        .help("help of multi")
        .metavar("MULTI")
        .nargs(2)
        .valid(new Args::ValidNumber())
        .defaults(args.vector("0", "1", "2", "3"))
        .dest(options.multiAppend);
    args.addArgument(args.vector("-e", "--extend"))
        .action(args.EXTEND)
        .help("help of extend")
        .metavar("EXTEND")
        .nargs(1)
        .defaults(args.vector("0", "1", "2", "3"))
        .dest(options.extend);
    args.addArgument(args.vector("-E", "--extend-number"))
        .action(args.EXTEND)
        .help("help of extend")
        .metavar("EXTEND")
        .nargs(2)
        .defaults(args.vector("0", "1", "2", "3"))
        .dest(options.extendNumber, &options.toExtendNumber);

    try {
        args.setAlternative().setHelpException().setVersionException().parseArguments(argc, argv);
    }
    catch (const Args::HelpException& e) {
        std::cout << e.what() << std::endl; // write usage message
        return 0;
    }
    catch (const Args::VersionException& e) {
        std::cout << e.what() << std::endl; // write version message
        return 0;
    }
    catch (const Args::ParseArgumentException& e) {
        std::cerr << args.getBinaryName() << ": " << e.what() << " -- '" << e.argument() << "'" << std::endl;
        return 1;
    }

    // ---------------------------------------------------------------------
    // ACCESS BY MAP
    // ---------------------------------------------------------------------

    std::cout << "--- MAP ---" << std::endl;

    if (args["NOTREQUIRED"]) {
        std::cout << "NOTREQUIRED: " << args["NOTREQUIRED"] << std::endl;
    }
    std::cout << "REQUIRED: " << args["REQUIRED"] << std::endl;

    std::cout << "-b: " << args["-b"] << std::endl;
    std::cout << "-c: " << args["-c"] << std::endl;

    if (args["--simple"]) {
        std::cout << "--simple: " << args["--simple"] << std::endl;
    }
    if (args["--number"]) {
        std::cout << "--number: " << args["--number"] << std::endl;
    }
    if (args["--infinite"]) {
        std::cout << "--infinite: " << args["--infinite"] << std::endl;
    }
    if (args["--multi"]) {
        std::cout << "--multi: " << args["--multi"] << std::endl;
    }
    if (args["--multiAppend"]) {
        std::cout << "--multiAppend: " << args["--multiAppend"] << std::endl;
    }
    if (args["--extend"]) {
        std::cout << "--extend: " << args["--extend"] << std::endl;
    }
    if (args["--extend-number"]) {
        std::cout << "--extend-number: " << args["--extend-number"] << std::endl;
    }

    // ---------------------------------------------------------------------
    // ACCESS BY DEST
    // ---------------------------------------------------------------------
    std::cout << "\n--- DEST ---" << std::endl;

    std::cout << "NOTREQUIRED: " << options.notrequired << std::endl;
    std::cout << "REQUIRED: " << options.required << std::endl;
    std::cout << "-b: " << options.b << std::endl;
    std::cout << "-c: " << options.c << std::endl;
    std::cout << "--simple: " << options.simple << std::endl;
    std::cout << "--number: [0]:" << options.number[0] << ", [1]:" << options.number[1] << std::endl;
    std::cout << "--infinite: ";
    for (std::size_t i = 0; i < options.infinite.size(); ++i) {
        if (i > 0) {
            std::cout << ", ";
        }
        std::cout << options.infinite[i];
    }
    std::cout << std::endl;

    std::cout << "--multi: ";
    for (std::size_t i = 0; i < options.multi.size(); ++i) {
        if (i > 0) {
            std::cout << ", ";
        }
        std::cout << options.multi[i];
    }
    std::cout << std::endl;

    std::cout << "--multiAppend: ";
    for (std::size_t i = 0; i < options.multiAppend.size(); ++i) {
        if (i > 0) {
            std::cout << ", ";
        }
        std::cout << options.multiAppend[i][0];
        std::cout << ", " << options.multiAppend[i][1];
    }
    std::cout << std::endl;

    std::cout << "--extend: ";
    for (std::size_t i = 0; i < options.extend.size(); ++i) {
        if (i > 0) {
            std::cout << ", ";
        }
        std::cout << options.extend[i];
    }
    std::cout << std::endl;

    std::cout << "--extend-number: ";
    for (std::size_t i = 0; i < options.extendNumber.size(); ++i) {
        if (i > 0) {
            std::cout << ", ";
        }
        std::cout << options.extendNumber[i].a;
        std::cout << ", " << options.extendNumber[i].b;
    }
    std::cout << std::endl;
    return 0;
}
```

```
$ ./a.out
./a.out: option is required -- '-n'
$ ./a.out -n 4 2 -s 100 42
--- MAP ---
REQUIRED: 42
-b: false
-c: true
--simple: 100
--number: 4, 2

--- DEST ---
NOTREQUIRED: foo
REQUIRED: 42
-b: 0
-c: 1
--simple: 100
--number: [0]:4, [1]:2
--infinite:
--multi: 0, 1, 2
--multiAppend: 0, 1, 2, 3
--extend: 0, 1, 2, 3
--extend-number: 0, 1, 2, 3
$ ./a.out --extend 4 -n 4 2 --extend-number 4 2 -s 100 42 -b -c --multi 4 --multiAppend 4 2 --multi 2 --extend 2 4 2 --extend-number 4 2 4 2
--- MAP ---
REQUIRED: 42
-b: true
-c: false
--simple: 100
--number: 4, 2
--multi: 4, 2
--multiAppend: (4, 2)
--extend: 4, 2, 4, 2
--extend-number: (4, 2), (4, 2), (4, 2)

--- DEST ---
NOTREQUIRED: foo
REQUIRED: 42
-b: 1
-c: 0
--simple: 100
--number: [0]:4, [1]:2
--infinite:
--multi: 4, 2
--multiAppend: 4, 2
--extend: 4, 2, 4, 2
--extend-number: 4, 2, 4, 2, 4, 2
$ ./a.out -h
usage: a.out -n ARG1 ARG2 -s argSimple [-E EXTEND] [-N MULTI] [-b] [-c]
             [-e EXTEND] [-h] [-m MULTI] [-v] [--infinite INFINITE...]
             --
             REQUIRED [NOTREQUIRED]

custom description message

positional arguments:
  REQUIRED              help of required positional argument (required)
  NOTREQUIRED           help of positional argument (default: foo)

optional arguments:
  -n, --number ARG1 ARG2
                        help of number (required)
  -s, --simple argSimple
                        help of simple option (required)
  -E, --extend-number EXTEND
                        help of extend (default: (0, 1), (2, 3))
  -N, --multiAppend MULTI
                        help of multi (default: (0, 1), (2, 3))
  -b                    help of boolean option
  -c                    help of count option
  -e, --extend EXTEND   help of extend (default: 0, 1, 2, 3)
  -h, --help            custom help option message
  -m, --multi MULTI     help of multi (default: 0, 1, 2)
  -v, --version         help of version option
  --infinite INFINITE...
                        help of infinite

custom epilog message
```

## Append

With nargs == 1

```cpp
#include <iostream>

#include "blet/args.h"

int main(int argc, char* argv[]) {
    blet::Args args;
    args.addArgument("-a").flag("--append").action(args.APPEND).help("custom append option message");

    try {
        args.setHelpException().setVersionException().parseArguments(argc, argv);
    }
    catch (const blet::Args::HelpException& e) {
        std::cout << e.what() << std::endl;
        return 0;
    }
    catch (const blet::Args::VersionException& e) {
        std::cout << e.what() << std::endl;
        return 0;
    }
    catch (const blet::Args::ParseArgumentException& e) {
        std::cerr << args.getBinaryName() << ": " << e.what() << " -- '" << e.argument() << "'" << std::endl;
        return 1;
    }

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

With nargs == 3

```cpp
#include <iostream>

#include "blet/args.h"

int main(int argc, char* argv[]) {
    blet::Args args;
    args.addArgument("ARG").help("custom argument message").nargs(3);

    try {
        args.setHelpException().setVersionException().parseArguments(argc, argv);
    }
    catch (const blet::Args::HelpException& e) {
        std::cout << e.what() << std::endl;
        return 0;
    }
    catch (const blet::Args::VersionException& e) {
        std::cout << e.what() << std::endl;
        return 0;
    }
    catch (const blet::Args::ParseArgumentException& e) {
        std::cerr << args.getBinaryName() << ": " << e.what() << " -- '" << e.argument() << "'" << std::endl;
        return 1;
    }

    if (args["ARG"]) {
        std::cout << args["ARG"] << std::endl;
    }
    if (args.getAdditionalArguments().size() > 0) {
        std::cout << "Additional argument(s):" << std::endl;
        for (std::size_t i = 0; i < args.getAdditionalArguments().size(); ++i) {
            std::cout << args.getAdditionalArguments()[i] << std::endl;
        }
    }

    return 0;
}
```

```
$ ./a.out -a 1 2 3 --append 4 5 6
1, 2, 3
4, 5, 6
```

## Argument

With nargs == 1

```cpp
#include <iostream>

#include "blet/args.h"

int main(int argc, char* argv[]) {
    blet::Args args;
    args.addArgument("ARG").help("custom argument message");

    try {
        args.setHelpException().setVersionException().parseArguments(argc, argv);
    }
    catch (const blet::Args::HelpException& e) {
        std::cout << e.what() << std::endl;
        return 0;
    }
    catch (const blet::Args::VersionException& e) {
        std::cout << e.what() << std::endl;
        return 0;
    }
    catch (const blet::Args::ParseArgumentException& e) {
        std::cerr << args.getBinaryName() << ": " << e.what() << " -- '" << e.argument() << "'" << std::endl;
        return 1;
    }

    if (args["ARG"]) {
        std::cout << args["ARG"] << std::endl;
    }
    if (args.getAdditionalArguments().size() > 0) {
        std::cout << "Additional argument(s):" << std::endl;
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
Additional argument(s):
1
2
3
```

With nargs == 1 and action == INFINITE

```cpp
#include <iostream>

#include "blet/args.h"

int main(int argc, char* argv[]) {
    blet::Args args;
    args.addArgument("ARG").help("custom argument message").nargs('+');
    // or args.addArgument("ARG").help("custom argument message").action(args.INFINITE);

    try {
        args.setHelpException().setVersionException().parseArguments(argc, argv);
    }
    catch (const blet::Args::HelpException& e) {
        std::cout << e.what() << std::endl;
        return 0;
    }
    catch (const blet::Args::VersionException& e) {
        std::cout << e.what() << std::endl;
        return 0;
    }
    catch (const blet::Args::ParseArgumentException& e) {
        std::cerr << args.getBinaryName() << ": " << e.what() << " -- '" << e.argument() << "'" << std::endl;
        return 1; // END
    }

    if (args["ARG"]) {
        std::cout << args["ARG"] << std::endl;
    }
    if (args.getAdditionalArguments().size() > 0) {
        std::cout << "Additional argument(s):" << std::endl;
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
$ ./a.out 42 1 2 3
42, 1, 2, 3
```

With nargs == 3

```cpp
#include <iostream>

#include "blet/args.h"

int main(int argc, char* argv[]) {
    blet::Args args;
    args.addArgument("ARG").help("custom argument message").nargs(3);

    try {
        args.setHelpException().setVersionException().parseArguments(argc, argv);
    }
    catch (const blet::Args::HelpException& e) {
        std::cout << e.what() << std::endl;
        return 0;
    }
    catch (const blet::Args::VersionException& e) {
        std::cout << e.what() << std::endl;
        return 0;
    }
    catch (const blet::Args::ParseArgumentException& e) {
        std::cerr << args.getBinaryName() << ": " << e.what() << " -- '" << e.argument() << "'" << std::endl;
        return 1;
    }

    if (args["ARG"]) {
        std::cout << args["ARG"] << std::endl;
    }
    if (args.getAdditionalArguments().size() > 0) {
        std::cout << "Additional argument(s):" << std::endl;
        for (std::size_t i = 0; i < args.getAdditionalArguments().size(); ++i) {
            std::cout << args.getAdditionalArguments()[i] << std::endl;
        }
    }

    return 0;
}
```

```
$ ./a.out
$ ./a.out 1 2 3
1, 2, 3
$ ./a.out -- 1 2 3
1, 2, 3
$ ./a.out -- 1 2 3 42
1, 2, 3
Additional argument(s):
42
```

With nargs == 3 and action == INFINITE

```cpp
#include <iostream>

#include "blet/args.h"

int main(int argc, char* argv[]) {
    blet::Args args;
    args.addArgument("ARG").help("custom argument message").nargs(3).action(args.INFINITE);

    try {
        args.setHelpException().setVersionException().parseArguments(argc, argv);
    }
    catch (const blet::Args::HelpException& e) {
        std::cout << e.what() << std::endl;
        return 0;
    }
    catch (const blet::Args::VersionException& e) {
        std::cout << e.what() << std::endl;
        return 0;
    }
    catch (const blet::Args::ParseArgumentException& e) {
        std::cerr << args.getBinaryName() << ": " << e.what() << " -- '" << e.argument() << "'" << std::endl;
        return 1;
    }

    if (args["ARG"]) {
        std::cout << args["ARG"] << std::endl;
    }
    if (args.getAdditionalArguments().size() > 0) {
        std::cout << "Additional argument(s):" << std::endl;
        for (std::size_t i = 0; i < args.getAdditionalArguments().size(); ++i) {
            std::cout << args.getAdditionalArguments()[i] << std::endl;
        }
    }

    return 0;
}
```

```
$ ./a.out
$ ./a.out 1 2 3
(1, 2, 3)
$ ./a.out -- 1 2 3
(1, 2, 3)
$ ./a.out 1 2 3 -- 42
(1, 2, 3)
Additional argument(s):
42
```

## Extend

With nargs == 1

```cpp
#include <iostream>

#include "blet/args.h"

int main(int argc, char* argv[]) {
    blet::Args args;
    args.addArgument(args.vector("-e", "--extend")).action(args.EXTEND).help("custom extend option message");

    try {
        args.setHelpException().setVersionException().parseArguments(argc, argv);
    }
    catch (const blet::Args::HelpException& e) {
        std::cout << e.what() << std::endl;
        return 0;
    }
    catch (const blet::Args::VersionException& e) {
        std::cout << e.what() << std::endl;
        return 0;
    }
    catch (const blet::Args::ParseArgumentException& e) {
        std::cerr << args.getBinaryName() << ": " << e.what() << " -- '" << e.argument() << "'" << std::endl;
        return 1;
    }

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

#include "blet/args.h"

int main(int argc, char* argv[]) {
    blet::Args args;
    args.addArgument(args.vector("-e", "--extend")).action(args.EXTEND).help("custom extend option message").nargs(3);

    try {
        args.setHelpException().setVersionException().parseArguments(argc, argv);
    }
    catch (const blet::Args::HelpException& e) {
        std::cout << e.what() << std::endl;
        return 0;
    }
    catch (const blet::Args::VersionException& e) {
        std::cout << e.what() << std::endl;
        return 0;
    }
    catch (const blet::Args::ParseArgumentException& e) {
        std::cerr << args.getBinaryName() << ": " << e.what() << " -- '" << e.argument() << "'" << std::endl;
        return 1;
    }

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

#include "blet/args.h"

int main(int argc, char* argv[]) {
    blet::Args args;
    args.addArgument(args.vector("-h", "--help")).action(args.HELP).help("custom help option message");

    try {
        args.setHelpException().parseArguments(argc, argv);
    }
    catch (const blet::Args::HelpException& e) {
        std::cout << e.what() << std::endl;
    }
    catch (const blet::Args::ParseArgumentException& e) {
        std::cerr << args.getBinaryName() << ": " << e.what() << " -- '" << e.argument() << "'" << std::endl;
        return 1; // END
    }

    return 0;
}
```

```
$ ./a.out
do nothing
$ ./a.out --help
usage: a.out [-h]

optional arguments:
  -h, --help            custom help option message
```

## Infinite

```cpp
#include <iostream>

#include "blet/args.h"

int main(int argc, char* argv[]) {
    blet::Args args;
    args.addArgument(args.vector("-i", "--infinite")).action(args.INFINITE).help("custom infinite option message");
    // or
    // args.addArgument(args.vector("-i", "--infinite")).nargs('+').help("custom infinite option message");

    try {
        args.setHelpException().setVersionException().parseArguments(argc, argv);
    }
    catch (const blet::Args::HelpException& e) {
        std::cout << e.what() << std::endl;
        return 0;
    }
    catch (const blet::Args::VersionException& e) {
        std::cout << e.what() << std::endl;
        return 0;
    }
    catch (const blet::Args::ParseArgumentException& e) {
        std::cerr << args.getBinaryName() << ": " << e.what() << " -- '" << e.argument() << "'" << std::endl;
        return 1;
    }

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

With nargs == 1

```cpp
#include <iostream>

#include "blet/args.h"

int main(int argc, char* argv[]) {
    blet::Args args;
    args.addArgument(args.vector("-n", "--none")).help("custom none option message");

    try {
        args.setHelpException().setVersionException().parseArguments(argc, argv);
        std::cout << args["--none"] << std::endl;
    }
    catch (const blet::Args::HelpException& e) {
        std::cout << e.what() << std::endl;
    }
    catch (const blet::Args::VersionException& e) {
        std::cout << e.what() << std::endl;
    }
    catch (const blet::Args::ParseArgumentException& e) {
        std::cerr << args.getBinaryName() << ": " << e.what() << " -- '" << e.argument() << "'" << std::endl;
        return 1;
    }
    return 0;
}
```

```
$ ./a.out -n 1
1
$ ./a.out -n 1 --none 2
2
```

With nargs == 3

```cpp
#include <iostream>

#include "blet/args.h"

int main(int argc, char* argv[]) {
    blet::Args args;
    args.addArgument(args.vector("-n", "--none")).help("custom none option message").nargs(3);

    try {
        args.setHelpException().setVersionException().parseArguments(argc, argv);
        for (std::size_t i = 0; i < args["--none"].size(); ++i) {
            std::cout << args["--none"][i] << std::endl;
        }
    }
    catch (const blet::Args::HelpException& e) {
        std::cout << e.what() << std::endl;
    }
    catch (const blet::Args::VersionException& e) {
        std::cout << e.what() << std::endl;
    }
    catch (const blet::Args::ParseArgumentException& e) {
        std::cerr << args.getBinaryName() << ": " << e.what() << " -- '" << e.argument() << "'" << std::endl;
        return 1; // END
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

## StoreFalse

```cpp
#include <iostream>

#include "blet/args.h"

int main(int argc, char* argv[]) {
    blet::Args args;
    args.addArgument("--no-boolean").action(args.STORE_FALSE).help("custom not boolean option message");

    try {
        args.setHelpException().setVersionException().parseArguments(argc, argv);
        if (args["--no-boolean"]) {
            std::cout << "true" << std::endl;
        }
        else {
            std::cout << "false" << std::endl;
        }
    }
    catch (const blet::Args::HelpException& e) {
        std::cout << e.what() << std::endl;
    }
    catch (const blet::Args::VersionException& e) {
        std::cout << e.what() << std::endl;
    }
    catch (const blet::Args::ParseArgumentException& e) {
        std::cerr << args.getBinaryName() << ": " << e.what() << " -- '" << e.argument() << "'" << std::endl;
        return 1; // END
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

## StoreTrue

```cpp
#include <iostream>

#include "blet/args.h"

int main(int argc, char* argv[]) {
    blet::Args args;
    args.addArgument(args.vector("-b", "--boolean")).action(args.STORE_TRUE).help("custom boolean option message");

    try {
        args.setHelpException().setVersionException().parseArguments(argc, argv);
        if (args["--boolean"]) {
            std::cout << "true" << std::endl;
            std::cout << "count: " << args["--boolean"].count() << std::endl;
        }
        else {
            std::cout << "false" << std::endl;
        }
    }
    catch (const blet::Args::HelpException& e) {
        std::cout << e.what() << std::endl;
    }
    catch (const blet::Args::VersionException& e) {
        std::cout << e.what() << std::endl;
    }
    catch (const blet::Args::ParseArgumentException& e) {
        std::cerr << args.getBinaryName() << ": " << e.what() << " -- '" << e.argument() << "'" << std::endl;
        return 1; // END
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

## Version

```cpp
#include <iostream>

#include "blet/args.h"

int main(int argc, char* argv[]) {
    blet::Args args;
    args.setVersion("multi line\nVersion: 0.0.0");
    args.addArgument("-v").flag("--version").action(args.VERSION).help("custom help version message");

    try {
        args.setHelpException().setVersionException().parseArguments(argc, argv);
        std::cout << "do nothing" << std::endl;
    }
    catch (const blet::Args::HelpException& e) {
        std::cout << e.what() << std::endl;
    }
    catch (const blet::Args::VersionException& e) {
        std::cout << e.what() << std::endl;
    }
    catch (const blet::Args::ParseArgumentException& e) {
        std::cerr << args.getBinaryName() << ": " << e.what() << " -- '" << e.argument() << "'" << std::endl;
        return 1; // END
    }
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

## Default value

```cpp
#include <iostream>

#include "blet/args.h"

int main(int argc, char* argv[]) {
    blet::Args args;
    args.addArgument("--option").help("custom option message").defaults("default value");
    args.addArgument("--option-number")
        .help("custom option-number message")
        .nargs(2)
        .defaults(args.vector("default1", "default2"));

    try {
        args.setHelpException().setVersionException().parseArguments(argc, argv);
        std::cout << args["--option"] << std::endl;
        std::cout << args["--option-number"][0] << "|" << args["--option-number"][1] << std::endl;
    }
    catch (const blet::Args::HelpException& e) {
        std::cout << e.what() << std::endl;
    }
    catch (const blet::Args::VersionException& e) {
        std::cout << e.what() << std::endl;
    }
    catch (const blet::Args::ParseArgumentException& e) {
        std::cerr << args.getBinaryName() << ": " << e.what() << " -- '" << e.argument() << "'" << std::endl;
        return 1;
    }

    return 0;
}
```

```
$ ./a.out
default value
default1|default2
$ ./a.out --option custom
custom
default1|default2
$ ./a.out --option-number custom1 custom2
default value
custom1|custom2
$ ./a.out -h
usage: a.out [-h] [--option OPTION]
             [--option-number OPTION-NUMBER OPTION-NUMBER]

optional arguments:
  -h, --help            show this help message and exit
  --option OPTION       custom option message (default: default value)
  --option-number OPTION-NUMBER OPTION-NUMBER
                        custom option-number message (default: default1,
                        default2)
```

## Default valid

```cpp
#include <iostream>

#include "blet/args.h"

int main(int argc, char* argv[]) {
    blet::Args args;
    blet::Args::ValidNumber validNumber; // create a scope IValid
    args.addArgument("--option")
        .help("custom option message")
        .valid(&validNumber, false) // set deletable at false
        // or .valid(new blet::Args::ValidNumber())
        .required(true);

    try {
        args.setHelpException().setVersionException().parseArguments(argc, argv);
        std::cout << args["--option"] << std::endl;
    }
    catch (const blet::Args::HelpException& e) {
        std::cout << e.what() << std::endl;
    }
    catch (const blet::Args::VersionException& e) {
        std::cout << e.what() << std::endl;
    }
    catch (const blet::Args::ParseArgumentException& e) {
        std::cerr << args.getBinaryName() << ": " << e.what() << " -- '" << e.argument() << "'" << std::endl;
        return 1;
    }

    return 0;
}
```

```
$ ./a.out
./a.out: option is required -- '--option'
$ ./a.out --option custom
./a.out: "custom" is not a number -- '--option'
$ ./a.out --option 42
42
$ ./a.out -h
usage: a.out --option OPTION [-h]

optional arguments:
  --option OPTION       custom option message (required)
  -h, --help            show this help message and exit
```

## Custom valid transform

```cpp
#include <iostream>
#include <sstream>

#include "blet/args.h"

class ValidCustom : public blet::Args::IValid {
  public:
    ValidCustom(const std::string& prefix, const std::string& suffix) :
        prefix_(prefix),
        suffix_(suffix) {}
    ~ValidCustom() {}

    bool isValid(std::vector<std::string>& arguments) {
        for (std::size_t i = 0; i < arguments.size(); ++i) {
            if (arguments[i] == prefix_) {
                arguments[i] += suffix_;
            }
            else {
                std::ostringstream oss("");
                oss << "\"" << arguments[i] << "\" is not \"" << prefix_ << "\"";
                throw blet::Args::ParseArgumentValidException(oss.str().c_str());
            }
        }
        return true;
    }

  private:
    std::string prefix_;
    std::string suffix_;
};

int main(int argc, char* argv[]) {
    blet::Args args;
    // Add suffix on arguments if argument is "foo"
    args.addArgument("--option").help("custom option message").valid(new ValidCustom("foo", "bar")).required(true);

    try {
        args.setHelpException().setVersionException().parseArguments(argc, argv);
        std::cout << args["--option"] << std::endl;
    }
    catch (const blet::Args::HelpException& e) {
        std::cout << e.what() << std::endl;
    }
    catch (const blet::Args::VersionException& e) {
        std::cout << e.what() << std::endl;
    }
    catch (const blet::Args::ParseArgumentException& e) {
        std::cerr << args.getBinaryName() << ": " << e.what() << " -- '" << e.argument() << "'" << std::endl;
        return 1;
    }

    return 0;
}
```

```
$ ./a.out
./a.out: option is required -- '--option'
$ ./a.out --option foo
foobar
$ ./a.out --option 42
./a.out: "42" is not "foo" -- '--option'
$ ./a.out -h
usage: a.out --option OPTION [-h]

optional arguments:
  --option OPTION       custom option message (required)
  -h, --help            show this help message and exit
```
