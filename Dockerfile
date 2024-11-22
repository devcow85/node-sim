# Ubuntu 기반 이미지 사용
FROM ubuntu:20.04

# 환경 설정
ENV DEBIAN_FRONTEND=noninteractive

# 필수 패키지 설치
RUN apt-get update && apt-get install -y \
    build-essential \
    python3 \
    python3-pip \
    kmod \
    && apt-get clean

# Python 패키지 설치
RUN pip3 install numpy

# 작업 디렉토리 생성
WORKDIR /app

# Python 런타임 관련 파일 복사
COPY device_runtime.py ./
COPY test_virtual_device.py ./

# Docker 컨테이너에서 커널 모듈을 직접 컴파일하지 않음
# 대신, 커널 모듈은 호스트에서 컴파일 후 사용하도록 설계
CMD ["bash"]
