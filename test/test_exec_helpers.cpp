#include <catch2/catch_test_macros.hpp>

#include <atomic>

using atomic_int = std::atomic<int>;
using atomic_uint = std::atomic<unsigned int>;


extern "C"
{
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <vaccel.h>
#include "session.h"
#include "plugin.h"
#include "shared_object.h"
}

TEST_CASE("exec")
{
    int ret;
	struct vaccel_session sess;
	int input;
	char out_text[512];
    sess.hint = VACCEL_PLUGIN_DEBUG;
    char iterations[] = "2";
    
    ret = vaccel_sess_init(&sess, sess.hint);
    REQUIRE(ret == VACCEL_OK);

    input = 10;	

	struct vaccel_arg read[1] = {
		{.size = sizeof(input),.buf = &input}};
	struct vaccel_arg write[1] = {
		{.size = sizeof(out_text),.buf = out_text}};

	for (int i = 0; i < atoi(iterations); ++i) {
		ret = vaccel_exec(&sess, "../plugins/noop/libvaccel-noop.so",
				"mytestfunc", read, 1, write, 1);
		if (ret) {
			fprintf(stderr, "Could not run op: %d\n", ret);
			goto close_session;
		}
	}


close_session:
	if (vaccel_sess_free(&sess) != VACCEL_OK) {
		fprintf(stderr, "Could not clear session\n");
		printf("%d\n", 1);
	}

	printf("%d\n", ret);
}


