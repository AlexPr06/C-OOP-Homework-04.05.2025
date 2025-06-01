#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <condition_variable>
#include <random>

#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"
#define RESET "\033[0m"

using namespace std;

mutex mtx;
condition_variable cv;

const int MAX_NUMBER_FOR_RANDOM_GENERATION = 5;

// Wood
class WoodWeaponCreating {
private:
	bool woodProcessOneDone = false;
	bool woodProcessTwoDone = false;
	bool woodProcessThreeDone = false;
	bool woodWeaponDone = false;
public:
	void processWood()
	{
		thread woodProcessOneThread(&WoodWeaponCreating::woodProcessOne, this);
		thread woodProcessTwoThread(&WoodWeaponCreating::woodProcessTwo, this);
		woodProcessOneThread.join();
		woodProcessTwoThread.join();
	}
	void woodProcessOne()
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dist(0, MAX_NUMBER_FOR_RANDOM_GENERATION);

		unique_lock<mutex> lockForWoodProcessOne(mtx);
		cout << endl << MAGENTA "Wood Process One started." << RESET << endl;
		while (true)
		{
			int r = dist(gen);
			if (r == 0)
			{
				cout << GREEN << "Wood Process One finished." << RESET << endl;
				woodProcessOneDone = true;
				lockForWoodProcessOne.unlock();
				cv.notify_all();
				break;
			}
			cout << "Wood Process One is working..." << endl;
			this_thread::sleep_for(chrono::milliseconds(100));
		}
	}

	void woodProcessTwo ()
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dist(0, MAX_NUMBER_FOR_RANDOM_GENERATION);

		unique_lock<mutex> lockForWoodProcessTwo(mtx);
		cv.wait(lockForWoodProcessTwo, [this] { return woodProcessOneDone; });
		cout << endl << MAGENTA << "Wood Process Two started." << RESET << endl;
		while (true)
		{
			int r = dist(gen);
			/*cout << RED << r << RESET << endl;*/
			if (r == 0)
			{
				cout << GREEN << "Wood Process Two finished." << RESET << endl;
				woodProcessTwoDone = true;
				lockForWoodProcessTwo.unlock();
				cv.notify_all();
				break;
			}
			cout << "Wood Process Two is working..." << endl;
			this_thread::sleep_for(chrono::milliseconds(100));
		}
	}

	void woodProcessThree()
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dist(0, MAX_NUMBER_FOR_RANDOM_GENERATION);

		unique_lock<mutex> lockForWoodProcessThree(mtx);
		cv.wait(lockForWoodProcessThree, [this] { return woodProcessTwoDone; });
		cout << endl << MAGENTA << "Wood Process Three started." << RESET << endl;
		while (true)
		{
			int r = dist(gen);
			/*cout << RED << r << RESET << endl;*/
			if (r == 0)
			{
				cout << GREEN << "Wood Process Three finished." << RESET << endl;
				woodProcessThreeDone = true;
				lockForWoodProcessThree.unlock();
				cv.notify_all();
				break;
			}
			cout << "Wood Process Three is working..." << endl;
			this_thread::sleep_for(chrono::milliseconds(100));
		}
	}

	bool weaponDone() {
		if (!(woodProcessOneDone && woodProcessTwoDone && woodProcessThreeDone))
		{
			cout << RED << "Weapon is not ready!" << RESET << endl;
			return false;
		}
		woodWeaponDone = true;
		cout << BLUE << "Wood Weapon is ready!" << RESET << endl;
		return woodWeaponDone;
	}
};

class SteelWeaponCreating {
private:
	bool steelProcessOneDone = false;
	bool steelProcessTwoDone = false;
	bool steelProcessThreeDone = false;
	bool steelWeaponDone = false;
public:
	void processSteel()
	{
		thread steelProcessOneThread(&SteelWeaponCreating::steelProcessOne, this);
		thread steelProcessTwoThread(&SteelWeaponCreating::steelProcessTwo, this);
		steelProcessOneThread.join();
		steelProcessTwoThread.join();
	}

	void steelProcessOne()
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dist(0, MAX_NUMBER_FOR_RANDOM_GENERATION);
		unique_lock<mutex> lockForSteelProcessOne(mtx);
		cout << endl << MAGENTA "Steel Process One started." << RESET << endl;
		while (true)
		{
			int r = dist(gen);
			if (r == 0)
			{
				cout << GREEN << "Steel Process One finished." << RESET << endl;
				steelProcessOneDone = true;
				lockForSteelProcessOne.unlock();
				cv.notify_all();
				break;
			}
			cout << "Steel Process One is working..." << endl;
			this_thread::sleep_for(chrono::milliseconds(100));
		}
	}
	void steelProcessTwo()
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dist(0, MAX_NUMBER_FOR_RANDOM_GENERATION);
		unique_lock<mutex> lockForSteelProcessTwo(mtx);
		cv.wait(lockForSteelProcessTwo, [this] { return steelProcessOneDone; });
		cout << endl << MAGENTA << "Steel Process Two started." << RESET << endl;
		while (true)
		{
			int r = dist(gen);
			if (r == 0)
			{
				cout << GREEN << "Steel Process Two finished." << RESET << endl;
				steelProcessTwoDone = true;
				lockForSteelProcessTwo.unlock();
				cv.notify_all();
				break;
			}
			cout << "Steel Process Two is working..." << endl;
			this_thread::sleep_for(chrono::milliseconds(100));
		}
	}
	void steelProcessThree()
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dist(0, MAX_NUMBER_FOR_RANDOM_GENERATION);
		unique_lock<mutex> lockForSteelProcessThree(mtx);
		cv.wait(lockForSteelProcessThree, [this] { return steelProcessTwoDone; });
		cout << endl << MAGENTA << "Steel Process Three started." << RESET << endl;
		while (true)
		{
			int r = dist(gen);
			if (r == 0)
			{
				cout << GREEN << "Steel Process Three finished." << RESET << endl;
				steelProcessThreeDone = true;
				lockForSteelProcessThree.unlock();
				cv.notify_all();
				break;
			}
			cout << "Steel Process Three is working..." << endl;
			this_thread::sleep_for(chrono::milliseconds(100));
		}
	}
	bool weaponDone() {
		if (!(steelProcessOneDone && steelProcessTwoDone && steelProcessThreeDone))
		{
			cout << RED << "Weapon is not ready!" << RESET << endl;
			return false;
		}
		steelWeaponDone = true;
		cout << BLUE << "Steel Weapon is ready!" << RESET << endl;
		return steelWeaponDone;
	}
};

class MultiWeaponCreation : public WoodWeaponCreating, public SteelWeaponCreating
{
public:
	void processWeapons()
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dist(0, MAX_NUMBER_FOR_RANDOM_GENERATION);
		unique_lock<mutex> processWeaponsLock(mtx);
		cv.wait(processWeaponsLock, [this]()
			{
				return (WoodWeaponCreating::weaponDone() && SteelWeaponCreating::weaponDone());
			}
		);
		cout << endl << YELLOW << "Weapon creation process started." << RESET << endl;
		while (true)
		{
			int r = dist(gen);
			if (r == 0)
			{
				cout << GREEN << "Weapon creation process finished." << RESET << endl;
				processWeaponsLock.unlock();
				cv.notify_all();
				break;
			}
			cout << "Weapon creation is working..." << endl;
			this_thread::sleep_for(chrono::milliseconds(100));
		}
		cout << endl << CYAN << "Multi weapon is ready!" << RESET << endl;
	}
};



int main()
{
	system("chcp 65001 > nul");
	cout << "Hello, World!" << endl;

	MultiWeaponCreation* multiWeaponCreating = new MultiWeaponCreation();

	thread wood1(&WoodWeaponCreating::woodProcessOne, multiWeaponCreating);
	thread wood2(&WoodWeaponCreating::woodProcessTwo, multiWeaponCreating);
	thread wood3(&WoodWeaponCreating::woodProcessThree, multiWeaponCreating);

	thread steel1(&SteelWeaponCreating::steelProcessOne, multiWeaponCreating);
	thread steel2(&SteelWeaponCreating::steelProcessTwo, multiWeaponCreating);
	thread steel3(&SteelWeaponCreating::steelProcessThree, multiWeaponCreating);

	wood1.join();
	wood2.join();
	wood3.join();

	steel1.join();
	steel2.join();
	steel3.join();

	multiWeaponCreating->processWeapons();

	delete multiWeaponCreating;
	return 0;
}
