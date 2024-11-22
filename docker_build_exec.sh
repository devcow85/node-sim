make
sudo docker build -t virtual-device .
sudo docker run --rm -it --privileged -v $(pwd)/virtual_device.ko:/app/virtual_device.ko virtual-device
