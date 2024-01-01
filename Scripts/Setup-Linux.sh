#!/bin/bash

pushd ..
Extern/Binaries/Premake/Linux/premake5 --cc=clang --file=Build.lua gmake2
popd
