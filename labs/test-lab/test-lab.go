package main

import (
	"fmt"
	"os"
)

func main() {
	
	if  len(os.Args) > 1{
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
