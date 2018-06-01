# SPLogger
It allows to log in file or console with ease
A small .h/.cpp c++11 file to simplify your logs to a file or console
To log something simply call your logger().

```cpp
SPLogger myLogger;
myLogger() << "Hello" << "World";
myLogger(L_WARNING) << "This is a warning";
```
> 2018-Jun-01:14'35'38:182|NOTICE| Hello World

> 2018-Jun-01:14'35'38:183|WARNING|This is a warning

## Motivation

While i'm currently working on a logging Framework, I thought of sharing this simplified version.
It was inspired by qtDebug for the way it is used.

## API

### Creating a logger

You can create a logger 2 ways. 
 * Default : it will write in your console
 * ostream : it will wherever your rdbuf point
 * path string : it will write in the file at the given path

### How to log

To Log, simply call your logger operator()
> myLogger() << [anything i want] << [and even more...];

By default, the LogLevel is Notice.
To specify a LogLevel, specify it in the operator()
> myLogger(LogLevel::Warning) << "This is a warning";

This header come with a small set of macro for LogLevels to call them
 
### Create your own display
SPLogger can log any object that can read an ostream. But sometimes you want a debug specific output.
To do so you'll need to specialized an SPLogStream operator <<.

```cpp
SPLogStream& operator<<(SPLogStream& ls, MyObject const& obj)
{
    ls.Write([WHAT I WANT IT TO DISPLAY]);
    return ls;
}
```


### LogLevels

 LogLevel | Macro | Use
 --- | --- | ---
Trace   | L_TRACE   | 
Debug   | L_DEBUG   | 
Info    | L_INFO    | 
Notice  | L_NOTICE  | 
Warning | L_WARNING | 
Error   | L_ERROR   | 
Fatal   | L_FATAL   | 

