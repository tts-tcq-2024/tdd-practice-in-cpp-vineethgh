#include "StringCalculator.h"
 
bool hasCustomDelimiter(const std::string& numbers) {
    return numbers.substr(0, 2) == "//";
}
 
std::string extractDelimiter(const std::string& numbers) {
    size_t delimiterEnd = numbers.find("\n");
    return numbers.substr(2, delimiterEnd - 2);
}
 
// Extract the numbers part of the string after the custom delimiter
std::string extractNumbers(const std::string& numbers) {
	size_t delimiterEnd = numbers.find("\n");
	return numbers.substr(delimiterEnd + 1);
}
 
// Normalize the numbers string by replacing new lines with the delimiter
std::string normalizeNumbers(const std::string& numbers, const std::string& delimiter) {
	return std::regex_replace(numbers, std::regex("\n"), delimiter);
}
void handleNumberWithinRange(int& num, std::string& item, std::string& negativeNumber, std::vector<int>& result) {
	if (num < 0) {
		negativeNumber = negativeNumber + item;
  	}
  	if (num <= 1000) {
	  	result.push_back(num); // Ignore numbers greater than 1000
  	}
}
void handleParsedNumbers(std::string& item, std::string& negativeNumber, std::vector<int>& result) {
	if (!item.empty()) {
		int num = std::stoi(item);
		handleNumberWithinRange(num, item, negativeNumber, result);
	}
	else {
		throw std::invalid_argument("Invalid Arguments");
	}  
}
 
std::vector<int> parseNumbers(const std::string& numbers, const std::string& delimiter) {
	std::vector<int> result;
	std::stringstream ss(numbers);
	std::string item;
	std::string negativeNumber;
 
	while (std::getline(ss, item, delimiter[0])) {
		handleParsedNumbers(item, negativeNumber, result);
	}
	if (!negativeNumber.empty()) {
		throw std::runtime_error("negatives not allowed: " + negativeNumber);
	}
	return result;
}
 
int calculateSum(const std::vector<int>& nums) {
	int sum = 0;
	for (int num : nums) {
		sum += num;
	}
	return sum;
}
 
int StringCalculator::add(const std::string& numbers) {
	if (numbers.empty()) {
	    return 0;
	}
  	std::string delimiter = ",";
	std::string numbersWithoutDelimiter = numbers;
  	if (hasCustomDelimiter(numbers)) {
      	delimiter = extractDelimiter(numbers); // Extract custom delimiter
      	numbersWithoutDelimiter = extractNumbers(numbers);
  	}
	  // Normalize the numbers string by replacing new lines with the delimiter
	  std::string normalizedNumbers = normalizeNumbers(numbersWithoutDelimiter, delimiter);
	  std::vector<int> nums = parseNumbers(normalizedNumbers, delimiter);
	  return calculateSum(nums);
}
