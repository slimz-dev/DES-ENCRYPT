#pragma once

namespace cryptography {

	using namespace System;
	using namespace System::IO;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}
		static String^ fileData;
		array<String^>^ cLockResult = gcnew array<String^>(29);
		array<String^>^ dLockResult = gcnew array<String^>(29);
		void hexToBin(String^ hex, array<String^>^ storage) {
			int temp = 1;
			for (int step = 0; step < 64; step++) {
				if (step >= hex->Length) {
					storage[temp] = "0";
				}
				else {
					// Convert the hexadecimal string to an integer
					Int64 decimalValue = Convert::ToInt64(hex[step].ToString(), 16);

					// Convert the integer to a binary string
					String^ binaryString = Convert::ToString(decimalValue, 2)->PadLeft(4, '0');
					for (int index = 0; index < 4; index++) {
						storage[temp++] = binaryString[index].ToString();
					}
				}
			}
		}
		String^ binToHex(array<String^>^ bin) {
			String^ binaryNumber; // Example binary number
			for (int i = 0; i < bin->Length; i++) {
				binaryNumber += bin[i];
			}
			Int64 decimalValue = Convert::ToInt64(binaryNumber, 2); // Convert binary to decimal
			String^ hex = Convert::ToString(decimalValue, 16);
			return hex;
		}
		void AsciiToBinary(String^ data,array<String^>^ binaryBlock) {
			int step = 1;
			for (int index = 0; index < 8; index++) {
				if (index >= data->Length) {
					for (int i = 0; i < 8; i++) {
						binaryBlock[step] = "0";
						step++;
					}
				}
				else {
					String^ binary = Convert::ToString(data[index], 2)->PadLeft(8, '0'); // Convert to binary and pad with zeroes to ensure it's 8 digits long
					for (int binaryStart = 0; binaryStart < 8; binaryStart++) {
						binaryBlock[step] = binary[binaryStart].ToString();
						step++;
					}
				}
			}
		}

		String^ BinToAscii(String^ binaryString) {
			String^ asciiString;
			String^ hex;
			for (int i = 0; i < binaryString->Length; i++) {
				hex += binaryString[i];
			}
			Int64 decimalValue = Convert::ToInt64(hex, 2); // Convert binary to decimal
			hex = Convert::ToString(decimalValue, 16);
			for (int i = 0; i < hex->Length - 1; i+=2)
			{
				String^ myhex = "0x";
				myhex += hex[i];
				myhex += hex[i + 1];
				Int64 thisHex = Convert::ToInt64(myhex,16);
				String^ byteChar = Char::ConvertFromUtf32(thisHex);
				asciiString += byteChar;
			}
			return asciiString;
		}

		String^ decToBin(int decimalValue){
			String^ binaryString = Convert::ToString(decimalValue, 2)->PadLeft(4,'0');
			return binaryString;
		}
		
		array<String^>^ permuteIP(array<String^>^ binary) {
			array<String^>^ permuteArray = gcnew array<String^>(65);
			int firstStart;
			int init = 1;
			for (int loop = 1; loop <= 8; loop++) {
				for (int index = 0; index <= 7; index++) {
					if (loop == 1) {
						firstStart = 58;
						permuteArray[init++] = binary[firstStart - 8 * index];
					}
					if (loop == 2) {
						firstStart = 60;
						permuteArray[init++] = binary[firstStart - 8 * index];
					}
					if (loop == 3) {
						firstStart = 62;
						permuteArray[init++] = binary[firstStart - 8 * index];
					}
					if (loop == 4) {
						firstStart = 64;
						permuteArray[init++] = binary[firstStart - 8 * index];
					}
					if (loop == 5) {
						firstStart = 57;
						permuteArray[init++] = binary[firstStart - 8 * index];
					}
					if (loop == 6) {
						firstStart = 59;
						permuteArray[init++] = binary[firstStart - 8 * index];
					}
					if (loop == 7) {
						firstStart = 61;
						permuteArray[init++] = binary[firstStart - 8 * index];
					}
					if (loop == 8) {
						firstStart = 63;
						permuteArray[init++] = binary[firstStart - 8 * index];
					}
				}

			}
			return permuteArray;
		}

		array<String^>^ permuteIP1(array<String^>^ inputArray) {
			array<String^>^ resultArray = gcnew array<String^>(65);
			array<int>^ permuteArray = gcnew array<int>{40, 8, 48, 16, 56, 24, 64, 32, 39, 7, 47, 15, 55, 23, 63, 31, 38, 6, 46, 14, 54, 22, 62, 30, 37, 5, 45, 13, 53, 21, 61, 29, 36, 4, 44, 12, 52, 20, 60, 28, 35, 3, 43, 11, 51, 19, 59, 27, 34, 2, 42, 10, 50, 18, 58, 26, 33, 1, 41, 9, 49, 17, 57, 25};
			for (int index = 1; index < inputArray->Length; index++) {
				int currentIndex = permuteArray[index - 1];
				resultArray[index] = inputArray[currentIndex];
			}
			return resultArray;
		}

		

		array<String^>^ sBox(array<String^>^ inputArray){
			array<String^>^ outputArray = gcnew array<String^>(33);
			array<String^>^ finalArray =gcnew array<String^>(33);
			int finalArrayIndex = 1;
			int columns = 16;
			int rows = 4;
			array<int>^ permuteArray = gcnew array<int>{16, 7, 20, 21,29,12,28,17,1,15,23,26,5,18,31,10,2,8,24,14,32,27,3,9,19,13,30,6,22,11,4,25};
			array<int, 2>^ sBox1 = gcnew array<int, 2>(rows, columns) {
				{14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
				{0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
				{4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
				{15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}
			};
			array<int, 2>^ sBox2 = gcnew array<int, 2>(rows, columns) {
				{15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10 }, 
				{3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5 },
				{0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15 },
				{13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}
			};
			array<int, 2>^ sBox3 = gcnew array<int, 2>(rows, columns) {
				{10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
				{13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
				{13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
				{1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}
			};
			array<int, 2>^ sBox4 = gcnew array<int, 2>(rows, columns) {
				{7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
				{13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
				{10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
				{3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}
			};
			array<int, 2>^ sBox5 = gcnew array<int, 2>(rows, columns) {
				{2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
				{14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
				{4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
				{11,8,12,7,0,14,2,13,6,15,0,9,10,4,5,3}
			};
			array<int, 2>^ sBox6 = gcnew array<int, 2>(rows, columns) {
				{12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
				{10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
				{9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
				{4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}
			};
			array<int, 2>^ sBox7 = gcnew array<int, 2>(rows, columns) {
				{4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
				{13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
				{1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
				{6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}
			};
			array<int, 2>^ sBox8 = gcnew array<int, 2>(rows, columns) {
				{13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
				{1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
				{7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
				{2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}
			};
			array<int, 2>^ selectedSBox = gcnew array<int, 2>(rows, columns);
			for (int index = 1; index <= 8; index++) {
				String^ firstHalf;
				String^ secondHalf;
				switch (index) {
				case 1:
					selectedSBox = sBox1;
					break;
				case 2:
					selectedSBox = sBox2;
					break; 
				case 3:
					selectedSBox = sBox3;
					break; 
				case 4:
					selectedSBox = sBox4;
					break; 
				case 5:
					selectedSBox = sBox5;
					break;
				case 6:
					selectedSBox = sBox6;
					break;
				case 7:
					selectedSBox = sBox7;
					break;
				default:
					selectedSBox = sBox8;
					break;
				}
				for (int arrayIndex = 1 + 6 * (index - 1); arrayIndex <= 6 * index; arrayIndex++) {
					if (arrayIndex == 1 + 6 * (index - 1) || arrayIndex == 6 * index) {
						firstHalf += inputArray[arrayIndex];
					}
					else {
						secondHalf += inputArray[arrayIndex];
					}
				}
				
				Int64 row = toDecimal(firstHalf);
				Int64 column = toDecimal(secondHalf);
				int resultNumber = selectedSBox[row,column];
				String^ boxResult = decToBin(resultNumber);
				for (int index = 0; index < 4; index++) {
					finalArray[finalArrayIndex++] = boxResult[index].ToString();
				}
			}
			for (int index = 1; index <= permuteArray->Length; index++) {
				int currentIndex = permuteArray[index-1];
				outputArray[index] = finalArray[currentIndex];
			}
			return outputArray;
		}

		Int64 toDecimal(String^ binaryString) {
			Int64 decimalValue = Convert::ToInt64(binaryString, 2);
			return decimalValue;
		}
		array<String^>^ xor(array<String^>^ firstArray, array<String^>^ secondArray) {
			array<String^>^ resultArray = gcnew array<String^>(firstArray->Length);
			for (int index = 1; index < resultArray->Length; index++) {
				if (firstArray[index] == secondArray[index]) {
					resultArray[index] = "0";
				}
				else {
					resultArray[index] = "1";
				}
			}
			return resultArray;
		}


		array<String^>^ changeRightArray(array<String^>^ rightArray, array<String^>^ lockArray) {
			array<String^>^ rightArrayAfterE = eBitArray(rightArray);
			array<String^>^ xorArray = xor (rightArrayAfterE, lockArray);
			array<String^>^ afterSBox = sBox(xorArray);
			return afterSBox;
		}

		array<String^>^ leftShift(array<String^>^ array,int num) {
			if (num == 1) {
				String^ temp;
				temp = array[28];
				array[28] = array[1];
				for (int index = 1; index <= 27; index++) {
					if (index == 27) {
						array[index] = temp;
					}
					else {
						array[index] = array[index + 1];
					}
				}
			}
			else if(num == 2){
				String^ firstShift;
				String^ secondShift;
				firstShift = array[28];
				secondShift = array[27];
				array[28] = array[2];
				array[27] = array[1];
				for (int index = 1; index <= 26; index++) {
					if (index == 25) {
						array[index] = secondShift;
					}
					else if (index == 26) {
						array[index] = firstShift;
					}
					else {
						array[index] = array[index + 2];
					}
				}
			}
			return array;
		}

		array<String^>^ permutePC2(array<String^>^ firstArray, array<String^>^ secondArray) {
			array<int>^ selectedArray = gcnew array<int>{14, 17, 11, 24, 1, 5, 3, 28, 15, 6, 21, 10, 23, 19, 12, 4, 26, 8, 16, 7, 27, 20, 13, 2, 41, 52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48, 44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32};
			array<String^>^ mergedArray = gcnew array<String^>(57);
			array<String^>^ permuteArray = gcnew array<String^>(49);
			int tempIndex = 1;
			//Merging
			for (int index = 1; index < mergedArray->Length; index++) {
				if (index <= 28) {
					mergedArray[index] = firstArray[index];
				}
				else {
					mergedArray[index] = secondArray[tempIndex++];
				}
			}
			
			//Permute PC-2
			for (int index = 1; index < permuteArray->Length; index++) {
				int currentIndex = selectedArray[index - 1];
				permuteArray[index] = mergedArray[currentIndex];
			}
			return permuteArray;
		}

		array<String^>^ handleLock(array<String^>^ lockArray,int iteration) {
			//Permute PC-1
			array<int>^ cLockArray = gcnew array<int>{57, 49, 41, 33, 25, 17, 9, 1, 58, 50, 42, 34, 26, 18, 10, 2, 59, 51, 43, 35, 27, 19, 11, 3, 60, 52, 44, 36};
			array<int>^ dLockArray = gcnew array<int>{63,55,47,39,31,23,15,7,62,54,46,38,30,22,14,6,61,53,45,37,29,21,13,5,28,20,12,4};
			if (String::IsNullOrEmpty(cLockResult[1])) {
				//Cx
				for (int index = 1; index <= 28; index++) {
					int currentIndex = cLockArray[index - 1];
					cLockResult[index] = lockArray[currentIndex];
				}
				//Dx
				for (int index = 1; index <= 28; index++) {
					int currentIndex = dLockArray[index - 1];
					dLockResult[index] = lockArray[currentIndex];
				}
			}
			//Left shift
			if (iteration == 1 || iteration == 2 || iteration == 9 || iteration == 16) {
				cLockResult = leftShift(cLockResult, 1);
				dLockResult= leftShift(dLockResult, 1);
			}
			else {
				cLockResult = leftShift(cLockResult, 2);
				dLockResult = leftShift(dLockResult, 2);
			}
			//Lock result
			array<String^>^ lockResult = permutePC2(cLockResult, dLockResult);
			if (iteration == 16) {
				cLockResult = gcnew array<String^>(29);
				dLockResult = gcnew array<String^>(29);
			}
			return lockResult;
		}


		array<String^>^ eBitArray(array<String^>^ arrayList) {
			array<String^>^ resultArray = gcnew array<String^>(49);
			array<int>^ eBit = gcnew array<int>{32,1,2,3,4,5,4,5,6,7,8,9,8,9,10,11,12,13,12,13,14,15,16,17,16,17,18,19,20,21,20,21,22,23,24,25,24,25,26,27,28,29,28,29,30,31,32,1};
			for (int index = 1; index <= eBit->Length; index++) {
				int currentIndex = eBit[index - 1];
				resultArray[index] = arrayList[currentIndex];
			}
			return resultArray;
		}

		array<String^>^ loopFunction(array<String^>^ leftArray, array<String^>^ rightArray, array<String^>^ lockArray) {
			array<String^>^ finalArray = gcnew array<String^>(65);
			for (int index = 1; index <= 16; index++) {
				array<String^>^ leftArrayBefore;
				leftArrayBefore = leftArray;
				leftArray = rightArray;
				array<String^>^ myLock = handleLock(lockArray, index);
				rightArray = changeRightArray(rightArray, myLock);
				rightArray = xor(rightArray, leftArrayBefore);
			}
			int indexForLeft = 1;
			for (int index = 1; index < finalArray->Length; index++) {
				if (index <= 32) {
					finalArray[index] = rightArray[index];
				}
				else {
					finalArray[index] = leftArray[indexForLeft++];
				}
			}


			array<String^>^ resultArray = permuteIP1(finalArray);
			return resultArray;
		}


        String^ handleEncrypting(array<String^>^ permute_array, array<String^>^ lockArray) {
			array<String^>^ leftArray = gcnew array<String^>(33);
			array<String^>^ rightArray = gcnew array<String^>(33);

			for (int index = 1; index <= 32; index++) {
				leftArray[index] = permute_array[index];
			}
			int right = 1;
			for (int index = 33; index <= 64; index++) {
				rightArray[right++] = permute_array[index];
			}
			array<String^>^ encryptingMessage = loopFunction(leftArray, rightArray, lockArray);
			String^ fileContent;
			for (int index = 1; index <= 64; index++) {
				fileContent += encryptingMessage[index];
			}
			return fileContent;
		}


//  -------------------------------------------------------------------------------------------------------------------



		String^ handleDecrypting(String^ inputString, array<String^>^ lockArray) {
			array<String^>^ reverseArray = reversePermuteIP1(inputString);
			array<String^>^ rightArray = gcnew array<String^>(33);
			array<String^>^ leftArray = gcnew array<String^>(33);

			//R16
			for (int i = 1; i <= 32; i++) {
				rightArray[i] = reverseArray[i];
			}

			//L16
			for (int i = 33; i <= 64; i++) {
				leftArray[i-32] = reverseArray[i];
			}

			String^ decryptingString = reverseLoop(leftArray, rightArray, lockArray);
			return decryptingString;
		}

		array<String^>^ reversePermuteIP1(String^ inputString) {
			array<int>^ reversePermute =gcnew array<int>{40, 8, 48, 16, 56, 24, 64, 32, 39, 7, 47, 15, 55, 23, 63, 31, 38, 6, 46, 14, 54, 22, 62, 30, 37, 5, 45, 13, 53, 21, 61, 29, 36, 4, 44, 12, 52, 20, 60, 28, 35, 3, 43, 11, 51, 19, 59, 27, 34, 2, 42, 10, 50, 18, 58, 26, 33, 1, 41, 9, 49, 17, 57, 25};
			array<String^>^ newArray = gcnew array<String^>(65);
			int index = 1;
			while(index < 65){
				for (int i = 0; i <= 63; i++) {
					if (reversePermute[i] == index) {
						newArray[index] = inputString[i].ToString();
				        index++;
						break;
					}
				}
			}
			return newArray;
		}

		array<String^>^ reversePermuteIP(String^ inputString) {
			array<int>^ reversePermute = gcnew array<int>{58,50,42,34,26,18,10,2,60,52,44,36,28,20,12,4,62,54,46,38,30,22,14,6,64,56,48,40,32,24,16,8,57,49,41,33,25,17,9,1,59,51,43,35,27,19,11,3,61,53,45,37,29,21,13,5,63,55,47,39,31,23,15,7};
			array<String^>^ newArray = gcnew array<String^>(65);
			int index = 1;
			while (index < 65) {
				for (int i = 0; i <= 63; i++) {
					if (reversePermute[i] == index) {
						newArray[index] = inputString[i].ToString();
						index++;
						break;
					}
				}
			}
			return newArray;
		}

		String^ reverseLoop(array<String^>^ leftArray, array<String^>^ rightArrayAfter, array<String^>^ lockArray) {
			array<String^>^ rightArray;
			for (int i = 16; i >= 1; i--) {
				rightArray = leftArray;
				array<String^>^ myLock = getLock(lockArray, i);
				array<String^>^ rightArrayAfterE = eBitArray(rightArray);
				array<String^>^ xorArray = xor (rightArrayAfterE, myLock);
				array<String^>^ afterSBox = sBox(xorArray);
				leftArray = xor (rightArrayAfter, afterSBox);
				rightArrayAfter = rightArray;
			}
			String^ myString;
			for (int i = 1; i < 33; i++) {
				myString += leftArray[i];
			}
			for (int i = 1; i < 33; i++) {
				myString += rightArray[i];
			}
			array<String^>^ myDecryptingArray = reversePermuteIP(myString);
			myString = "";
			for (int i = 1; i < myDecryptingArray->Length; i++) {
				myString += myDecryptingArray[i];
			}
			myString = BinToAscii(myString);
			return myString;
		}

		array<String^>^ getLock(array<String^>^ lockArray, int iteration) {
			//Permute PC-1
			array<int>^ cLockArray = gcnew array<int>{57, 49, 41, 33, 25, 17, 9, 1, 58, 50, 42, 34, 26, 18, 10, 2, 59, 51, 43, 35, 27, 19, 11, 3, 60, 52, 44, 36};
			array<int>^ dLockArray = gcnew array<int>{63, 55, 47, 39, 31, 23, 15, 7, 62, 54, 46, 38, 30, 22, 14, 6, 61, 53, 45, 37, 29, 21, 13, 5, 28, 20, 12, 4};
			for (int step = 1; step <= iteration; step++) {
			if (step == 1) {
				//Cx
				for (int index = 1; index <= 28; index++) {
					int currentIndex = cLockArray[index - 1];
					cLockResult[index] = lockArray[currentIndex];
				}
				//Dx
				for (int index = 1; index <= 28; index++) {
					int currentIndex = dLockArray[index - 1];
					dLockResult[index] = lockArray[currentIndex];
				}
			}
			//Left shift
			if (step == 1 || step == 2 || step == 9 || step == 16) {
				cLockResult = leftShift(cLockResult, 1);
				dLockResult = leftShift(dLockResult, 1);
			}
			else {
				cLockResult = leftShift(cLockResult, 2);
				dLockResult = leftShift(dLockResult, 2);
			}
			}
			//Lock result
			array<String^>^ lockResult = permutePC2(cLockResult, dLockResult);
			if (iteration == 1) {
				cLockResult = gcnew array<String^>(29);
				dLockResult = gcnew array<String^>(29);
			}
			return lockResult;
		}
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	protected:
	private: System::Windows::Forms::ContextMenuStrip^ contextMenuStrip1;
	private: System::Windows::Forms::ContextMenuStrip^ contextMenuStrip2;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TextBox^ filePath;


	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::TextBox^ folderPath;


	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::TextBox^ fileName;

	private: System::Windows::Forms::Button^ addButton;
	private: System::Windows::Forms::Button^ openFolderButton;
	private: System::Windows::Forms::Button^ encryptButton;
	private: System::Windows::Forms::Button^ decryptButton;
	private: System::Windows::Forms::TextBox^ lock;





	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::TextBox^ encryptTime;

	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::TextBox^ decryptTime;

	private: System::Windows::Forms::Label^ label7;


	private: System::ComponentModel::IContainer^ components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->contextMenuStrip1 = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->contextMenuStrip2 = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->filePath = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->folderPath = (gcnew System::Windows::Forms::TextBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->fileName = (gcnew System::Windows::Forms::TextBox());
			this->addButton = (gcnew System::Windows::Forms::Button());
			this->openFolderButton = (gcnew System::Windows::Forms::Button());
			this->encryptButton = (gcnew System::Windows::Forms::Button());
			this->decryptButton = (gcnew System::Windows::Forms::Button());
			this->lock = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->encryptTime = (gcnew System::Windows::Forms::TextBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->decryptTime = (gcnew System::Windows::Forms::TextBox());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// contextMenuStrip1
			// 
			this->contextMenuStrip1->Name = L"contextMenuStrip1";
			this->contextMenuStrip1->Size = System::Drawing::Size(61, 4);
			this->contextMenuStrip1->Opening += gcnew System::ComponentModel::CancelEventHandler(this, &MyForm::contextMenuStrip1_Opening);
			// 
			// contextMenuStrip2
			// 
			this->contextMenuStrip2->Name = L"contextMenuStrip2";
			this->contextMenuStrip2->Size = System::Drawing::Size(61, 4);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::SystemColors::Desktop;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(128)),
				static_cast<System::Int32>(static_cast<System::Byte>(128)));
			this->label1->Location = System::Drawing::Point(21, 83);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(75, 20);
			this->label1->TabIndex = 2;
			this->label1->Text = L"File Path:";
			// 
			// filePath
			// 
			this->filePath->BackColor = System::Drawing::Color::White;
			this->filePath->Cursor = System::Windows::Forms::Cursors::No;
			this->filePath->Enabled = false;
			this->filePath->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->filePath->Location = System::Drawing::Point(232, 79);
			this->filePath->Margin = System::Windows::Forms::Padding(3, 10, 3, 10);
			this->filePath->Multiline = true;
			this->filePath->Name = L"filePath";
			this->filePath->Size = System::Drawing::Size(338, 26);
			this->filePath->TabIndex = 3;
			this->filePath->TextChanged += gcnew System::EventHandler(this, &MyForm::filePath_TextChanged);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(128)),
				static_cast<System::Int32>(static_cast<System::Byte>(128)));
			this->label3->Location = System::Drawing::Point(21, 124);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(128, 20);
			this->label3->TabIndex = 5;
			this->label3->Text = L"Folder saved file:";
			this->label3->Click += gcnew System::EventHandler(this, &MyForm::label3_Click);
			// 
			// folderPath
			// 
			this->folderPath->BackColor = System::Drawing::Color::White;
			this->folderPath->Cursor = System::Windows::Forms::Cursors::No;
			this->folderPath->Enabled = false;
			this->folderPath->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->folderPath->Location = System::Drawing::Point(232, 118);
			this->folderPath->Margin = System::Windows::Forms::Padding(3, 10, 3, 10);
			this->folderPath->Multiline = true;
			this->folderPath->Name = L"folderPath";
			this->folderPath->Size = System::Drawing::Size(338, 26);
			this->folderPath->TabIndex = 6;
			this->folderPath->TextChanged += gcnew System::EventHandler(this, &MyForm::folderPath_TextChanged);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label5->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(128)),
				static_cast<System::Int32>(static_cast<System::Byte>(128)));
			this->label5->Location = System::Drawing::Point(21, 164);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(199, 20);
			this->label5->TabIndex = 8;
			this->label5->Text = L"File\'s name after executed:";
			this->label5->Click += gcnew System::EventHandler(this, &MyForm::label5_Click);
			// 
			// fileName
			// 
			this->fileName->BackColor = System::Drawing::Color::White;
			this->fileName->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->fileName->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->fileName->Location = System::Drawing::Point(232, 157);
			this->fileName->Margin = System::Windows::Forms::Padding(3, 10, 10, 0);
			this->fileName->Multiline = true;
			this->fileName->Name = L"fileName";
			this->fileName->Size = System::Drawing::Size(338, 27);
			this->fileName->TabIndex = 9;
			this->fileName->Text = L"Output";
			this->fileName->TextChanged += gcnew System::EventHandler(this, &MyForm::fileName_TextChanged);
			// 
			// addButton
			// 
			this->addButton->BackColor = System::Drawing::Color::Black;
			this->addButton->Cursor = System::Windows::Forms::Cursors::Hand;
			this->addButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->addButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->addButton->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(128)));
			this->addButton->Location = System::Drawing::Point(585, 79);
			this->addButton->Name = L"addButton";
			this->addButton->Size = System::Drawing::Size(90, 26);
			this->addButton->TabIndex = 10;
			this->addButton->Text = L"Add file";
			this->addButton->UseVisualStyleBackColor = false;
			this->addButton->Click += gcnew System::EventHandler(this, &MyForm::addButton_Click);
			// 
			// openFolderButton
			// 
			this->openFolderButton->BackColor = System::Drawing::Color::Black;
			this->openFolderButton->Cursor = System::Windows::Forms::Cursors::Hand;
			this->openFolderButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->openFolderButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->openFolderButton->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(128)));
			this->openFolderButton->Location = System::Drawing::Point(585, 122);
			this->openFolderButton->Name = L"openFolderButton";
			this->openFolderButton->Size = System::Drawing::Size(90, 26);
			this->openFolderButton->TabIndex = 11;
			this->openFolderButton->Text = L"Open folder";
			this->openFolderButton->UseVisualStyleBackColor = false;
			this->openFolderButton->Click += gcnew System::EventHandler(this, &MyForm::openFolderButton_Click);
			// 
			// encryptButton
			// 
			this->encryptButton->BackColor = System::Drawing::Color::Black;
			this->encryptButton->Cursor = System::Windows::Forms::Cursors::Hand;
			this->encryptButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->encryptButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->encryptButton->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(128)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->encryptButton->Location = System::Drawing::Point(245, 242);
			this->encryptButton->Name = L"encryptButton";
			this->encryptButton->Size = System::Drawing::Size(90, 26);
			this->encryptButton->TabIndex = 12;
			this->encryptButton->Text = L"Encrypt";
			this->encryptButton->UseVisualStyleBackColor = false;
			this->encryptButton->Click += gcnew System::EventHandler(this, &MyForm::encryptButton_Click);
			// 
			// decryptButton
			// 
			this->decryptButton->BackColor = System::Drawing::Color::Black;
			this->decryptButton->Cursor = System::Windows::Forms::Cursors::Hand;
			this->decryptButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->decryptButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->decryptButton->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(128)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->decryptButton->Location = System::Drawing::Point(408, 242);
			this->decryptButton->Name = L"decryptButton";
			this->decryptButton->Size = System::Drawing::Size(90, 26);
			this->decryptButton->TabIndex = 13;
			this->decryptButton->Text = L"Decrypt";
			this->decryptButton->UseVisualStyleBackColor = false;
			this->decryptButton->Click += gcnew System::EventHandler(this, &MyForm::decryptButton_Click);
			// 
			// lock
			// 
			this->lock->BackColor = System::Drawing::Color::White;
			this->lock->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lock->Location = System::Drawing::Point(232, 202);
			this->lock->Margin = System::Windows::Forms::Padding(3, 10, 3, 10);
			this->lock->Multiline = true;
			this->lock->Name = L"lock";
			this->lock->Size = System::Drawing::Size(167, 27);
			this->lock->TabIndex = 14;
			this->lock->TextChanged += gcnew System::EventHandler(this, &MyForm::lock_TextChanged);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(128)),
				static_cast<System::Int32>(static_cast<System::Byte>(128)));
			this->label2->Location = System::Drawing::Point(21, 209);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(47, 20);
			this->label2->TabIndex = 15;
			this->label2->Text = L"Lock:";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label4->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(128)),
				static_cast<System::Int32>(static_cast<System::Byte>(128)));
			this->label4->Location = System::Drawing::Point(68, 299);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(122, 20);
			this->label4->TabIndex = 16;
			this->label4->Text = L"Encrypting time:";
			// 
			// encryptTime
			// 
			this->encryptTime->BackColor = System::Drawing::Color::White;
			this->encryptTime->Cursor = System::Windows::Forms::Cursors::No;
			this->encryptTime->Enabled = false;
			this->encryptTime->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->encryptTime->Location = System::Drawing::Point(192, 292);
			this->encryptTime->Margin = System::Windows::Forms::Padding(3, 10, 3, 10);
			this->encryptTime->Multiline = true;
			this->encryptTime->Name = L"encryptTime";
			this->encryptTime->Size = System::Drawing::Size(96, 27);
			this->encryptTime->TabIndex = 17;
			this->encryptTime->TextChanged += gcnew System::EventHandler(this, &MyForm::encryptTime_TextChanged);
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label6->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(128)),
				static_cast<System::Int32>(static_cast<System::Byte>(128)));
			this->label6->Location = System::Drawing::Point(461, 299);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(123, 20);
			this->label6->TabIndex = 18;
			this->label6->Text = L"Decrypting time:";
			// 
			// decryptTime
			// 
			this->decryptTime->BackColor = System::Drawing::Color::White;
			this->decryptTime->Cursor = System::Windows::Forms::Cursors::No;
			this->decryptTime->Enabled = false;
			this->decryptTime->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->decryptTime->Location = System::Drawing::Point(586, 292);
			this->decryptTime->Margin = System::Windows::Forms::Padding(3, 10, 3, 10);
			this->decryptTime->Multiline = true;
			this->decryptTime->Name = L"decryptTime";
			this->decryptTime->Size = System::Drawing::Size(96, 27);
			this->decryptTime->TabIndex = 19;
			this->decryptTime->TextChanged += gcnew System::EventHandler(this, &MyForm::decryptTime_TextChanged);
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->BackColor = System::Drawing::SystemColors::Desktop;
			this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 21.75F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->label7->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(128)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->label7->Location = System::Drawing::Point(114, 19);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(522, 33);
			this->label7->TabIndex = 20;
			this->label7->Text = L"Simple Cryptography app using DES";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->ClientSize = System::Drawing::Size(763, 338);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->decryptTime);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->encryptTime);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->lock);
			this->Controls->Add(this->decryptButton);
			this->Controls->Add(this->encryptButton);
			this->Controls->Add(this->openFolderButton);
			this->Controls->Add(this->addButton);
			this->Controls->Add(this->fileName);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->folderPath);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->filePath);
			this->Controls->Add(this->label1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"MyForm";
			this->Text = L"Cryptography 101";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void contextMenuStrip1_Opening(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e) {

	}
	private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void textBox1_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		// Do nothing to prevent text selection
	}
	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
		// Disable tab stop for all controls on the form
		for each (Control ^ control in this->Controls)
		{
			control->TabStop = false;
		}

		// Set ActiveControl to nullptr to prevent any control from receiving focus
		this->ActiveControl = nullptr;
	}
	private: System::Void label2_Click(System::Object^ sender, System::EventArgs^ e) {
	}
private: System::Void label3_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void label5_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void folderPath_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void filePath_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void addButton_Click(System::Object^ sender, System::EventArgs^ e) {
	// Open file
	OpenFileDialog^ openFileDialog = gcnew OpenFileDialog();
	if (openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		String^ selectedFilePath = openFileDialog->FileName;
		// Get file Path
		this->filePath->Text = selectedFilePath;
		try
		{
			// Create a StreamReader to read the file
			StreamReader^ reader = gcnew StreamReader(selectedFilePath);

			//Store file data into variable
			fileData = reader->ReadToEnd();

			// Close the StreamReader
			reader->Close();
		}
		catch (Exception^ e)
		{
			// Handle any exceptions that occur during file reading
			Console::WriteLine("Error: {0}", e->Message);
		}
	}
}
private: System::Void encryptButton_Click(System::Object^ sender, System::EventArgs^ e) {
	System::DateTime startTime = System::DateTime::Now;
	if (this->lock->Text->Length != 8) {
		MessageBox::Show("Please fill in a lock with 8 characters long","Alert",MessageBoxButtons::RetryCancel,MessageBoxIcon::Warning);
	}
	else if (this->filePath->Text == "") {
		MessageBox::Show("File path required", "Alert", MessageBoxButtons::RetryCancel, MessageBoxIcon::Warning);
	}else {


		//saved data to block
		int lengthOfFile = fileData->Length;
		String^ lock = this->lock->Text;
		array<String^>^ lockBinaryArray = gcnew array<String^>(65);
		int myDataLength = 0;
		if (lengthOfFile % 8 == 0) {
			myDataLength = lengthOfFile / 8;
		}
		else {
			myDataLength = (lengthOfFile / 8) + 1;
		}
		array<String^>^ dataBlock = gcnew array<String^>(myDataLength);
		for (int index = 0; index < dataBlock->Length; index++) {
			int step = index + 7 * index;
			for (int dataIndex = step; dataIndex < step + 8; dataIndex++) {
				if (dataIndex >= lengthOfFile) {
					dataBlock[index] += "";
				}
				else {
					dataBlock[index] += fileData[dataIndex];
				}
			}
		}


		//handle encrypt
		  //Lock to binary
		AsciiToBinary(lock, lockBinaryArray);
		//hexToBin(lock, lockBinaryArray);
	      //Block 
			String^ myEncryptedString; 
		for (int index = 0; index < dataBlock->Length; index++) {
			array<String^>^ binaryBlock = gcnew array<String^>(65);
			AsciiToBinary(dataBlock[index], binaryBlock);
			//hexToBin(dataBlock[index], binaryBlock);
			array<String^>^ permuteArrayIP= permuteIP(binaryBlock);
			myEncryptedString += handleEncrypting(permuteArrayIP, lockBinaryArray);

		}
		// Create the file path and name
		String^ myPath = this->folderPath->Text + "\\" + this->fileName->Text;

		// Create the StreamWriter object
		StreamWriter^ writer = gcnew StreamWriter(myPath);
		writer->Write(myEncryptedString);
		// Close the StreamWriter
		writer->Close();
		System::TimeSpan elapsedTime = System::DateTime::Now - startTime;
		// Print the elapsed time
		this->encryptTime->Text = elapsedTime.TotalMilliseconds.ToString()+"ms";
	}
	

}
private: System::Void decryptButton_Click(System::Object^ sender, System::EventArgs^ e) {
	System::DateTime startTime = System::DateTime::Now;
	if (this->lock->Text->Length != 8) {
		MessageBox::Show("Please fill in a lock with 8 characters long", "Alert", MessageBoxButtons::RetryCancel, MessageBoxIcon::Warning);
	}
	else if (this->filePath->Text == "") {
		MessageBox::Show("File path required", "Alert", MessageBoxButtons::RetryCancel, MessageBoxIcon::Warning);
	}
	else {
		//Save lock and convert binary
		String^ lock = this->lock->Text;
		array<String^>^ lockBinaryArray = gcnew array<String^>(65);
		//hexToBin(lock, lockBinaryArray);
		AsciiToBinary(lock, lockBinaryArray);
		//saved data to block
		int lengthOfFile = fileData->Length;
		int myDataLength = 0;
		if (lengthOfFile % 64 == 0) {
			myDataLength = lengthOfFile / 64;
		}
		else {
			myDataLength = (lengthOfFile / 64) + 1;
		}
		array<String^>^ dataBlock = gcnew array<String^>(myDataLength);
		for (int index = 0; index < dataBlock->Length; index++) {
			int step = index + 63 * index;
			for (int dataIndex = step; dataIndex < step + 64; dataIndex++) {
				if (dataIndex >= lengthOfFile) {
					dataBlock[index] += "";
				}
				else {
					dataBlock[index] += fileData[dataIndex];
				}
			}
		}
		String^ myDecryptingString;
		for (int i = 0; i < dataBlock->Length; i++) {
			myDecryptingString += handleDecrypting(dataBlock[i],lockBinaryArray);
		}

		Console::WriteLine(myDecryptingString);
		// Create the file path and name
		String^ myPath = this->folderPath->Text + "\\" + this->fileName->Text;

		// Create the StreamWriter object
		StreamWriter^ writer = gcnew StreamWriter(myPath);
		writer->Write(myDecryptingString);
		// Close the StreamWriter
		writer->Close();
		System::TimeSpan elapsedTime = System::DateTime::Now - startTime;
		// Print the elapsed time
		this->decryptTime->Text = elapsedTime.TotalMilliseconds.ToString() + "ms";
	}
}
private: System::Void encryptTime_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void decryptTime_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void fileName_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void openFolderButton_Click(System::Object^ sender, System::EventArgs^ e) {
	FolderBrowserDialog^ folderBrowserDialog = gcnew FolderBrowserDialog();

	// Set the initial directory and file filter if needed
	// openFileDialog.InitialDirectory = "C:\\";
	// openFileDialog.Filter = "Text files (*.txt)|*.txt|All files (*.*)|*.*";

	if (folderBrowserDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		String^ selectedFolderPath = folderBrowserDialog->SelectedPath;
		// Do something with the selected file path, such as displaying it in a TextBox or processing the file
		this->folderPath->Text = selectedFolderPath;
	}
}
private: System::Void lock_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
};
}
