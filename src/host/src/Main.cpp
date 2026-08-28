#include <iostream>

#include "Loader.hpp"
#include "Wrapper.hpp"

using namespace std;

int main() {
	Loader loader;
	auto instances = loader.load();

	Wrapper wrapper;
	wrapper.setWasmInstance(std::move(instances));
	auto messages = wrapper.getMessages(loader.getStore());

	for (auto& message : messages) {
		cout << message << endl;
	}

	return 0;
}