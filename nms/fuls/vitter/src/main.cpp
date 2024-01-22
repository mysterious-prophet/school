#include "../headers/Stat/StatArchiver.h"
#include "../headers/Dyn/DynArchiver.h"
#include <algorithm>
#include <chrono>
#include <limits>



#ifndef IOSTREAM
#define IOSTREAM
    #include <iostream>
#endif

int IntConsoleInput(const std::string& message) {
    
    int c = 0;
    std::cout << message;

    std::cin >> c;

    while (std::cin.fail()) {
        
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "Incorrect input! Repeat" << std::endl;
        std::cout << message;
        std::cin >> c;
    }

    return c;
}

bool ChoiceConsoleInput(const std::string& message, const std::string incorrect) {

    int c = IntConsoleInput(message);

    while((c != 1) && (c != 0)){

        std::cout << std::endl << incorrect << std::endl;
        c = IntConsoleInput(message);
    }

    return static_cast<bool>(c);
}

void ChoiceArchUnarch(Archiver& archiver) {

    std::string nof = "";
    std::string message_c = "If you want to archive - enter 1, unarchive - 0 : ";

    std::string incorrect = "Choose 0 or 1!";

    bool c = ChoiceConsoleInput(message_c, incorrect);

    bool success = false;
    bool exit = false;
    bool no_except = true;

    if (c) {

        while (!success && !exit) {

            no_except = true;

            std::cout << "Enter name of file which you want to archive : ";
            std::cin >> nof;

            try {

                archiver.arch(nof);

            } catch (Archiver::cant_open_file_error& cant_open) {

                no_except = false;

                std::cout << cant_open.what() << " : " << cant_open.get_nof() << std::endl;

                std::string message_e = "Try again - 1, exit - 0\n";
                exit = !ChoiceConsoleInput(message_e, incorrect);
                
            } catch (Archiver::write_in_exist_file_error& arch_file_exist) {
                
                no_except = false;

                std::cout << arch_file_exist.what() << " : " << arch_file_exist.get_nof() << std::endl;
                std::cout << "Delete it or move to another dir before archiving" << std::endl;
            
                exit = true;
            }

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (no_except) {

                success = true;
                std::cout << "<< Archiving done! >>" << std::endl;
            }
        }

    } else {

        std::string un_nof = "";

        while (!success && !exit) {

            no_except = true;

            std::cout << "Enter name of file which you want to unarchive : ";
            std::cin >> nof;

            std::string message_un = "Name of unarchived file 1 - custom, 0 - standart : ";

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (ChoiceConsoleInput(message_un, incorrect)) {

                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                
                std::cin >> un_nof;
            }

            try {

                archiver.unarch(nof, un_nof);

            } catch (Archiver::cant_open_file_error& cant_open) {

                no_except = false;

                std::cout << cant_open.what() << " : " << cant_open.get_nof() << std::endl;

                std::string message_e = "Try again - 1, exit - 0\n";
                exit = !ChoiceConsoleInput(message_e, incorrect);
                
            } catch (Archiver::write_in_exist_file_error& arch_file_exist) {
                
                no_except = false;

                std::cout << arch_file_exist.what() << " : " << arch_file_exist.get_nof() << std::endl;
                std::cout << "Delete it or move to another dir before unarchiving" << std::endl;
            
                exit = true;

            } catch (Archiver::file_is_not_archive& file_not_arch) {

                no_except = false;

                std::cout << file_not_arch.what() << " : " << file_not_arch.get_nof() << std::endl;

                std::string message_e = "Try again - 1, exit - 0\n";
                exit = !ChoiceConsoleInput(message_e, incorrect);
            }

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (no_except) {

                success = true;
                std::cout << "<< Unarchiving done! >>" << std::endl;
            }
        }
    }
}
std::chrono::steady_clock::time_point begin;
std::chrono::steady_clock::time_point end;
void tic()
{
	begin = std::chrono::steady_clock::now();
}

void tac()
{
	end = std::chrono::steady_clock::now();
	std::cout << "Estimated time: " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << std::endl;

}
int main(int argc, char * argv[]) {

    std::cin.sync();

    std::string message = "Choose archiver dyn - 1, stat - 0 : ";
    std::string incorrect = "Choose 0 or 1!";

    bool c = ChoiceConsoleInput(message, incorrect);

    if (c) {
		tic();
        DynArchiver darch;
        ChoiceArchUnarch(darch);
		tac();

    } else {

        StatArchiver sarch;
        ChoiceArchUnarch(sarch);
    }
	system("pause");
    return 0;
}
