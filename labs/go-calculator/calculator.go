package main

import (
	"fmt"
	"os"
	"strings"
	"strconv"
)

// adds/subtracts/multiplies all values that are in the *values array.
// nValues is the number of values you're reading from the array
// operator will indicate if it's an addition (1), subtraction (2) or
// multiplication (3)
func calc(operator int, values []int) int {
	result := values[0]
	fmt.Printf("%v + ", values[0])

	for i := 1; i < len(values); i++ {
		if operator == 1 {
			result += values[i]
			if i < len(values) - 1 {
				fmt.Printf("%d + ", values[i])
			} else {
				fmt.Printf("%d ", values[i])
			}
		} else if operator == 2 {
			result -= values[i]
			if i < len(values) - 1 {
				fmt.Printf("%d - ", values[i])
			} else {
				fmt.Printf("%d ", values[i])
			}		
		} else {
			result *= values[i]
			if i < len(values) - 1 {
				fmt.Printf("%d * ", values[i])
			} else {
				fmt.Printf("%d ", values[i])
			}		}
	}

	return result
}

func numberOfOperator(operation string) int{
	if(strings.Compare(operation, "add") == 0){
		return 1;
	} else if(strings.Compare(operation, "sub") == 0){
		return 2;
	} else if(strings.Compare(operation, "mult") == 0){
		return 3;
	} else{
		return -1;
	}
}

func main() {

	if len(os.Args) < 4{
		fmt.Printf("Invalid number of arguments\n")
		return;
	} else {
		operator := numberOfOperator(os.Args[1])

		if(operator == -1){
			fmt.Printf("Invalid operator\n")
			return;
		} else {

			var j int = 0;
			numbers := make([]int, len(os.Args[2:]))

			for i:= 2; i < len(numbers) + 2; i++ {
				value, err := strconv.Atoi(os.Args[i])

				if err == nil {
					numbers[j] = value
					j++
				} else{
					fmt.Printf("Invalid argument as number -> %s \n", os.Args[i])
           			return 
				}
			}

			fmt.Printf(" = %v \n", calc(operator, numbers))
		}
	}

}
