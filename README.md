# Cataract

A port scanner for Linux

## Dependencies

- Posix sockets
- Qt framework (mainly QtCore and QtWidget)

## Build

You want Qt Creator. Use Qt Creator to open the CMakeLists.txt file and build the project.

## Usage

### CLI

```
cataract ports <ports> host <hostname>
cataract ports <ports> host6 <hostname>
```

ports ranges are set with hyphens (-) and you can set multiple seperated port numbers with commas (,)

host specify the ipv4 hostname

host6 specify the ipv6 hostname

### GUI

You can either just

```
cataract
```

Or double-click the executable

### example :

```
cataract ports 20-50,80 host <hostname>
```

hostname can be a domain name, an ipv4 address in dot-decimal notation or an ipv6 address in colon hexadecimal notation

## License

MIT License
