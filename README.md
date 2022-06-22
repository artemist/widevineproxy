# widevineproxy

## How to build

```shell
# from MSYS2 bash on Windows
cmake .
cmake --build .
```

## How to use

```shell
cp msys-widevineproxy.dll "/c/Program Files (x86)/Microsoft/Edge/Application/102.0.1245.44/WidevineCdm/_platform_specific/win_x64/widevinecdm.dll"
cp msys-widevineproxy.dll "/c/Program Files (x86)/Microsoft/EdgeCore/102.0.1245.44/WidevineCdm/_platform_specific/win_x64/widevinecdm.dll"
# open Edge browser and test at https://bitmovin.com/demos/drm
```
