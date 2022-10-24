ARG tag=latest
FROM externalpackages:${tag}

COPY . /quantlibparser

WORKDIR /quantlibparser/build.quantlibparser
RUN cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_STANDARD=20
RUN make -j ${num_cores} && make install 
RUN cd / && rm -rf quantlibparser && ldconfig

WORKDIR /
CMD bash