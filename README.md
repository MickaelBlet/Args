# Optparsor
Check and Get options from argc and argv

## Build
```bash
# static build
mkdir build ; pushd build && cmake .. && make -j ; popd
# shared build
mkdir build ; pushd build && cmake -DBUILD_SHARED_LIBS=1 .. && make -j ; popd
# static build and launch test
mkdir build ; pushd build && cmake -DBUILD_TESTING=1 .. && make -j && make test ; popd
# shared build and launch test
mkdir build ; pushd build && cmake -DBUILD_SHARED_LIBS=1 -DBUILD_TESTING=1 .. && make -j && make test ; popd
```

## Examples
```cpp
mblet::Optparsor optparsor;
try {
    #if __cplusplus >= 201103L
        optparsor.addOption("-t", "--test", "TEST", false, 3, {"TEST", "TUTU", "TATA"}, {"TEST", "TUTU", "TATA"});
    #else
        optparsor.addOption("-t", "--test", "test options", false, 3, MBLET_OPT_VECTOR("TESTS", "TUTU", "TATA"), MBLET_OPT_VECTOR("TUTU", "TATA", "TESTS"));
        optparsor.addOption("-s", "", "little s options", false, 1, MBLET_OPT_VECTOR("TESTS"), MBLET_OPT_VECTOR("TUTU"));
        optparsor.addArgument("PLOUF", "plouf arg", true);
    #endif
    optparsor.parseArguments(argc, argv);
    for (std::size_t i = 0 ; i < optparsor["-t"].size() ; ++i) {
        std::cout << optparsor["-t"][i] << std::endl;
    }
    for (std::size_t i = 0 ; i < optparsor["-s"].size() ; ++i) {
        std::cout << optparsor["-s"][i] << std::endl;
    }
    if (optparsor["PLOUF"]) {
        std::cout << optparsor["PLOUF"] << std::endl;
    }
}
catch (const mblet::Optparsor::ParseArgumentRequiredException& e) {
    std::cerr << optparsor.getBynaryName() << ": " << e.what() << " -- '" << e.argument() << "'" << std::endl;
    optparsor.getUsage(std::cerr);
}
catch (const mblet::Optparsor::ParseArgumentException& e) {
    std::cerr << optparsor.getBynaryName() << ": " << e.what() << " -- '" << e.argument() << "'" << std::endl;
    optparsor.getUsage(std::cerr);
}
catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
}
optparsor.getUsage(std::cerr);
```