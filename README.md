# GPU_replacement_policy_test

GPU replacement policy test used on real GPU (VEGA) or gem5 simulated GPU


## Compiling tests

Go into each signle test folder to compile
```bash
cd test_folder
docker run --volume $(pwd):$(pwd) -w $(pwd) YOUR_DOCKER_IMAGE make
```


### Running the tests
Running benchmarks with different replacement policies for TCP and TCC caches

1. First running with debug flag GPUKernelInfo to get kernel1 start time and complete time as debug start time and debug end time
```bash
docker run --volume $(pwd):$(pwd) -w $(pwd) YOUR_DOCKER_IMAGE build/VEGA_X86/gem5.opt configs/example/apu_se.py -n 3 --dgpu --gfx-version=gfx900 --num-compute-units=4 --cu-per-sa=4 --num-gpu-complex=1 --reg-alloc-policy=dynamic --num-tccs=8 --num-dirs=64 --mem-size=16GB --mem-type=HBM_2000_4H_1x64 --vreg-file-size=16384 --sreg-file-size=800 --tcc-size=4MB --gpu-clock=1801MHz --ruby-clock=1000MHz --vrf_lm_bus_latency=6 --mem-req-latency=69 --mem-resp-latency=69 --mandatory_queue_latency=1 --max-cu-tokens=160 --max-coalesces-per-cycle=10 --sqc-size=16kB --tcp-size=4MB --scalar-mem-req-latency=28 --TCP_latency=4 --tcp-assoc=16 --tcp-num-banks=16 --TCC_latency=121 --tcc-assoc=16 --tcc-tag-access-latency=1 --tcc-data-access-latency=1 --tcp-rp=YOUR_REPLACEMENT_POLICY --WB_L2 --tcc-rp=YOUR_REPLACEMENT_POLICY -c YOUR_TEST
```

