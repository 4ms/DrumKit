# Build with:
#    make install-mm-sdk
#    make mm-plugin
#
# Or install the SDK somewhere, then do:
#    export METAMODULE_SDK_DIR=path/to/sdk 
#    make mm-plugin

METAMODULE_SDK_DIR ?= metamodule-plugin-sdk

mm-plugin:
	cmake -B build -G Ninja -DMETAMODULE_SDK_DIR=$(METAMODULE_SDK_DIR)
	cmake --build build

install-mm-sdk:
	rm -rf metamodule-plugin-sdk
	git clone https://github.com/4ms/metamodule-plugin-sdk --recursive 

install-mm-sdk-2.0:
	rm -rf metamodule-plugin-sdk
	git clone -b v2.0-dev https://github.com/4ms/metamodule-plugin-sdk --recursive 
