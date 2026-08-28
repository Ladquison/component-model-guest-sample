#pragma once

#include <map>
#include <string>
#include <vector>

#include <wasmtime/_store_class.hh>
#include <wasmtime/component/instance.hh>

class Wrapper {
private:
	//! wasmファイルの名前とそのインスタンスの組
	std::map<std::string, wasmtime::component::Instance> instances;

public:
	/**
	 * @brief コンストラクタ
	 */
	Wrapper() = default;

	/**
	 * @brief デストラクタ
	 */
	virtual ~Wrapper() = default;

	/**
	 * @brief インスタンス化したwasmデータをセットします
	 * @param inInstances wasmデータのインスタンス一覧
	 */
	void setWasmInstance(std::map<std::string, wasmtime::component::Instance>&& inInstances);

	/**
	 * @brief wasmの関数を呼び出し、メッセージを取得します
	 * @param store Wasmtime Store
	 * @param wasm毎のメッセージ一覧
	 */
	std::vector<std::string> getMessages(wasmtime::Store& store);
};