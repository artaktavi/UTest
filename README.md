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

Test will register automatically, so that's all you need to do.



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



## Installation



## Extra docs links
