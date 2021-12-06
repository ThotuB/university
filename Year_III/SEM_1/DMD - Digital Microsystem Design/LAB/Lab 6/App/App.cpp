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

	for (int i = 0; i < count; i++) {
		switch (proc_info[i].Relationship) {
            case RelationNumaNode:
                cout << "NumaNode - Mask: " << proc_info[i].ProcessorMask << " Node Number: "<< proc_info[i].NumaNode.NodeNumber << endl;
                break;

            case RelationProcessorCore:
                cout << "Processor Core - Mask: " << proc_info[i].ProcessorMask << " Cores: " << CountSetBits(proc_info[i].ProcessorMask) << endl;
                break;

            case RelationCache:
                CACHE_DESCRIPTOR Cache = proc_info[i].Cache;
                cout << "Cache - Level: ";
                switch (Cache.Level) {
                    case 1: cout << "L1 "; break;
                    case 2: cout << "L2 "; break;
                    case 3: cout << "L3 "; break;
                    case 4: cout << "L4 "; break;
                }
                cout << "Type: ";
                switch (Cache.Type) {
                    case CacheUnified: cout << "Unified "; break;
                    case CacheInstruction: cout << "Instruction "; break;
                    case CacheData: cout << "Data "; break;
                    case CacheTrace: cout << "Trace "; break;
                }
                cout << "Cache Size: " << Cache.Size << " Bytes Linesize: " << Cache.LineSize << " Bytes Associativity: " << Cache.Associativity << endl;
                break;

            case RelationProcessorPackage:
                cout << "Processor Package - Mask: " << proc_info[i].ProcessorMask << " Number of Processors: " << CountSetBits(proc_info[i].ProcessorMask) << endl;
                break;

            default:
                cout << "Error: Unsupported LOGICAL_PROCESSOR_RELATIONSHIP value.\n";
                break;
        }
	}
}

int main() {
    PSYSTEM_LOGICAL_PROCESSOR_INFORMATION buffer = NULL;
    DWORD returnLength = 0;
	
	GetLogicalProcessorInformation(nullptr, &returnLength);

	int count = returnLength / sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION);
	buffer = new SYSTEM_LOGICAL_PROCESSOR_INFORMATION[count];

	GetLogicalProcessorInformation(buffer, &returnLength);
	
	PrintProcessorInformation(buffer, count);

    free(buffer);

    return 0;
}