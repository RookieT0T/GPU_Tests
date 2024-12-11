#include "hip/hip_runtime.h"
#define HCC_ENABLE_PRINTF
#include <stdio.h>
#include <stdlib.h>

// define enough entries to fit all of addresses we want to access
#define CACHE_ENTRIES 4194304

// kernel code
// Access pattern: a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, a, q, c, e, r, f, i, s, t, b, a, d, e, g,
//                 u, m, n, o, p, v, b, w, a, m, x, f, e, i, b, o, u, c, n, d
// Access count: 50
// If you have a 4MB cache with 16-way associativity, and each cache
// line is 64B with BRRIP replacement policy, you will observe:
// 26 misses, 4 hits

// for RRIP replacement policy, we expect 23 misses, 7 hits

__global__ void kernel(int * arr) {
  // every array location is 4B wide, so given a cache of size N and associativity M, we can figure out which addresses map to which indices

  uint64_t a = 0;
  //, b = 0, c = 0, d = 0, e = 0, f = 0, g = 0, h = 0, i = 0, j = 0, k = 0, l = 0, m = 0, n = 0, o = 0, p = 0, q = 0;
  //uint64_t r = 0, s = 0, t = 0, u = 0, v = 0, w = 0, x = 0, y = 0, z = 0, a1 = 0, a2 = 0, a3 = 0, a4 = 0;
  //uint64_t b0 = 0, b1 = 0, b2 = 0, b3 = 0, b4 = 0, b5 = 0, b6 = 0, b7 = 0, b8 = 0, b9 = 0, b10 = 0, b11 = 0, b12 = 0, b13 = 0, b14 = 0, b15 = 0, b16 = 0, b17 = 0, b18 = 0, b19 = 0;

  asm volatile(
	  /*
		Ensure any initializing code is not being cached before code we care about.
    */
    // load all entries with wait between each
    "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
    "buffer_wbinvl1\n\t"
    "flat_load_dwordx2 %[out0], %[in1] glc\n\t"   // a
    
    "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
    "flat_load_dwordx2 %[out2], %[in3] glc\n\t"   // b
    
    "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
    "flat_load_dwordx2 %[out4], %[in5] glc\n\t"   // c
    
    "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
    "flat_load_dwordx2 %[out6], %[in7] glc\n\t"   // d
    
    "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
    "flat_load_dwordx2 %[out8], %[in9] glc\n\t"   // e
    
    "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
    "flat_load_dwordx2 %[out10], %[in11] glc\n\t" // f
    
    "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
    "flat_load_dwordx2 %[out12], %[in13] glc\n\t" // g
    
    "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
    "flat_load_dwordx2 %[out14], %[in15] glc\n\t" // h
    
    "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
    "flat_load_dwordx2 %[out16], %[in17] glc\n\t" // i
    
    "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
    "flat_load_dwordx2 %[out18], %[in19] glc\n\t" // j
    
    "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
    "flat_load_dwordx2 %[out20], %[in21] glc\n\t" // k
    
    "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
    "flat_load_dwordx2 %[out22], %[in23] glc\n\t" // l
    
    "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
    "flat_load_dwordx2 %[out24], %[in25] glc\n\t" // m
    
    "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
    "flat_load_dwordx2 %[out26], %[in27] glc\n\t" // n
    
    "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
    "flat_load_dwordx2 %[out28], %[in29] glc\n\t" // o
    
    "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
    "flat_load_dwordx2 %[out30], %[in31] glc\n\t" // p
    
    "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
    "flat_load_dwordx2 %[out32], %[in33] glc\n\t" // a

    "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
    "flat_load_dwordx2 %[out34], %[in35] glc\n\t" // q

    "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
    "flat_load_dwordx2 %[out36], %[in37] glc\n\t" // c

    "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
    "flat_load_dwordx2 %[out38], %[in39] glc\n\t" // e

    "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
    "flat_load_dwordx2 %[out40], %[in41] glc\n\t" // r

    "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
    "flat_load_dwordx2 %[out42], %[in43] glc\n\t" // f

    "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
    "flat_load_dwordx2 %[out44], %[in45] glc\n\t" // i

    "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
    "flat_load_dwordx2 %[out46], %[in47] glc\n\t" // s

    "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
    "flat_load_dwordx2 %[out48], %[in49] glc\n\t" // t

    "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
    "flat_load_dwordx2 %[out50], %[in51] glc\n\t" // b

    "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
    "flat_load_dwordx2 %[out52], %[in53] glc\n\t" // a

    "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
    "flat_load_dwordx2 %[out54], %[in55] glc\n\t" // d

    "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
    "flat_load_dwordx2 %[out56], %[in57] glc\n\t" // e

    "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
    "flat_load_dwordx2 %[out58], %[in59] glc\n\t" // g
    
    // *
    "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
    "flat_load_dwordx2 %[out60], %[in61] glc\n\t" // u

    "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
    "flat_load_dwordx2 %[out62], %[in63] glc\n\t" // m

    "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
    "flat_load_dwordx2 %[out64], %[in65] glc\n\t" // n

    "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
    "flat_load_dwordx2 %[out66], %[in67] glc\n\t" // o

    "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
    "flat_load_dwordx2 %[out68], %[in69] glc\n\t" // p

    "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
    "flat_load_dwordx2 %[out70], %[in71] glc\n\t" // v

    "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
    "flat_load_dwordx2 %[out72], %[in73] glc\n\t" // b

    "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
    "flat_load_dwordx2 %[out74], %[in75] glc\n\t" // w

    "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
    "flat_load_dwordx2 %[out76], %[in77] glc\n\t" // a

    "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
    "flat_load_dwordx2 %[out78], %[in79] glc\n\t" // m
    
    "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
    "flat_load_dwordx2 %[out80], %[in81] glc\n\t" // x

    "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
    "flat_load_dwordx2 %[out82], %[in83] glc\n\t" // f

    "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
    "flat_load_dwordx2 %[out84], %[in85] glc\n\t" // e

    "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
    "flat_load_dwordx2 %[out86], %[in87] glc\n\t" // i

    "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
    "flat_load_dwordx2 %[out88], %[in89] glc\n\t" // b

    "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
    "flat_load_dwordx2 %[out90], %[in91] glc\n\t" // o

    "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
    "flat_load_dwordx2 %[out92], %[in93] glc\n\t" // u

    "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
    "flat_load_dwordx2 %[out94], %[in95] glc\n\t" // c

    "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
    "flat_load_dwordx2 %[out96], %[in97] glc\n\t" // n

    "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
    "flat_load_dwordx2 %[out98], %[in99] glc\n\t" // d

    "s_waitcnt vmcnt(0) & lgkmcnt(0)\n\t"
    "s_nop 0\n\t"
    : 
    [out0]"=v"(a), [out2]"=v"(a), [out4]"=v"(a), [out6]"=v"(a), 
    [out8]"=v"(a), [out10]"=v"(a), [out12]"=v"(a), [out14]"=v"(a), 
    [out16]"=v"(a), [out18]"=v"(a), [out20]"=v"(a), [out22]"=v"(a), 
    [out24]"=v"(a), [out26]"=v"(a), [out28]"=v"(a), [out30]"=v"(a), 
    [out32]"=v"(a), [out34]"=v"(a), [out36]"=v"(a), [out38]"=v"(a), 
    [out40]"=v"(a), [out42]"=v"(a), [out44]"=v"(a), [out46]"=v"(a),
    [out48]"=v"(a), [out50]"=v"(a), [out52]"=v"(a), [out54]"=v"(a),
    [out56]"=v"(a), [out58]"=v"(a), [out60]"=v"(a), [out62]"=v"(a),
    [out64]"=v"(a), [out66]"=v"(a), [out68]"=v"(a), [out70]"=v"(a),
    [out72]"=v"(a), [out74]"=v"(a), [out76]"=v"(a), [out78]"=v"(a),
    [out80]"=v"(a), [out82]"=v"(a), [out84]"=v"(a), [out86]"=v"(a),
    [out88]"=v"(a), [out90]"=v"(a), [out92]"=v"(a), [out94]"=v"(a),
    [out96]"=v"(a), [out98]"=v"(a)
    : 
    [in1]"v"((uint64_t *)&arr[0]), [in3]"v"((uint64_t *)&arr[65536]), 
    [in5]"v"((uint64_t *)&arr[131072]), [in7]"v"((uint64_t *)&arr[196608]), 
    [in9]"v"((uint64_t *)&arr[262144]), [in11]"v"((uint64_t *)&arr[327680]), 
    [in13]"v"((uint64_t *)&arr[393216]), [in15]"v"((uint64_t *)&arr[458752]), 
    [in17]"v"((uint64_t *)&arr[524288]), [in19]"v"((uint64_t *)&arr[589824]),
    [in21]"v"((uint64_t *)&arr[655360]), [in23]"v"((uint64_t *)&arr[720896]), 
    [in25]"v"((uint64_t *)&arr[786432]), [in27]"v"((uint64_t *)&arr[851968]),
    [in29]"v"((uint64_t *)&arr[917504]), [in31]"v"((uint64_t *)&arr[983040]),    // 16 misses to fill the set
    [in33]"v"((uint64_t *)&arr[1]), [in35]"v"((uint64_t *)&arr[1048576]),        // access a & q
    [in37]"v"((uint64_t *)&arr[131073]), [in39]"v"((uint64_t *)&arr[262145]),    // access c & e 
    [in41]"v"((uint64_t *)&arr[1114112]), [in43]"v"((uint64_t *)&arr[327681]),   // access r & f
    [in45]"v"((uint64_t *)&arr[524289]), [in47]"v"((uint64_t *)&arr[1179648]),   // access i & s
    [in49]"v"((uint64_t *)&arr[1245184]), [in51]"v"((uint64_t *)&arr[65537]),    // access t & b
    [in53]"v"((uint64_t *)&arr[2]), [in55]"v"((uint64_t *)&arr[196609]),         // access a & d 
    [in57]"v"((uint64_t *)&arr[262146]), [in59]"v"((uint64_t *)&arr[393217]),    // access e & g
    [in61]"v"((uint64_t *)&arr[1310720]), [in63]"v"((uint64_t *)&arr[786433]),   // access u & m
    [in65]"v"((uint64_t *)&arr[851969]), [in67]"v"((uint64_t *)&arr[917505]),    // access n & o
    [in69]"v"((uint64_t *)&arr[983041]), [in71]"v"((uint64_t *)&arr[1376256]),   // access p & v
    [in73]"v"((uint64_t *)&arr[65538]), [in75]"v"((uint64_t *)&arr[1441792]),    // access b & w
    [in77]"v"((uint64_t *)&arr[3]), [in79]"v"((uint64_t *)&arr[786434]),         // access a & m
    [in81]"v"((uint64_t *)&arr[1507328]), [in83]"v"((uint64_t *)&arr[327682]),   // access x & f
    [in85]"v"((uint64_t *)&arr[262147]), [in87]"v"((uint64_t *)&arr[524290]),    // access e & i
    [in89]"v"((uint64_t *)&arr[65539]), [in91]"v"((uint64_t *)&arr[917506]),     // access b & o
    [in93]"v"((uint64_t *)&arr[1310721]), [in95]"v"((uint64_t *)&arr[131074]),   // access u & c
    [in97]"v"((uint64_t *)&arr[851970]), [in99]"v"((uint64_t *)&arr[196610])     // access n & d
    :"memory"
            );
}

// host code
int main(){
    int *arr = (int *)calloc(sizeof(int), CACHE_ENTRIES);
    //uint64_t *dummy = (uint64_t *)calloc(sizeof(uint64_t), 1);

    int *arr_g;
    //uint64_t *dummy_g;

    hipMallocManaged(&arr_g, CACHE_ENTRIES*sizeof(int));
    //hipMallocManaged(&dummy_g, CACHE_ENTRIES*sizeof(uint64_t));

    // initialize arr_g with arr
    hipMemcpy(arr_g, arr, CACHE_ENTRIES*sizeof(int), hipMemcpyHostToDevice);

    // just want 1 GPU thread to run our kernel
    hipLaunchKernelGGL(kernel, dim3(1), dim3(1), 0, 0,  arr_g);

    // copy dummy value back to ensure compiler doesn't optimize out anything
    //hipMemcpy(dummy, dummy_g, 1*sizeof(uint64_t), hipMemcpyDeviceToHost);
    //printf("Dummy value = %lu\n", dummy[0]);

    hipFree(arr_g);
    //hipFree(dummy_g);
    free(arr);
    //free(dummy);
    return 0;
}
