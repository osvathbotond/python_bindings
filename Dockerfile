FROM ubuntu:latest

RUN : \
    && apt-get update \
    && DEBIAN_FRONTEND=noninteractive apt-get install -y python3 \
                                                         python3-pip \
                                                         python3-dev \
                                                         libboost-python-dev \
    && rm -rf /var/lib/apt/lists/* \
    && :


RUN python3 -m pip --no-cache-dir --disable-pip-version-check install pybind11
