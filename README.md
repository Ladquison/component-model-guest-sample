# component-model-guest-sample

WebAssembly Component Modelの実装サンプルです。<br>
以下のゲスト言語でWebAssembly Componentを作成し、それをWasmtime C++ APIを使って呼び出します。
- C++
- C#
- Python
- Rust
- TypeScript

# 開発環境

開発のため、事前に`tools`内の各フォルダに置いているリンクからツールをダウンロードし、そのフォルダ内に展開してください。<br>
さらにゲスト・ホストの開発のため、それぞれ追加でインストールが必要となる場合があります。

## C++

- CMake
- Visual Studio 2022
  - `src/host/`のビルド設定を変更することで他のツールに置き換えることができます。

## C#

- [.NET 10+ SDK](https://dotnet.microsoft.com/en-us/download/dotnet/10.0)
- [componentize-dotnet](https://github.com/bytecodealliance/componentize-dotnet)
  - `dotnet new install BytecodeAlliance.Componentize.DotNet.Templates`でインストールできます。

## Python

- [componentize-py](https://github.com/bytecodealliance/componentize-py)
  - `pip install componentize-py`でインストールできます。

## Rust

- cargo-component
  - `cargo install cargo-component`でインストールできます。

## TypeScript

- [jco](https://github.com/bytecodealliance/jco)
  - `npm install -g @bytecodealliance/jco --force`でインストールできます。
  - `--force`を付けるのを忘れないよう注意してください。

# スクリプト

開発環境が構築できたら、`script`内のスクリプトを実行することで各環境の構築及びビルドが実施できます。<br>
`00_generate_wasm_binding.bat`と`10_setup_guest.bat`に関しては、オプションでどの言語の環境を構築するのか指定する必要があります。指定できるのは以下のいずれかです。
| オプション | 対象言語 |
| - | - |
| cpp | C++ |
| csharp | C# |
| python | Python |
| rust | Rust |
| ts | TypeScript |

## 00_generate_wasm_binding.bat

WITファイルからバインディングコードを生成します。ゲスト言語によってはWITファイルを使ってWebAssembly Componentをビルドできるものがあるため、コピーだけとなる場合があります。

## 10_setup_guest.bat

ゲスト言語でビルドを実行し、WebAssembly Componentを生成します。

## 20_setup_host.bat

ホスト環境でビルドを実行します。

# 実行結果

生成されたwasmファイルを読み込み、それぞれの関数を呼び出して取得した文字列を出力しています。

```
Component_cpp.wasm      : This is C++ function, number = 1
Component_csharp.wasm   : This is C# function, number = 2
Component_python.wasm   : This is Python functon, number = 3
Component_rust.wasm     : This is Rust function, number = 4
Component_ts.wasm       : This is TypeScript function, number = 5
```