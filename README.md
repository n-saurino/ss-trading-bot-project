# ss-trading-bot-project
First project of self-study: Implementing a SMA trading bot

# Objectives:

- Develop a trading bot that can place buy/sell orders based on simple moving average (SMA) and exponential moving average (EMA) strategies.
- Gain hands-on experience in financial algorithms and trading strategies.
- Integrate knowledge of C++ programming, the Standard Library (STL), and design patterns.

# Project Requirements:

## Trading Strategies:

- **Simple Moving Average (SMA)**: Calculate the average price of a security over a specified number of time periods.
- **Exponential Moving Average (EMA)**: Calculate the weighted average price of a security, giving more weight to recent prices.

## Order Placement:

- Implement functions to place buy and sell orders based on the SMA and EMA indicators.
- The trading bot should place a buy order when the SMA or EMA indicates an upward trend and a sell order when it indicates a downward trend.

## Data Handling:

- Use historical price data to simulate the trading environment.
- Ensure that the bot processes and analyzes the data efficiently.

## Design Patterns:

- Use appropriate design patterns (e.g., Strategy, Observer) to structure the trading bot’s components.

## Code Quality:

- Write clean, maintainable, and well-documented code.
- Follow best practices in C++ programming and design.

# Steps and Guidelines:

## Setup:

- Create a new GitHub repository for your project.
- Set up a basic C++ project structure with appropriate directories for source files, headers, and data.

## Data Preparation:

- Obtain historical price data for a security (e.g., a stock) in CSV format.
- Write a function to read and parse the CSV file into a data structure (e.g., std::vector).

```cpp
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

struct PriceData {
    std::string date;
    double price;
};

std::vector<PriceData> readPriceData(const std::string& filename) {
    std::vector<PriceData> data;
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string date;
        double price;
        if (iss >> date >> price) {
            data.push_back({date, price});
        }
    }
    return data;
}
```

### SMA and EMA Calculation:

- Implement functions to calculate the Simple Moving Average (SMA).
- Implement functions to calculate the Exponential Moving Average (EMA).

```cpp
double calculateSMA(const std::vector<PriceData>& data, int period, int index) {
    if (index < period - 1) return 0.0; // Not enough data
    double sum = 0.0;
    for (int i = 0; i < period; ++i) {
        sum += data[index - i].price;
    }
    return sum / period;
}

double calculateEMA(const std::vector<PriceData>& data, int period, int index, double previousEMA) {
    double alpha = 2.0 / (period + 1);
    return alpha * data[index].price + (1 - alpha) * previousEMA;
}
```

## Trading Logic

- Implement the trading logic to place buy/sell orders based on SMA and EMA indicators.

```cpp
enum class OrderType { BUY, SELL, HOLD };

OrderType determineOrder(const std::vector<PriceData>& data, int index, int smaPeriod, int emaPeriod, double& previousEMA) {
    double sma = calculateSMA(data, smaPeriod, index);
    double ema = calculateEMA(data, emaPeriod, index, previousEMA);
    previousEMA = ema;

    if (sma > ema) {
        return OrderType::BUY;
    } else if (sma < ema) {
        return OrderType::SELL;
    } else {
        return OrderType::HOLD;
    }
}
```

## Order Execution

- Implement functions to simulate the execution of buy/sell orders.

```cpp
void executeOrder(OrderType order, double& balance, double& holdings, double price) {
    switch (order) {
        case OrderType::BUY:
            if (balance >= price) {
                holdings += 1;
                balance -= price;
                std::cout << "Bought at " << price << std::endl;
            }
            break;
        case OrderType::SELL:
            if (holdings > 0) {
                holdings -= 1;
                balance += price;
                std::cout << "Sold at " << price << std::endl;
            }
            break;
        case OrderType::HOLD:
            // Do nothing
            break;
    }
}
```

## Simulation

- Combine the components to simulate trading over the historical data.

```cpp
int main() {
    std::vector<PriceData> data = readPriceData("historical_data.csv");
    double balance = 10000.0; // Starting balance
    double holdings = 0.0; // No initial holdings
    double previousEMA = 0.0; // Initialize previous EMA

    int smaPeriod = 10;
    int emaPeriod = 10;

    for (size_t i = 0; i < data.size(); ++i) {
        OrderType order = determineOrder(data, i, smaPeriod, emaPeriod, previousEMA);
        executeOrder(order, balance, holdings, data[i].price);
    }

    std::cout << "Final balance: " << balance << std::endl;
    std::cout << "Final holdings: " << holdings << std::endl;

    return 0;
}
```

## Submission

- Commit all your code, including the README file, to your GitHub repository.
- Ensure your repository is private and share access with your instructor.

## Evaluation Criteria

- **Correctness**: The trading bot should compile and run correctly, performing the specified tasks.
- **Strategy Implementation**: Accurate calculation of SMA and EMA, and correct trading logic based on these indicators.
- **Code Quality**: Clean, readable, and well-documented code following best practices.
- **README File**: Clear and comprehensive explanation of the trading bot’s logic, setup instructions, and results interpretation.

## Example README Structure

```markdown
# Trading Bot Project

## Overview
This project implements a trading bot that uses Simple Moving Average (SMA) and Exponential Moving Average (EMA) strategies to place buy and sell orders.

## Trading Strategies
### Simple Moving Average (SMA)
The SMA is calculated by taking the average price of a security over a specified number of time periods.

### Exponential Moving Average (EMA)
The EMA gives more weight to recent prices and is calculated using the formula:
\[ \text{EMA} = \alpha \times \text{Price} + (1 - \alpha) \times \text{Previous EMA} \]
where \(\alpha\) is the smoothing factor.

## Order Placement Logic
- **Buy Order**: Placed when the SMA indicates an upward trend.
- **Sell Order**: Placed when the SMA indicates a downward trend.

## How to Run
1. Clone the repository.
2. Ensure you have a C++ compiler installed.
3. Compile the program using the provided `Makefile`.
4. Run the program and observe the output.

## Example Output
Bought at: 100.5
Sold at: 105.2
Final balance: 10105.2
Final holdings: 0
```