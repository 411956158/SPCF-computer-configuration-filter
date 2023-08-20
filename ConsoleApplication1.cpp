#include <array>
#include <iostream>
#include <intrin.h>
#include <string>
#include <windows.h>

std::string getCPUName();
double getSystemMemory(int runMode);
std::string getCPUVendor();
std::string getCPUType();
std::string getIntelGeneration();
std::string getAMDGeneration();
int ascii_to_integer(const char* string);
int canInstall(int gen, int mem);

int brandFlag = 0;
int typeFlag = 0;
int genFlag = 0;
std::string IntelGen = "";


int main()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);//设置黄色
	std::cout << "尊敬的用户，您好，欢迎访问人工智能配置自动筛查系统，系统正在加载中……\n";
	std::cout << "尊贵的内测用户，感谢您参与本系统的测试，SPCF大模型载入中……\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);//设置浅黄色
	std::cout << "尊敬的用户，由于SPCF模型仍处于内测阶段，识别结果可能有误，请以人工客服判断为准\n\n";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);//白色
	std::cout << "CPU Brand: " << getCPUVendor() << std::endl;
	std::cout << "CPU Name: " << getCPUName() << std::endl;

	double memorySize = getSystemMemory(0);

	if (brandFlag == 1) {
		//std::cout << "CPU GEN: " << getIntelGeneration() << std::endl;
		std::cout << "CPU TYPE: " << getCPUType() << std::endl;
		IntelGen= getIntelGeneration();
		genFlag = ascii_to_integer(IntelGen.c_str());
		std::cout << "CPU GEN: " << genFlag << std::endl;
	}else if (brandFlag == 2) {
		std::cout << "CPU GEN: " << getAMDGeneration() << std::endl;
	}
	else {
		std::cout << "尊敬的用户，您的CPU目前不在支持列表，请联系人工客服确认\n";
	}
	std::cout << std::endl;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);//亮白色
	canInstall(genFlag, memorySize);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);//设置浅红色
	printf("SPCF系统仅可以作为快速判断配置的参考，请以工作人员的判断为准\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);//设置红色
	printf("SPCF系统仅可以作为快速判断配置的参考，请以工作人员的判断为准\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);//设置浅红色
	printf("SPCF系统仅可以作为快速判断配置的参考，请以工作人员的判断为准\n");

	/*
	std::cout << "原色testCOLOR（没有设置字体颜色）" << std::endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);//设置三色相加
	std::cout << "白色testCOLOR（红色绿色蓝色相加）" << std::endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);//设置红色
	std::cout << "红色testCOLOR（设置的颜色为红色）" << std::endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);//设置绿色
	std::cout << "绿色testCOLOR（设置的颜色为绿色）" << std::endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);//设置蓝色
	std::cout << "蓝色testCOLOR（设置的颜色为蓝色）" << std::endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED |FOREGROUND_GREEN);//设置红色和绿色相加(黄色）
	std::cout << "黄色testCOLOR（红色和绿色相加色）" << std::endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED |FOREGROUND_BLUE);//设置红色和蓝色相加
	std::cout << "粉色testCOLOR（红色和蓝色相加色）" << std::endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN |FOREGROUND_BLUE);//设置绿色和蓝色相加
	std::cout << "青色testCOLOR（绿色和蓝色相加色）" << std::endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
	//设置颜色，没有添加颜色，故为原色
	*/

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY );//设置三色相加
	std::cout << std::endl;
	system("pause");
	return 114;
}

std::string getCPUName() {
	std::array<int, 4> CPUInfo = { -1 };
	std::array<char, 0x40> CPUBrandString = { 0 };
	__cpuid(CPUInfo.data(), 0x80000000);
	unsigned int nExIds = CPUInfo[0];

	for (unsigned int i = 0x80000000; i <= nExIds; ++i) {
		__cpuid(CPUInfo.data(), i);

		if (i == 0x80000002)
			memcpy(CPUBrandString.data(), CPUInfo.data(), sizeof(CPUInfo));
		else if (i == 0x80000003)
			memcpy(CPUBrandString.data() + 16, CPUInfo.data(), sizeof(CPUInfo));
		else if (i == 0x80000004)
			memcpy(CPUBrandString.data() + 32, CPUInfo.data(), sizeof(CPUInfo));
	}

	std::string cpuName(CPUBrandString.data());
	//std::cout << "CPU Name: " << cpuName << std::endl;
	return cpuName;
}

double getSystemMemory(int runMode) {
	MEMORYSTATUSEX statex;
	statex.dwLength = sizeof(statex);
	GlobalMemoryStatusEx(&statex);
	double totalPhysicalMemoryInGB = statex.ullTotalPhys / (1024.0 * 1024 * 1024);
	totalPhysicalMemoryInGB = round(totalPhysicalMemoryInGB * pow(10, runMode)) / pow(10, runMode);  // Keep runMode decimal places
	std::cout << "Total Physical Memory: " << totalPhysicalMemoryInGB << " GB" << std::endl;
	return totalPhysicalMemoryInGB;
}

std::string getCPUVendor() {
	int CPUInfo[4] = { -1 };
	char CPUVendor[0x20];
	__cpuid(CPUInfo, 0);
	std::memcpy(CPUVendor, &CPUInfo[1], sizeof(int)); // ebx
	std::memcpy(CPUVendor + 4, &CPUInfo[3], sizeof(int)); // edx
	std::memcpy(CPUVendor + 8, &CPUInfo[2], sizeof(int)); // ecx
	CPUVendor[12] = '\0'; // null terminate string
	std::string vendor(CPUVendor);
	if (vendor == "GenuineIntel") {
		brandFlag = 1;
		return "Intel";
		//std::cout << "CPU brand:Intel " << std::endl;
	}
	else if (vendor == "AuthenticAMD") {
		brandFlag = 2;
		//std::cout << "CPU brand:AMD " << std::endl;
		return "AMD";
	}
	else {
		brandFlag = 0;
		//std::cout << "CPU brand:UnKnown " << std::endl;
		return "Other";
	}
}

std::string getCPUType() {
	std::string cpuName = getCPUName();
	if (cpuName.find("Core") != std::string::npos) {
		typeFlag = 1;
		return "Core";
	}
	else if (cpuName.find("Pentium") != std::string::npos) {
		typeFlag = 2;
		return "Pentium";
	}
	else if (cpuName.find("Celeron") != std::string::npos) {
		typeFlag = 3;
		return "Celeron";
	}
	else {
		typeFlag = 0;
		return "Unknown";
	}
}

/*std::string getIntelGeneration() {
	std::string cpuName = getCPUName();
	if (cpuName.find("i3") != std::string::npos || cpuName.find("i5") != std::string::npos || cpuName.find("i7") != std::string::npos || cpuName.find("i9") != std::string::npos) {
		size_t pos = cpuName.find("-");
		if (pos != std::string::npos && cpuName.length() > pos + 3) {
			return cpuName.substr(pos + 1, 2); // 返回代数，例如"10"代表第10代
		}
	}
	return "Unknown";
}*/

/*std::string getIntelGeneration() {
	int CPUInfo[4];
	__cpuid(CPUInfo, 1);
	int family = ((CPUInfo[0] >> 8) & 0xf) + ((CPUInfo[0] >> 20) & 0xff);
	int model = ((CPUInfo[0] >> 4) & 0xf) + ((CPUInfo[0] >> 12) & 0xf0);
	if (family == 6) {
		switch (model) {
		case 0x1A: case 0x1E: case 0x1F: case 0x2E:  // Nehalem
		case 0x25: case 0x2C: case 0x2F:  // Westmere
			return "1st";
		case 0x2A: case 0x2D:  // Sandy Bridge
			return "2nd";
		case 0x3A: case 0x3E:  // Ivy Bridge
			return "3rd";
		case 0x3C: case 0x3F: case 0x45: case 0x46:  // Haswell
			return "4th";
		case 0x3D: case 0x47: case 0x4F: case 0x56:  // Broadwell
			return "5th";
		case 0x4E: case 0x5E:  // Skylake
			return "6th";
		case 0x8E: case 0x9E:  // Kaby Lake
			return "7th";
		case 0x7E:  // Coffee Lake
			return "8th";
		case 0xA6:  // Coffee Lake Refresh
			return "9th";
		case 0xA5:   // Comet Lake
			return "10th";
		default:
			return "Unknown";
		}
	}
}*/

std::string getIntelGeneration() {
	std::string cpuName = getCPUName();
	size_t pos = cpuName.find("@");
	if (pos != std::string::npos) {
		cpuName = cpuName.substr(0, pos);
	}
	//std::cout << "NOW CPU Name: " << cpuName << std::endl;
	if (cpuName.find("i3") != std::string::npos || cpuName.find("i5") != std::string::npos || cpuName.find("i7") != std::string::npos || cpuName.find("i9") != std::string::npos) {
		size_t pos = cpuName.find("-");
		if (pos != std::string::npos && cpuName.length() > pos + 3) {
			std::string generationStr = cpuName.substr(pos + 1);
			size_t spacePos = generationStr.find(" ");
			if (spacePos != std::string::npos) {
				generationStr = generationStr.substr(0, spacePos);
			}
			//std::cout << "NOW generationStr: " << generationStr << std::endl;
			for (int i = 0; i < generationStr.length(); ++i) {
				//std::cout << "NOW generationStrAi: " << i << generationStr[i] << std::endl;
				if (!isdigit(generationStr[i])) {
					//std::cout << "NOW generationStrBi: " << i << generationStr[i] << std::endl;
					if (generationStr[i] != 'G'&& generationStr[i] != 'P'&& generationStr[i] != 'U') {
						if (i == 5) {
							//std::cout << "NOW generationStrCi: " << i << generationStr[i] << std::endl;
							return generationStr.substr(0, 2); // 如果型号是5位数，取前两位作为代数
						}
						else {
							//std::cout << "NOW generationStrDi: " << i << generationStr[i] << std::endl;
							return generationStr.substr(0, 1); // 如果型号不是5位数，取第一位作为代数
						}
					}
					else {
						//std::cout << "NOW generationStrEi: " << i << generationStr[i] << std::endl;
						return generationStr.substr(0, 2); // 如果第一个非数字字符是G，取前两位作为代数
					}
				}
				
			}

			for (int i = 0; i < generationStr.length(); ++i) {
				//std::cout << "NOW generationStrAAi: " << i << generationStr[i] << std::endl;
				//if (!isdigit(generationStr[i])) {
					//std::cout << "NOW generationStrBBi: " << i << generationStr[i] << std::endl;
					
						if (i == 4) {
							//std::cout << "NOW generationStrCCi: " << i << generationStr[i] << std::endl;
							return generationStr.substr(0, 2); // 如果型号是5位数，取前两位作为代数
						}
						else {
							//std::cout << "NOW generationStrDDi: " << i << generationStr[i] << std::endl;
							return generationStr.substr(0, 1); // 如果型号不是5位数，取第一位作为代数
						}
					
					
				//}

			}

		}
	}
	return "Unknown";
}

std::string getAMDGeneration() {
	int CPUInfo[4];
	__cpuid(CPUInfo, 1);
	int family = ((CPUInfo[0] >> 8) & 0xf) + ((CPUInfo[0] >> 20) & 0xff);
	int model = ((CPUInfo[0] >> 4) & 0xf) + ((CPUInfo[0] >> 12) & 0xf0);
	if (family == 0x15) {
		genFlag = 0;
		return "Bulldozer/Piledriver/Steamroller/Excavator";
	}
	else if (family == 0x17) {
		if (model <= 0xf) {
			genFlag = 5;
			return "Zen/Zen+";
		}
		else if (model <= 0x1f) {
			genFlag = 7;
			return "Zen 2";
		}
		else {
			genFlag = 10;
			return "Zen 3 or Newer";
		}
	}
	else {
		genFlag = 0;
		return "Unknown";
	}
}

int ascii_to_integer(const char* string) {
	int x = 0;
	if (!string) {
		return 0;
	}
	//printf("string: %s\n", string);
	char ch;
	while (ch = *string++) {
		//printf("ch = %c,(ascii: %d)\n", ch, ch);
		if (ch >= '0' && ch <= '9') {
			ch -= '0';
			x = (x * 10 + ch);
			//printf("x = %d\n", x);
		}
		else {
			return 0;
		}
	}
	return x;
}

int canInstall(int gen, int mem) {
	if (brandFlag == 1 && typeFlag != 1) {
		printf("强烈不建议安装\nCPU过弱\n");
		return -1;
	}
	else {
		switch (gen) {
		case 0:case 1: case 2:case 3:case 4:
			printf("强烈不建议安装\nCPU过弱\n");break;
		case 5:case 6: case 7:
			printf("不建议安装\nCPU性能不佳\n");break;
		case 8:case 9:
			if (mem >= 8) {
				printf("可能可以安装,但会存在卡顿\n建议升级配置，请以工作人员的判断为准\n");
			}
			else {
				printf("内存可能不足，不建议安装\n");
			}break;
		default:
			if (mem >= 8 && mem < 16) {
				printf("可以安装\n可能存在卡顿，请以工作人员的判断为准\n");
			}
			else if (mem >= 16) {
				printf("可以安装\nSPCF认为您的配置合理，但请以工作人员的判断为准\n");
			}
		}
	}
	std::cout << std::endl;
	//printf("SPCF系统仅可以作为快速判断配置的参考，请以工作人员的判断为准\n");
	return 0;
}