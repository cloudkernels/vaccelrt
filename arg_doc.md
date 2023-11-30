# How to pass arguments when running a vAccel operation
Usually, when running an operation in vAccel, we do so by calling a function like that:
```c
ret = vaccel_op( ..., <read args>, <num_read>, <write args>, <num_write>);
```

If we are willing not to pass each of the arguments by hand, we could use the structure below:

```c
struct vaccel_arg_list{
    uint32_t size;
    struct vaccel_arg* list;
};
```
which can be initialised with the function:

```c
vaccel_args_init()
```
For example, in case that we want to pass both input and output arguments, we should initialise two instances of that structure like that:

```c
struct vaccel_arg_list* read   = vaccel_args_init();
struct vaccel_arg_list* write  = vaccel_args_init();
```

## Main Program
### Add an input argument 
Let's say we want to call an operation with two input arguments. One integer and one other kind of structure which is not already serialised(i.e. contains pointers to other data)

#### Already serialised
In the first case, we simply define the buffer in which our input is placed. For example:
```c
int input = ...;
vaccel_add_ser_arg(read, &input, sizeof(input));
```
#### Non-serialied
However, in case that our argument is not serialised (i.e. cannot be directly transfered remotely), except the buffer, we should also pass a pointer to function that serialises the structure. For example:
```c
struct mystruct = init_mystruct();

void* ser_mystruct(void* buf, uint32_t* bytes){
  ...
}
// buf   -> pointer to non-serialised structure
// bytes -> address to write the size of the serialised data
// returns: pointer to the buffer where the serialised data were written

vaccel_add_deser_arg(read, &mystruct, 0, ser_mystruct);
```

### Add output arguments
Now, since we may expect by the operation to return back some data, we should define the location in which they will be written:

#### Already serialised
In case we expect to get back a float, we simply add the following command:
```c
float out;
vaccel_expect_ser_arg(write, &out, sizeof(out));
```
#### Non-serialised
Similarly, we call the corresponding function for non-serialised arguments, however we do not define any buffer or size since we don't know the size in advance. Later (after calling the operation), we can ask for the output using their indeces.
```c
vaccel_expect_deser_arg(write);
```

### Read the output arguments
Now that the operation returned, we ask for our data using "**extract**" functions.
#### Already serialised
For serialised data (i.e. the float we expect) we have direct access by the buffer we provided:
```c
float ret_val = out;
```
However, we can also ask for the location by calling:
```c
float *outptr = vaccel_extract_ser_arg(write->list, 0);
// where 0 is the index of our output
```

#### Non-serialised
On the other hand, for non-serialised output, we cannot just ask for the value, since the returned data has been serialised. Thus, we now provide a deserialiser function to get the right structure:
```c
void* deser_mystruct(void* buf, uint32_t bytes){
  ...
}
// buf   -> pointer to serialised data
// bytes -> size of the serialised data
// returns: pointer to the buffer where the structure was written

struct mystruct *outbuf;
outbuf = vaccel_extract_deser_arg(write->list, 1, deser_mystruct);
// where 1 is the index on the arguments list
```
### Clean the memory

Finally, we can clean the memory that was allocated by the argument lists by running:
```c
delete_arg_list(read);
delete_arg_list(write);
```
## Plugin

Inside the plugin, we want to read the input, process it and return the result back to the main program.

### Read the arguments 
The "**extract**" functions that were previously used, will be used again to receive the input. The rationale remains the same.

#### Already serialised
```c
static int plugin_func(struct vaccel_arg *read,
        size_t nr_read, struct vaccel_arg *write, size_t nr_write){

  // we expect an integer at index 0
  int *input = vaccel_extract_ser_arg(write->list, 0);

  ...
}
```

#### Non-serialied
```c
static int plugin_func(struct vaccel_arg *read,
        size_t nr_read, struct vaccel_arg *write, size_t nr_write){

  ...

  // we also expect a "mystruct" input at index 1
  struct mystruct *inbuf;
  inbuf = vaccel_extract_ser_arg(write->list, 1, deser_mystruct);

  ...
}
```
### Write to output arguments
Finally, we want to write the response of the plugin to the buffers that were previously defined. For that reason we use the "**write**" functions
#### Already serialised
Since the user defined that expects to receive a float at index 0, we can provide the value with the following function:
```c
...
float response = ...;
vaccel_write_ser_arg(write->list, 0, &response);
...
```
#### Non-serialied

Similarly, it was also defined that a non-serialised structure will be received at index 1. So:
```c
...
struct mystruct out = ...;
vaccel_write_deser_arg(write->list, 1, &out, ser_mystruct);
...
```
