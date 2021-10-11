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
    }
    else
    {
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