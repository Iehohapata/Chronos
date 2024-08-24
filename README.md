# Chronos
Command line utility of a dubious quality for changing file timestamp.
Avaliable on Linux, Windows and macOS.
Usage:
```bash
chronos <filename> "CCYY/MM/DD hh:mm:ss"
```
# Installation
Use one of the precompiled binaries in latest Release, manually adding it to your PATH, or compile it using the following instructions.
# Compilation

**Build dependencies**

```
cmake
msvc (Windows)
ninja (macOS)
swiftc (macOS)
```
## Linux
```bash
git clone https://github.com/Iehohapata/Chronos.git
cd Chronos
cmake .
cmake --build .
sudo cmake --install .
```
## Windows
Building with following commands should add binary to system application folder(e.g. C:\Program Files (x86)\Chronos\bin). Following commands should be run as an administrator.
```bash
git clone https://github.com/Iehohapata/Chronos.git
cd Chronos
cmake --build . --config Release --target INSTALL
```
Run PowerShell and then naviagate to `helpers` folder of the project, run the following(where `[optional flag]`):
```powershell
Set-ExecutionPolicy Unrestricted
.\update_path.ps1 -appPath <path-to-executable> [-SystemWide]
Set-ExecutionPolicy Restricted
```
## macOS
```zsh
git clone https://github.com/Iehohapata/Chronos.git
cd Chronos
cmake . -G Ninja
cmake --build .
sudo cmake --install .
```
