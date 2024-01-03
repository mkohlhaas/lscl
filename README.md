### List OpenCL platforms and devices in JSON.

### Build

```shell
git clone https://github.com/mkohlhaas/lscl.git
cmake -S lscl -B build -G Ninja
cmake --build build/
```

### Usage with [jq](https://github.com/jqlang/jq)

```shell
lscl | jq
```
