#include <Windows.h>
#include <iostream>

void PrintSystemInfo(SYSTEM_INFO systemInfo) {
    auto GetProcessorArchitecture = [](WORD processorArchitecture) -> std::string {
        switch ( processorArchitecture ) {
            case PROCESSOR_ARCHITECTURE_INTEL:
                return "Intel x86";
            case PROCESSOR_ARCHITECTURE_IA64:
                return "Intel Itanium";
            case PROCESSOR_ARCHITECTURE_AMD64:
                return "AMD x86-64";
            case PROCESSOR_ARCHITECTURE_ARM:
                return "ARM";
            default:
                return "Unknown";
        }
    };

    std::cout << "SYSTEM INFO\n";
    std::cout << "Processor architecture: " << GetProcessorArchitecture(systemInfo.wProcessorArchitecture) << "\n";
    std::cout << "Page size: " << systemInfo.dwPageSize << "\n";
    std::cout << "Application address: " << systemInfo.lpMinimumApplicationAddress << " - " << systemInfo.lpMaximumApplicationAddress << "\n";
    std::cout << "Active processor mask: " << systemInfo.dwActiveProcessorMask << "\n";
    std::cout << "Number of processors: " << systemInfo.dwNumberOfProcessors << "\n";
    std::cout << "Allocation granularity: " << systemInfo.dwAllocationGranularity << "\n";
    std::cout << "Processor level: " << systemInfo.wProcessorLevel << "\n";
    std::cout << "Processor revision: " << systemInfo.wProcessorRevision << "\n\n";
}

void PrintMemoryStatus(MEMORYSTATUSEX memoryStatus) {
    std::cout << "MEMORY STATUS\n";
    std::cout << "Length: " << memoryStatus.dwLength << " bytes\n";
    std::cout << "Memory load: " << memoryStatus.dwMemoryLoad << "%\n";
    std::cout << "Physical memory: " << memoryStatus.ullAvailPhys << " / " << memoryStatus.ullTotalPhys << " bytes\n";
    std::cout << "Page file: " << memoryStatus.ullAvailPageFile << " / " << memoryStatus.ullTotalPageFile << " bytes\n";
    std::cout << "Virtual memory: " << memoryStatus.ullAvailVirtual << " / " << memoryStatus.ullTotalVirtual << " bytes\n\n";
}

int main() {
    SYSTEM_INFO *lpSystemInfo = new SYSTEM_INFO();
    MEMORYSTATUSEX *lpMemoryStatus = new MEMORYSTATUSEX();

    GetSystemInfo(lpSystemInfo);
    GetLogicalProcessorInformationEx();
    GlobalMemoryStatusEx(lpMemoryStatus);

    PrintSystemInfo(*lpSystemInfo);
    PrintMemoryStatus(*lpMemoryStatus);

    return 0;
}