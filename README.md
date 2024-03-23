# UTest

UTest is a unit testing library based on C++11. The main purpose of this project is to provide a convenient and flexible way of writing tests and collecting information. So here are key features of this library:

- [Simple test writing with `TEST` keyword](#tests-writing)
- [Verification statements `ASSERT` and `EXPECT`](#asserts-and-expects)
- [Collecting data from tests](#getting-data)
- [Saving data to json (and back)](#json-conversion)



## Usage

Here is a little tutorial of possible ways UTest usage:

### Tests writing

Use `TEST` keyword to declare your own test. The first argument is name of this test, the second is the name of test group. For example:

```cpp
TEST(MyTestName, Common) {
    // some code in test
}
```

Test will register automatically, so that's all you need to do to create test.



### Asserts and expects

You can use `ASSERT_TRUE` and `EXPECT_TRUE` keywords to verify some statement:

```cpp
TEST(MyTestName, Common) {
    ASSERT_TRUE(2 * 2 == 4)
    EXPECT_TRUE(5 != 7)
}
```

Please note that `ASSERT` statement will stop test execution in case of fail, in opposite `EXPECT` will only indicate that statement inside was wrong.



### Test execution

When tests are done, you should execute them to get results: use

- `TestRegistry::ExecuteTestAll()` to execute all tests
- `TestRegistry::ExecuteTestGroup(std::string group_name)` to execute all tests by their group
- `TestRegistry::ExecuteTest(std::string test_name)` to execute exact test

All of these methods return `TestResult` class, that you can interact to.



### Getting data





### Json conversion 



## Examples

There are some examples of using UTest in `examples/` folder. If you want to run one of them, use instructions:

1. Make temp folder in UTest repository like `build/` or `tmp/`
2. Move to it using `cd tmp` and run cmake: `cmake -DBUILD_EXAMPLES=ON ..`
3. Run `make`
4. Examples are built, so u need to choose one and run via `examples/<example_name>`



## Installation



## Running tests for UTest

Clone UTest repository, create some folder inside for test build, for example `tmp/` or `build/`.

Move to this folder and run `cmake -DBUILD_TESTS=ON ..` and `make` after that. Now tests are built and you just need to use `tests/tests` for tests execution.

That's it! You have tested library for testing :)



## Extra docs links
