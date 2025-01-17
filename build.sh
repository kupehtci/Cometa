#!/bin/bash
# Settle for macOS

## Clean previous build
## Generate MakeFile and dependencies with targeted OS as macOS
## Compile the project with debug configuration using `make` command
## Run the compiled binary as DEBUG by default
## If you want to run the release version, change the config to release

source /Users/dlaplana/VulkanSDK/1.3.275.0/setup-env.sh

premake5 clean

premake5 gmake --cc=gcc --os=macosx

make config=debug

bin/Debug/AuraGL