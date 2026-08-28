@echo off

componentize-py ^
	--wit-path wit\utility.wit ^
	--world utility ^
	componentize Component ^
	-o ..\..\host\wasm\Component_python.wasm