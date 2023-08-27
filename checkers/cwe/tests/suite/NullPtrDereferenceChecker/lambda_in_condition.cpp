bool assertFailure() {
    return false;
}

void foo1()
{
    int* ptr2 = nullptr;
    auto cond_lamda = [] (bool val) {
        return val;
    };

    if ([result = ptr2 == nullptr || assertFailure()]() { return result; }()) {
        return;
    }

    *ptr2 = 1234;
}

void foo2()
{
    int* ptr = nullptr;

    if ([result = ptr == nullptr]() { return result; }()) {
        return;
    }

    *ptr = 1234;
}

void foo5()
{
    int* ptr5 = nullptr;

    if ([]() { return true; }()) {
        return;
    }
    *ptr5 = 1234;
}

void foo3()
{
    int* ptr4 = nullptr;
    auto val = []() { return true; };
    if (val()) {
        return;
    }
    *ptr4 = 1234;
}

void foo6()
{
    int* ptr6 = nullptr;
    auto cond_lamda = [] (bool val) {
        return val;
    };
    if (cond_lamda(true)) {
        return;
    }
    *ptr6 = 1234;
}

