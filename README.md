# Ellie Native Library Example
This repo shows native library support on ellie language

# Creating native library
Ellie is a type safe language and it needs headers like c or cpp. So you should create a `.eih` in your directory first.

```ellie
@input=NativeTest.c;
pub fn test() > String;
```

We defined a function named test and we gave a return type. You can find complicated example in specific language documentation. Now let's create a native file.

## Languages

- [c](./c/README.md)