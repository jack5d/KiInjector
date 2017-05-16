#include "mainwindow.h"
#include <QApplication>
#include "antis.h"



MYWORD test=0,test2=0;


void WINAPI tls_callback(void* , DWORD Reason, void* )
{
   // using namespace andrivet::ADVobfuscator;

    if(Reason==DLL_THREAD_ATTACH)
    {
        test |=cpuid_is_hypervisor();
        test2|= memory_space();
    }
   if (Reason == DLL_PROCESS_ATTACH)

   {
      test|= memory_space();
      test2|= disk_size_getdiskfreespace() | rdtsc_diff_vmexit();

    /*  printf("Regs: %d \n",ldt_trick());
      printf("CpuHy: %d \n" ,cpuid_is_hypervisor());   fflush(stdout);
      printf("Mem: %d \n",memory_space());   fflush(stdout);
      printf("Disk %d \n",disk_size_getdiskfreespace());    fflush(stdout);
      printf(" VmEx: %d\n",rdtsc_diff_vmexit());    fflush(stdout);*/

    }

    //printf("T: %d  %d\n" ,test,test2);   fflush(stdout);

}

extern "C"
{
PIMAGE_TLS_CALLBACK mtl_tls_callback_ __attribute__ ((section(".CRT$XLB"))) = tls_callback;
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();

}
