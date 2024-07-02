/*
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "../src/utils.h"
#include <vaccel.h>

int main(int argc, char *argv[])
{
	int ret;
	char *image;
       	size_t image_size;
	char out_imagename[512];
	struct vaccel_session sess;

	if (argc != 3) {
		fprintf(stderr, "Usage: %s filename #iterations\n", argv[0]);
		return 0;
	}

	ret = vaccel_sess_init(&sess, 0);
	if (ret != VACCEL_OK) {
		fprintf(stderr, "Could not initialize session\n");
		return 1;
	}

	printf("Initialized session with id: %u\n", sess.session_id);

	ret = read_file(argv[1], (void **)&image, &image_size);
	if (ret)
		goto close_session;

	enum vaccel_op_type op_type = VACCEL_IMG_SEGME;
	struct vaccel_arg read[2] = {
		{ .size = sizeof(enum vaccel_op_type), .buf = &op_type},
		{ .size = image_size, .buf = image }
	};
	struct vaccel_arg write[1] = {
		{ .size = sizeof(out_imagename), .buf = out_imagename },
	};

	for (int i = 0; i < atoi(argv[2]); ++i) {
		ret = vaccel_genop(&sess, read, 2, write, 1);
		if (ret) {
			fprintf(stderr, "Could not run op: %d\n", ret);
			goto close_session;
		}
	}


close_session:
	free(image);
	if (vaccel_sess_free(&sess) != VACCEL_OK) {
		fprintf(stderr, "Could not clear session\n");
		return 1;
	}

	return ret;
}
