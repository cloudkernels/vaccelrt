#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <vaccel.h>
#include <vaccel_ops.h>

int read_file(const char *filename, char **img, size_t *img_size)
{
	int fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0) {
		perror("open: ");
		return 1;
	}

	struct stat info;
	fstat(fd, &info);
	fprintf(stdout, "Image size: %luB\n", info.st_size);

	char *buf = malloc(info.st_size);
	if (!buf) {
		fprintf(stderr, "Could not allocate memory for image\n");
		goto close_file;
	}

	long bytes = 0;
	do {
		int ret = read(fd, buf, info.st_size);
		if (ret < 0) {
			perror("Error while reading image: ");
			goto free_buff;
		}
		bytes += ret;
	} while (bytes < info.st_size);

	if (bytes < info.st_size) {
		fprintf(stderr, "Could not read image\n");
		goto free_buff;
	}

	*img = buf;
	*img_size = info.st_size;
	close(fd);

	return 0;

free_buff:
	free(buf);
close_file:
	close(fd);
	return 1;
}

int main(int argc, char *argv[])
{
	int ret;
	char *image;
       	size_t image_size;
	char out_text[512], out_imagename[512];

	if (argc != 2) {
		fprintf(stderr, "Usage: %s filename\n", argv[0]);
		return 0;
	}

	struct vaccel_session sess;
	sess.session_id = 0;

	/*
	ret = vaccel_sess_init(&sess, 0);
	if (ret != VACCEL_OK) {
		fprintf(stderr, "Could not initialize session\n");
		return 1;
	}
	*/

	ret = read_file(argv[1], &image, &image_size);
	if (ret)
		goto close_session;

	ret = vaccel_image_classification(&sess, image, out_text, out_imagename,
			image_size, sizeof(out_text), sizeof(out_imagename));

free(image);

close_session:
/*
ret = vaccel_sess_free(&sess);
if (ret != VACCEL_OK) {
	fprintf(stderr, "Could not clear session\n");
	return 1;
}
*/
return ret;
}
