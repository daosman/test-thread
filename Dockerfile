ARG BASE_IMAGE
ARG BUILD_IMAGE

FROM ${BUILD_IMAGE} AS builder
WORKDIR /build/

COPY . .

RUN yum groupinstall -y "Development Tools" 

RUN make clean && make

FROM ${BASE_IMAGE}

RUN microdnf install -y procps util-linux; microdnf clean all

COPY --from=builder /build/test-thread /usr/local/bin/
RUN setcap 'cap_sys_nice+ep' /usr/local/bin/test-thread
