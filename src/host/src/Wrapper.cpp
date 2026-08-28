#include <wasmtime/component/val.hh>

#include "Wrapper.hpp"

using namespace std;
using namespace wasmtime;

// インスタンス化したwasmデータをセットします
void Wrapper::setWasmInstance(map<string, component::Instance>&& inInstances) {
	this->instances = std::move(inInstances);
}

// wasmの関数を呼び出し、メッセージを取得します
vector<string> Wrapper::getMessages(Store& store) {
	vector<string> messages;
	int32_t index = 0;
	for (const auto& [name, instance] : this->instances) {
		auto infoInterfaceIndex = instance.get_export_index(store, nullptr, "app:utility/info");
		if (!infoInterfaceIndex.has_value()) {
			continue;
		}
		auto functioneIndex = instance.get_export_index(
			store, &infoInterfaceIndex.value(), "get-message");
		if (!functioneIndex.has_value()) {
			continue;
		}
		auto func = instance.get_func(store, functioneIndex.value());
		if (!func.has_value()) {
			continue;
		}
		vector<component::Val> params = {
			component::Val(++index)
		};
		vector<component::Val> results = {
			component::Val::string("")
		};
		if (!func.value().call(store, params, results)) {
			continue;
		}
		messages.push_back(name + "\t: " + string(results.at(0).get_string()));
	}
	return messages;
}