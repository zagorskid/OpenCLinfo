#include <iostream>
#include <vector>
#include <string> 

#include <CL/cl.h>

using namespace std;
const int MAX_DEVICES = 100;

string getDeviceTypeName(cl_device_type deviceType)
{
	string deviceTypeName = "OTHER DEVICE";

	if (deviceType == CL_DEVICE_TYPE_CPU)
		deviceTypeName = "CPU DEVICE";

	if (deviceType == CL_DEVICE_TYPE_GPU)
		deviceTypeName = "GPU DEVICE, YAY!";

	return deviceTypeName;
}


int main(int argc, char* argv[])
{
	cout << "OpenCL Platform & Device Info Tool" << endl;

	// OpenCL init
	cl_int status; // CL_SUCCESS if ok
	cl_uint num_platforms = 0;
	cl_uint num_devices = 0;

	// Check number of OpenCL platforms
	status = clGetPlatformIDs(0, NULL, &num_platforms);
	if (num_platforms == 0 || status != CL_SUCCESS) 
	{	
		cout << "No compatible OpenCL devices found." << endl;
		return EXIT_FAILURE; 
	}
	
	// Get platforms ids
	vector<cl_platform_id> platforms(num_platforms);	

	// Display available platforms
	cout << "\nOpenCL platforms found: " << num_platforms << endl;

	status = clGetPlatformIDs(num_platforms, &platforms.front(), NULL);

	const cl_device_type deviceType = CL_DEVICE_TYPE_ALL;
	cl_device_id device;
	cl_platform_id platform;	

	for (cl_uint i = 0; i < num_platforms; ++i) 
	{
		platform = platforms[i];

		// platform info	
		const int LEN = 10240;
		char buffer[LEN]; 
		cl_uint buf_uint = 0;
		cl_ulong buf_ulong = 0;
		cl_device_type buf_type = 0;

		cout << "\n### PLATFORM #" << i << " INFO: ###" << endl;
		clGetPlatformInfo(platform, CL_PLATFORM_NAME, sizeof(buffer), buffer, NULL);
		cout << "PLATFORM NAME: " << buffer << endl;
		clGetPlatformInfo(platform, CL_PLATFORM_VERSION, sizeof(buffer), buffer, NULL);
		cout << "PLATFORM VERSION: " << buffer << endl;
		clGetPlatformInfo(platform, CL_PLATFORM_VENDOR, sizeof(buffer), buffer, NULL);
		cout << "PLATFORM VENDOR: " << buffer << endl;
		clGetPlatformInfo(platform, CL_PLATFORM_EXTENSIONS, sizeof(buffer), buffer, NULL);
		cout << "PLATFORM EXTENSIONS: " << buffer << endl;
		
		cl_device_id devices[MAX_DEVICES];
		status = clGetDeviceIDs(platforms[i], deviceType, MAX_DEVICES, devices, &num_devices);

		// Devices info
		cout << "Number of devices on platform #" << i << ": " << num_devices << ": " << endl;		
		
		for (cl_uint j = 0; j < num_devices && status == CL_SUCCESS; ++j)
		{
			device = devices[j];
			cout << "\n### DEVICE #" << j << " INFO: ###" << endl;
			clGetDeviceInfo(device, CL_DEVICE_TYPE, sizeof(buf_type), &buf_type, NULL);
			cout << "DEVICE TYPE: " << getDeviceTypeName(buf_type) << endl;
			clGetDeviceInfo(device, CL_DEVICE_NAME, sizeof(buffer), buffer, NULL);
			cout << "DEVICE NAME: " << buffer << endl;
			clGetDeviceInfo(device, CL_DEVICE_VENDOR, sizeof(buffer), buffer, NULL);
			cout << "DEVICE VENDOR: " << buffer << endl;
			clGetDeviceInfo(device, CL_DEVICE_VERSION, sizeof(buffer), buffer, NULL);
			cout << "DEVICE VERSION: " << buffer << endl;
			clGetDeviceInfo(device, CL_DRIVER_VERSION, sizeof(buffer), buffer, NULL);
			cout << "DRIVER VERSION: " << buffer << endl;
			clGetDeviceInfo(device, CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(buf_uint), &buf_uint, NULL);
			cout << "DEVICE MAX COMPUTE UNITS: " << (unsigned int)buf_uint << endl;
			clGetDeviceInfo(device, CL_DEVICE_MAX_CLOCK_FREQUENCY, sizeof(buf_uint), &buf_uint, NULL);
			cout << "DEVICE MAX CLOCK FREQUENCY: " << (unsigned int)buf_uint << endl;
			clGetDeviceInfo(device, CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS, sizeof(buf_uint), &buf_uint, NULL);
			cout << "DEVICE MAX WORK ITEM DIMENSIONS: " << (unsigned int)buf_uint << endl;
			clGetDeviceInfo(device, CL_DEVICE_MAX_WORK_ITEM_SIZES, sizeof(buf_uint), &buf_uint, NULL);
			cout << "DEVICE MAX WORK ITEM SIZES: " << (unsigned int)buf_uint << endl;
			clGetDeviceInfo(device, CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(buf_uint), &buf_uint, NULL);
			cout << "DEVICE MAX WORK GROUP SIZE: " << (unsigned int)buf_uint << endl;
			clGetDeviceInfo(device, CL_DEVICE_LOCAL_MEM_SIZE, sizeof(buf_ulong), &buf_ulong, NULL);
			cout << "DEVICE LOCAL MEM SIZE: " << (unsigned long long)buf_ulong / 1024 << " kB" << endl;
			clGetDeviceInfo(device, CL_DEVICE_GLOBAL_MEM_SIZE, sizeof(buf_ulong), &buf_ulong, NULL);
			cout << "DEVICE GLOBAL MEM SIZE: " << (unsigned long long)buf_ulong / (1024 * 1024) << " MB" << endl;
			clGetDeviceInfo(device, CL_KERNEL_PREFERRED_WORK_GROUP_SIZE_MULTIPLE, sizeof(buf_uint), &buf_uint, NULL);
			cout << "KERNEL PREFERRED WORK GROUP SIZE MULTIPLE: " << (unsigned int)buf_uint << endl;
		}
		
		if (num_platforms > 1 && i != num_platforms - 1)
		{
			cout << "\n------------------------------\n" << endl;
		}
	}

		
	std::system("PAUSE");
	return 0;
}
