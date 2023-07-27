# libparser
Simple libc parser to parse args from command line.

## Platform
Linux only for the moment. It will be improved.

## How to build
### Build lib
```bash
cmake -B build
cmake --build build
```

### Build test
```bash
cmake -B build -DTESTING=ON
cmake --build build
```
Then, to run test, execute:
```bash
./bin/test_parser
```

## Contribute
No specification, ask for feature by creating issue or creating pull requests with changes.

## Contact
[osvegn](thomas.prudhomme@epitech.eu)
