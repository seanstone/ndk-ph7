#include "print.hpp"

extern "C"
{

#define PHP_PROG "<?php "\
                 "echo 'Welcome guest'.PHP_EOL;"\
                 "echo 'Current system time is: '.date('Y-m-d H:i:s').PHP_EOL;"\
                 "echo 'and you are running '.php_uname();"\
                 "?>"

#include <stdio.h>
#include <stdlib.h>

#include "ph7.h"

/*
 * Display an error message and exit.
 */
static void Fatal(const char *zMsg)
{
	puts(zMsg);
	/* Shutdown the library */
	ph7_lib_shutdown();
	/* Exit immediately */
	exit(0);
}

/*
 * VM output consumer callback.
 * Each time the virtual machine generates some outputs, the following
 * function gets called by the underlying virtual machine to consume
 * the generated output.
 * This function is registered later via a call to ph7_vm_config()
 * with a configuration verb set to: PH7_VM_CONFIG_OUTPUT.
 */
static int Output_Consumer(const void *pOutput, unsigned int nOutputLen, void *pUserData /* Unused */)
{
    char output[nOutputLen+1];
    sprintf(output, (const char*) pOutput, nOutputLen);
    output[nOutputLen] = '\0';
    print(output);

	return PH7_OK;
}

int intro(void)
{
	ph7 *pEngine; /* PH7 engine */
	ph7_vm *pVm;  /* Compiled PHP program */
	int rc;
	/* Allocate a new PH7 engine instance */
	rc = ph7_init(&pEngine);
	if( rc != PH7_OK ){
		/*
		 * If the supplied memory subsystem is so sick that we are unable
		 * to allocate a tiny chunk of memory, there is no much we can do here.
		 */
		Fatal("Error while allocating a new PH7 engine instance");
	}
	/* Compile the PHP test program defined above */
	rc = ph7_compile_v2(
		pEngine,  /* PH7 engine */
		PHP_PROG, /* PHP test program */
		-1        /* Compute input length automatically*/,
		&pVm,     /* OUT: Compiled PHP program */
		0         /* IN: Compile flags */
		);
	if( rc != PH7_OK ){
		if( rc == PH7_COMPILE_ERR ){
			const char *zErrLog;
			int nLen;
			/* Extract error log */
			ph7_config(pEngine,
				PH7_CONFIG_ERR_LOG,
				&zErrLog,
				&nLen
				);
			if( nLen > 0 ){
				/* zErrLog is null terminated */
				puts(zErrLog);
			}
		}
		/* Exit */
		Fatal("Compile error");
	}
	/*
	 * Now we have our script compiled, it's time to configure our VM.
	 * We will install the VM output consumer callback defined above
	 * so that we can consume the VM output and redirect it to STDOUT.
	 */
	rc = ph7_vm_config(pVm,
		PH7_VM_CONFIG_OUTPUT,
		Output_Consumer,    /* Output Consumer callback */
		0                   /* Callback private data */
		);
	if( rc != PH7_OK ){
		Fatal("Error while installing the VM output consumer callback");
	}
	/*
	 * And finally, execute our program. Note that your output (STDOUT in our case)
	 * should display the result.
	 */
	ph7_vm_exec(pVm, 0);
	/* All done, cleanup the mess left behind.
	*/
	ph7_vm_release(pVm);
	ph7_release(pEngine);
	return 0;
}

}
