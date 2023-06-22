#include <iostream>
#include <vector>
#include <map>
#include <iomanip>

using namespace std;

map<string, map<string, double>> generate_prices() {
    map<string, map<string, double>> store_prices;
    store_prices["BestBuy"]["IPhone14"] = 999.99;
    store_prices["BestBuy"]["IPad Pro"] = 1599.99;
    store_prices["BestBuy"]["Noise Cancelling Headphones"] = 99.99;
    store_prices["BestBuy"]["Black Roller"] = 59.99;
    store_prices["BestBuy"]["Bike"] = 349.99;
    store_prices["Amazon"]["IPhone14"] = 799.99;
    store_prices["Amazon"]["IPad Pro"] = 1799.99;
    store_prices["Amazon"]["Noise Cancelling Headphones"] = 119.99;
    store_prices["Amazon"]["Black Roller"] = 49.99;
    store_prices["Amazon"]["Bike"] = 299.99;
    store_prices["eBay"]["IPhone14"] = 899.99;
    store_prices["eBay"]["IPad Pro"] = 1399.99;
    store_prices["eBay"]["Noise Cancelling Headphones"] = 79.99;
    store_prices["eBay"]["Black Roller"] = 99.99;
    store_prices["eBay"]["Bike"] = 249.99;
    store_prices["Temu"]["IPhone14"] = 1399.99;
    store_prices["Temu"]["IPad Pro"] = 1699.99;
    store_prices["Temu"]["Noise Cancelling Headphones"] = 39.99;
    store_prices["Temu"]["Black Roller"] = 39.99;
    store_prices["Temu"]["Bike"] = 399.99;
    store_prices["Staples"]["IPhone14"] = 999.99;
    store_prices["Staples"]["IPad Pro"] = 1499.99;
    store_prices["Staples"]["Noise Cancelling Headphones"] = 99.99;
    store_prices["Staples"]["Black Roller"] = 119.99;
    store_prices["Staples"]["Bike"] = 199.99;
    return store_prices;
}

map<string, double> get_average_price(vector<string> products, vector<string> stores, map<string, map<string, double>> store_prices) {
    map<string, double> average_price;
    double counter = 0;
    double total = 0;
    for (string s1 : products) {
        for (string s2 : stores) {
            total += store_prices[s2][s1];
            counter += 1;
        }
        average_price[s1] = (total / counter);
        total = 0;
        counter = 0;
    }
    return average_price;
}

map<string, string> get_best_price(vector<string> products, vector<string> stores, map<string, map<string, double>> store_prices) {
    map<string, string> best_prices;
    string store_holder = "";
    string product_holder = "";
    double price_holder = 100000000000000;
    for (string s1 : products) {
        for (string s2 : stores) {
            if (store_prices[s2][s1] < price_holder) {
                price_holder = store_prices[s2][s1];
                product_holder = s1;
                store_holder = s2;
            }
        }
        best_prices[product_holder] = store_holder;
        price_holder = 100000000000000;
        product_holder = "";
        store_holder = "";
    }
    return best_prices;
}

int main() {
    map<string, map<string, double>> store_prices = generate_prices();
    vector<string> stores;
    vector<string> products;
    cout << "Name ";
    cout << setw(25) << " ";
    for (const auto& pair : store_prices) {
        const string& store = pair.first;
        cout << setw(10) << store;
        stores.push_back(store);
    }
    for (const auto& pair : store_prices[stores[0]]) {
        const string& product = pair.first;
        products.push_back(product);
    }
    cout << "\n";
    for (string s1 : products) {
        cout << s1 << setw(34 - s1.length()) << " ";
        for (string s2: stores) {
            cout << setw(10) << store_prices[s2][s1];
        }
        cout << "\n";
    }
    map<string, double> average_prices = get_average_price(products, stores, store_prices);
    for (const auto& pair : average_prices) {
        const string& product = pair.first;
        cout << product << ": " << average_prices[product] << "\n";
    }
    map<string, string> best_prices = get_best_price(products, stores, store_prices);
    for (const auto& pair : best_prices) {
        const string& product = pair.first;
        cout << product << ", Best Price Offered By: " << best_prices[product] << "\n";
    }

    return 0;
}
