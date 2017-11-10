#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "rapidjson\document.h"
#include "rapidjson\stringbuffer.h"
#include "rapidjson\writer.h"

namespace JsonUtils {

	enum ResultCode {
		kSuccess,
		kFailToOpenFile,
		kParseError,
	};
	
	// return false if fail to open the file.
	static bool ReadFileToString(std::string file_path, std::string& content) {
		std::ifstream fin(file_path);
		if (!fin.good()) {
			fin.close();
			return false;
		}
		else {
			while (true) {
				char c = fin.get();
				if (c == EOF) {
					break;
				}
				else {
					content += c;
				}
			}
			fin.close();
			return true;
		}		
	}

	static bool WriteStringToFile(std::string file_path, std::string& content) {
		std::ofstream fout(file_path);
		if (fout.is_open()) {
			std::cout << file_path << " is open " << std::endl;
			fout << content;
			fout.flush();
			fout.close();
			return true;
		}
		else {
			std::cout << file_path << " not open " << std::endl;
			return false;
		}
	}

	static rapidjson::Value DoubleVectorToValue(const std::vector<double>& a, rapidjson::Document::AllocatorType& allocator) {
		rapidjson::Value v;
		v.SetArray();
		for (int i = 0; i < a.size(); i++) {
			v.PushBack(a[i], allocator);
		}
		return v;
	}

	static bool ValueToDoubleVector(const rapidjson::Value& value, std::vector<double>& vector) {
		vector.clear();
		if (!value.IsArray()) {
			return false;
		}
		for (rapidjson::SizeType i = 0; i < value.Size(); i++) {
			if (!value[i].IsDouble()) {
				return false;
			}
		}
		for (rapidjson::SizeType i = 0; i < value.Size(); i++) {
			vector.push_back(value[i].GetDouble());
		}
		return true;
	}

	//create a string value by copying it. need a allocator.
	static rapidjson::Value CreateStringValue(std::string str, rapidjson::Document::AllocatorType& allocator) {
		rapidjson::Value v;
		v.SetString(str.c_str(), str.length(), allocator);
		return v;
	}

	static std::string StringfyDocument(const rapidjson::Document& d) {
		rapidjson::StringBuffer buffer;
		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		d.Accept(writer);
		return (std::string)buffer.GetString();
	}

	static std::string StringfyValue(const rapidjson::Value& v) {
		rapidjson::StringBuffer buffer;
		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		v.Accept(writer);
		return (std::string)buffer.GetString();
	}

	static ResultCode ParseFile(std::string file_path, rapidjson::Document& document) {
		std::string content;
		if (!ReadFileToString(file_path, content)) {
			return kFailToOpenFile;
		}
		else {
			document.Parse(content.c_str());
			if (document.HasParseError()) {
				return kParseError;
			}
			else {
				return kSuccess;
			}
		}
	}

	template<typename T>
	static void PrintVector(std::vector<T> a) {
		for (int i = 0; i < a.size(); i++) {
			std::cout << a[i] << "  ";
		}
		std::cout << std::endl;
	}
}