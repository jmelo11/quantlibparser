# QuantLib String Parser #

Transforma string a objectos de QuantLib y viceversa.

## Instalación ##

Ejemplo de instalacion con cmake:

Windows:

    mkdir build && cd build
    cmake .. -DCMAKE_PREFIX_PATH='C:\Users\bloomberg\Desktop\Desarrollo\builds' -DCMAKE_INSTALL_PREFIX='C:\Users\bloomberg\Desktop\Desarrollo\builds' -DCMAKE_BUILD_TYPE=Release -DBoost_INCLUDE_DIR='C:\Users\bloomberg\Desktop\Desarrollo\builds\boost'
    cmake --build . --config Release --target install -j 18



## Uso ##

    project("SI-Example")
    find_package(quantlibparser REQUIRED)
    add_executable(SI-example src/main.cc)
    arget_link_libraries(SI-example SI::SI)