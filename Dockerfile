ARG BASE_IMAGE
ARG BUILD_IMAGE

FROM ${BUILD_IMAGE} AS builder
WORKDIR /build/

COPY . .

RUN yum groupinstall -y "Development Tools" 

RUN make clean && make

FROM ${BASE_IMAGE}

COPY --from=builder /build/test-thread /usr/local/bin/
RUN chmod +x /usr/local/bin/test-thread

#ENTRYPOINT ["/usr/local/bin/test-thread"]
