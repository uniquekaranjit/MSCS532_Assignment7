class StatisticsCalculator:
    """
    A class to calculate basic statistical measures from a dataset.
    
    Attributes:
        data (list): List of numerical values for statistical calculations
    """
    
    def __init__(self, data):
        """
        Initialize the StatisticsCalculator with input data.
        
        Args:
            data (list): List of numerical values
        """
        if not isinstance(data, list):
            raise TypeError("Input must be a list")
        if not all(isinstance(x, (int, float)) for x in data):
            raise TypeError("All elements must be numbers")
        if not data:
            raise ValueError("Input list cannot be empty")
        self.data = data

    def mean(self):
        """
        Calculate the arithmetic mean of the dataset.
        
        Returns:
            float: The mean value of the dataset
        """
        return sum(self.data) / len(self.data)

    def median(self):
        """
        Calculate the median of the dataset.
        For even number of elements, returns average of two middle values.
        
        Returns:
            float: The median value of the dataset
        """
        sorted_data = sorted(self.data)
        n = len(sorted_data)
        mid = n // 2
        if n % 2 == 0:
            return (sorted_data[mid - 1] + sorted_data[mid]) / 2
        return sorted_data[mid]

    def mode(self):
        """
        Calculate the mode(s) of the dataset.
        Returns all values that appear most frequently.
        
        Returns:
            list: List of mode(s) in the dataset
        """
        freq = {}
        for num in self.data:
            freq[num] = freq.get(num, 0) + 1
        max_freq = max(freq.values())
        return [k for k, v in freq.items() if v == max_freq]


def main():
    """
    Example usage of the StatisticsCalculator class.
    """
    try:
        # Sample dataset
        data = [1, 2, 2, 3, 4]
        calc = StatisticsCalculator(data)
        
        # Calculate and display statistics
        print(f"Dataset: {data}")
        print(f"Mean: {calc.mean():.2f}")
        print(f"Median: {calc.median():.2f}")
        print(f"Mode: {calc.mode()}")
        
    except Exception as e:
        print(f"Error: {str(e)}")


if __name__ == "__main__":
    main()
