#include "Skip_list.h"

int main()
{
    std::cout << "Enter structure layers: ";

    int layers;

    std::cin >> layers;

    Skip_list structure(layers);

    std::cout << "Enter elements (0 to stop): ";

    int elem;

    while (std::cin >> elem && elem != 0)
    {
        structure.insert(elem);
    }

    std::cout << "\nStructure contents:\n";

    structure.display();

    std::cout << "\nEnter element to locate: ";

    std::cin >> elem;

    if (auto node = structure.locate(elem))
    {
        std::cout << "Element " << elem << " found\n";
    }
    else
    {
        std::cout << "Element not found\n";
    }

    std::cout << "Enter element to remove: ";

    std::cin >> elem;

    try
    {
        structure.erase(elem);

        std::cout << "Element removed\n";
    }
    catch (const std::exception& e)
    {
        std::cout << "Error: " << e.what() << "\n";
    }
}