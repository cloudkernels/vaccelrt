#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <vaccel.h>
#include <vaccel_ops.h>

int main()
{
	int ret;
	struct vaccel_session sess;

	ret = vaccel_sess_init(&sess, 0);
	if (ret != VACCEL_OK) {
		fprintf(stderr, "Could not initialize session\n");
		return 1;
	}

	printf("Initialized session with id: %u\n", sess.session_id);

	char A[] = "this is a sentence";
	char B[] = "this is a another sentence";
	size_t len = strlen(A) + strlen(B);
	char *ptr = malloc (len);
	memcpy(ptr, A, strlen(A));
	memcpy(ptr+strlen(A),B,strlen(B));
	char *out_ptr = malloc (len);
	ret = vaccel_genop(&sess,out_ptr, ptr, len, len);
	if (ret) {
		fprintf(stderr, "Could not run op: %d\n", ret);
		goto close_session;
	}
	printf("input%s\n", ptr);
	printf("output %s\n", out_ptr);

close_session:
	if (vaccel_sess_free(&sess) != VACCEL_OK) {
		fprintf(stderr, "Could not clear session\n");
		return 1;
	}

	return ret;
}