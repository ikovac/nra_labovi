#include <iostream>
#include <napi.h>
#include <thread>

int randomNumberGenerator()
{
	int randomNumber = 0;

	randomNumber = rand() % (6 - 1) + 1;

	return randomNumber;
}

int sumArr() {
    int i = 0;
    int sum = 0;

    for(i = 0; i < 200000; i ++) {
        sum += randomNumberGenerator();
    }

    return sum;
}

void sumParalel(int start, int end, int *sum) {
    int local_sum = 0;
    int i = 0;

    for(i = start; i < end; i ++) {
        local_sum += randomNumberGenerator();
    }

    *sum = local_sum;
}

int makeItParalel() {
    int sum1 = 0;
    int sum2 = 0;

    std::thread th1(sumParalel, 0, 100000, &sum1);
    std::thread th2(sumParalel, 100000, 200000, &sum2);

    th1.join();
    th2.join();

    return sum1 + sum2;
}

Napi::Number sumArrWrapper(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    return Napi::Number::New(env, sumArr());
}

Napi::Number sumParalelWrapper(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    return Napi::Number::New(env, makeItParalel());
}


Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
    exports.Set(
        "sum", Napi::Function::New(env, sumArrWrapper)
    );
    exports.Set(
        "sumParalel", Napi::Function::New(env, sumParalelWrapper)
    );
    return exports;
}

NODE_API_MODULE(customaddon, InitAll)