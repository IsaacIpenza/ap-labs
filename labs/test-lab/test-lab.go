package main

import (
	"fmt"
	"os"
)

func main() {
	
	if len(os.Args) == 2 {
		name := os.Args[1]
		fmt.Printf("Welcome %v to the jungle \n", name)
	} else if len(os.Args) > 2{
		allArgs := os.Args[1:]
		
		fmt.Printf("Welcome ")
		
		for _,str := range allArgs{
			fmt.Printf("%s ", str)
		}

		fmt.Printf("to the jungle \n")

	} else{
		fmt.Println("No argument !!!")
	}
	
}
