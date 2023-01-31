/**
 * Alberto J. Garcia
 * Last date modifed: 01/30/2023
 *
 * Exercise:
 * This program should begin by reading the cost of a meal ordered
 * at a restaurant from the user. Then it should compute the tax
 * and tip for the meal. The output from your program should
 * include the tax amount, the tip amount, and the grand
 * total for the meal including both the tax and the tip.
 * The output format should be displayed using two decimal places.
 */

#include <iostream>
#include <utility>
#include <tuple>
#include <iomanip>
#include <vector>
#include <algorithm>

float tax = 5.75; // 5.75% Ohio sales tax rate

class GetReceipt
{
public:
    void print_receipt()
    {
        /**
         * This function prints out the relevant information for the receipt.
         */

        unsigned short int max_num = 0;
        std::pair<std::vector<float>, std::vector<float>> total_items{};

        dishes_info = get_order("dish");
        drinks_info = get_order("drink");
        total_prices = compute_total_price(std::get<2>(dishes_info) + std::get<2>(drinks_info));
        max_num = std::max(std::get<0>(dishes_info), std::get<0>(drinks_info));
        total_items = check_item_size(std::get<1>(dishes_info), std::get<1>(drinks_info));

        std::cout << "Receipt:" << std::endl;
        std::cout << "--------" << std::endl;

        std::cout << std::setprecision(2) << std::fixed;
        for (unsigned short int i = 0; i < max_num; i++)
        {
            std::cout << "Meal #" << i + 1 << std::endl;
            std::cout << "Dish price:   $" << std::get<0>(total_items)[i] << std::endl;
            std::cout << "Drink price:  $" << std::get<1>(total_items)[i] << std::endl;
            std::cout << "Total:        $" << std::get<0>(total_items)[i] + std::get<1>(total_items)[i] << std::endl;
            std::cout << std::endl;
        }

        std::cout << "Tax: $" << std::get<1>(total_prices) << std::endl;
        std::cout << "Tip: " << (int)std::get<2>(total_prices) << "%" << std::endl;
        std::cout << "Your total price is: $" << std::get<0>(total_prices) << std::endl;
    }

private:
    std::tuple<int, std::vector<float>, float> dishes_info{};
    std::tuple<int, std::vector<float>, float> drinks_info{};
    std::tuple<float, float, float> total_prices{};

    std::tuple<int, std::vector<float>, float> get_order(std::string obj)
    {
        /**
         * This function prompts the user to input whether
         * they got a ''obs'' (either ''dish'' or ''drink'').
         */

        std::string input{};

        std::cout << "Did you get a " << obj << "? (Y/N): ";
        std::cin >> input;
        input = check_input(input);

        return order_info(input, obj);
    }

    std::tuple<int, std::vector<float>, float> order_info(std::string ans, std::string obj)
    {
        /**
         * This function prompts the user to input the itemized price.
         * Also asks the user if there are more items in the order.
         */

        unsigned short int num_order = 0;
        float price = 0.0;
        float total_price = 0.0;
        std::vector<float> indiv_price{};

        if (ans == "Y")
        {
            while (ans == "Y")
            {
                num_order += 1;
                indiv_price.push_back(1);
                std::cout << "How much was your " << obj << "? $";
                std::cin >> price;

                indiv_price[num_order - 1] = price;
                total_price += price;
                std::cout << "Did anyone else get a " << obj << "? (Y/N): ";
                std::cin >> ans;
                ans = check_input(ans);
            }
        }
        std::cout << std::endl;
        return std::tuple<int, std::vector<float>, float>(num_order, indiv_price, total_price);
    }

    std::string make_uppercase(std::string input)
    {
        /**
         * This function turns the user input into uppercase.
         */

        std::transform(input.begin(), input.end(), input.begin(), std::ptr_fun<int, int>(std::toupper));
        return input;
    }

    std::string check_input(std::string ans)
    {
        /**
         * This function checks the user input.
         * A while loop is used for when the input is incorrect.
         */

        ans = make_uppercase(ans);
        while ((ans != "Y") && (ans != "N"))
        {
            std::cout << "Please enter an appropriate response! (Y/N)" << std::endl;
            std::cin >> ans;
            ans = make_uppercase(ans);
        }

        return ans;
    }

    std::tuple<float, float, float> compute_total_price(float cost)
    {
        /**
         * This function computes the total price of the order, including tax and tip.
         */

        float total_tax = 0.0;
        std::pair<float, float> total_tip{};

        total_tax = compute_tax(cost);
        total_tip = compute_tip(cost);

        return std::tuple<float, float, float>(cost + total_tax + std::get<1>(total_tip), total_tax, std::get<0>(total_tip));
    }

    float compute_tax(float cost)
    {
        /**
         * This function computes the tax.
         */

        return cost * tax / 100.0;
    }

    std::pair<float, float> compute_tip(float cost)
    {
        /**
         * This function computes the tip.
         */

        float tip_percent = 0.0;

        std::cout << "How much would you like to tip? (in %) ";
        std::cin >> tip_percent;
        std::cout << std::endl;
        return std::pair<float, float>(tip_percent, cost * tip_percent / 100.0);
    }

    std::pair<std::vector<float>, std::vector<float>> check_item_size(std::vector<float> item1, std::vector<float> item2)
    {
        /**
         * This function checks the drinks and dishes order sizes.
         * Resizes the shorter one (if there is one) to match the bigger one.
         * Used for proper printing of receipt. Will print $0 for portion resized.
         */

        unsigned short int max_idx = 0;

        if (item1.size() != item2.size())
        {
            max_idx = std::max(item1.size(), item2.size());

            if (max_idx != item1.size())
            {
                item1.resize(max_idx);
            }
            else
            {
                item2.resize(max_idx);
            }
        }

        return std::pair<std::vector<float>, std::vector<float>>(item1, item2);
    }
};

int main()
{
    GetReceipt receipt;

    receipt.print_receipt();
    return 0;
}