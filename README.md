# QuantLib String Parser #

Transforma string a objectos de QuantLib y viceversa.

## Instalación ##

Ejemplo de instalacion con cmake:

    mkdir build 
    cd build
    cmake .. -DCMAKE_PREFIX_PATH='C:\Users\bloomberg\Desktop\Desarrollo\builds' -DCMAKE_INSTALL_PREFIX='C:\Users\bloomberg\Desktop\Desarrollo\builds\quantlibparser' -DCMAKE_CXX_STANDARD=20
    cmake --build . --config Release --target install

## Uso ##

    project("SI-Example")
    find_package(SI CONFIG REQUIRED)
    add_executable(SI-example src/main.cc)|
    arget_link_libraries(SI-example SI::SI)