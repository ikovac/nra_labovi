#include <iostream>
#include <napi.h>

int arr[10000] = {0};

int randomNumberGenerator()
{
	int randomNumber = 0;

	randomNumber = rand() % (10001 - 1) + 1;

	return randomNumber;
}

void randomMemoryAccess() {
    int i = 0;
    int rand_index = 0;
    for(i = 0; i < 10000; i++) {
        rand_index = randomNumberGenerator();
        arr[rand_index] = rand_index;
    }
}

void sequentiallyMemoryAccess() {
    int i = 0;
    int rand_index = 0;
    for(i = 0; i < 10000; i++) {
        rand_index = randomNumberGenerator();
        arr[i] = rand_index;
    }
}

void randomMemoryAccessWrapper(const Napi::CallbackInfo &info) {
    randomMemoryAccess();
}

void sequentiallyMemoryAccessWrapper(const Napi::CallbackInfo &info) {
    sequentiallyMemoryAccess();
}


Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
    exports.Set(
        "randAccess", Napi::Function::New(env, randomMemoryAccessWrapper)
    );
    exports.Set(
        "seqAccess", Napi::Function::New(env, sequentiallyMemoryAccessWrapper)
    );
    return exports;
}

NODE_API_MODULE(customaddon, InitAll)