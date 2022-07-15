#PATH=/usr/lib64/gcc/x86_64-suse-linux/11/:/usr/local/cuda-11.7/bin/:$PATH
nvcc curand.cu -lcurand -o curand
