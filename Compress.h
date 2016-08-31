#pragma once

#include "CharInfo.h"
#include "HuffmanTree.h"
#include <assert.h>

template<class T>
class Compress
{
public:
	Compress(char* File)
	{
		//将数组中下标对应的ASCII码初始化成对应的字符且出现次数初始化为0
		for (size_t i = 0;i < 256;++i)
		{
			c_info[i]._ch = i;
			c_info[i]._count = 0;
		}

		//读写文件都以二进制的形式
		FILE* fRead = fopen(File, "rb");
		assert(fRead);
		FILE* fWrite = fopen("CompressFile.txt", "wb");
		assert(fWrite);

		//统计字符出现次数
		char ch = fgetc(fRead);
		while (!feof(fRead))
		{
			c_info[(unsigned char)ch]._count++;
			ch = fgetc(fRead);
		}

		//生成Huffman树
		CharInfo invalid(0);
		Huffman<CharInfo> ht(c_info, 256, invalid);

		//生成Huffman编码
		string code;
		GenerateHuffmanCode(ht.GetRoot(), code);

		//读Huffman树，写入压缩文件
		fseek(fRead, 0, SEEK_SET);
		ch = fgetc(fRead);
		int pos = 0;
		unsigned char value = 0;
		while (!feof(fRead))
		{
			string& code = c_info[(unsigned char)ch]._code;
			for (size_t j = 0; j < c_info[(unsigned char)ch]._code.size(); ++j)
			{
				//满8位(一个字节)写入一次文件
				value <<= 1;
				if (code[j] == '1')
					value |= 1;

				if (++pos == 8)
				{
					pos = 0;
					fputc(value, fWrite);
					value = 0;
				}
			}
			ch = fgetc(fRead);
		}

		//如果剩余不足八位则补0
		if (pos > 0)
		{
			value <<= (8 - pos);
			fputc(value, fWrite);
		}

		//写配置文件
		FILE* configfile = fopen("ConfigFile.txt", "wb");
		char str_count[20];
		string str_info;
		for (int i = 0; i < 256; ++i)
		{
			if (c_info[i] != invalid)
			{
				str_info = c_info[i]._ch;
				str_info += ',';
				_itoa(c_info[i]._count, str_count, 10);
				str_info += str_count;
				str_info += '\n';

				fputs(str_info.c_str(), configfile);
			}
		}
		fclose(fWrite);
		fclose(fRead);
		fclose(configfile);
	}

	void GenerateHuffmanCode(BinaryTreeNode<CharInfo>* root, string code)
	{
		_GenerateHuffmanCode(root, code);
	}

protected:
	void _GenerateHuffmanCode(BinaryTreeNode<CharInfo>* root, string code)
	{
		if (root == NULL)
			return;

		if (root->_left != NULL)
			_GenerateHuffmanCode(root->_left, code + '0');

		if (root->_right != NULL)
			_GenerateHuffmanCode(root->_right, code + '1');

		if (root->_left == NULL && root->_right == NULL)
		{
			root->_value._code = code;
			c_info[root->_value._ch]._code = code;
			cout << c_info[root->_value._ch]._ch << c_info[root->_value._ch]._code << endl;
		}
	}
protected:
	CharInfo c_info[256];
};
