Contributing
============
Firstly, please read the license - it's a Modified BSD license. Secondly, when conributing, your anme will be added to the AUTHORS file to give you credit for your work. The license doesn't change and you don't get special rights, you just get credit - so think about that before pouring your heart and soul into anything.

To conribute, for the project on GitHub, make changes, then submit a pull request. **For simple adjustments, you don't even need to install git, you can make changes from the web interface.**

## Expectations / Formatting
For images, **no tilesets**. Every animation frame must be an individual image file. All images must be in **PNG** format, and must already have propery transparency/alpha channel. Please don't take images of other formats and convert them, it often leaves ugly artifacts.

For source code:
* You must use tabs for initial indentation, and you must use spaces for further indentation (e.g. to align code over multiple lines). This way, the size of tabs doesn't matter - it can be 4 spaces per tab, 1 space per tab, or 92 spaces per tab, based on your editor's settings.
* All code should be written in C++11
* Never use the `.h` C standard library headers, use the versions that start with `c` and have no extension.
* The `class` keyword is evil and should never be used, ever. Always use `struct`, _especially_ for declaring classes. `struct MyClass { /**/ };`
* Always use `*.cpp` and `*.hpp` file extensions (this means that source files can be detected as `*.*pp`).
* `lowwercasecalloneword` for parameter and local variable names.
* `UpperCamelCase` for class names.
* `UpperCamelCase_t` for type aliases.
* `lowerCamelCase` for member function names.
* `lower_case_underscore` for private member variables.
* `lwrabbrcase` for namespace names.
* Braces must always be on their own lines.
* All control structures must have braces.
* Braces should always cause one tab of indentation.
* Always use smart pointers instead of raw pointers.
* Never use `typedef x y;`, always use `using y = x;`.
* Never use exceptions unless forced to.
* Public interfaces should not require explanation or documentation - if they do, they're designed _wrong_.
* Always use the C++ standard library when possible, avoid writing your own code to do something.
* Use nameless scopes in functions to exactly define the intended lifetime of objects.
* Helper functions should be in an anonymous namespace and should be declared static.
* Don't mix client and server responsibilities.
* Prefer defining as many things inline as possible.
* Try to make as many functions `noexcept(true)` as possible.
* Avoid strange excess spaces in random places unless they are specifically for alignment.
* There is no line character limit, but if a line of code is long you may need to reconsider why it does so much in one line.
* Constructor initializer lists should follow this style:
```cpp
	SomeClass()
	: member(blah)
	, member(blah)
	, member(blah)
	{
		//...
	}
```
* `const` should _always_ appear to the right of the type name:
```cpp
	SomeType const &st;
```
* `*` and *&` should snuggle with the identifier but be afraid of `const`, as in the above example.
