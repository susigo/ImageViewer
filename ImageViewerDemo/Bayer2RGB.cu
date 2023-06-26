
#include<iostream>
#include <cuda_runtime.h> 
#include <device_launch_parameters.h>

/*核函数（设备运行函数）*/
__global__ void vectorAdd(const float* A, const float* B, float* C, int numElements)
{
	int i = blockDim.x * blockIdx.x + threadIdx.x; //获取线程id
	if (i < numElements)
	{
		C[i] = A[i] * B[i] + 10;
	}
}
//定义内核函数，在设备得线程上运行
__global__ void VecAdd(float* a, float* b, float* c)
{
	int i = threadIdx.x;
	c[i] = a[i] + b[i];
}

__global__ void addOne(int* data, int numdata)
{
	int i = blockDim.x * blockIdx.x + threadIdx.x; //获取线程id
	if (i < numdata)
	{
		data[i] = data[i] + 1;
	}
}


void test()
{
	float A[5] = { 1.0,2.2,3.3,4.4,5.5 };
	float B[5] = { 1.0,2.2,3.3,4.4,5.5 };
	float C[5] = { 1.0,2.2,3.3,4.4,5.5 };
	VecAdd << <1, 5 >> > (A, B, C);
	std::cout << A[0] << std::endl;
}

/*主机函数*/
void test1(int num)
{
	/*生成主机数据内存 h_A, h_B, h_C*/
	int numElements = num;
	size_t size = numElements * sizeof(float);
	float* h_A = (float*)malloc(size);
	float* h_B = (float*)malloc(size);
	float* h_C = (float*)malloc(size);
	for (int i = 0; i < numElements; ++i)
	{
		h_A[i] = rand() / (float)RAND_MAX;
		h_B[i] = rand() / (float)RAND_MAX;
	}

	/*生成设备内存 d_A，d_B，d_C */
	float* d_A = NULL;
	cudaMalloc((void**)&d_A, size);
	float* d_B = NULL;
	cudaMalloc((void**)&d_B, size);
	float* d_C = NULL;
	cudaMalloc((void**)&d_C, size);

	/*将主机内存数据复制到设备内存 h_A--d_A，h_B--d_B */
	cudaMemcpy(d_A, h_A, size, cudaMemcpyHostToDevice);
	cudaMemcpy(d_B, h_B, size, cudaMemcpyHostToDevice);

	/*设置设备的线程数，并调用核函数*/
	int threadsPerBlock = 256; //每个线程块的线程数量
	int blocksPerGrid = (numElements + threadsPerBlock - 1) / threadsPerBlock; //线程块的数量
	vectorAdd << < blocksPerGrid, threadsPerBlock >> > (d_A, d_B, d_C, numElements);
	cudaGetLastError();

	/*将设备内存数据复制到主机内存 d_C--h_C */
	cudaMemcpy(h_C, d_C, size, cudaMemcpyDeviceToHost);

	/* 释放设备内存 d_A d_B d_C */
	cudaFree(d_A);
	cudaFree(d_B);
	cudaFree(d_C);

	/* 结果验证 */
	std::cout << "A[0]: " << (float)h_A[0] << " B[0]: " << (float)h_B[0] << " 结果C[0] = A[i] + B[i] + 10: " << (float)h_C[0] << std::endl;
	std::cout << "A[1]: " << (float)h_A[1] << " B[1]: " << (float)h_B[1] << " 结果C[1] = A[i] + B[i] + 10: " << (float)h_C[1] << std::endl;
	std::cout << "A[2]: " << (float)h_A[2] << " B[2]: " << (float)h_B[2] << " 结果C[2] = A[i] + B[i] + 10: " << (float)h_C[2] << std::endl;

	/* 释放主机内存 h_A h_B h_C */
	free(h_A);
	free(h_B);
	free(h_C);
}


void addList(int* _data_ptr, int size)
{
	size_t data_size = size * sizeof(int);
	int* d_A = NULL;
	cudaMalloc((void**)&d_A, data_size);

	cudaMemcpy(d_A, _data_ptr, data_size, cudaMemcpyHostToDevice);
	/*设置设备的线程数，并调用核函数*/
	int threadsPerBlock = 256; //每个线程块的线程数量
	int blocksPerGrid = (data_size + threadsPerBlock - 1) / threadsPerBlock; //线程块的数量
	addOne << < blocksPerGrid, threadsPerBlock >> > (d_A, data_size);

	/*将设备内存数据复制到主机内存 d_C--h_C */
	cudaMemcpy(_data_ptr, d_A, data_size, cudaMemcpyDeviceToHost);

	cudaFree(d_A);
}