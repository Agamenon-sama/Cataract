# Cataract

A port scanner for Linux

## Dependencies

For now, nothing except the C++ standard library

## Build

```
cd build
make
```

## Usage

```
cataract ports <ports> host <hostname>
cataract ports <ports> host6 <hostname>
```

ports ranges are set with hyphens (-) and you can set multiple seperated port numbers with commas (,)

host specify the ipv4 hostname

host6 specify the ipv6 hostname

### example :

```
cataract ports 20-50,80 host <hostname>
```

hostname can be a domain name, an ipv4 address in dot-decimal notation or an ipv6 address in colon hexadecimal notation

## License

MIT License