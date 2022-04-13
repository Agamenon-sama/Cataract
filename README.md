# Cataract

A port scanner for Linux

## Dependencies

For now, nothing except the C++ standard library

## Build

```
cd build
make
```

I currently have a problem where make doesn't recompile modified files. This will be fixed but until then, every time you want to recompile, you have to use

```
make clean
make
```

## Usage

```
cataract ports <ports> host <hostname>
```

ports ranges are set with hyphens (-) and you can set multiple seperated port numbers with commas (,)

example :

```
cataract ports 20-50,80 host <hostname>
```

hostname can be a domain name or an ipv4 address in dot-decimal notation

## License

MIT License