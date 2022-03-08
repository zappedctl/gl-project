#!/bin/bash

PROJECT_NAME="gl"
LIBRARIES="-lGL -lGLU -lglfw -lGLEW -L/usr/include/stb -lX11 -lXxf86vm -lXrandr -lpthread -lXi"

if [[ $1 == "comp" ]]
then
  echo "Compiling..."
  mkdir -p build
  rm -f build/*
  g++ -c src/Main.cpp src/Classes/*.cpp --std=c++11
  g++ *.o -o build/$PROJECT_NAME -I src/Headers $LIBRARIES
  rm *.o
elif [[ $1 == "comph" ]]
then
  echo "Compiling headers..."
  g++ --std=c++11 src/Headers.h
elif [[ $1 == "cc" ]]
then
  > src/Headers/${2^}.h
  > src/Classes/${2^}.cpp

  echo "#ifndef ${2^^}_H" >> src/Headers/${2^}.h
  echo "#define ${2^^}_H" >> src/Headers/${2^}.h
  echo "" >> src/Headers/${2^}.h
  echo "class ${2^}" >> src/Headers/${2^}.h
  echo "{" >> src/Headers/${2^}.h
  echo "  public:" >> src/Headers/${2^}.h
  echo "    // Constructor and Destructor" >> src/Headers/${2^}.h
  echo "    ${2^}();" >> src/Headers/${2^}.h
  echo "    virtual ~${2^}();" >> src/Headers/${2^}.h
  echo "};" >> src/Headers/${2^}.h
  echo "" >> src/Headers/${2^}.h
  echo "#endif // ${2^^}_H" >> src/Headers/${2^}.h

  echo "#include \"../Headers/${2^}.h\"" >> src/Classes/${2^}.cpp
  echo "" >> src/Classes/${2^}.cpp
  echo "// Constructor and Destructor" >> src/Classes/${2^}.cpp
  echo "" >> src/Classes/${2^}.cpp
  echo "${2^}::${2^}()" >> src/Classes/${2^}.cpp
  echo "{" >> src/Classes/${2^}.cpp
  echo "" >> src/Classes/${2^}.cpp
  echo "}" >> src/Classes/${2^}.cpp
  echo "" >> src/Classes/${2^}.cpp
  echo "${2^}::~${2^}()" >> src/Classes/${2^}.cpp
  echo "{" >> src/Classes/${2^}.cpp
  echo "" >> src/Classes/${2^}.cpp
  echo "}" >> src/Classes/${2^}.cpp

  echo "Successfuly created class ${2^}!"
elif [[ $1 == "rc" ]]
then
  rm src/Headers/${2^}.h
  rm src/Classes/${2^}.cpp

  echo "Successfuly removed class ${2^}!"
elif [[ $1 == "run" ]]
then
  echo "Launching ${PROJECT_NAME}..."
  ./build/$PROJECT_NAME
else
  echo "No valid option provided!"
fi
