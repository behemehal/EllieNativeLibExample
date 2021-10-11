#ifndef _ELLIE_NATIVE_BRIDGE_H
#define _ELLIE_NATIVE_BRIDGE_H

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

typedef enum EllieTypeDefinings {
  ELLIE_TYPE_DEFININGS_INT,
  ELLIE_TYPE_DEFININGS_STRING,
  ELLIE_TYPE_DEFININGS_FLOAT,
} EllieTypeDefinings;

typedef struct EllieException {
  uint32_t code;
  char *error_name;
  char *reason;
} EllieException;

typedef struct StringType {
  char *value;
} StringType;

typedef enum IntegerSize_Tag {
  INTEGER_SIZE_U8,
  INTEGER_SIZE_U16,
  INTEGER_SIZE_U32,
  INTEGER_SIZE_U64,
  INTEGER_SIZE_USIZE,
  INTEGER_SIZE_I8,
  INTEGER_SIZE_I16,
  INTEGER_SIZE_I32,
  INTEGER_SIZE_I64,
  INTEGER_SIZE_ISIZE,
} IntegerSize_Tag;

typedef struct IntegerSize {
  IntegerSize_Tag tag;
  union {
    struct {
      uint8_t u8;
    };
    struct {
      uint16_t u16;
    };
    struct {
      uint32_t u32;
    };
    struct {
      uint64_t u64;
    };
    struct {
      uintptr_t usize;
    };
    struct {
      int8_t i8;
    };
    struct {
      int16_t i16;
    };
    struct {
      int32_t i32;
    };
    struct {
      int64_t i64;
    };
    struct {
      intptr_t isize;
    };
  };
} IntegerSize;

typedef struct IntegerType {
  struct IntegerSize value;
} IntegerType;

typedef enum FloatSize_Tag {
  FLOAT_SIZE_F32,
  FLOAT_SIZE_F64,
} FloatSize_Tag;

typedef struct FloatSize {
  FloatSize_Tag tag;
  union {
    struct {
      float f32;
    };
    struct {
      double f64;
    };
  };
} FloatSize;

typedef struct FloatType {
  struct FloatSize value;
} FloatType;

typedef enum EllieType_Tag {
  ELLIE_TYPE_STRING_TYPE,
  ELLIE_TYPE_INT_TYPE,
  ELLIE_TYPE_FLOAT_TYPE,
} EllieType_Tag;

typedef struct EllieType {
  EllieType_Tag tag;
  union {
    struct {
      struct StringType string_type;
    };
    struct {
      struct IntegerType int_type;
    };
    struct {
      struct FloatType float_type;
    };
  };
} EllieType;

typedef enum NativeFunctionReturn_Tag {
  NATIVE_FUNCTION_RETURN_EXCEPTION,
  NATIVE_FUNCTION_RETURN_RESPONSE,
} NativeFunctionReturn_Tag;

typedef struct NativeFunctionReturn {
  NativeFunctionReturn_Tag tag;
  union {
    struct {
      struct EllieException exception;
    };
    struct {
      struct EllieType response;
    };
  };
} NativeFunctionReturn;

typedef struct NativeFunctionParameter {
  char *name;
  struct EllieType ptype;
} NativeFunctionParameter;

typedef struct NativeFunction {
  char *name;
  enum EllieTypeDefinings return_type;
  struct NativeFunctionParameter *parameters;
} NativeFunction;

typedef struct NativeLib {
  char *name;
  void (*on_load)(void);
  struct NativeFunctionReturn (*on_function_call)(struct NativeFunction function);
} NativeLib;

#endif /* _ELLIE_NATIVE_BRIDGE_H */

