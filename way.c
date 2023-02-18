/***********************************************************
WAY
***********************************************************/


#include<sys/utsname.h>	/* Header for 'uname'  */
#include<sys/sysinfo.h>	/* Header for 'sysinfo' */
#include<stdio.h>
#include<sys/sysctl.h> /* Header for system info */
#include <sys/types.h> /* Header for system info */

int main()
{
	struct utsname uname_pointer;
	//struct sysinfo sysinfo_pointer;
 
	int result = 0;	// A variable to check results

	//System variables

	int maxProc = 0;
	unsigned long memorySize = 0;
	unsigned long cpuFreq = 0;
	unsigned long cpuFreqMin = 0;
	unsigned long cpuFreqMax = 0;
	int cpuType = 0;
	int cpuSubType = 0;
	int secureLevel = 0;
/*Bilgehan: New addition
	timeval bootTime = 0;

	clocking clockRate = 0;
*/

	result = uname(&uname_pointer); 

	if(result != 0)
	{
		perror("uname doesn't return 0, so there is an error");
		printf("uname doesn't return 0, so there is an error with no: %d \n", result);
		return(result);
	}

	printf("System name - %s \n", uname_pointer.sysname);
	printf("Nodename    - %s \n", uname_pointer.nodename);
	printf("Release     - %s \n", uname_pointer.release);
	printf("Version     - %s \n", uname_pointer.version);
	printf("Machine     - %s \n", uname_pointer.machine);
	//printf("Domain name - %s \n", uname_pointer.domainname);

	/**********************************
	*	MAC system info
	**********************************/
	//result = sysinfo(&sysinfo_pointer);

           size_t len = sizeof(int);
           sysctlbyname("kern.maxproc", &maxProc, &len, NULL, 0);
	result = sysctl (name, namelen, NULL , 0 , NULL, 0);

	if(result != 0)
	{
		perror("sysinfo doesn't return 0, so there is an error");
		printf("sysinfo doesn't return 0, so there is an error with no: %d \n", result);
		return(result);
	}

	return(0); 
}
