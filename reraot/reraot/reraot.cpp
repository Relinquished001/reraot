// Auth: Relinquished
// Desc: Finds Optimized Armor Combinations for Elden Ring.

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

// ------------------------------------------------- Protector

class Protector {
public:
	string protectorName;
	float weight;
	float absPhysical;
	float absStrike;
	float absSlash;
	float absPierce;
	float absMagic;
	float absFire;
	float absLightning;
	float absHoly;

	int resImmunity;
	int resRobustness;
	int resFocus;
	int resVitality;

	float poise;

	// Member function declarations
	void initializeProtector(string n, float w, float a0, float a1, float a2, float a3, float a4, float a5, float a6, float a7, int r0, int r1, int r2, int r3, float p);
};

// Member function definitions
void Protector::initializeProtector(string n, float w, float a0, float a1, float a2, float a3, float a4, float a5, float a6, float a7, int r0, int r1, int r2, int r3, float p) {
	protectorName = n;
	weight = w;
	absPhysical = a0;
	absStrike = a1;
	absSlash = a2;
	absPierce = a3;
	absMagic = a4;
	absFire = a5;
	absLightning = a6;
	absHoly = a7;

	resImmunity = r0;
	resRobustness = r1;
	resFocus = r2;
	resVitality = r3;

	poise = p;
}

// ------------------------------------------------- Config

struct Config {
	float maxWeight = 0;
	float currentWeight = 0;
	float rollType = 0;
	float minPoise = 0;

	float minAbsPhysical = 0;
	float minAbsStrike = 0;
	float minAbsSlash = 0;
	float minAbsPierce = 0;
	float minAbsMagic = 0;
	float minAbsFire = 0;
	float minAbsLightning = 0;
	float minAbsHoly = 0;

	int minResImmunity = 0;
	int minResRobustness = 0;
	int minResFocus = 0;
	int minResVitality = 0;

	string forceHead = "";
	string forceBody = "";
	string forceArms = "";
	string forceLegs = "";

	int maxOutput = 8000;
};

// ------------------------------------------------- Declaration of Global Variables

Protector head[168] = {};
Protector body[204] = {};
Protector arms[92] = {};
Protector legs[106] = {};

Config config;

// ------------------------------------------------- File Reading / Writing

void loadProtectors() {
	ifstream infile("data\\protectors.txt");
	if (infile.is_open()) {
		string temp, str1;
		float arr1[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		int arr2[4] = { 0, 0, 0, 0 };
		int count = 0;
		while (!infile.eof()) {
			getline(infile, str1, ',');
			for (int i = 0; i <= 8; i++) {

				getline(infile, temp, ',');
				arr1[i] = stof(temp);
			}
			for (int i = 0; i <= 3; i++) {

				getline(infile, temp, ',');
				arr2[i] = stoi(temp);
			}
			getline(infile, temp, '\n');
			arr1[9] = stof(temp);

			if (count < 168) {
				head[count].initializeProtector(str1, arr1[0], arr1[1], arr1[2], arr1[3], arr1[4], arr1[5], arr1[6], arr1[7], arr1[8], arr2[0], arr2[1], arr2[2], arr2[3], arr1[9]);
			}
			else if (count < 372) {
				body[count - 168].initializeProtector(str1, arr1[0], arr1[1], arr1[2], arr1[3], arr1[4], arr1[5], arr1[6], arr1[7], arr1[8], arr2[0], arr2[1], arr2[2], arr2[3], arr1[9]);
			}
			else if (count < 464) {
				arms[count - 372].initializeProtector(str1, arr1[0], arr1[1], arr1[2], arr1[3], arr1[4], arr1[5], arr1[6], arr1[7], arr1[8], arr2[0], arr2[1], arr2[2], arr2[3], arr1[9]);
			}
			else {
				legs[count - 464].initializeProtector(str1, arr1[0], arr1[1], arr1[2], arr1[3], arr1[4], arr1[5], arr1[6], arr1[7], arr1[8], arr2[0], arr2[1], arr2[2], arr2[3], arr1[9]);
			}

			count++;
		}
	}
	else { cout << "Error opening file"; }
	infile.close();
}

void loadSettings(Config& cfg) {
	ifstream infile("data\\settings.txt");
	if (infile.is_open()) {
		string temp;
		while (getline(infile, temp)) {
			istringstream sin(temp.substr(temp.find("=") + 1));
			if (temp.find("maxWeight") != -1)
				sin >> cfg.maxWeight;
			else if (temp.find("currentWeight") != -1)
				sin >> cfg.currentWeight;
			else if (temp.find("rollType") != -1)
				sin >> cfg.rollType;
			else if (temp.find("minPoise") != -1)
				sin >> cfg.minPoise;
			else if (temp.find("minAbsPhysical") != -1)
				sin >> cfg.minAbsPhysical;
			else if (temp.find("minAbsStrike") != -1)
				sin >> cfg.minAbsStrike;
			else if (temp.find("minAbsSlash") != -1)
				sin >> cfg.minAbsSlash;
			else if (temp.find("minAbsPierce") != -1)
				sin >> cfg.minAbsPierce;
			else if (temp.find("minAbsMagic") != -1)
				sin >> cfg.minAbsMagic;
			else if (temp.find("minAbsFire") != -1)
				sin >> cfg.minAbsFire;
			else if (temp.find("minAbsLightning") != -1)
				sin >> cfg.minAbsLightning;
			else if (temp.find("minAbsHoly") != -1)
				sin >> cfg.minAbsHoly;
			else if (temp.find("minResImmunity") != -1)
				sin >> cfg.minResImmunity;
			else if (temp.find("minResRobustness") != -1)
				sin >> cfg.minResRobustness;
			else if (temp.find("minResFocus") != -1)
				sin >> cfg.minResFocus;
			else if (temp.find("minResVitality") != -1)
				sin >> cfg.minResVitality;
			else if (temp.find("forceHead") != -1)
				getline(sin >> ws, cfg.forceHead);
			else if (temp.find("forceBody") != -1)
				getline(sin >> ws, cfg.forceBody);
			else if (temp.find("forceArms") != -1)
				getline(sin >> ws, cfg.forceArms);
			else if (temp.find("forceLegs") != -1)
				getline(sin >> ws, cfg.forceLegs);
			else
				sin >> cfg.maxOutput;
		}
	}
	else { cout << "Error opening file"; }
	infile.close();
}

void saveSettings() {
	ofstream outfile("data\\settings.txt");
	if (outfile.is_open()) {
		outfile << "maxWeight = " << config.maxWeight
			<< "\ncurrentWeight = " << config.currentWeight
			<< "\nrollType = " << config.rollType
			<< "\nminPoise = " << config.minPoise
			<< "\nminAbsPhysical = " << config.minAbsPhysical
			<< "\nminAbsStrike = " << config.minAbsStrike
			<< "\nminAbsSlash = " << config.minAbsSlash
			<< "\nminAbsPierce = " << config.minAbsPierce
			<< "\nminAbsMagic = " << config.minAbsMagic
			<< "\nminAbsFire = " << config.minAbsFire
			<< "\nminAbsLightning = " << config.minAbsLightning
			<< "\nminAbsHoly = " << config.minAbsHoly
			<< "\nminResImmunity = " << config.minResImmunity
			<< "\nminResRobustness = " << config.minResRobustness
			<< "\nminResFocus = " << config.minResFocus
			<< "\nminResVitality = " << config.minResVitality
			<< "\nforceHead = " << config.forceHead
			<< "\nforceBody = " << config.forceBody
			<< "\nforceArms = " << config.forceArms
			<< "\nforceLegs = " << config.forceLegs
			<< "\nmaxOutput = " << config.maxOutput;
	}
	else { cout << "Error opening file"; }
	outfile.close();
}

// ------------------------------------------------- Calculation

void OptimizeArmor() {

	int count = 0;

	for (int i = 0; i < sizeof(head) / sizeof(head[0]); i++) {
		if (config.forceHead != "")
			if (config.forceHead != head[i].protectorName)
				continue;
		for (int j = 0; j < sizeof(body) / sizeof(body[0]); j++) {
			if (config.forceBody != "")
				if (config.forceBody != body[j].protectorName)
					continue;
			for (int k = 0; k < sizeof(arms) / sizeof(arms[0]); k++) {
				if (config.forceArms != "")
					if (config.forceArms != arms[k].protectorName)
						continue;
				for (int l = 0; l < sizeof(legs) / sizeof(legs[0]); l++) {
					if (config.forceLegs != "")
						if (config.forceLegs != legs[l].protectorName)
							continue;

					float totalWeight = head[i].weight + body[j].weight + arms[k].weight + legs[l].weight;
					float totalPoise = (head[i].poise + body[j].poise + arms[k].poise + legs[l].poise) * 1000;

					float totalAbsPhysical = (1 - (head[i].absPhysical*body[j].absPhysical*arms[k].absPhysical*legs[l].absPhysical)) * 100;
					float totalAbsStrike = (1 - (head[i].absStrike*body[j].absStrike*arms[k].absStrike*legs[l].absStrike)) * 100;
					float totalAbsSlash = (1 - (head[i].absSlash*body[j].absSlash*arms[k].absSlash*legs[l].absSlash)) * 100;
					float totalAbsPierce = (1 - (head[i].absPierce*body[j].absPierce*arms[k].absPierce*legs[l].absPierce)) * 100;
					float totalAbsMagic = (1 - (head[i].absMagic*body[j].absMagic*arms[k].absMagic*legs[l].absMagic)) * 100;
					float totalAbsFire = (1 - (head[i].absFire*body[j].absFire*arms[k].absFire*legs[l].absFire)) * 100;
					float totalAbsLightning = (1 - (head[i].absLightning*body[j].absLightning*arms[k].absLightning*legs[l].absLightning)) * 100;
					float totalAbsHoly = (1 - (head[i].absHoly*body[j].absHoly*arms[k].absHoly*legs[l].absHoly)) * 100;

					int totalResImmunity = head[i].resImmunity + body[j].resImmunity + arms[k].resImmunity + legs[l].resImmunity;
					int totalResRobustness = head[i].resRobustness + body[j].resRobustness + arms[k].resRobustness + legs[l].resRobustness;
					int totalResFocus = head[i].resFocus + body[j].resFocus + arms[k].resFocus + legs[l].resFocus;
					int totalResVitality = head[i].resVitality + body[j].resVitality + arms[k].resVitality + legs[l].resVitality;

					if ((totalWeight <= ((config.maxWeight * config.rollType) - config.currentWeight)) && (totalPoise >= config.minPoise)
						&& (totalAbsPhysical >= config.minAbsPhysical) && (totalAbsStrike >= config.minAbsStrike) && (totalAbsSlash >= config.minAbsSlash) && (totalAbsPierce >= config.minAbsPierce) && (totalAbsMagic >= config.minAbsMagic) && (totalAbsFire >= config.minAbsFire) && (totalAbsLightning >= config.minAbsLightning) && (totalAbsHoly >= config.minAbsHoly)
						&& (totalResImmunity >= config.minResImmunity) && (totalResRobustness >= config.minResRobustness) && (totalResFocus >= config.minResFocus) && (totalResVitality >= config.minResVitality)) {

						string armor = "\t" + head[i].protectorName + ", " + body[j].protectorName + ", " + arms[k].protectorName + ", " + legs[l].protectorName + "\n";
						cout << armor;

						count++;
					}

					if (count == config.maxOutput) {

						cout << "\nMax Output reached\n";

						return;
					}
				}
			}
		}
	}
}

// ------------------------------------------------- User Interface

void SettingsMenu() {

	char condition = ' ';
	int choice;

	while (condition != '#') {

		system("cls");

		cout << "Relinquished's Elden Ring Armor Optimization Tool";

		cout << "\n\n-------------------------------------------------"
			<< "\n\n                  Settings Menu                  "
			<< "\n\n-------------------------------------------------";

		cout << "\n\n[0] - Back"
			<< "\n\n[1] - Max Weight - " << config.maxWeight << "\t\t[2] - Current Weight - " << config.currentWeight
			<< "\n\n[3] - Roll Type - " << config.rollType << "\t\t[4] - Min Poise - " << config.minPoise
			<< "\n\n[5] - Min Physical Absorb - " << config.minAbsPhysical << "\t\t[6] - Min Strike Absorb - " << config.minAbsStrike
			<< "\n\n[7] - Min Slash Absorb - " << config.minAbsSlash << "\t\t[8] - Min Pierce Absorb - " << config.minAbsPierce
			<< "\n\n[9] - Min Magic Absorb - " << config.minAbsMagic << "\t\t[10] - Min Fire Absorb - " << config.minAbsFire
			<< "\n\n[11] - Min Lightning Absorb - " << config.minAbsLightning << "\t\t[12] - Min Holy Absorb - " << config.minAbsHoly
			<< "\n\n[13] - Min Immunity - " << config.minResImmunity << "\t\t[14] - Min Robustness - " << config.minResRobustness
			<< "\n\n[15] - Min Focus - " << config.minResFocus << "\t\t[16] - Min Vitality - " << config.minResVitality
			<< "\n\n[17] - Force Head - " << config.forceHead << "\t\t[18] - Force Body - " << config.forceBody
			<< "\n\n[19] - Force Arms - " << config.forceArms << "\t\t[20] - Force Legs - " << config.forceLegs
			<< "\n\n[21] - Max Output - " << config.maxOutput;

		cout << "\n\nPlease enter your choice: ";
		cin >> choice;
		if (cin.fail()) { while (cin.fail()) { cin.clear(); cin.ignore(INT_MAX, '\n'); } cout << "\nUnrecognized Command\n\n"; system("pause"); continue; }

		switch (choice) {

		case 0:
			system("cls");

			cout << "Relinquished's Elden Ring Armor Optimization Tool";

			cout << "\n\nReturning to Main Menu\n\n";

			system("pause");

			condition = '#';

			break;
		case 1:
			cout << "\nPlease enter new Max Weight: ";
			cin >> config.maxWeight;
			if (cin.fail()) { while (cin.fail()) { cin.clear(); cin.ignore(INT_MAX, '\n'); } cout << "\nYou must enter a float value\n\n"; system("pause"); continue; }
			break;
		case 2:
			cout << "\nPlease enter new Current Weight: ";
			cin >> config.currentWeight;
			if (cin.fail()) { while (cin.fail()) { cin.clear(); cin.ignore(INT_MAX, '\n'); } cout << "\nYou must enter a float value\n\n"; system("pause"); continue; }
			break;
		case 3:
			cout << "\nPlease enter new Roll Type: ";
			cin >> config.rollType;
			if (cin.fail()) { while (cin.fail()) { cin.clear(); cin.ignore(INT_MAX, '\n'); } cout << "\nYou must enter a float value\n\n"; system("pause"); continue; }
			break;
		case 4:
			cout << "\nPlease enter new Min Poise: ";
			cin >> config.minPoise;
			if (cin.fail()) { while (cin.fail()) { cin.clear(); cin.ignore(INT_MAX, '\n'); } cout << "\nYou must enter a float value\n\n"; system("pause"); continue; }
			break;
		case 5:
			cout << "\nPlease enter new Min Physical Absorb: ";
			cin >> config.minAbsPhysical;
			if (cin.fail()) { while (cin.fail()) { cin.clear(); cin.ignore(INT_MAX, '\n'); } cout << "\nYou must enter a float value\n\n"; system("pause"); continue; }
			break;
		case 6:
			cout << "\nPlease enter new Min Strike Absorb: ";
			cin >> config.minAbsStrike;
			if (cin.fail()) { while (cin.fail()) { cin.clear(); cin.ignore(INT_MAX, '\n'); } cout << "\nYou must enter a float value\n\n"; system("pause"); continue; }
			break;
		case 7:
			cout << "\nPlease enter new Min Slash Absorb: ";
			cin >> config.minAbsSlash;
			if (cin.fail()) { while (cin.fail()) { cin.clear(); cin.ignore(INT_MAX, '\n'); } cout << "\nYou must enter a float value\n\n"; system("pause"); continue; }
			break;
		case 8:
			cout << "\nPlease enter new Min Pierce Absorb: ";
			cin >> config.minAbsPierce;
			if (cin.fail()) { while (cin.fail()) { cin.clear(); cin.ignore(INT_MAX, '\n'); } cout << "\nYou must enter a float value\n\n"; system("pause"); continue; }
			break;
		case 9:
			cout << "\nPlease enter new Min Magic Absorb: ";
			cin >> config.minAbsMagic;
			if (cin.fail()) { while (cin.fail()) { cin.clear(); cin.ignore(INT_MAX, '\n'); } cout << "\nYou must enter a float value\n\n"; system("pause"); continue; }
			break;
		case 10:
			cout << "\nPlease enter new Min Fire Absorb: ";
			cin >> config.minAbsFire;
			if (cin.fail()) { while (cin.fail()) { cin.clear(); cin.ignore(INT_MAX, '\n'); } cout << "\nYou must enter a float value\n\n"; system("pause"); continue; }
			break;
		case 11:
			cout << "\nPlease enter new Min Lightning Absorb: ";
			cin >> config.minAbsLightning;
			if (cin.fail()) { while (cin.fail()) { cin.clear(); cin.ignore(INT_MAX, '\n'); } cout << "\nYou must enter a float value\n\n"; system("pause"); continue; }
			break;
		case 12:
			cout << "\nPlease enter new Min Holy Absorb: ";
			cin >> config.minAbsHoly;
			if (cin.fail()) { while (cin.fail()) { cin.clear(); cin.ignore(INT_MAX, '\n'); } cout << "\nYou must enter a float value\n\n"; system("pause"); continue; }
			break;
		case 13:
			cout << "\nPlease enter new Min Immunity: ";
			cin >> config.minResImmunity;
			if (cin.fail()) { while (cin.fail()) { cin.clear(); cin.ignore(INT_MAX, '\n'); } cout << "\nYou must enter an integer value\n\n"; system("pause"); continue; }
			break;
		case 14:
			cout << "\nPlease enter new Min Robustness: ";
			cin >> config.minResRobustness;
			if (cin.fail()) { while (cin.fail()) { cin.clear(); cin.ignore(INT_MAX, '\n'); } cout << "\nYou must enter an integer value\n\n"; system("pause"); continue; }
			break;
		case 15:
			cout << "\nPlease enter new Min Focus: ";
			cin >> config.minResFocus;
			if (cin.fail()) { while (cin.fail()) { cin.clear(); cin.ignore(INT_MAX, '\n'); } cout << "\nYou must enter an integer value\n\n"; system("pause"); continue; }
			break;
		case 16:
			cout << "\nPlease enter new Min Vitality: ";
			cin >> config.minResVitality;
			if (cin.fail()) { while (cin.fail()) { cin.clear(); cin.ignore(INT_MAX, '\n'); } cout << "\nYou must enter an integer value\n\n"; system("pause"); continue; }
			break;
		case 17:
			cout << "\nPlease enter new Force Head (Enter 0 to clear): ";
			getline(cin >> ws, config.forceHead);
			if (config.forceHead == "0")
				config.forceHead = "";
			break;
		case 18:
			cout << "\nPlease enter new Force Body (Enter 0 to clear): ";
			getline(cin >> ws, config.forceBody);
			if (config.forceBody == "0")
				config.forceBody = "";
			break;
		case 19:
			cout << "\nPlease enter new Force Arms (Enter 0 to clear): ";
			getline(cin >> ws, config.forceArms);
			if (config.forceArms == "0")
				config.forceArms = "";
			break;
		case 20:
			cout << "\nPlease enter new Force Legs (Enter 0 to clear): ";
			getline(cin >> ws, config.forceLegs);
			if (config.forceLegs == "0")
				config.forceLegs = "";
			break;
		case 21:
			cout << "\nPlease enter new Max Output: ";
			cin >> config.maxOutput;
			if (cin.fail()) { while (cin.fail()) { cin.clear(); cin.ignore(INT_MAX, '\n'); } cout << "\nYou must enter an integer value\n\n"; system("pause"); continue; }
			break;
		default:
			cout << "\nUnrecognized Command\n\n";
			system("pause");
			break;
		}

		saveSettings();
	}

	return;
}

void MainMenu() {

	char condition = ' ';
	int choice;

	while (condition != '#') {

		system("cls");

		cout << "Relinquished's Elden Ring Armor Optimization Tool";

		cout << "\n\n-------------------------------------------------"
			<< "\n\n                    Main Menu                    "
			<< "\n\n-------------------------------------------------";

		cout << "\n\n[0] - Exit"
			<< "\n\n[1] - Optimize Armor" << "\t\t[2] - Settings";

		cout << "\n\nPlease enter your choice: ";
		cin >> choice;
		if (cin.fail()) { while (cin.fail()) { cin.clear(); cin.ignore(INT_MAX, '\n'); } cout << "\nUnrecognized Command\n\n"; system("pause"); continue; }

		switch (choice) {

		case 0:
			system("cls");

			cout << "Relinquished's Elden Ring Armor Optimization Tool";

			cout << "\n\nAre you sure you want to exit?";

			cout << "\n\n[0] - Yes" << "\t\t[1] - No";

			cout << "\n\nPlease confirm your choice: ";
			cin >> choice;
			if (cin.fail()) { while (cin.fail()) { cin.clear(); cin.ignore(INT_MAX, '\n'); } continue; }

			if (choice == 0)
				cout << "\nDrive safe and don't smoke\n\n";
			system("pause");
			condition = '#';
			break;
		case 1:
			cout << "\nYour armor combinations are:\n";
			OptimizeArmor();
			cout << "\n";
			system("pause");
			break;
		case 2:
			SettingsMenu();
			break;
		default:
			cout << "\nUnrecognized Command\n\n";
			system("pause");
			break;
		}
	}

	exit(1);
}

// ------------------------------------------------- Main

int main() {

	loadProtectors();

	loadSettings(config);

	MainMenu();
}