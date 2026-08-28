#pragma once

#include <cstdint>
#include <map>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include <wasmtime/_store_class.hh>
#include <wasmtime/engine.hh>
#include <wasmtime/component/instance.hh>

class Loader {
private:
	//! Wasmtime Engine
	std::unique_ptr<wasmtime::Engine> engine;
	//! Wasmtime Store
	std::unique_ptr<wasmtime::Store> store;

public:
	/**
	 * @brief コンストラクタ
	 */
	Loader() = default;

	/**
	 * @brief デストラクタ
	 */
	virtual ~Loader() = default;

	/**
	 * @brief wasmファイルを読み込んで初期化します
	 * @retun インスタンス化に成功したwasmのファイル名とインスタンスの組
	 */
	std::map<std::string, wasmtime::component::Instance> load();

	/**
	 * @brief Wasmtime Storeを取得します
	 * @return Store
	 */
	wasmtime::Store& getStore();

private:
	/**
	 * @brief ファイルからバイナリデータを取得します
	 * @param filePath 読み込むファイルのパス
	 * @return 読み込み結果
	 */
	std::optional<std::vector<uint8_t>> loadFile(const std::string& filePath);
};