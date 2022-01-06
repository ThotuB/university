#include <iostream>
#include <windows.h>

using namespace std;

DWORD CountSetBits(ULONG_PTR bitMask) {
    DWORD LSHIFT = sizeof(ULONG_PTR) * 8 - 1;
    DWORD bitSetCount = 0;
    ULONG_PTR bitTest = (ULONG_PTR)1 << LSHIFT;
    DWORD i;

    for (i = 0; i <= LSHIFT; ++i) {
        bitSetCount += ((bitMask & bitTest) ? 1 : 0);
        bitTest /= 2;
    }

    return bitSetCount;
}

void PrintProcessorInformation(PSYSTEM_LOGICAL_PROCESSOR_INFORMATION proc_info, int count) {
    int numaNodeCount = 0;
    int processorCoreCount = 0;
    int processorPackageCount = 0;
    int processorThreadCount = 0;
    int L1CacheCount = 0;
    int L2CacheCount = 0;
    int L3CacheCount = 0;

	for (int i = 0; i < count; i++) {
		switch (proc_info[i].Relationship) {
            case RelationNumaNode:
                cout << "NumaNode - Mask: " << proc_info[i].ProcessorMask << " Node Number: "<< proc_info[i].NumaNode.NodeNumber << endl;
                numaNodeCount++;
                break;

            case RelationProcessorCore:
                cout << "Processor Core - Mask: " << proc_info[i].ProcessorMask << " -> Threads: " << CountSetBits(proc_info[i].ProcessorMask) << endl;
                processorCoreCount++;
                processorThreadCount += CountSetBits(proc_info[i].ProcessorMask);
                break;

            case RelationCache:
                CACHE_DESCRIPTOR Cache = proc_info[i].Cache;
                cout << "Cache ";
                switch ( Cache.Level ) {
                    case 1: cout << "L1:"; L1CacheCount++; break;
                    case 2: cout << "L2:"; L2CacheCount++; break;
                    case 3: cout << "L3:"; L3CacheCount++; break;
                    case 4: cout << "L4:"; break;
                }
                cout << "\n\tType: ";
                switch ( Cache.Type ) {
                    case CacheUnified: cout << "Unified "; break;
                    case CacheInstruction: cout << "Instruction "; break;
                    case CacheData: cout << "Data "; break;
                    case CacheTrace: cout << "Trace "; break;
                }
                cout << "\n\tCache Size: " << Cache.Size << " Bytes\n\tLinesize: " << Cache.LineSize << "\n\tAssociativity: " << (int)Cache.Associativity << endl;
                break;

            case RelationProcessorPackage:
                cout << "Processor Package - Mask: " << proc_info[i].ProcessorMask << " Number of Processors: " << CountSetBits(proc_info[i].ProcessorMask) << endl;
                processorPackageCount++;
                break;

            default:
                cout << "Error: Unsupported LOGICAL_PROCESSOR_RELATIONSHIP value.\n";
                break;
        }
	}

    cout << "Numa Nodes: " << numaNodeCount << endl;
    cout << "Processor Packages" << processorPackageCount << endl;
    cout << "Processor Cores: " << processorCoreCount << endl;
    cout << "Processor Threads: " << processorThreadCount << endl;
    cout << "L1 Cache: " << L1CacheCount << endl;
    cout << "L2 Cache: " << L2CacheCount << endl;
    cout << "L3 Cache: " << L3CacheCount << endl;
}

int main() {
    PSYSTEM_LOGICAL_PROCESSOR_INFORMATION buffer = NULL;
    DWORD returnLength = 0;
	
	GetLogicalProcessorInformation(nullptr, &returnLength);

	int count = returnLength / sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION);
	buffer = new SYSTEM_LOGICAL_PROCESSOR_INFORMATION[count];

	GetLogicalProcessorInformation(buffer, &returnLength);
	
	PrintProcessorInformation(buffer, count);

    delete [] buffer;

    return 0;
}