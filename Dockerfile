ARG tag=latest
FROM externalpackages:${tag}

COPY . /quantlibparser

WORKDIR /quantlibparser/build.quantlibparser
RUN cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_STANDARD=20 -DCMAKE_INCLUDE_PATH='/usr/local/include'
RUN make -j ${num_cores} && make install 

WORKDIR /quantlibparser/python
RUN pip3 install pybind11 && python3 setup.py install
RUN cd / && rm -rf quantlibparser && ldconfig

WORKDIR /
CMD bash