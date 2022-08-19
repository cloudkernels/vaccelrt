#include <stdio.h>
#include <plugin.h>
#include <string.h>
#include <error.h>
#include <ops/vaccel_ops.h>
#include <byteswap.h>
#include <dlfcn.h>

#include <vaccel.h>


static int fpga(struct vaccel_session *session) {
	
	//vaccel_debug(stdout, "Calling vaccel-fpga for session %u\n", session->session_id);
	fprintf(stdout, "Calling vaccel-fpga for session %u\n", session->session_id);
	//vaccel_debug("Execution of FPGA plugin for session");

	return VACCEL_OK;
}

static int fpga_test(struct vaccel_session *session){
	fprintf(stdout, "Test operation A");

	return VACCEL_OK;
}


// int fpga_uio_irq_on(struct vaccel_session *sess, int uio_fd){

// 	unsigned int irq_on = 1;
// 	fprintf(stdout, "[fpga] Calling uio_irq_on for session %u\n",sess->session_id);
// 	write(uio_fd, &irq_on,sizeof(irq_on));
// }

// int fpga_uio_wait_irq(struct vaccel_session *sess, int uio_fd){
// 	unsigned int  count = 0;
// 	fprintf(stdout, "[fpga] Calling uio_wait_irq for session %u\n", sess-> session_id);
//     return read(uio_fd, &count,  sizeof(count));
// }

// int fpga_uio_poll_irq(struct vaccel_session *sess, int uio_fd){

//     struct pollfd   fds[1];
//     struct timespec timeout;
//     sigset_t        sigmask;
//     int             poll_result;
//     unsigned int    irq_count;
//     fds[0].fd       = uio_fd;
//     fds[0].events   = POLLIN;
//     timeout.tv_sec  = 100;
//     timeout.tv_nsec = 0;

// 	fprintf(stdout, "[fpga] Calling uio_poll_irq for session %u\n", sess-> session_id);

//     poll_result = ppoll(fds, 1, &timeout, &sigmask);
//     if ((poll_result > 0) && (fds[0].revents & POLLIN)) {
//         read(uio_fd, &irq_count,  sizeof(irq_count));
//     }
//     return poll_result;
// }

//----------------//


// static int exec(struct vaccel_session *session, const char *library, const char
// 		*fn_symbol, void *read, size_t nr_read, void *write,
// 		size_t nr_write){
// 	int i = 0;
// 	void *dl;
// 	int (*fptr)(void *, size_t, void *, size_t);
// 	int ret;
// 	struct vaccel_arg *args;

// 	vaccel_debug("Calling exec for session %u", session->session_id);

// 	vaccel_debug("[exec] library: %s", library);
// 	dl = dlopen(library, RTLD_NOW);
// 	if (!dl) {
// 		vaccel_error("%s", dlerror());
// 		return VACCEL_EINVAL;
// 	}

// 	/* Get the function pointer based on the relevant symbol */
// 	vaccel_debug("[exec] symbol: %s", fn_symbol);
// 	fptr = (int (*)(void*, size_t, void*,size_t))dlsym(dl, fn_symbol);
// 	if (!fptr) {
// 		vaccel_error("%s", dlerror());
// 		return VACCEL_EINVAL;
// 	}
// 	printf("SIIIIIIIIIIIIIIIIIII");

// 	ret = (*fptr)(read, nr_read, write, nr_write);
// 	if (ret)
// 		return VACCEL_ENOEXEC;

// 	return VACCEL_OK;
// }

// --------------//


///  I think here I would need to implement it here via the API:

static int fpga_load(struct vaccel_session *session, int test){
	int do_some_operation;
	return VACCEL_OK;
}

struct vaccel_op ops[] = {
	VACCEL_OP_INIT(ops[0], VACCEL_NO_OP, fpga),
	VACCEL_OP_INIT(ops[1], VACCEL_EXEC, fpga_test),
	///VACCEL_OP_INIT(ops[2],VACCEL_FPGA_LOAD, fpga_load), ... etc
};

static int init(void)
{
	return register_plugin_functions(ops, sizeof(ops)/ sizeof(ops[0]));
}

static int fini(void)
{
	return VACCEL_OK;
}

VACCEL_MODULE(
	.name = "fpga",
	.version = "0.1",
	.init = init,
	.fini = fini
)
