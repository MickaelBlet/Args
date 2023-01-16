# Dest

## Simple type to destination

```cpp
#include <iostream>

#include "mblet/argparsor.h"

int main(int argc, char* argv[]) {
    int i = 0;
    double d = 0;
    float f = 0;
    unsigned int ui = 0;

    mblet::Argparsor args;
    args.addArgument("--int").dest(i);
    args.addArgument("--double").dest(d);
    args.addArgument("--float").dest(f);
    args.addArgument("--uint").dest(ui);
    try {
        args.parseArguments(argc, argv);
        std::cout << i << std::endl;
        std::cout << d << std::endl;
        std::cout << f << std::endl;
        std::cout << ui << std::endl;
    }
    catch (const mblet::Argparsor::ParseArgumentException& e) {
        std::cerr << args.getBynaryName() << ": " << e.what();
        std::cerr << " -- '" << e.argument() << "'" << std::endl;
        return 1; // END
    }
    return 0;
}
```

```
$ a.out --int 42 --double 42.42 --float 24.24 --uint 42
42
42.42
24.24
42
```

## Custom type to destination

```cpp
#include <iostream>

#include "mblet/argparsor.h"

enum Enum {
    ENUM0,
    ENUM1,
    ENUM2,
    ENUM3
};

void argToEnum(Enum& e, bool /*isExist*/, const std::string& argument) {
    static const std::pair<std::string, eLogLevel> pairEnums[] = {
        std::pair<std::string, eLogLevel>("ENUM0", ENUM0),
        std::pair<std::string, eLogLevel>("ENUM1", ENUM1),
        std::pair<std::string, eLogLevel>("ENUM2", ENUM2),
        std::pair<std::string, eLogLevel>("ENUM3", ENUM3)};
    static const std::map<std::string, eLogLevel> enums(
        pairEnums, pairEnums + sizeof(pairEnums) / sizeof(*pairEnums));

    e = enums.at(argument);
}

int main(int argc, char* argv[]) {
    Enum e;

    mblet::Argparsor args;
    args.addArgument("-e").flag("--enum").help("help of enum").metavar("ENUM")
        .valid(new mblet::Argparsor::ValidChoise(args.vector("ENUM0", "ENUM1", "ENUM2", "ENUM3")))
        .defaults("ENUM0")
        .dest(e, argToEnum);
    try {
        args.parseArguments(argc, argv, true);
        switch(e) {
            case ENUM0:
                std::cout << "ENUM0" << std::end;
                break;
            case ENUM1:
                std::cout << "ENUM1" << std::end;
                break;
            case ENUM2:
                std::cout << "ENUM2" << std::end;
                break;
            case ENUM3:
                std::cout << "ENUM3" << std::end;
                break;
        }
    }
    catch (const mblet::Argparsor::ParseArgumentException& e) {
        std::cerr << args.getBynaryName() << ": " << e.what();
        std::cerr << " -- '" << e.argument() << "'" << std::endl;
        return 1; // END
    }
    return 0;
}
```

```
$ a.out --enum EMUN3
ENUM3
```

## Vector type to destination

```cpp
#include <iostream>

#include "mblet/argparsor.h"

int main(int argc, char* argv[]) {
    std::vector<int> i = 0;
    std::vector<double> d = 0;
    std::vector<float> f = 0;
    std::vector<unsigned int> ui = 0;

    mblet::Argparsor args;
    args.addArgument("--int").action(args.APPEND).dest(i);
    args.addArgument("--double").action(args.APPEND).dest(d);
    args.addArgument("--float").action(args.APPEND).dest(f);
    args.addArgument("--uint").action(args.APPEND).dest(ui);
    try {
        args.parseArguments(argc, argv);
        for (std::size_t j = 0; j < i.size(); ++j) {
            std::cout << "i: " << i[j] << std::endl;
        }
        for (std::size_t j = 0; j < d.size(); ++j) {
            std::cout << "d: " << d[j] << std::endl;
        }
        for (std::size_t j = 0; j < f.size(); ++j) {
            std::cout << "f: " << f[j] << std::endl;
        }
        for (std::size_t j = 0; j < ui.size(); ++j) {
            std::cout << "ui: " << ui[j] << std::endl;
        }
    }
    catch (const mblet::Argparsor::ParseArgumentException& e) {
        std::cerr << args.getBynaryName() << ": " << e.what();
        std::cerr << " -- '" << e.argument() << "'" << std::endl;
        return 1; // END
    }
    return 0;
}
```

```
$ a.out --int 0 --int 1 --double 2 --double 3
i: 0
i: 1
d: 2
d: 3
```

## Vector of vector of type to destination

```cpp
#include <iostream>

#include "mblet/argparsor.h"

int main(int argc, char* argv[]) {
    std::vector<std::vector<int> > i = 0;
    std::vector<std::vector<double> > d = 0;
    std::vector<std::vector<float> > f = 0;
    std::vector<std::vector<unsigned int> > ui = 0;

    mblet::Argparsor args;
    args.addArgument("--int").action(args.APPEND).nargs(2).dest(i);
    args.addArgument("--double").action(args.APPEND).nargs(2).dest(d);
    args.addArgument("--float").action(args.APPEND).nargs(2).dest(f);
    args.addArgument("--uint").action(args.APPEND).nargs(2).dest(ui);
    try {
        args.parseArguments(argc, argv);
        for (std::size_t j = 0; j < i.size(); ++j) {
            for (std::size_t k = 0; k < i[j].size(); ++k) {
                std::cout << "i: " << i[j][k] << std::endl;
            }
        }
        for (std::size_t j = 0; j < d.size(); ++j) {
            for (std::size_t k = 0; k < d[j].size(); ++k) {
                std::cout << "d: " << d[j][k] << std::endl;
            }
        }
        for (std::size_t j = 0; j < f.size(); ++j) {
            for (std::size_t k = 0; k < f[j].size(); ++k) {
                std::cout << "f: " << f[j][k] << std::endl;
            }
        }
        for (std::size_t j = 0; j < ui.size(); ++j) {
            for (std::size_t k = 0; k < ui[j].size(); ++k) {
                std::cout << "ui: " << ui[j][k] << std::endl;
            }
        }
    }
    catch (const mblet::Argparsor::ParseArgumentException& e) {
        std::cerr << args.getBynaryName() << ": " << e.what();
        std::cerr << " -- '" << e.argument() << "'" << std::endl;
        return 1; // END
    }
    return 0;
}
```

```
$ a.out --int 0 1 --double 2 3
i: 0
i: 1
d: 2
d: 3
```