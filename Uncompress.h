#pragma once

#include "CharInfo.h"
#include "HuffmanTree.h"
#include <assert.h>

template<class T>
class Uncompress
{
public:
	Uncompress(const char * CompressFile, const char * ConfigFile)
	{
		FILE* fRead = fopen(CompressFile, "rb");
		FILE* fConfig = fopen(ConfigFile, "rb");
		FILE* fWrite = fopen("Uncompress.txt", "wb");
		assert(fRead);

		string str;
		while (ReadLine(fConfig, str))
		{
			//对\n做处理
			if (str.empty())
			{
				str += '\n';
			}
			else
			{
				u_info[(unsigned char)str.c_str()[0]]._ch = (unsigned char)str.c_str()[0];
				u_info[(unsigned char)str.c_str()[0]]._count = atoi(str.substr(2).c_str());
				str.clear();
			}

		}

		//根据配置文件生成Huffman树
		CharInfo invalid(0);
		Huffman<CharInfo> ht(u_info, 256, invalid);
		
		//重建Huffman树
		BinaryTreeNode<CharInfo>* root = ht.GetRoot();
		
		LongType i = ht.GetRoot()->_value._count;
		char ch = fgetc(fRead);
		while (i > 0)
		{
			unsigned char value = (unsigned char)ch;
			int pos = 7;
			
			while (pos >= 0 && i > 0)
			{
				if (((value >> pos) & 1) == 0)
				{
					root = root->_left;
				}
				else
				{
					root = root->_right;
				}

				if (root->_left == NULL && root->_right == NULL)
				{
					fputc(root->_value._ch, fWrite);
					root = ht.GetRoot();
					--i;
				}
				--pos;
			}
			ch = fgetc(fRead);
		}
		fclose(fRead);
		fclose(fConfig);
		fclose(fWrite);
	}

	bool ReadLine(FILE* file, string& str)
	{

		char ch = fgetc(file);
		if (feof(file))
			return false;

		while (!feof(file) && ch != '\n')
		{
			str += ch;
			ch = fgetc(file);
		}
		return true;
	}

private:
	CharInfo u_info[256];
};
