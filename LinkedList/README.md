# LinkedList Project *(in proggress)*

## Description

In this project you can find a simple `LinkedList` implementation. This class contains basic methods:
 * `add()`
 * `remove()`
 * `contains()`

and has a `prettyPrint()` method thas prints the list elements.
For example:

    3 -> -7 -> -23 -> 132

## One thing to notice

The implementation was separated from a .h file to a .cpp file.

So, in order to have the code compiling you need to add a line at the end of the .cpp file, like this:

```cpp
// you can add more lines with other types
// in order to be able to use the list with them
template class LinkedList<int>;
```

Obviously, that's not the best solution to this problem and you propably should have the implementation in .h file

More about this you can find [here](https://stackoverflow.com/questions/456713/why-do-i-get-unresolved-external-symbol-errors-when-using-templates) or [here](https://stackoverflow.com/questions/1724036/splitting-templated-c-classes-into-hpp-cpp-files-is-it-possible)
