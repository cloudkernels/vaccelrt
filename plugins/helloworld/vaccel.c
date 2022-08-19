#include <stdio.h>
#include <plugin.h>

static int helloworld(struct vaccel_session *session)
{
	fprintf(stdout, "Calling vaccel-helloworld for session %u\n", session->session_id);

	printf("_______________________________________________________________\n\n");
	printf("This is the helloworld plugin, implementing the NOOP operation!\n");
	printf("===============================================================\n\n");

	return VACCEL_OK;
}

struct vaccel_op op = VACCEL_OP_INIT(op, VACCEL_NO_OP, helloworld);

static int init(void)
{
	return register_plugin_function(&op);
}

static int fini(void)
{
	return VACCEL_OK;
}

VACCEL_MODULE(
	.name = "helloworld",
	.version = "0.1",
	.init = init,
	.fini = fini
)