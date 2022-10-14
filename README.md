# QuantLib String Parser #

Transforma string a objectos de QuantLib y viceversa.

## Instalación ##

Ejemplo de instalacion con cmake:

    mkdir build 
    cd build
    cmake .. -DCMAKE_INSTALL_PREFIX='C:\Users\bloomberg\Desktop\Desarrollo\builds' -DBoost_INCLUDE_DIR='C:\Users\bloomberg\Desktop\Desarrollo\builds\boost'
    cmake --build . --config Release --target install

## Uso ##

    project("SI-Example")

    find_package(SI CONFIG REQUIRED)

    add_executable(SI-example src/main.cc)|
    arget_link_libraries(SI-example SI::SI)