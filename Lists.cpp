#include <iostream>
#include <list>
#include <chrono>

int main()
{
	// lambda function to roll a die 1-6
	auto roll = []() { return rand() % 6 + 1;  };

	// Create container
	std::list<int> container;

	// add a single element to the container
	container.push_back(roll());

	// Here, const int* is an int pointer (int being the data type that is being pointed TO not the pointer itself)
	// pointing to &(*container.begin()), which is the memory address of the pointer pointing to the first element of the vector
	// const because we don't want to modify, only read the memory address.
	const int* pAddressOfOriginalItemZero = &(*container.begin());

	// creating a system clock that measures time spans down to microseconds
	std::chrono::duration<double> durInsertTime(0);

	do
	{
		// get memory address of first item
		const int* pAddressOfItemZero = &(*container.begin());

		std::cout << "Contains " << container.size() << " elements, took " <<
			std::chrono::duration_cast<std::chrono::microseconds>(durInsertTime).count() << "us\n";

		// iterate for every element in the container
		for (const auto& i : container)
		{
			// memory address of current element
			const int* pAddressOfItemX = &i;
			// distance in memory from previous element
			int pItemOffset = pAddressOfItemX - pAddressOfItemZero;
			// distance in memory from original memory address
			int pItemOffsetOriginal = pAddressOfItemX - pAddressOfOriginalItemZero;
			std::cout << "Offset From Original: " << pItemOffsetOriginal << "	Offset From Zero: " << pItemOffset << "	:	Content: " << i << "\n";
		}

		// resets clock for next cycle
		auto tp1 = std::chrono::high_resolution_clock::now();
		container.push_back(roll());
		auto tp2 = std::chrono::high_resolution_clock::now();
		durInsertTime = (tp2 - tp1);

		// waits for user to press enter
	} while (getc(stdin));




}
