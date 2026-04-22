# c_standards-99-11

### Dependency

```
python3 -m venv .venv
source .venv/bin/activate
pip3 install kconfiglib
```
if venv path is not .venv, you can change it using `make menuconfig`

### Configuration
```
make menuconfig
```
Saving menuconfig will create .config file used for compilation

### How to run
```
make run
```
or
```
make test
```
