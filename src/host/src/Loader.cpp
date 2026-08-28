#include <filesystem>
#include <fstream>
#include <iostream>

#include <wasmtime/config.hh>
#include <wasmtime/component/component.hh>
#include <wasmtime/component/linker.hh>

#include "Loader.hpp"

using namespace std;
using namespace wasmtime;
namespace fs = std::filesystem;

// wasmファイルを読み込んで初期化します
map<string, component::Instance> Loader::load() {
	map<string, component::Instance> instanceMap;
	Config config;
	config.wasm_component_model(true);
	this->engine = make_unique<Engine>(std::move(config));
	this->store = make_unique<Store>(*this->engine);
	WasiConfig wasiConfig;
	if (!this->store->context().set_wasi(std::move(wasiConfig))) {
		cout << " Failed to set WASI config" << endl;
		return instanceMap;
	}
	component::Linker linker(*this->engine);
	if (!linker.add_wasip2()) {
		cout << " Failed to add WASI Preview 2" << endl;
		return instanceMap;
	}
	if (!linker.add_wasi_http()) { // TypeScriptで生成したwasmのインスタンス化に必要
		cout << " Failed to add WASI HTTP" << endl;
		return instanceMap;
	}

	// wasmファイルを読み込みます
	for (const auto& entry : fs::directory_iterator(WASM_PATH)) {
		if (!entry.is_regular_file()) {
			continue;
		}
		if (entry.path().extension() != ".wasm") {
			continue;
		}
		// ファイルからバイナリデータを取得
		auto binary = this->loadFile(fs::absolute(entry.path()).string());
		if (!binary.has_value()) {
			cout << "Failed to open " << entry.path().filename() << endl;
			continue;
		}
		// ファイルを読み込みコンパイル
		auto component = component::Component::compile(*this->engine, binary.value());
		if (!component) {
			cout << "Failed to compile " << entry.path().filename()
				<< ": " << component.err().message() << endl;
			continue;
		}
		// インスタンス化
		auto instance = linker.instantiate(*this->store, component.ok());
		if (!instance) {
			cout << "Failed to instantiate " << entry.path().filename()
				<< ": " << instance.err().message() << endl;
			continue;
		}
		instanceMap.try_emplace(
			entry.path().filename().string(), std::move(instance.ok()));
	}
	return instanceMap;
}

// Wasmtime Storeを取得します
wasmtime::Store& Loader::getStore() {
	return *this->store;
}

// ファイルからバイナリデータを取得します
optional<vector<uint8_t>> Loader::loadFile(const string& filePath) {
	std::ifstream ifs(filePath, ios::binary);
	if (!ifs) {
		return nullopt;
	}
	return vector<uint8_t>(
		istreambuf_iterator<char>(ifs), istreambuf_iterator<char>());
}