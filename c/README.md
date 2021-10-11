# C Ellie Native Bridge

In this file we have documented creating a native library in c.

<br>

Before we create rest of the code we should import `ellie_nb.h` to our code.

```c
#include "./ellie_nb.h"
```

Now we should create `on_load` function to get notified when library loaded.

```c
void on_load()
{
    printf("LIBRARY LOADED");
}
```


Secondly we're creating `on_function_call` function to communicate between ellie to c.

```c
EllieType on_function_call(NativeFunction targeted_function) {}
```

Now we can define our library, important thing is you should make library name exactly the same.

```c
NativeLib get_lib()
{
    NativeLib lib = {
        "test", //You can change this
        on_load,
        on_function_call,
    };

    return lib;
}
```

We successfully created a blank library. Now let's add some checks to our `on_function_call` code.


### Defining return_type

Native bridge function has two different return_types, `NATIVE_FUNCTION_RETURN_EXCEPTION` and `NATIVE_FUNCTION_RETURN_RESPONSE`. Lets define our return type.

```c
NativeFunctionReturn on_function_call(NativeFunction function_called)
{
    NativeFunctionReturn return_type;

    return return_type;
```

### Parameter checks
As you know from [main readme](../c/README.md#creating-native-library) before we create native code we should create ellie headers. In ellie headers every parameter and return type is already defined but if a header file ever got wrong or updated we should give a exception to user.


- Checking function name

```c
    if (function_called.name == "test") {
        ...
    } else {
        //Create a exception
        EllieException exception;

        //Set exception code
        exception.code = 1;

        //Set exception error_name
        exception.error_name = "NOT_FOUND";

        //Set exception error_message
        exception.reason = "Function does not exist in native function";

        //Apply exception data to return_type
        return_type.exception = exception;

        //Describe return type is exception
        return_type.tag = NATIVE_FUNCTION_RETURN_EXCEPTION;
    }
    ...
```

As you can see we successfully caught an error and threw an exception to runtime.
---

We're now retuning user a return type, and we should in struct that we're turning a type.

```c
if (function_called.name == "test") {
    return_type.tag = NATIVE_FUNCTION_RETURN_RESPONSE;

} else {
    ...
}
...
```

Now lets create a return type

```c
if (function_called.name == "test") {
    return_type.tag = NATIVE_FUNCTION_RETURN_RESPONSE;
    EllieType return_data;
    StringType ellie_string;

    return_data.tag = ELLIE_TYPE_STRING_TYPE;
    return_data.string_type = ellie_string;

} else {
    ...
}
...
```

We're creating a string, so we should define in return_data and set a value

```c
if (function_called.name == "test") {
    return_type.tag = NATIVE_FUNCTION_RETURN_RESPONSE;
    EllieType return_data;
    StringType ellie_string;

    ellie_string.value = "Hello from native";
    return_data.tag = ELLIE_TYPE_STRING_TYPE;
    return_data.string_type = ellie_string;
} else {
    ...
}
...
```

Final code should look like this. You can find this code [here](./no_param.c) and complicated parameter example is [here](./with_param.c)

To compile code you can use `gcc ./[extension-name].c --shared -o [output-name].so` for linux.

```c
#include "./ellie_nb.h"
#include <stdio.h>

void on_load()
{
    printf("LIBRARY LOADED");
}


NativeFunctionReturn on_function_call(NativeFunction function_called)
{
    NativeFunctionReturn return_type;
    if (function_called.name == "test")
    {
        //Create a return type
        EllieType return_data;

        //Create a string_type
        StringType ellie_string;
        ellie_string.value = "Hello from native";

        //Describe return type as a string_type
        return_data.tag = ELLIE_TYPE_STRING_TYPE;
        return_data.string_type = ellie_string;
        return_type.tag = NATIVE_FUNCTION_RETURN_RESPONSE;
    } else {
        //Create a exception
        EllieException exception;

        //Set exception code
        exception.code = 1;

        //Set exception error_name
        exception.error_name = "NOT_FOUND";

        //Set exception error_message
        exception.reason = "Function does not exist in native function";

        //Apply exception data to return_type
        return_type.exception = exception;

        //Describe return type is exception
        return_type.tag = NATIVE_FUNCTION_RETURN_EXCEPTION;
    }
    return return_type;
}

NativeLib get_lib()
{
    NativeLib lib = {
        "test",
        on_load,
        on_function_call,
    };

    return lib;
}

```