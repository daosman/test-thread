#!/bin/bash

REGISTRY='quay.io/dosman'
IMAGE='test-thread'

BUILD_IMAGE='quay.io/centos/centos:stream8'
BASE_IMAGE='registry.access.redhat.com/ubi8-minimal:latest'
TAG="latest"

podman build -f Dockerfile --no-cache . \
    --build-arg BASE_IMAGE=${BASE_IMAGE} \
    --build-arg BUILD_IMAGE=${BUILD_IMAGE} \
  -t ${REGISTRY}/${IMAGE}:${TAG}

podman push ${REGISTRY}/${IMAGE}:${TAG}
