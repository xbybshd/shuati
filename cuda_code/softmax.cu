// matrix row softmax
#define WARP_SIZE 32
// 单block softmax，模板版本
template <class T>
struct MaxOp {
    __device__ __forceinline__ T operator()(const T& x, const T& y) {
        return x > y ? x : y;
    }
};

template <>
struct MaxOp<float> {
    __device__ __forceinline__ float operator()(const float& x, const float& y) {
        return fmaxf(x, y);
    }
};

template <class T>
struct SumOp {
    __device__ __forceinline__ T operator()(const T& x, const T& y) {
        return x + y;
    }
};

template <class Operator, const int kWarpSize = WARP_SIZE>
__device__ __forceinline__ float warp_reduce_fp32(float val, Operator& op) {
#pragma unroll
    for (int mask = kWarpSize >> 1; mask >= 1; mask >>= 1) {
        val = op(val, __shfl_xor_sync(0xffffffff, val, mask));
    }
    return val;
}

template <class Operator, const int NUM_THREADS = 256>
__device__ float block_reduce_fp32(float val, int N, Operator& op) {
    int tid = threadIdx.x;
    int warp = tid / WARP_SIZE;
    int lane = tid % WARP_SIZE;
    constexpr int NUM_WARPS = (NUM_THREADS + WARP_SIZE - 1) / WARP_SIZE;
    __shared__ float reduce[NUM_WARPS];
    float value = warp_reduce_fp32<Operator, WARP_SIZE>(val, op);
    if (lane == 0) {
        reduce[warp] = value;
    }
    __syncthreads();
    value = (lane < NUM_WARPS) ? reduce[lane] : 0.0f;
    value = warp_reduce_fp32<Operator, NUM_WARPS>(value, op);
    // value = __shfl_sync(0xffffffff, value, 0,32);
    return value;
}

template <const int NUM_THREADS = 256>
__global__ void safe_softmax_block_fp32(float* x, float* y, int M, int N) {
    int tid = threadIdx.x;
    int row = blockIdx.x;
    if (row >= M)
        return;
    MaxOp<float> max_op;
    SumOp<float> sum_op;
    float max_val_thread = -FLT_MAX;
    for (int i = tid; i < N; i += NUM_THREADS) {
        max_val_thread = fmaxf(max_val_thread, x[row * N + i]);
    }
    float max_val =
        block_reduce_fp32<MaxOp<float>, NUM_THREADS>(max_val_thread, N, max_op);
    float exp_val = 0.0;
    for (int i = tid; i < N; i += NUM_THREADS) {
        exp_val += expf(x[row * N + i] - max_val);
    }
    float exp_sum =
        block_reduce_fp32<SumOp<float>, NUM_THREADS>(exp_val, N, sum_op);
    for (int i = tid; i < N; i += NUM_THREADS) {
        y[row * N + i] = expf(x[row * N + i] - max_val) / exp_sum;
    }
}
